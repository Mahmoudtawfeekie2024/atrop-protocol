# ATROP Control Plane Handlers

The **ATROP Protocol Handlers** module contains the initial stub implementations for processing ATROP’s core packet types in the control plane.

Each handler is a placeholder designed to log reception and identify message types such as `Discovery`, `Decision`, and `Observation`. They serve as entry points for future parsing, validation, and FSM routing.

---

## Implemented Handlers

| Packet Type | Handler File               | Purpose                                       |
|-------------|----------------------------|-----------------------------------------------|
| Discovery   | `discovery_handler.cpp`    | Handles node introduction and topology sync   |
| Decision    | `decision_handler.cpp`     | Processes AI routing intent and policies      |
| Observation | `observation_handler.cpp`  | Accepts telemetry and learning feedback       |

All stubs follow a consistent pattern:
- Log packet receipt
- Identify message type
- Add `TODO` markers for parsing headers (NIV, IDR, PIV, FIF)
- Add `FIXME` for FSM dispatch hooks

---

## Stub Design Philosophy

Each handler currently includes:

- Function signature:
  ```cpp
  void handle<Type>Packet(const std::vector<uint8_t>& packet);
  ```

- Central logging call:
  ```cpp
  LOG_INFO("Received <TYPE> packet");
  ```

- Placeholder comments:
  ```cpp
  // TODO: Extract NIV
  // FIXME: Integrate with FSM
  ```

These stubs are safe to compile, test, and evolve during Phase 1 and Phase 2 of the ATROP protocol implementation lifecycle.

---

## Logging Integration

The handlers use the unified logging abstraction from `daemon/common/logger.[hpp|cpp]`. All logs are formatted consistently and routed to stdout or files, based on ATROP config.

---

## Future Enhancements

- Full binary/TLV parsing of ATROP protocol headers
- FSM state dispatch (e.g., trigger `DISCOVERY → LEARN`)
- Packet validation and trust domain enforcement
- Protocol error handling and resilience fallbacks

---

© 2025 Mahmoud Tawfeek – Conceptual only. For vendor integration and research use.
