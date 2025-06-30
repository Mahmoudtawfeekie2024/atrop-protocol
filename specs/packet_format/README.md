# ✉️ ATROP Packet Format Specification

**Document Version:** 0.1  
**Maintainer:** Protocol Engineer  
**Last Updated:** 25 June 2025  
**Applies To:** All ATROP packet types (control, telemetry, correction)

---

## 🎯 Purpose

This document defines the encoding, structure, and field semantics for ATROP packet types used in control plane coordination, data plane feedback, and inter-node zone behavior. These formats are designed for extensibility, introspection, and real-time feedback loops between AI and ML subsystems.

ATROP packets may be transported over native L3, overlay tunnels, or IPC/messaging backplanes.

---

## 📦 Core Packet Types

| Packet Type     | Direction       | Purpose                                               |
|------------------|------------------|-------------------------------------------------------|
| `DISCOVERY`      | Node → Zone      | Advertise identity, capabilities, and zone request    |
| `DECISION`       | AI → Node        | AI-driven route policy output                         |
| `CORRECT`        | Peer ↔ Peer      | Trigger state transition or rollback due to anomaly   |
| `FIF`            | ML → AI          | Feedback Injection Field from data plane behavior     |
| `PIV`            | Node → Node      | Path Intelligence Vector for route traceability       |
| `IDR`            | Intent Origin → AI | Intent Descriptor Record for service/path goals     |

---

## 🧬 Common Header Fields

Each packet begins with a shared 16-byte header:

| Field        | Size (Bytes) | Description                                    |
|--------------|---------------|------------------------------------------------|
| Version      | 1             | ATROP protocol version                         |
| Type         | 1             | Packet type (DISCOVERY, DECISION, etc.)       |
| Length       | 2             | Total packet length                           |
| Src Node ID  | 4             | Sender's Node Identity Vector (NIV)           |
| Dst Node ID  | 4             | Target node or broadcast zone ID              |
| Flags        | 2             | Control bits (ACK, ERROR, TTL override, etc.) |
| Checksum     | 2             | CRC16 for header validation                   |

---

## 📘 Packet-Specific Payloads

### 🔍 DISCOVERY Packet

| Field           | Size | Description                          |
|------------------|------|--------------------------------------|
| Capabilities     | var  | Supported features, FSM state        |
| Zone Request     | 4    | Desired ATZ ID (if any)              |
| Timestamp        | 8    | Epoch time in microseconds           |

### 🧠 DECISION Packet

| Field           | Size | Description                          |
|------------------|------|--------------------------------------|
| Route Vector     | var  | Ordered node/path list (Node IDs)    |
| Policy Token     | 4    | Intent match hash or UUID            |
| Confidence Score | 2    | AI model certainty (0–10000 scale)   |
| Validity TTL     | 2    | Lifetime in seconds or hops          |

### ⚠️ CORRECT Packet

| Field           | Size | Description                          |
|------------------|------|--------------------------------------|
| Error Code       | 2    | Type of detected anomaly             |
| Affected Nodes   | var  | List of Node IDs                     |
| Suggested Action | 1    | REJOIN, ISOLATE, RETRAIN, etc.       |
| Origin Zone ID   | 4    | Zone reporting the issue             |

### 📊 FIF (Feedback Injection Field)

| Field           | Size | Description                          |
|------------------|------|--------------------------------------|
| Flow Hash        | 4    | Hashed representation of flow tuple  |
| Classification   | 1    | ML-detected type (video, burst, etc.)|
| Confidence       | 2    | Model certainty                      |
| Anomaly Flags    | 1    | Suspicious, unresponsive, overloaded |
| Timestamp        | 8    | Observation time (µs epoch)          |

### 📈 PIV (Path Intelligence Vector)

| Field           | Size | Description                          |
|------------------|------|--------------------------------------|
| Node Sequence    | var  | Traversed nodes (ordered)            |
| Latency Metrics  | var  | Per-hop RTT or jitter                |
| Trust Scores     | var  | Normalized score (0–100)             |

### 🧾 IDR (Intent Descriptor Record)

| Field           | Size | Description                          |
|------------------|------|--------------------------------------|
| Service Intent   | var  | SLA: latency, loss, bandwidth        |
| Zone Preference  | 4    | Preferred ATZ ID (if any)            |
| Path Constraints | var  | Include/exclude nodes/regions        |
| Tenant ID        | 4    | Multi-tenant identifier              |

---

## 📐 Encoding & Transport

- Default encoding: TLV (Type-Length-Value) format with optional compression.
- Transport: Native IP/UDP, gRPC streams (for agents), or intra-node IPC.
- Endianness: Network byte order (big endian)
- Optional encryption for sensitive payloads (future extension)

---

## 🧩 Related Components

- `daemon/ipc/encoder.py` — Packet construction and serialization  
- `specs/state_machines/README.md` — FSM responses to packet events  
- `tools/telemetry/` — Packet logging and debug capture  
- `test/packet_parsing/` — Unit tests for headers and payload decoding  

---

## 👥 Review & Validation

| Role             | Reviewer        |
|------------------|-----------------|
| Protocol Engineer | ✅ Required     |
| AI/ML Architect   | ✅ Advisory     |
| Security Lead     | ✅ Advisory     |
| QA/Test Lead      | ✅ Required     |

---
