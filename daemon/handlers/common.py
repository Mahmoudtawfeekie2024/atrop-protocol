"""Shared utilities for Python daemon packet handlers."""

from __future__ import annotations

import json
from dataclasses import asdict, is_dataclass
from functools import lru_cache
from typing import Any, Callable, Dict, Iterable, Mapping, MutableMapping, Sequence, Tuple

from ..logger import setup_logger

HEADER_KEYS = {"message_id", "type", "source", "destination", "sequence", "payload"}


class PacketValidationError(ValueError):
    """Raised when a packet has an invalid structure or payload."""


@lru_cache(maxsize=1)
def get_ipc_logger():
    """Return a cached IPC logger instance."""

    return setup_logger("ATROP.IPC", {})


def coerce_packet(raw_packet: Any) -> Dict[str, Any]:
    """Ensure the incoming packet can be treated as a dictionary."""

    if isinstance(raw_packet, (bytes, bytearray)):
        try:
            raw_packet = raw_packet.decode("utf-8")
        except UnicodeDecodeError as exc:  # pragma: no cover - defensive guard
            raise PacketValidationError("Packet bytes must be UTF-8 encoded") from exc

    if isinstance(raw_packet, str):
        try:
            raw_packet = json.loads(raw_packet)
        except json.JSONDecodeError as exc:
            raise PacketValidationError("Packet string is not valid JSON") from exc
    elif is_dataclass(raw_packet):
        raw_packet = asdict(raw_packet)
    elif hasattr(raw_packet, "model_dump"):
        raw_packet = raw_packet.model_dump()
    elif hasattr(raw_packet, "dict"):
        raw_packet = raw_packet.dict()
    elif hasattr(raw_packet, "_asdict"):
        raw_packet = raw_packet._asdict()

    if isinstance(raw_packet, Mapping):
        return dict(raw_packet)

    raise PacketValidationError("Packet must be provided as a mapping or JSON object")


def extract_header(packet: Mapping[str, Any]) -> Dict[str, Any]:
    """Normalize and validate the common packet header fields."""

    for field in ("message_id", "type"):
        if field not in packet:
            raise PacketValidationError(f"Missing required header field '{field}'")

    sequence = packet.get("sequence", 0)
    try:
        sequence = int(sequence)
    except (TypeError, ValueError):
        raise PacketValidationError("Header field 'sequence' must be an integer")

    return {
        "message_id": packet["message_id"],
        "type": str(packet["type"]),
        "source": str(packet.get("source", "")),
        "destination": str(packet.get("destination", "")),
        "sequence": sequence,
    }


def extract_payload(packet: Mapping[str, Any]) -> Dict[str, Any]:
    """Return the payload mapping and merge any loose fields."""

    payload = packet.get("payload", {})
    if payload is None:
        payload = {}
    elif not isinstance(payload, Mapping):
        raise PacketValidationError("Packet payload must be a mapping")
    else:
        payload = dict(payload)

    for key, value in packet.items():
        if key not in HEADER_KEYS:
            payload.setdefault(key, value)

    return payload


def normalize_packet(raw_packet: Any) -> Tuple[Dict[str, Any], Dict[str, Any]]:
    """Return the normalized header/payload tuple for the handler routines."""

    packet = coerce_packet(raw_packet)
    header = extract_header(packet)
    payload = extract_payload(packet)
    return header, payload


def pop_any(payload: MutableMapping[str, Any], names: Sequence[str], *, required: bool) -> Any:
    """Pop the first present key from ``names`` and optionally enforce presence."""

    for name in names:
        if name in payload:
            return payload.pop(name)

    if required:
        raise PacketValidationError(f"Missing required payload field '{names[0]}'")

    return None


def coerce_int(value: Any, field: str, *, minimum: int | None = None, maximum: int | None = None) -> int:
    """Coerce a value into an integer with optional bounds."""

    if isinstance(value, bool) or value is None:
        raise PacketValidationError(f"{field} must be an integer")

    try:
        result = int(value)
    except (TypeError, ValueError) as exc:
        raise PacketValidationError(f"{field} must be an integer") from exc

    if minimum is not None and result < minimum:
        raise PacketValidationError(f"{field} must be >= {minimum}")

    if maximum is not None and result > maximum:
        raise PacketValidationError(f"{field} must be <= {maximum}")

    return result


