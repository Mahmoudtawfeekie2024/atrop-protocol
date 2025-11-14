import sys
import os

# Add sdk/python/src to sys.path for all test imports
BASE_TEST_DIR = os.path.dirname(__file__)
sys.path.insert(0, os.path.abspath(os.path.join(BASE_TEST_DIR, "..")))
sys.path.insert(0, os.path.abspath(os.path.join(BASE_TEST_DIR, '../sdk/python/src')))
