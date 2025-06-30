# 🖼️ ATROP Diagram Index

This directory contains all visual assets, sequence flows, and architecture diagrams used to describe and communicate the internal behavior of **ATROP** (Autonomous Topology-Optimized Routing Protocol).

These diagrams are essential for onboarding contributors, explaining protocol logic, vendor integration, and RFC-standardization clarity.

---

## 📂 Directory Structure

| Folder | Description |
|--------|-------------|
| `fsm/` | Protocol state machines (per-node FSM, zone sync, correction logic) |
| `learning/` | AI/ML feedback loops, deferred vs real-time inference diagrams |
| `topology/` | ATZ hierarchy, inter-domain routing behavior, zone abstraction |
| `deployment/` | Edge/cloud deployments, brownfield overlays, vendor modes |
| `security/` | Zero-trust trust domain enforcement and identity flows |
| `interop/` | Integration with BGP, MPLS, Segment Routing, FRRouting |
| `simulation/` | Testing diagrams for Mininet, Ubuntu labs, and FSM triggers |

---

## 🧬 Diagram Format Standards

All diagrams are written in one of the following formats:

- ✅ **PlantUML** (`.puml`) — for editable diagrams (preferred)
- ✅ **Markdown-linked PNG/SVG** — exported diagrams with links to source `.puml`
- ✅ **PDFs** — used in external whitepaper outputs or slide decks

---

## 🧠 Key Topics Visualized

### 1. Protocol FSM Diagrams (`fsm/`)
- `global_fsm_overview.puml` – Full protocol state machine per node
- `zone_sync_state.puml` – Zone-wide FSM behavior during correction events
- `fallback_path_recovery.puml` – From SLA violation to route correction

### 2. Learning Flow (`learning/`)
- `ai_feedback_loop.puml` – Data-plane FIF → AI → route adjustment
- `real_vs_deferred_learning.puml` – Edge inference vs offline training

### 3. Topology Hierarchy (`topology/`)
- `atz_hierarchy_stack.puml` – Node → Zone → Domain → Global Tier abstraction
- `interzone_boundary_behavior.puml` – Cross-zone intent and summarization

### 4. Security Architecture (`security/`)
- `trust_domain_negotiation.puml` – Adjacency verification handshake
- `niv_ssip_validation.puml` – Node identity & secure session flow

### 5. Deployment (`deployment/`)
- `vendor_stack_mapping.png` – Cisco/Juniper/EOS/NOS stack overlay
- `brownfield_mode_flow.puml` – Passive/advisory mode decision handling

---

## 🔧 Tooling and Contribution Guidelines

To generate or edit diagrams:

1. Install PlantUML or use [PlantUML Online Editor](https://plantuml.com/plantuml)
2. Use the `@startuml`/`@enduml` block syntax
3. Include `.puml` + `.png` (exported) in the respective folder
4. Reference any diagram inside markdown via:
   ```markdown
   ![FSM Overview](fsm/global_fsm_overview.png)
   ```

📁 Template examples are provided in each subfolder.

---

## 🧩 Related Spec References

| Diagram Topic | Related Spec |
|---------------|--------------|
| FSM & States | [`specs/state_machines/`](../../specs/state_machines/) |
| AI/ML Flow | [`specs/ai_control_plane/`](../../specs/ai_control_plane/), [`specs/ml_data_plane/`](../../specs/ml_data_plane/) |
| Packet Headers | [`specs/packet_format/`](../../specs/packet_format/) |
| Security | [`specs/security/`](../../specs/security/) |
| Interop & Vendors | [`examples/frr-integration/`](../../examples/frr-integration/) |

---

## 🚧 Work in Progress

As of now, the following diagrams are **planned but pending**:

- ATZ rebalancing loop (`learning/`)
- MPLS + ATROP feedback injection (`interop/`)
- Mininet emulation FSM test plan (`simulation/`)

If you'd like to contribute, open a PR or issue using the templates in `.github/`.

---

_© Mahmoud Tawfeek, 2025. All rights reserved._
