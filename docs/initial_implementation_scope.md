# 🧱 ATROP Initial Implementation Scope

**Document Version:** 0.1  
**Maintainer:** Protocol Architect  
**Last Updated:** 25 June 2025  
**Applies To:** Initial functional build and testable deployment of ATROP

---

## 🎯 Purpose

This document outlines the baseline scope of the first implementation of the ATROP protocol. It identifies the essential components required to realize a working, testable prototype — including architectural constructs, behavioral logic, and data-driven features — without reliance on legacy protocols or advanced vendor integrations.

This scoped definition ensures consistent alignment across engineering, testing, and integration teams while providing a solid foundation for future expansion.

---

## 📐 Design Boundaries

The initial implementation of ATROP will adhere to the following boundaries:

- **Device-Native:** All protocol logic executes natively on the network OS (not VM/container-based).
- **Protocol-Independent:** No dependency on existing routing protocols (e.g., OSPF, BGP) for core operation.
- **Topology-Aware:** Implements hierarchical zone logic (Autonomous Topology Zones - ATZ) for all routing decisions.
- **Interoperability-Ready:** Adapters and shims may be stubbed, but not fully integrated in this phase.
- **Self-Contained Learning:** Feedback and adaptation are handled internally through control/data plane feedback loops.

---

## 🧩 Components In Scope

The following components are considered **in scope** for the initial implementation:

### 🧠 AI Control Plane

- Topology learning via Graph Neural Networks (GNN) or Reinforcement Learning (RL)
- Intent interpretation and translation into routing decisions
- Policy fallback logic when model confidence is low
- AI feedback receiver (via FIF, PIV)

### ⚙️ ML Data Plane

- Flow classification models (e.g., DT, CNN) for identifying app behavior and traffic patterns
- Real-time trust scoring for links and paths
- Telemetry generation: Feedback Injection Field (FIF)
- Safety fallback to deterministic routing if models fail

### 🔄 FSM & Routing Logic

- Node state machine lifecycle (INIT → DISCOVERY → ENFORCE → FEEDBACK → CORRECT)
- Zone (ATZ) formation, split/merge handling
- Policy enforcement and transition triggers
- Correction packet handling for anomaly resolution

### 🔌 IPC & Daemon Services

- Lightweight daemon for control, data, and model services
- IPC via UNIX sockets or gRPC
- Queue/buffer support for FIF/Decision messages
- Agent lifecycle, heartbeat, and reload commands

### 🛰️ Telemetry Infrastructure

- Telemetry emission (PIV, FIF, IDR) for AI training and audit
- JSON export for observability pipeline
- Hook for offline or federated training stub

---

## 🚫 Out of Scope

These elements are explicitly **excluded** from the initial implementation:

- Full vendor SDK or driver integration (e.g., JunOS, IOS-XR)
- Real-time training of AI/ML models
- Native redistribution with legacy protocols
- Label-based switching (e.g., SR-MPLS, SRv6)
- Hardware offload or ASIC acceleration
- Secure bootstrapping and zero-trust token validation (stubbed only)

---

## 🧭 Deployment Assumptions

- Runs on Ubuntu/Debian-based systems with user-space daemon model
- Initial testing performed in Mininet and Linux namespaces
- No production-grade deployment tooling or orchestration expected at this stage
- Agents run with simulated data inputs (PCAPs, replayed flows, synthetic topology)

---

## ✅ Exit Criteria

The following capabilities must be verifiably implemented and testable:

- Functional state machine across ATZ-capable nodes
- AI routing decision output based on simulated or static topology
- ML flow classification and FIF generation on live or simulated traffic
- IPC synchronization and message routing between control/data planes
- Initial telemetry logs from both planes in machine-readable format

---

## 👥 Review & Approval

| Role             | Reviewer          |
|------------------|-------------------|
| Protocol Architect | ✅ Required     |
| AI Architect     | ✅ Required       |
| ML Engineer      | ✅ Required       |
| Integration Lead | ✅ Required       |
| QA Lead          | ✅ Required       |

---
