# sdk/python/src/atrop_sdk/config_loader.py

import os
import json
import yaml

class ConfigLoaderError(Exception):
    """Raised when there is a failure in loading the configuration."""
    pass

def load_config(config_path):
    """
    Load a JSON or YAML configuration file.

    Args:
        config_path (str): Absolute or relative path to the config file.

    Returns:
        dict: Parsed configuration dictionary.

    Raises:
        ConfigLoaderError: If file is missing or parsing fails.
    """
    if not os.path.exists(config_path):
        raise ConfigLoaderError(f"Configuration file does not exist: {config_path}")

    ext = os.path.splitext(config_path)[1].lower()

    try:
        with open(config_path, "r") as f:
            if ext == ".json":
                return json.load(f)
            elif ext in [".yaml", ".yml"]:
                return yaml.safe_load(f)
            else:
                raise ConfigLoaderError(f"Unsupported file extension '{ext}'. Use .json or .yaml.")
    except Exception as e:
        raise ConfigLoaderError(f"Failed to load configuration: {e}")
