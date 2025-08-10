"""
ATROP Protocol Packet Dispatcher

Routes packets to appropriate handler based on message type.
Handles:
 - Discovery
 - Decision
 - Correction
 - Observation/Telemetry

Parses and validates basic ATROP headers:
 - message_id, type, source, destination, sequence
Logs errors and supports both simulated/test source (raw dict/bytes) and real inputs.

Usage:
    dispatcher = PacketDispatcher()
    dispatcher.dispatch(raw_packet)
"""

from logger import setup_logger
from handlers.discovery_handler import handle_discovery_packet
from handlers.decision_handler import handle_decision_packet
from handlers.correction_handler import handle_correction_packet
from handlers.observation_handler import handle_observation_packet

class PacketDispatcher:
    def __init__(self, logger_name="ATROP.Dispatcher", log_config=None):
        self.log = setup_logger(logger_name, log_config or {})

    def parse_header(self, raw_packet):
        """
        Expecting raw_packet as dict for simulation. In prod, decode bytes here.
        Expected keys: message_id, type, source, destination, sequence
        """
        try:
            header = {
                'message_id': raw_packet['message_id'],
                'type': raw_packet['type'],
                'source': raw_packet.get('source', ''),
                'destination': raw_packet.get('destination', ''),
                'sequence': raw_packet.get('sequence', 0),
            }
            return header
        except (KeyError, TypeError) as e:
            self.log.error(f"Header parsing error: {e}")
            return None

    def dispatch(self, raw_packet):
        header = self.parse_header(raw_packet)
        if not header:
            self.log.error("Invalid or corrupt packet; dispatch aborted.")
            return False

        msg_type = header['type'].lower()
        self.log.info(f"Dispatching packet type: {msg_type} (id={header['message_id']})")

        try:
            if msg_type == "discovery":
                handle_discovery_packet(raw_packet)
            elif msg_type == "decision":
                handle_decision_packet(raw_packet)
            elif msg_type == "correction":
                handle_correction_packet(raw_packet)
            elif msg_type in ("observation", "telemetry"):
                handle_observation_packet(raw_packet)
            else:
                self.log.warning(f"Unknown message type '{msg_type}'")
                return False
        except Exception as exc:
            self.log.error(f"Dispatch error for type '{msg_type}': {exc}")
            return False

        return True
