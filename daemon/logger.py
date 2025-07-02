import logging
import logging.config
from pythonjsonlogger import jsonlogger
import os

DEFAULT_LOG_LEVEL = "INFO"
DEFAULT_LOG_FORMAT = "text"  # Options: 'text', 'json'

def setup_logger(name: str, config: dict = None) -> logging.Logger:
    """
    Sets up and returns a logger with the given name.
    Supports text and JSON formatting, file and console output.
    """
    log_level = config.get("level", DEFAULT_LOG_LEVEL) if config else DEFAULT_LOG_LEVEL
    log_format = config.get("format", DEFAULT_LOG_FORMAT) if config else DEFAULT_LOG_FORMAT
    log_to_file = config.get("file", None) if config else None

    logger = logging.getLogger(name)
    logger.setLevel(getattr(logging, log_level.upper(), logging.INFO))
    logger.propagate = False  # Avoid duplicate logs

    # Clear any existing handlers
    if logger.hasHandlers():
        logger.handlers.clear()

    # Formatter selection
    if log_format == "json":
        formatter = jsonlogger.JsonFormatter('%(asctime)s %(levelname)s %(name)s %(message)s')
    else:
        formatter = logging.Formatter('%(asctime)s - %(levelname)s - %(name)s - %(message)s')

    # Console Handler
    ch = logging.StreamHandler()
    ch.setFormatter(formatter)
    logger.addHandler(ch)

    # Optional File Handler
    if log_to_file:
        fh = logging.FileHandler(log_to_file)
        fh.setFormatter(formatter)
        logger.addHandler(fh)

    return logger
