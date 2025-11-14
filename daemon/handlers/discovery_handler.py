"""Discovery packet handler implementation."""

from __future__ import annotations

from typing import Dict, List, Mapping, Tuple

from .common import (
    PacketValidationError,
    coerce_int,
    coerce_optional_int,
    coerce_sequence,
    normalize_packet,
    pop_any,
    get_ipc_logger,
)


LOGGER = get_ipc_logger()


def _normalize_capabilities(value: object) -> Tuple[List[str], Dict[str, bool]]:
    """Return a normalized capability list and map."""

    if isinstance(value, Mapping):
        capability_map = {str(key): bool(enabled) for key, enabled in value.items()}
        capability_list = [name for name, enabled in capability_map.items() if enabled]
        return capability_list, capability_map

    if isinstance(value, str):
        raw_items = [item.strip() for item in value.replace("->", ",").split(",")]
        capability_list = [item for item in raw_items if item]
    else:
        capability_list = [item.strip() for item in coerce_sequence(value, "capabilities", item_converter=str, allow_scalar=True) if item]

    capability_map = {name: True for name in capability_list}
    return capability_list, capability_map


def handle_discovery_packet(raw_packet):
    """Parse discovery packets into a normalized structure."""

    header, payload = normalize_packet(raw_packet)
    working_payload = dict(payload)

    raw_capabilities = pop_any(working_payload, ["capabilities", "features", "capability_list"], required=True)
    raw_zone_request = pop_any(working_payload, ["zone_request", "requested_zone", "zone"], required=False)
    raw_timestamp = pop_any(working_payload, ["timestamp", "ts", "observed_at"], required=True)

    capabilities, capability_map = _normalize_capabilities(raw_capabilities)
    zone_request = coerce_optional_int(raw_zone_request, "zone_request", minimum=0)
    timestamp = coerce_int(raw_timestamp, "timestamp", minimum=0)

    normalized_payload = {
        "capabilities": capabilities,
        "capability_map": capability_map,
        "zone_request": zone_request,
        "timestamp": timestamp,
    }

    extras = dict(working_payload)

    LOGGER.info(
        "Discovery packet processed: id=%s src=%s zone=%s",
        header["message_id"],
        header["source"],
        zone_request,
    )
    LOGGER.debug("Discovery payload normalized: %s extras=%s", normalized_payload, extras)

    return {"header": header, "payload": normalized_payload, "extras": extras}


__all__ = ["handle_discovery_packet", "PacketValidationError"]
