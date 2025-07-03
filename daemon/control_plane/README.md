
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

## 🧾 Configuration Loader

The control plane uses the internal `ConfigLoader` module to load structured configuration at startup.

Supported formats:
- `.json` (preferred)
- `.yaml` / `.yml`

Default lookup order:
1. `ATROP_CONFIG_PATH` environment variable (if set)
2. Local `config.json` / `config.yaml`
3. Built-in fallback defaults

Typical keys:
```json
{
  "module.port": 9090,
  "module.timeout": 30,
  "paths.log_dir": "/var/log/atrop",
  "environment.mode": "dev"
}
```

Missing required fields may result in:
- an error
- or fallback to sensible defaults (e.g., port 8080)

The loaded config is validated and logged on startup.

---

## 🧩 Handler Stub Files

The following handler stubs represent the modular entrypoints for incoming protocol messages. These will later be extended with FSM integration, structured parsing, and inference hooks.

| File Name                         | Purpose Description                                                                 |
|----------------------------------|--------------------------------------------------------------------------------------|
| `discovery_handler.cpp`          | Handles topology discovery packets to bootstrap neighbor awareness and state entry. |
| `decision_handler.cpp`           | Processes AI-driven routing decisions and updates path intelligence structures.     |
| `observation_handler.cpp`        | Handles telemetry feedback and status reports for reinforcement learning updates.   |

All handler files reside in:

```
daemon/control_plane/handlers/
```

Each stub uses `LOG_INFO` for tracing and includes `TODO` and `FIXME` placeholders for future extensions:
- Parse: **Node Identity Vector (NIV)**, **Path Intelligence Vector (PIV)**, **Intent Descriptor (IDR)**
- Inject: **Feedback Injection Field (FIF)** (Observation only)
- Dispatch: Finite State Machine (FSM) control signals

---

## Future Integration

- Intent policy compiler (IPU)
- Zone-based AI model loading
- Decision fallback safety logic

---

© 2025 Mahmoud Tawfeek – Conceptual only. For vendor integration and research use.
