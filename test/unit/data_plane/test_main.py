import subprocess
import os

def test_main_executes():
    """Run main.py in a subprocess and check exit code."""
    repo_root = os.path.abspath(os.path.join(os.path.dirname(__file__), "../../.."))
    main_script = os.path.join(repo_root, "daemon/data_plane/main.py")

    result = subprocess.run(['python3', main_script], cwd=repo_root, capture_output=True)
    print(result.stdout.decode())
    print(result.stderr.decode())
    assert result.returncode == 0
