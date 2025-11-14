"""Security packet handler implementation."""

from __future__ import annotations

from typing import Any, Dict, Mapping

from .common import (
    PacketValidationError,
    coerce_string,
    get_ipc_logger,
    normalize_blob,
    normalize_packet,
    pop_any,
)


LOGGER = get_ipc_logger()


def _normalize_challenge(value: object) -> Any:
    if isinstance(value, Mapping):
        return dict(value)
    return normalize_blob(value, "challenge")


def _normalize_key_material(value: object) -> Dict[str, Any] | str:
    if value is None:
        raise PacketValidationError("key_material is required")

    if isinstance(value, Mapping):
        return dict(value)

    normalized = normalize_blob(value, "key_material")
    if isinstance(normalized, str):
        return normalized

    raise PacketValidationError("key_material must be mapping or string-like")


def _normalize_signature(value: object) -> Any:
    if isinstance(value, Mapping):
        return dict(value)
    return normalize_blob(value, "signature")


def handle_security_packet(raw_packet):
    """Parse security packets and extract authentication materials."""

    header, payload = normalize_packet(raw_packet)
    working_payload = dict(payload)

    raw_auth_type = pop_any(working_payload, ["auth_type", "type", "mode"], required=True)
    raw_challenge = pop_any(working_payload, ["challenge", "nonce"], required=True)
    raw_signature = pop_any(working_payload, ["signature", "sig"], required=True)
    raw_key_material = pop_any(working_payload, ["key_material", "keys", "material"], required=True)

    auth_type = coerce_string(raw_auth_type, "auth_type", to_upper=True)
    challenge = _normalize_challenge(raw_challenge)
    signature = _normalize_signature(raw_signature)
    key_material = _normalize_key_material(raw_key_material)

    normalized_payload = {
        "auth_type": auth_type,
        "challenge": challenge,
        "signature": signature,
        "key_material": key_material,
    }

    extras = dict(working_payload)

    LOGGER.info(
        "Security packet processed: id=%s auth=%s", header["message_id"], auth_type
    )
    LOGGER.debug("Security payload normalized: %s extras=%s", normalized_payload, extras)

    return {"header": header, "payload": normalized_payload, "extras": extras}


__all__ = ["handle_security_packet", "PacketValidationError"]