def coerce_optional_int(
    value: Any,
    field: str,
    *,
    default: int | None = None,
    minimum: int | None = None,
    maximum: int | None = None,
) -> int | None:
    """Coerce an optional integer value with bounds and default support."""

    if value is None:
        return default

    return coerce_int(value, field, minimum=minimum, maximum=maximum)


def coerce_float(
    value: Any,
    field: str,
    *,
    minimum: float | None = None,
    maximum: float | None = None,
) -> float:
    """Coerce a value into a floating point number with optional bounds."""

    if isinstance(value, bool) or value is None:
        raise PacketValidationError(f"{field} must be a number")

    try:
        result = float(value)
    except (TypeError, ValueError) as exc:
        raise PacketValidationError(f"{field} must be a number") from exc

    if minimum is not None and result < minimum:
        raise PacketValidationError(f"{field} must be >= {minimum}")

    if maximum is not None and result > maximum:
        raise PacketValidationError(f"{field} must be <= {maximum}")

    return result


def coerce_optional_float(
    value: Any,
    field: str,
    *,
    default: float | None = None,
    minimum: float | None = None,
    maximum: float | None = None,
) -> float | None:
    """Coerce an optional float with default support."""

    if value is None:
        return default

    return coerce_float(value, field, minimum=minimum, maximum=maximum)


def coerce_sequence(
    value: Any,
    field: str,
    *,
    item_converter: Callable[[Any], Any] | None = None,
    allow_scalar: bool = False,
) -> list[Any]:
    """Coerce a value into a list and optionally convert each element."""

    if value is None:
        if allow_scalar:
            return []
        raise PacketValidationError(f"{field} must be a sequence")

    if isinstance(value, str):
        if allow_scalar:
            items: Iterable[Any] = [value]
        else:
            raise PacketValidationError(f"{field} must be a sequence")
    elif isinstance(value, Iterable):
        items = list(value)
    else:
        if allow_scalar:
            items = [value]
        else:
            raise PacketValidationError(f"{field} must be a sequence")

    result = []
    for item in items:
        if item_converter is not None:
            try:
                result.append(item_converter(item))
            except Exception as exc:
                raise PacketValidationError(f"{field} contains invalid items") from exc
        else:
            result.append(item)

    return result


def coerce_mapping(value: Any, field: str, *, allow_none: bool = False) -> Dict[str, Any]:
    """Coerce a value into a mapping (dictionary)."""

    if value is None:
        if allow_none:
            return {}
        raise PacketValidationError(f"{field} must be a mapping")

    if not isinstance(value, Mapping):
        raise PacketValidationError(f"{field} must be a mapping")

    return dict(value)


def coerce_string(value: Any, field: str, *, allow_empty: bool = False, to_upper: bool = False) -> str:
    """Coerce a value into a trimmed string."""

    if value is None:
        raise PacketValidationError(f"{field} must be a string")

    if isinstance(value, (bytes, bytearray)):
        try:
            value = value.decode("utf-8")
        except UnicodeDecodeError as exc:
            raise PacketValidationError(f"{field} bytes must be UTF-8") from exc

    result = str(value)
    if not allow_empty:
        result = result.strip()
        if not result:
            raise PacketValidationError(f"{field} must be a non-empty string")

    if to_upper:
        result = result.upper()

    return result


def normalize_blob(value: Any, field: str) -> Any:
    """Normalize binary-like blobs to a JSON-friendly form."""

    if value is None:
        raise PacketValidationError(f"{field} is required")

    if isinstance(value, (bytes, bytearray)):
        return value.hex()

    return value


__all__ = [
    "PacketValidationError",
    "get_ipc_logger",
    "normalize_packet",
    "pop_any",
    "coerce_int",
    "coerce_optional_int",
    "coerce_float",
    "coerce_optional_float",
    "coerce_sequence",
    "coerce_mapping",
    "coerce_string",
    "normalize_blob",
]

