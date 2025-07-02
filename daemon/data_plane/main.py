#!/usr/bin/env python3
"""
main.py - ATROP Data Plane Entrypoint
Description: Launches the ATROP ML inference loop for per-flow forwarding decisions.
Future: Argument parsing, model load trigger, and telemetry hooks.
Status: Stub implementation
"""

from atrop_sdk.config_loader import load_config, ConfigLoaderError

def main():
    print("ATROP Data Plane Daemon started...")

    try:
        config = load_config("config.yaml")
        print("[CONFIG] Successfully loaded:")
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
