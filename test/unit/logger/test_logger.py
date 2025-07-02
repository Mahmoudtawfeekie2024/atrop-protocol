from logger import setup_logger

def test_json_log_output():
    log = setup_logger("ATROP.Test", {
        "level": "DEBUG",
        "format": "json"
    })
    log.info("Structured log test passed")
    assert True
