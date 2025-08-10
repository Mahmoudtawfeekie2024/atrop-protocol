import pytest
from daemon.packet_dispatcher import PacketDispatcher

class DummyHandler:
    invoked = False
    payload = None

    @classmethod
    def handler(cls, raw_packet):
        cls.invoked = True
        cls.payload = raw_packet

@pytest.fixture(autouse=True)
def restore_dummy(monkeypatch):
    # Patch stub handlers for test, revert after
    from daemon import packet_dispatcher
    packet_dispatcher.handle_discovery_packet = DummyHandler.handler
    packet_dispatcher.handle_decision_packet = DummyHandler.handler
    packet_dispatcher.handle_correction_packet = DummyHandler.handler
    packet_dispatcher.handle_observation_packet = DummyHandler.handler
    yield
    DummyHandler.invoked = False
    DummyHandler.payload = None

def test_dispatch_discovery():
    pd = PacketDispatcher()
    pkt = {'message_id': 1, 'type': 'Discovery', 'source': 'A', 'destination': 'B', 'sequence': 100}
    assert pd.dispatch(pkt)
    assert DummyHandler.invoked
    assert DummyHandler.payload == pkt

def test_dispatch_decision():
    pd = PacketDispatcher()
    pkt = {'message_id': 2, 'type': 'Decision', 'source': 'X', 'destination': 'Y', 'sequence': 200}
    assert pd.dispatch(pkt)
    assert DummyHandler.invoked
    assert DummyHandler.payload == pkt

def test_dispatch_invalid():
    pd = PacketDispatcher()
    # Missing type
    pkt = {'message_id': 3, 'source': 'A'}
    assert pd.dispatch(pkt) is False

def test_dispatch_unknown_type():
    pd = PacketDispatcher()
    pkt = {'message_id': 4, 'type': 'foobar', 'source': 'A', 'destination': 'B'}
    assert pd.dispatch(pkt) is False
