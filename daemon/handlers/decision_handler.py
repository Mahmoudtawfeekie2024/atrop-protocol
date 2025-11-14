"""Decision packet handler implementation."""

from __future__ import annotations

from typing import List

from .common import (
    PacketValidationError,
    coerce_float,
    coerce_int,
    coerce_sequence,
    coerce_string,
    get_ipc_logger,
    normalize_packet,
    pop_any,
)


LOGGER = get_ipc_logger()


def _normalize_route_vector(value: object) -> List[str]:
    if isinstance(value, str):
        segments = [segment.strip() for segment in value.replace("->", ",").split(",") if segment.strip()]
        if not segments:
            raise PacketValidationError("route_vector must contain at least one hop")
        return segments

    hops = coerce_sequence(value, "route_vector", item_converter=str, allow_scalar=False)
    hops = [hop.strip() for hop in hops if hop.strip()]
    if not hops:
        raise PacketValidationError("route_vector must contain at least one hop")
    return hops


def handle_decision_packet(raw_packet):
    """Parse decision packets and normalize route metadata."""

    header, payload = normalize_packet(raw_packet)
    working_payload = dict(payload)

    raw_route_vector = pop_any(working_payload, ["route_vector", "path", "route"], required=True)
    raw_policy_token = pop_any(working_payload, ["policy_token", "policy", "token"], required=True)
    raw_confidence = pop_any(working_payload, ["confidence", "confidence_score"], required=True)
    raw_ttl = pop_any(working_payload, ["validity_ttl", "ttl"], required=True)

    route_vector = _normalize_route_vector(raw_route_vector)
    policy_token = coerce_string(raw_policy_token, "policy_token")
    confidence = coerce_float(raw_confidence, "confidence", minimum=0.0, maximum=10_000.0)
    validity_ttl = coerce_int(raw_ttl, "validity_ttl", minimum=0)

    normalized_payload = {
        "route_vector": route_vector,
        "policy_token": policy_token,
        "confidence": confidence,
        "validity_ttl": validity_ttl,
    }

    extras = dict(working_payload)

    LOGGER.info(
        "Decision packet processed: id=%s policy=%s ttl=%s",
        header["message_id"],
        policy_token,
        validity_ttl,
    )
    LOGGER.debug("Decision payload normalized: %s extras=%s", normalized_payload, extras)

    return {"header": header, "payload": normalized_payload, "extras": extras}


__all__ = ["handle_decision_packet", "PacketValidationError"]
