"""Unit tests for the Python packet handlers."""

from __future__ import annotations

import pytest

from daemon.handlers.common import PacketValidationError
from daemon.handlers.correction_handler import handle_correction_packet
from daemon.handlers.decision_handler import handle_decision_packet
from daemon.handlers.discovery_handler import handle_discovery_packet
from daemon.handlers.exit_handler import handle_exit_packet
from daemon.handlers.observation_handler import handle_observation_packet
from daemon.handlers.security_handler import handle_security_packet


def make_packet(packet_type: str, payload: dict, **overrides) -> dict:
    base = {
        "message_id": overrides.pop("message_id", "pkt-001"),
        "type": packet_type,
        "source": overrides.pop("source", "node-a"),
        "destination": overrides.pop("destination", "node-b"),
        "sequence": overrides.pop("sequence", "9"),
    }
    base.update(overrides)
    base["payload"] = payload
    return base


def test_discovery_handler_normalizes_capabilities():
    packet = make_packet(
        "discovery",
        {
            "capabilities": {"gnn": True, "grpc": False, "telemetry": 1},
            "zone_request": "42",
            "timestamp": 123456789,
            "notes": "prefers zone 42",
        },
    )

    result = handle_discovery_packet(packet)

    assert result["header"]["sequence"] == 9
    assert result["payload"]["capabilities"] == ["gnn", "telemetry"]
    assert result["payload"]["capability_map"] == {"gnn": True, "grpc": False, "telemetry": True}
    assert result["payload"]["zone_request"] == 42
    assert result["payload"]["timestamp"] == 123456789
    assert result["extras"] == {"notes": "prefers zone 42"}


def test_discovery_handler_missing_capabilities_raises():
    packet = make_packet("discovery", {"zone_request": 1, "timestamp": 2})

    with pytest.raises(PacketValidationError):
        handle_discovery_packet(packet)


def test_decision_handler_normalizes_route_vector():
    payload = {
        "route_vector": "node-a -> node-b -> node-c",
        "policy_token": "policy-007",
        "confidence": "8750.5",
        "validity_ttl": "45",
        "intent": "priority",
    }
    packet = make_packet("decision", payload)

    result = handle_decision_packet(packet)

    assert result["payload"]["route_vector"] == ["node-a", "node-b", "node-c"]
    assert result["payload"]["confidence"] == pytest.approx(8750.5)
    assert result["payload"]["validity_ttl"] == 45
    assert result["extras"] == {"intent": "priority"}

    invalid_packet = make_packet("decision", {**payload, "confidence": 20000})
    with pytest.raises(PacketValidationError):
        handle_decision_packet(invalid_packet)


def test_correction_handler_normalizes_nodes():
    packet = make_packet(
        "correction",
        {
            "error_code": "404",
            "affected_nodes": "node-1,node-2",
            "suggested_action": "isolate",
            "origin_zone": 9,
            "details": {"reason": "anomaly"},
        },
    )

    result = handle_correction_packet(packet)

    assert result["payload"]["error_code"] == 404
    assert result["payload"]["affected_nodes"] == ["node-1", "node-2"]
    assert result["payload"]["suggested_action"] == "ISOLATE"
    assert result["payload"]["origin_zone"] == "9"
    assert result["payload"]["remediation_step"] is None
    assert result["extras"] == {"details": {"reason": "anomaly"}}


def test_observation_handler_parses_flags_and_bounds():
    packet = make_packet(
        "observation",
        {
            "telemetry": {"latency_ms": 12},
            "trust_score": "88.2",
            "anomaly_flags": "suspicious,latency",
            "flow_hash": "deadbeef",
        },
    )

    result = handle_observation_packet(packet)

    assert result["payload"]["telemetry"] == {"latency_ms": 12}
    assert result["payload"]["trust_score"] == pytest.approx(88.2)
    assert result["payload"]["anomaly_flags"] == ["suspicious", "latency"]
    assert result["payload"]["timestamp"] is None
    assert result["extras"] == {"flow_hash": "deadbeef"}

    invalid_packet = make_packet(
        "observation",
        {"telemetry": {"latency_ms": 10}, "trust_score": 150},
    )
    with pytest.raises(PacketValidationError):
        handle_observation_packet(invalid_packet)


def test_security_handler_accepts_binary_material():
    packet = make_packet(
        "security",
        {
            "auth_type": "mutual_tls",
            "challenge": b"\x01\x02",
            "signature": b"\xff\x00",
            "key_material": {"certificate": "abc"},
        },
    )

    result = handle_security_packet(packet)

    assert result["payload"]["auth_type"] == "MUTUAL_TLS"
    assert result["payload"]["challenge"] == "0102"
    assert result["payload"]["signature"] == "ff00"
    assert result["payload"]["key_material"] == {"certificate": "abc"}
    assert result["extras"] == {}

    missing_sig_packet = make_packet(
        "security",
        {"auth_type": "psk", "challenge": b"\x01", "key_material": "feed"},
    )
    with pytest.raises(PacketValidationError):
        handle_security_packet(missing_sig_packet)


def test_exit_handler_defaults_snapshot_when_missing():
    packet = make_packet(
        "exit",
        {"reason": "maintenance", "timestamp": "1700", "note": "scheduled"},
    )

    result = handle_exit_packet(packet)

    assert result["payload"]["reason"] == "maintenance"
    assert result["payload"]["state_snapshot"] == {}
    assert result["payload"]["timestamp"] == 1700
    assert result["extras"] == {"note": "scheduled"}

    missing_reason = make_packet("exit", {"timestamp": 1})
    with pytest.raises(PacketValidationError):
        handle_exit_packet(missing_reason)
