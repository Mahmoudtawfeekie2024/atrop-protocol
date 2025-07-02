# sdk/python/src/atrop_sdk/config_loader.py

import os
import json
import yaml

class ConfigLoaderError(Exception):
    """Raised when there is a failure in loading the configuration."""
    pass

def apply_defaults(cfg):
    """Inject default values for missing config fields."""
    return {
        "module": {
            "port": cfg.get("module", {}).get("port", 8080),
            "timeout": cfg.get("module", {}).get("timeout", 10),
            "log_level": cfg.get("module", {}).get("log_level", "INFO")
        },
        "environment": {
            "mode": cfg.get("environment", {}).get("mode", "dev")
        },
        "paths": {
            "model_dir": cfg.get("paths", {}).get("model_dir", "./models"),
            "data_dir": cfg.get("paths", {}).get("data_dir", "./data"),
            "log_dir": cfg.get("paths", {}).get("log_dir", "./logs")
        }
    }

def validate_required_fields(config):
    """Ensure critical required fields are not missing after defaults."""
    try:
        _ = config["module"]["port"]
        _ = config["environment"]["mode"]
        _ = config["paths"]["log_dir"]
    except KeyError as e:
        raise ConfigLoaderError(f"Missing required config field: {e}")

def load_config(config_path):
    """
    Load a JSON or YAML configuration file with default fallback.

    Args:
        config_path (str): Absolute or relative path to the config file.

    Returns:
        dict: Parsed configuration dictionary with defaults.

    Raises:
        ConfigLoaderError: If file is missing or parsing fails.
    """
    if not os.path.exists(config_path):
        raise ConfigLoaderError(f"Configuration file does not exist: {config_path}")

    ext = os.path.splitext(config_path)[1].lower()

    try:
        with open(config_path, "r") as f:
            if ext == ".json":
                try:
                    cfg = apply_defaults(json.load(f))
                except json.JSONDecodeError as e:
                    raise ConfigLoaderError(f"Syntax error in JSON config: {e}")
            elif ext in [".yaml", ".yml"]:
                try:
                    cfg = apply_defaults(yaml.safe_load(f))
                except yaml.YAMLError as e:
                    raise ConfigLoaderError(f"Syntax error in YAML config: {e}")
            else:
                raise ConfigLoaderError(f"Unsupported file extension '{ext}'. Use .json or .yaml.")

            validate_required_fields(cfg)
            print(f"[CONFIG] Successfully loaded and validated: {config_path}")
            return cfg

    except Exception as e:
        raise ConfigLoaderError(f"Failed to load configuration: {e}")
