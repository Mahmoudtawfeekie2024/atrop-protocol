from logger import setup_logger
from config_loader import load_config
from discovery_handler import handle_discovery_packet  # Newly added import

def main():
    config = load_config("config.yaml")

    log = setup_logger("ATROP.IPC", config.get("module", {}))
    log.info("IPC daemon logger started")

    # Simulate runtime
    log.debug("Waiting for control/data plane connections...")

    # Simulate receiving a Discovery packet (stub)
    handle_discovery_packet("DISCOVERY_PACKET_PLACEHOLDER")

if __name__ == "__main__":
    main()
