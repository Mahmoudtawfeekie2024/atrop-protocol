# ATROP IPC Module

The **ATROP IPC Daemon** manages inter-process communication between ATROP components (Control Plane, Data Plane, Model Engine). It ensures reliable message exchange and daemon lifecycle coordination.

---

## Entrypoint

**`main.cpp`**

- Starts the IPC handling service
- Placeholder for:
  - Argument parsing
  - IPC channel initialization (e.g., UNIX sockets, shared memory)
- Returns `0` on successful initialization

To compile:

```bash
g++ main.cpp -o atrop_ipc
./atrop_ipc
```

---

## Responsibilities

- Broker messages across daemons (FIF, PIV, decisions)
- Handle agent registration and heartbeat
- Secure the IPC layer (permissions, identity check)
- Coordinate hot reload of models or config

---

## 🔄 Message Dispatch Logic

The IPC module includes a dispatch switch that routes each message type to the corresponding control-plane handler.

### 🧠 Dispatch Mapping Table

| Hex Code | Message Type | Routed Handler Function                   |
|----------|--------------|-------------------------------------------|
| `0x01`   | DISCOVERY     | `handleDiscoveryPacket(const std::vector<uint8_t>&)` |
| `0x02`   | DECISION      | `handleDecisionPacket(const std::vector<uint8_t>&)`  |
| `0x03`   | OBSERVATION   | `handleObservationPacket(const std::vector<uint8_t>&)`|

When a message is received:
1. The header byte is read.
2. A switch-case routes it based on type.
3. The associated handler stub is invoked.

This logic lives in `ipc/main.cpp` and will evolve to include:
- Packet validation
- Source identity lookup
- Future dispatch to FSM states

---

## 🔧 Configuration Loader

The IPC Daemon loads its configuration from a `config.json` or `config.yaml` file at startup.

### ✅ Supported Locations

1. Path specified by `ATROP_CONFIG_PATH`
2. Defaults: `./config.json` or `./config.yaml`
3. Fallbacks embedded in code

### 🔑 Required Fields

| Key              | Description                        |
|------------------|------------------------------------|
| `ipc.socket_path`| Path to the IPC UNIX domain socket |
| `ipc.timeout`    | Timeout for message retries (ms)   |

Missing required fields result in fallback defaults or startup failure (if critical).

### 🧪 Sample Config

```json
{
  "ipc.socket_path": "/tmp/atrop.sock",
  "ipc.timeout": 2000
}
```

See `test/unit/sdk/config/` for more examples.

---

© 2025 Mahmoud Tawfeek – For conceptual demonstration of ATROP architecture only.
