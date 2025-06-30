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

© 2025 Mahmoud Tawfeek – For conceptual demonstration of ATROP architecture only.
