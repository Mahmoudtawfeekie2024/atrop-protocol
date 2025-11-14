# daemon/ipc/exit_handler.py

"""Exit packet handler implementation."""

from __future__ import annotations

from .common import (
    coerce_int,
    coerce_mapping,
    coerce_string,
    get_ipc_logger,
    normalize_packet,
    pop_any,
)


LOGGER = get_ipc_logger()


def handle_exit_packet(raw_packet):
    """Parse exit packets describing shutdown events."""

    header, payload = normalize_packet(raw_packet)
    working_payload = dict(payload)

    raw_reason = pop_any(working_payload, ["reason", "exit_reason", "status"], required=True)
    raw_snapshot = pop_any(working_payload, ["state_snapshot", "state", "snapshot"], required=False)
    raw_timestamp = pop_any(working_payload, ["timestamp", "ts"], required=True)

    reason = coerce_string(raw_reason, "reason")
    state_snapshot = coerce_mapping(raw_snapshot, "state_snapshot", allow_none=True)
    timestamp = coerce_int(raw_timestamp, "timestamp", minimum=0)

    normalized_payload = {
        "reason": reason,
        "state_snapshot": state_snapshot,
        "timestamp": timestamp,
    }

    extras = dict(working_payload)

    LOGGER.info("Exit packet processed: id=%s reason=%s", header["message_id"], reason)
    LOGGER.debug("Exit payload normalized: %s extras=%s", normalized_payload, extras)

    return {"header": header, "payload": normalized_payload, "extras": extras}


__all__ = ["handle_exit_packet"]
