# ATROP Control Plane

The **ATROP Control Plane Daemon** governs the AI-assisted routing logic of the protocol. It interprets topology, service intent, and policy to make optimized routing decisions via a finite state machine (FSM).

This module represents the "brain" of ATROP, operating at the zone and domain levels.

---

## Entrypoint

**`main.cpp`**

- Starts the control plane logic
- Future features:
  - Argument parsing
  - Topology initialization
  - AI decision loop bootstrap
- Returns `0` on success

To compile:

```bash
g++ main.cpp -o atrop_control
./atrop_control
```

---

## Core Responsibilities

- Run ATROP FSM (INIT → DISCOVERY → LEARN → DECIDE → ...)
- Interface with AI Engine (GNN/RL)
- Process `Discovery`, `Decision`, `Correction` packets
- Enforce SLA, security, and topology policies

---

## Future Integration

- Intent policy compiler (IPU)
- Zone-based AI model loading
- Decision fallback safety logic

---

© 2025 Mahmoud Tawfeek – Conceptual only. For vendor integration and research use.
