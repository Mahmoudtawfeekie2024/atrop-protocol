#!/usr/bin/env python3
"""
main.py - ATROP Data Plane Entrypoint
Description: Launches the ATROP ML inference loop for per-flow forwarding decisions.
Future: Argument parsing, model load trigger, and telemetry hooks.
"""

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
