# ATROP Protocol Packet Dispatcher

The Packet Dispatcher routes incoming protocol packets based on the message type in their standard ATROP headers.

## Packet Structure

```json
{
  "message_id": 101,
  "type": "discovery",  // discovery|decision|correction|observation|telemetry
  "source": "NodeA",
  "destination": "NodeB",
  "sequence": 1234,
  "payload": { /* ... extensibility ... */ }
}
```

### Message Types
- **discovery** — Handled by `handle_discovery_packet`
- **decision** — Handled by `handle_decision_packet`
- **correction** — Handled by `handle_correction_packet`
- **observation** / **telemetry** — Handled by `handle_observation_packet`

### Error Handling
Malformed headers, unknown message types, or handler exceptions are logged via the unified logger.

### Simulation & Testing
The dispatcher supports unit testing by injecting simulated packet dictionaries.

**Example**
```python
from daemon.packet_dispatcher import PacketDispatcher

dispatcher = PacketDispatcher()
dispatcher.dispatch({
    "message_id": 42,
    "type": "decision",
    "source": "MLNODE1",
    "destination": "FSM0",
    "sequence": 1,
    "payload": {"policy_id": "P1"}
})
```

---

## Plan of Action (Summary)

1. **Add `daemon/packet_dispatcher.py`**: Central logic for packet parsing/dispatch.
2. **Add unit test**: `test/unit/protocol/test_packet_dispatcher.py` mocking handlers.
3. **Add documentation**: `docs/protocol/dispatcher.md` describes format, use, examples.
4. **(Optional) Wire-up dispatcher in IPC main / simulation code for integration.**
5. **(Optional) Future: C++ version for production daemon; propagate interface.**

---

### Targeted Path Repo Changes
- **New file:** `daemon/packet_dispatcher.py`
- **New test:** `test/unit/protocol/test_packet_dispatcher.py`
- **New documentation:** `docs/protocol/dispatcher.md`

---

## CI & Test Note

- The CI job (`.github/workflows/ci.yml`) should auto-discover and run new Python unit tests; ensure this is confirmed after commit.
- If not present, add `pytest` invocation on `test/unit/protocol`.

---

### Next Steps

1. Implement the files above.
2. Confirm test and doc visibility in CI.
3. (Optional) Discuss with team if you want both Python **and** C++ dispatcher, or Python remains reference/proto and C++ is implemented later.

---

**If you want a C++ version as well, just ask!**

---

**Source**:  
- All code and structure derived from user acceptance, repo structure, and discovered handler/test/documentation conventions.  
- [Repo Link](https://github.com/Mahmoudtawfeekie2024/atrop-protocol)
