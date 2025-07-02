import sys
import os
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '../../../daemon')))
from logger import setup_logger



def test_text_log_format(tmp_path):
    log_file = tmp_path / "log_text.log"
    log = setup_logger("ATROP.TextTest", {
        "level": "DEBUG",
        "format": "text",
        "file": str(log_file)
    })
    log.info("Text format test passed")

    with open(log_file) as f:
        lines = f.readlines()
        assert any("Text format test passed" in line for line in lines)

def test_json_log_format(tmp_path):
    log_file = tmp_path / "log_json.log"
    log = setup_logger("ATROP.JsonTest", {
        "level": "INFO",
        "format": "json",
        "file": str(log_file)
    })
    log.info("JSON format test passed")

    with open(log_file) as f:
        line = json.loads(f.readline())
        assert line["message"] == "JSON format test passed"
        assert line["levelname"] == "INFO"

def test_console_logging(capsys):
    log = setup_logger("ATROP.ConsoleTest", {
        "level": "WARNING",
        "format": "text"
    })
    log.warning("Console warning test")
    captured = capsys.readouterr()
    assert "Console warning test" in captured.out + captured.err

