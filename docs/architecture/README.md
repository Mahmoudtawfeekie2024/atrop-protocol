# 🧠 ATROP Architecture Overview

Welcome to the architectural documentation for **ATROP** (Autonomous Topology-Optimized Routing Protocol). This document provides an introductory view of the protocol’s conceptual framework, core layers, intelligence models, and how they come together to form an autonomous, AI-native routing fabric.

---

## 🧭 Vision

ATROP is not an evolution of existing protocols — it is a clean-slate reinvention. Designed for live device OS deployment, it introduces **AI-driven decision logic in the control plane** and **ML-based adaptive flow handling in the data plane**. It enables dynamic, real-time optimization based on topology, service intent, flow behavior, and security posture.

---

## 🧩 Dual-Plane Intelligence Stack

### 🔹 Control Plane – AI-Driven Logic
Implements dynamic, intent-aware routing decisions using:

- **Graph Neural Networks (GNN)** and **Reinforcement Learning (RL)**
- Topology state monitoring and prediction
- SLA-based policy orchestration
- Federated learning across Autonomous Topology Zones (ATZs)
- Confidence scoring and fallback logic

📁 Refer: [`specs/ai_control_plane/`](../../specs/ai_control_plane/)

---

### 🔸 Data Plane – ML-Augmented Execution
Embeds lightweight ML models per node to:

- Classify traffic behavior in real-time (burst, video, anomaly)
- Adjust forwarding paths preemptively
- Emit telemetry via **Feedback Injection Field (FIF)**
- Enforce **trust scores** per flow/link

📁 Refer: [`specs/ml_data_plane/`](../../specs/ml_data_plane/)

---

## 🏛️ Finite State Machines (FSMs)

Each ATROP node runs a protocol FSM controlling its behavior across phases:

1. `INIT` → node startup, identity validation
2. `DISCOVERY` → adjacency + zone mapping
3. `LEARN` → AI/ML engagement begins
4. `DECIDE` → route and zone policy decisions
5. `ENFORCE` → control→data handoff
6. `OBSERVE` → telemetry, anomaly watch
7. `FEEDBACK` → AI re-evaluation cycle
8. `CORRECT` → error handling, policy override

📁 Refer: [`specs/state_machines/`](../../specs/state_machines/)

---

## 🗺️ Hierarchical Topology Awareness

ATROP supports four routing cognition layers:

| Layer         | Scope                          | Role                                      |
|---------------|--------------------------------|-------------------------------------------|
| Global Tier   | Cross-domain / inter-AS        | SLA and intent federation                 |
| Domain Tier   | AS or data center zone         | Policy partitioning and enforcement       |
| ATZ Tier      | Metro/fabric/local cluster     | Real-time AI + ML decision autonomy       |
| Node Tier     | Individual router/switch       | Per-flow ML inference, fast reaction      |

📁 Refer: [`specs/protocol/`](../../specs/protocol/)

---

## 🧠 Key Packet Fields

| Field | Purpose |
|-------|---------|
| `NIV` | Node Identity Vector — cryptographically signed identity |
| `PIV` | Path Intelligence Vector — telemetry + inference data |
| `IDR` | Intent Descriptor — SLA/policy/context per flow |
| `FIF` | Feedback Injection Field — downstream feedback |

All ATROP packets (e.g., `DISCOVERY`, `DECISION`, `CORRECTION`, `OBSERVATION`, `SECURITY`) carry combinations of these headers for full-stack cognition.

📁 Refer: [`specs/packet_format/`](../../specs/packet_format/)

---

## 🛡️ Security Core Principles

- **Zero-Trust Adjacency Model**
- **Per-hop cryptographic validation**
- **Behavioral trust scoring**
- **Replay protection and session tokens**

📁 Refer: [`specs/security/`](../../specs/security/)

---

## ⚙️ Deployment & Integration Notes

- **Runs natively on NOS kernels** (no VM/container required)
- Supported on Cisco IOS-XR/NX-OS, JunOS, EOS, VRP, SONiC
- Deployable in:
  - Passive telemetry mode (brownfield)
  - Overlay advisory mode (interop with FRR/BGP/OSPF)
  - Native autonomous mode (greenfield)

📁 See also:
- [`daemon/control_plane/`](../../daemon/control_plane/)
- [`daemon/data_plane/`](../../daemon/data_plane/)
- [`daemon/ipc/`](../../daemon/ipc/)

---

## 📚 More Documentation

- [📜 Whitepaper (June 2025 Draft)](../whitepaper/ATROP_White_Paper_Draft_June2025.pdf)
- [📊 Diagrams and Topologies](../diagrams/README.md)
- [📏 Standards and Compliance](../standards/README.md)

---

_© Mahmoud Tawfeek, 2025. All rights reserved._
