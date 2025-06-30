# ATROP Data Plane

The **ATROP Data Plane Daemon** is responsible for real-time per-flow inference using lightweight machine learning models.

It interacts with network interfaces or flow taps, classifies traffic behavior (e.g., congestion, burstiness, anomalies), and emits telemetry (`FIF`) back to the control plane AI engine.

---

## Entrypoint

**`main.py`**

- Launches the ML inference agent
- Planned support for:
  - Argument parsing
  - Runtime model hot-swap
  - Telemetry FIFO export
- Returns exit code `0` on successful startup

Run it manually:

```bash
python main.py
```

---

## Future Additions

- Flow classification models: DT, CNN, RL (Q-learning)
- Integration with eBPF, Netfilter, DPDK (optional)
- Support for Brownfield “shadow” inference mode

---

© 2025 Mahmoud Tawfeek – For conceptual design and vendor evaluation only.
