import logging
from logging.handlers import RotatingFileHandler
from pythonjsonlogger import jsonlogger

def setup_logger(name: str, config: dict = None) -> logging.Logger:
    log_level = config.get("level", "INFO") if config else "INFO"
    log_format = config.get("format", "text") if config else "text"
    log_to_file = config.get("file", None)
    rotate = config.get("rotate", False)
    max_bytes = config.get("max_bytes", 1_000_000)
    backup_count = config.get("backup_count", 3)

    logger = logging.getLogger(name)
    logger.setLevel(getattr(logging, log_level.upper(), logging.INFO))
    logger.propagate = False

    if logger.hasHandlers():
        logger.handlers.clear()

    if log_format == "json":
        formatter = jsonlogger.JsonFormatter('%(asctime)s %(levelname)s %(name)s %(message)s')
    else:
        formatter = logging.Formatter('%(asctime)s - %(levelname)s - %(name)s - %(message)s')

    # Console
    console = logging.StreamHandler()
    console.setFormatter(formatter)
    logger.addHandler(console)

    # File Logging (flat or rotated)
    if log_to_file:
        if rotate:
            file_handler = RotatingFileHandler(log_to_file, maxBytes=max_bytes, backupCount=backup_count)
        else:
            file_handler = logging.FileHandler(log_to_file)

        file_handler.setFormatter(formatter)
        logger.addHandler(file_handler)

    return logger
