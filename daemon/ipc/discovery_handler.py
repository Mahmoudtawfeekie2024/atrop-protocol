# daemon/ipc/discovery_handler.py

from logger import setup_logger

def handle_discovery_packet(raw_packet):
    """
    T1-09 Discovery Packet Handler (stub)
    Handles Discovery packets (initial node intro, topology discovery)
    Expected fields: NIV, node_id, zone_info, etc.
    TODO: Implement full parsing and dispatch in Phase 2 (see T2-03)
    """
    log = setup_logger("ATROP.IPC", {})
    log.info("[STUB] Received Discovery packet (stub handler)")
    # TODO: Parse raw_packet for Discovery fields (NIV, node_id, etc.)
    # FIXME: Implement full parsing and dispatch in Phase 2
