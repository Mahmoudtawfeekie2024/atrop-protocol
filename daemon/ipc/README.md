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

## Future Scope

- Support for gRPC or Netlink as IPC backend
- Add sandboxing and privilege controls
- Integrate with systemd service supervision

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
---