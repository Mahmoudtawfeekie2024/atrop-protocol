#!/usr/bin/env python3
"""ATROP data plane entrypoint used by the unit tests."""

import sys
from pathlib import Path


REPO_ROOT = Path(__file__).resolve().parents[2]
SDK_SRC = REPO_ROOT / "sdk" / "python" / "src"
if str(SDK_SRC) not in sys.path:
    sys.path.insert(0, str(SDK_SRC))

from atrop_sdk.config_loader import load_config, ConfigLoaderError

def main():
    print("ATROP Data Plane Daemon started...")

    try:
        config = load_config("config.yaml")

        # Selectively print structured keys
        print("[CONFIG] Selected Values:")
        print("  Port:", config["module"]["port"])
        print("  Timeout:", config["module"]["timeout"])
        print("  Log Level:", config["module"]["log_level"])
        print("  Mode:", config["environment"]["mode"])
        print("  Model Dir:", config["paths"]["model_dir"])
        print("  Data Dir:", config["paths"]["data_dir"])
        print("  Log Dir:", config["paths"]["log_dir"])

        # Full printout for inspection/debug
        print("[CONFIG] Full Configuration:")
        for key, value in config.items():
            print(f"  {key}: {value}")

    except ConfigLoaderError as e:
        print(f"[CONFIG] Error: {e}")
        return 1

    # TODO: Use config values to initialize model, telemetry, etc.
    return 0

if __name__ == "__main__":
    import sys
    sys.exit(main())
