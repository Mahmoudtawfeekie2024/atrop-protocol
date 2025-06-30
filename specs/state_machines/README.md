# 🧠 ATROP Finite State Machines (FSM)

**Document Version:** 0.1  
**Maintainer:** Protocol Architect  
**Last Updated:** 25 June 2025  
**Applies To:** All ATROP nodes (intra- and inter-zone)

---

## 🎯 Purpose

This document defines the state machines governing ATROP’s operational behavior. FSMs are used per node to control lifecycle transitions, zone participation, anomaly recovery, and synchronization with the AI/ML planes.

FSMs provide deterministic structure over ATROP’s otherwise dynamic, learning-driven behavior — ensuring reliable operation under both normal and failure conditions.

---

## 🔄 FSM Overview

Each ATROP node runs a local FSM that governs its routing state and reaction to network and learning events. Transitions are triggered by:

- Topology discovery or loss  
- AI-driven route decisions  
- ML-based flow anomalies (via FIF)  
- Zone correction packets (CORRECT)  
- Manual or policy-based triggers  

---

## 🧭 State Definitions

| State       | Description                                                                 |
|-------------|-----------------------------------------------------------------------------|
| `INIT`      | Node is booting or restarting. No adjacencies or AI/ML feedback yet.       |
| `DISCOVERY` | Node performs neighbor/zone discovery using base hello protocol.           |
| `LEARN`     | AI collects topology data and initial intents to train decision policy.    |
| `DECIDE`    | AI makes routing choices, triggers transitions to enforce state.           |
| `ENFORCE`   | Control plane decisions are pushed to forwarding tables.                   |
| `OBSERVE`   | Data plane monitors flows and classifies behaviors (FIF emitted).          |
| `FEEDBACK`  | Control plane absorbs FIF telemetry, adjusts policy or model confidence.   |
| `CORRECT`   | Recovery state: override routing, isolate faults, or re-trigger learning.  |

---

## 🔁 Transition Logic

```text
INIT --> DISCOVERY
DISCOVERY --> LEARN
LEARN --> DECIDE
DECIDE --> ENFORCE
ENFORCE --> OBSERVE
OBSERVE --> FEEDBACK
FEEDBACK --> DECIDE | CORRECT
CORRECT --> DISCOVERY | LEARN
```

Special Cases:  
- `CORRECT` can be triggered from any state on anomaly or policy violation  
- `FEEDBACK` loops into `DECIDE` if model confidence is sufficient  
- `INIT` can be re-entered on daemon crash or reset  

---

## 🧪 Events and Triggers

| Event Type         | Source             | Triggered State |
|--------------------|--------------------|-----------------|
| Adjacency Up       | Protocol Neighbor  | DISCOVERY       |
| Zone Join Complete | FSM                | LEARN           |
| AI Decision Ready  | Control Plane      | DECIDE          |
| Policy Match       | AI Intent Engine   | ENFORCE         |
| FIF Received       | ML Data Plane      | FEEDBACK        |
| Anomaly Detected   | AI/ML              | CORRECT         |
| Manual Reset       | Admin/Policy       | INIT            |

---

## 🔐 Zone FSM Synchronization

Each ATZ (Autonomous Topology Zone) maintains FSM cohesion by:

- Sharing summarized state vectors across peers  
- Broadcasting correction messages if divergence occurs  
- Electing correction leaders in split-brain cases  

This allows FSM transitions to be both node-local and zone-aware.

---

## 🧩 Related Components

- `daemon/control_plane/fsm_engine.py` — FSM transition driver  
- `specs/protocol/` — Message types (DISCOVERY, DECISION, CORRECT)  
- `test/fsm-simulations/` — Simulated transition test cases  
- `specs/packet_format/README.md` — FIF and state vector encoding  

---

## 🧬 Extensibility

Future enhancements may include:

- Sub-states for granular diagnostics  
- Multi-phase correction states  
- AI-assisted transition scoring  
- FSM replays for audit/rollback  

---

## 👥 Review & Validation

| Role             | Reviewer        |
|------------------|-----------------|
| Protocol Architect | ✅ Required   |
| Test Lead        | ✅ Required     |
| AI/ML Lead       | ✅ Advisory     |

---
