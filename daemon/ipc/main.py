from logger import setup_logger
from config_loader import load_config

def main():
    config = load_config("config.yaml")

    log = setup_logger("ATROP.IPC", config.get("module", {}))
    log.info("IPC daemon logger started")

    # Simulate runtime
    log.debug("Waiting for control/data plane connections...")

if __name__ == "__main__":
    main()
