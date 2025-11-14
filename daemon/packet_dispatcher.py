"""Central ATROP packet dispatcher used by the control daemon."""

from __future__ import annotations

from typing import Any, Callable, Dict, Optional

from .logger import setup_logger
from .handlers.discovery_handler import handle_discovery_packet as _handle_discovery_packet
from .handlers.decision_handler import handle_decision_packet as _handle_decision_packet
from .handlers.correction_handler import handle_correction_packet as _handle_correction_packet
from .handlers.observation_handler import handle_observation_packet as _handle_observation_packet

# Re-export handler callables so tests can monkeypatch them easily.
handle_discovery_packet = _handle_discovery_packet
handle_decision_packet = _handle_decision_packet
handle_correction_packet = _handle_correction_packet
handle_observation_packet = _handle_observation_packet


class PacketDispatcher:
    """Parse packets and route them to the appropriate handler."""

    def __init__(self, logger_name: str = "ATROP.Dispatcher", log_config: Optional[Dict[str, Any]] = None):
        self.log = setup_logger(logger_name, log_config or {})

    def parse_header(self, raw_packet: Any) -> Optional[Dict[str, Any]]:
        """Validate the basic header information from the raw packet."""
        if not isinstance(raw_packet, dict):
            self.log.error("Raw packet must be a dictionary")
            return None

        try:
            header = {
                "message_id": raw_packet["message_id"],
                "type": raw_packet["type"],
                "source": raw_packet.get("source", ""),
                "destination": raw_packet.get("destination", ""),
                "sequence": raw_packet.get("sequence", 0),
            }
        except KeyError as exc:  # pragma: no cover - defensive branch
            self.log.error(f"Header parsing error: {exc}")
            return None

        return header

    def _resolve_handler(self, message_type: str) -> Optional[Callable[[Dict[str, Any]], None]]:
        mapping = {
            "discovery": handle_discovery_packet,
            "decision": handle_decision_packet,
            "correction": handle_correction_packet,
            "observation": handle_observation_packet,
            "telemetry": handle_observation_packet,
        }
        return mapping.get(message_type.lower())

    def dispatch(self, raw_packet: Any) -> bool:
        header = self.parse_header(raw_packet)
        if not header:
            self.log.error("Invalid or corrupt packet; dispatch aborted.")
            return False

        handler = self._resolve_handler(header["type"])
        if handler is None:
            self.log.warning(f"Unknown message type '{header['type']}'")
            return False

        self.log.info(
            "Dispatching packet type: %s (id=%s)",
            header["type"].lower(),
            header["message_id"],
        )

        try:
            handler(raw_packet)
        except Exception as exc:  # pragma: no cover - defensive branch
            self.log.error(f"Dispatch error for type '{header['type']}': {exc}")
            return False

        return True


__all__ = [
    "PacketDispatcher",
    "handle_discovery_packet",
    "handle_decision_packet",
    "handle_correction_packet",
    "handle_observation_packet",
]
