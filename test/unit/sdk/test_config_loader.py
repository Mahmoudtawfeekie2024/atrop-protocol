import os
import pytest
from atrop_sdk import config_loader

BASE_DIR = os.path.dirname(__file__)
CONFIG_DIR = os.path.join(BASE_DIR, "config")

def test_valid_json_load():
    cfg = config_loader.load_config(os.path.join(CONFIG_DIR, "config.json"))
    assert cfg["module"]["port"] == 9000
    assert cfg["environment"]["mode"] == "prod"
    assert cfg["paths"]["log_dir"] == "/var/log/atrop"

def test_valid_yaml_load():
    cfg = config_loader.load_config(os.path.join(CONFIG_DIR, "config.yaml"))
    assert cfg["module"]["timeout"] == 20
    assert cfg["module"]["log_level"] == "DEBUG"

def test_missing_required_field():
    with pytest.raises(config_loader.ConfigLoaderError):
        config_loader.load_config(os.path.join(CONFIG_DIR, "missing_log_dir.yaml"))

def test_invalid_json_format():
    with pytest.raises(config_loader.ConfigLoaderError):
        config_loader.load_config(os.path.join(CONFIG_DIR, "invalid.json"))

def test_env_override(monkeypatch):
    # Not implemented yet — placeholder for future test
    assert True
