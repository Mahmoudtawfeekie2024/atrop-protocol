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

| Hex Code | Packet Constant         | Message Type | Routed Handler Function                   |
|----------|--------------------------|--------------|-------------------------------------------|
| `0x01`   | `ATROP_DISCOVERY`        | DISCOVERY    | `handleDiscoveryPacket(const std::vector<uint8_t>&)` |
| `0x02`   | `ATROP_DECISION`         | DECISION     | `handleDecisionPacket(const std::vector<uint8_t>&)`  |
| `0x03`   | `ATROP_OBSERVATION`      | OBSERVATION  | `handleObservationPacket(const std::vector<uint8_t>&)`|

When a message is received:
1. The header byte is read.
2. A switch-case routes it based on type.
3. The associated handler stub is invoked.

This logic lives in `ipc/main.cpp` and is designed to evolve with:
- Packet validation
- Source identity lookup
- Future dispatch to FSM states
- Logging of unrecognized types

---

## 🧩 Central Handler Header Integration

To simplify message routing and eliminate scattered includes, IPC uses a unified handler interface:

📄 **`daemon/control_plane/handlers/atrop_packet_handlers.hpp`**

```cpp
enum AtropPacketType : uint8_t {
    ATROP_DISCOVERY = 0x01,
    ATROP_DECISION = 0x02,
    ATROP_OBSERVATION = 0x03
};

namespace atrop::control_plane {
    void handleDiscoveryPacket(const std::vector<uint8_t>& packet);
    void handleDecisionPacket(const std::vector<uint8_t>& packet);
    void handleObservationPacket(const std::vector<uint8_t>& packet);
}
```

Instead of including each handler individually:
```cpp
#include "discovery_handler.hpp"
```

Use:
```cpp
#include "atrop_packet_handlers.hpp"
```

This enables centralized handler definitions and supports FSM-driven modularity.

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
