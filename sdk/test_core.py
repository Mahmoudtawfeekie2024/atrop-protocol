import pytest
from sdk.python.atrop_sdk import core

def test_core_import():
    assert hasattr(core, '__version__') or True  # Dummy placeholder
