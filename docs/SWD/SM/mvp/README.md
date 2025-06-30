# 🧩 ATROP MVP Scope & Governance Overview

This document defines the **Minimum Viable Product (MVP)** for the ATROP protocol stack and outlines the **governance policies** guiding early contributions, standards alignment, and open-source community practices.

---

## 🚀 MVP Scope (Phase 0 Definition)

The MVP release focuses on validating ATROP’s **core protocol behavior**, **AI/ML integration**, and **cross-component messaging**, deployable on real Linux-based NOS environments.

### 🎯 MVP Functional Components

| Layer        | Scope |
|--------------|-------|
| ✅ Protocol FSM | Node lifecycle states: INIT → CORRECT |
| ✅ Control Plane AI | GNN or RL model for path decisions |
| ✅ Data Plane ML | Flow classification, trust scoring, FIF telemetry |
| ✅ IPC Layer | Secure messaging between daemon agents |
| ✅ Minimal SDK | Python/gRPC-based developer interface |
| ✅ Unit/Integration Testing | CI-triggered validation for FSM, model outputs, packet flow |
| ✅ Ubuntu Deployment | Systemd-compatible services for native install (no VM/container) |

📁 See also: [`docs/architecture/`](../architecture/), [`daemon/`](../../daemon/)

---

## ⚙️ Supported Modes (MVP)

| Mode | Description |
|------|-------------|
| 🧪 Passive Observe | Learn topology & behavior, no control injection |
| 🧠 Advisory Mode | Suggest paths via AI, fallback to legacy protocols |
| 🛣️ ATZ Native Mode | Enforce routes in Autonomous Topology Zones (FSM + AI + ML) |

---

## 📏 Governance Alignment

ATROP development is community-governed but protected by clear rules:

### ✅ Licensing

- 📜 License: [MIT License](../../LICENSE)
- 📎 Copyright: © Mahmoud Tawfeek
- 🤝 Compliant with IETF open standard contribution policies

### ✅ Contributor Rules

| File | Purpose |
|------|---------|
| [`CODE_OF_CONDUCT.md`](../../CODE_OF_CONDUCT.md) | Contributor behavior and enforcement |
| [`CONTRIBUTING.md`](../../CONTRIBUTING.md) | Pull request and issue guidelines |
| [`SECURITY.md`](../../docs/standards/) | Reporting vulnerabilities and responsible disclosure |
| [`LICENSE`](../../LICENSE) | Legal use, redistribution, and reuse terms |

---

## 🔒 Vendor-Aware, Standard-Ready

| Aspect | Status |
|--------|--------|
| Cisco, Juniper, Arista profiles | ✅ Covered in vendor playbooks |
| IETF/IEEE alignment | ✅ Sectioned in whitepaper and docs |
| GitHub Open Source Baseline | ✅ `.github/`, workflows, governance reviewed |
| Whitepaper, Diagrams, Specs | ✅ Staged in `/docs/` for RFC-style reading |
| MVP Deployment Targets | ✅ Mininet, Ubuntu (systemd), FRR integration |

---

## 📅 Planned MVP Completion

| Phase | Target Completion |
|-------|--------------------|
| MVP Protocol Engine | ✅ Phase 2 |
| AI/ML Decision + Feedback | ✅ Phases 3 & 4 |
| IPC + Daemon Services | ✅ Phase 5 |
| Testing + CI | ✅ Phases 6 & 7 |
| Initial Docs | ✅ T0-10 (this doc + others)

---

## 🛠️ How to Propose Changes to MVP Scope

1. Open an issue labeled `mvp-scope-review`
2. Use the `docs/mvp/` folder for versioned MVP proposals
3. All changes must be reviewed by the Protocol Architect & Product Owner

---

_© Mahmoud Tawfeek, 2025. All rights reserved. MVP v0.1 as of June 30, 2025._
