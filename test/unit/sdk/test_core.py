import sys
import os
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '../../../../sdk/python/src')))

import pytest  # noqa: F401
from atrop_sdk import core  # noqa: F401

def test_dummy():
    assert True
