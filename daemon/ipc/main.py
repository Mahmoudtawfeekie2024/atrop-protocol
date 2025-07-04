from logger import setup_logger
from config_loader import load_config
from discovery_handler import handle_discovery_packet
from decision_handler import handle_decision_packet
from observation_handler import handle_observation_packet
from correction_handler import handle_correction_packet
from security_handler import handle_security_packet
from exit_handler import handle_exit_packet

def main():
    config = load_config("config.yaml")

    log = setup_logger("ATROP.IPC", config.get("module", {}))
    log.info("IPC daemon logger started")

    # Simulate runtime
    log.debug("Waiting for control/data plane connections...")

    # Simulate receiving a Discovery packet (stub)
    handle_discovery_packet("DISCOVERY_PACKET_PLACEHOLDER")

    # Simulate receiving a Decision packet (stub)
    handle_decision_packet("DECISION_PACKET_PLACEHOLDER")

    # Simulate receiving an Observation packet (stub)
    handle_observation_packet("OBSERVATION_PACKET_PLACEHOLDER")

    # Simulate receiving a Correction packet (stub)
    handle_correction_packet("CORRECTION_PACKET_PLACEHOLDER")

    # Simulate receiving a Security packet (stub)
    handle_security_packet("SECURITY_PACKET_PLACEHOLDER")

    # Simulate receiving an Exit packet (stub)
    handle_exit_packet("EXIT_PACKET_PLACEHOLDER")
