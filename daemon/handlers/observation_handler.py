"""Observation packet handler implementation."""

from __future__ import annotations

from typing import List

from .common import (
    PacketValidationError,
    coerce_float,
    coerce_mapping,
    coerce_optional_int,
    normalize_packet,
    pop_any,
    coerce_sequence,
    get_ipc_logger,
)


LOGGER = get_ipc_logger()


def _normalize_flags(value: object) -> List[str]:
    if value is None:
        return []

    if isinstance(value, str):
        return [flag.strip() for flag in value.replace("|", ",").split(",") if flag.strip()]

    flags = coerce_sequence(value, "anomaly_flags", item_converter=str, allow_scalar=True)
    return [flag.strip() for flag in flags if flag.strip()]


def handle_observation_packet(raw_packet):
    """Parse observation packets and return telemetry metrics."""

    header, payload = normalize_packet(raw_packet)
    working_payload = dict(payload)

    raw_telemetry = pop_any(working_payload, ["telemetry", "metrics", "data"], required=True)
    raw_trust = pop_any(working_payload, ["trust_score", "trust"], required=True)
    raw_flags = pop_any(working_payload, ["anomaly_flags", "flags", "anomalies"], required=False)
    raw_timestamp = pop_any(working_payload, ["timestamp", "ts", "observed_at"], required=False)

    telemetry = coerce_mapping(raw_telemetry, "telemetry")
    trust_score = coerce_float(raw_trust, "trust_score", minimum=0.0, maximum=100.0)
    anomaly_flags = _normalize_flags(raw_flags)
    timestamp = coerce_optional_int(raw_timestamp, "timestamp", minimum=0)

    normalized_payload = {
        "telemetry": telemetry,
        "trust_score": trust_score,
        "anomaly_flags": anomaly_flags,
        "timestamp": timestamp,
    }

    extras = dict(working_payload)

    LOGGER.info(
        "Observation packet processed: id=%s trust=%.2f flags=%d",
        header["message_id"],
        trust_score,
        len(anomaly_flags),
    )
    LOGGER.debug("Observation payload normalized: %s extras=%s", normalized_payload, extras)

    return {"header": header, "payload": normalized_payload, "extras": extras}


__all__ = ["handle_observation_packet", "PacketValidationError"]
