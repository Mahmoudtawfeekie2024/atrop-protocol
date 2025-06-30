import subprocess

def test_main_executes():
    """Run main.py in a subprocess and check exit code."""
    result = subprocess.run(['python3', 'daemon/data_plane/main.py'], capture_output=True)
    assert result.returncode == 0
