"""Correction packet handler implementation."""

from __future__ import annotations

from typing import List

from .common import (
    PacketValidationError,
    coerce_int,
    coerce_optional_int,
    coerce_sequence,
    coerce_string,
    get_ipc_logger,
    normalize_packet,
    pop_any,
)


LOGGER = get_ipc_logger()


def _normalize_affected_nodes(value: object) -> List[str]:
    if isinstance(value, str):
        entries = [item.strip() for item in value.replace("->", ",").split(",") if item.strip()]
        if not entries:
            raise PacketValidationError("affected_nodes must contain at least one entry")
        return entries

    nodes = coerce_sequence(value, "affected_nodes", item_converter=str, allow_scalar=False)
    nodes = [node.strip() for node in nodes if node.strip()]
    if not nodes:
        raise PacketValidationError("affected_nodes must contain at least one entry")
    return nodes


def handle_correction_packet(raw_packet):
    """Parse correction packets and expose normalized anomaly directives."""

    header, payload = normalize_packet(raw_packet)
    working_payload = dict(payload)

    raw_error_code = pop_any(working_payload, ["error_code", "code"], required=True)
    raw_nodes = pop_any(working_payload, ["affected_nodes", "affected", "nodes"], required=True)
    raw_action = pop_any(working_payload, ["suggested_action", "action"], required=True)
    raw_origin_zone = pop_any(working_payload, ["origin_zone", "origin_zone_id", "zone_id"], required=True)
    raw_sequence = pop_any(working_payload, ["sequence", "step"], required=False)

    error_code = coerce_int(raw_error_code, "error_code", minimum=0)
    affected_nodes = _normalize_affected_nodes(raw_nodes)
    suggested_action = coerce_string(raw_action, "suggested_action", to_upper=True)
    origin_zone = coerce_string(raw_origin_zone, "origin_zone")
    remediation_step = coerce_optional_int(raw_sequence, "sequence", minimum=0)

    normalized_payload = {
        "error_code": error_code,
        "affected_nodes": affected_nodes,
        "suggested_action": suggested_action,
        "origin_zone": origin_zone,
        "remediation_step": remediation_step,
    }

    extras = dict(working_payload)

    LOGGER.info(
        "Correction packet processed: id=%s action=%s nodes=%d",
        header["message_id"],
        suggested_action,
        len(affected_nodes),
    )
    LOGGER.debug("Correction payload normalized: %s extras=%s", normalized_payload, extras)

    return {"header": header, "payload": normalized_payload, "extras": extras}


__all__ = ["handle_correction_packet", "PacketValidationError"]
