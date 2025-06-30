# 🧪 ATROP Test Strategy

**Document Version:** 0.1  
**Maintainer:** Test Architect  
**Last Updated:** 25 June 2025  
**Applies To:** Foundational protocol components during initial implementation

---

## 🎯 Purpose

This strategy defines the multi-layered test approach for the initial implementation of the ATROP protocol. Its goal is to ensure all protocol components — including control and data planes, IPC, FSMs, and telemetry — are tested early, modularly, and continuously. This supports test-driven development, fault isolation, and long-term maintainability across diverse deployment environments.

---

## 🧱 Scope

This test strategy applies to the core components of ATROP, focusing on validating behavior, interoperability, and resilience under both expected and anomalous conditions.

The testing framework will cover:

- **Finite State Machines (FSMs):** Represent the node-level behavioral logic of ATROP, managing key states such as INIT, DISCOVERY, LEARN, ENFORCE, FEEDBACK, and CORRECT. These are essential for autonomous topology awareness and self-healing.

- **AI-Based Control Plane:** Performs policy-driven decision-making using topology intelligence, graph analysis, and reinforcement learning. Tests will evaluate AI route decisions, fallback logic, and intent enforcement.

- **ML-Augmented Data Plane:** Executes real-time per-packet inference to classify flows, apply trust scoring, and emit Feedback Injection Fields (FIF). Coverage includes inference correctness, telemetry generation, and integration with AI feedback loops.

- **Inter-Process Communication (IPC):** Enables secure and efficient communication between the control plane, data plane, and auxiliary modules. Testing covers message structure, queue behavior, error handling, and protocol synchronization.

- **Telemetry and Feedback Loop:** Validates the generation, propagation, and consumption of telemetry fields (PIV, FIF, IDR), ensuring data plane behavior accurately informs AI model updates and zone decisions.

- **Legacy Compatibility and Integration:** Ensures ATROP can coexist with or interoperate across traditional protocols (e.g., OSPF, BGP, MPLS). Tests validate correct redistribution, policy translation, and hook behavior for brownfield deployment.

This strategy supports incremental validation of ATROP’s unique autonomous behavior while providing a stable foundation for integration with legacy networks and emerging infrastructure.

---

## 🧪 Test Layers

| Layer            | Purpose                                                          | Target Components                          | Tools                 |
|------------------|------------------------------------------------------------------|--------------------------------------------|------------------------|
| Unit Testing      | Validate isolated logic, I/O, and edge cases                     | `daemon/*`, `sdk/*`, `specs/*`             | `pytest`, `gtest`      |
| FSM Simulation    | Test state transitions, anomalies, correction flows              | `test/fsm-simulations/`                    | Custom FSM sim engine  |
| Integration Tests | Validate end-to-end control/data plane communication             | `test/integration/`, `daemon/ipc/`         | Mininet, FRRouting     |
| Telemetry Tests   | Validate telemetry generation, propagation, and interpretation   | `daemon/data_plane/`, `tools/telemetry/`   | FIF parser, JSON log   |

---

## 🧩 Module-Test Mapping

| Module                  | Test Type            | Scope                                                                 |
|-------------------------|----------------------|-----------------------------------------------------------------------|
| `daemon/control_plane/` | Unit, Integration    | AI model behavior, policy decisioning                                |
| `daemon/data_plane/`    | Unit, Integration    | ML flow classification, FIF generation                               |
| `daemon/ipc/`           | Unit, Integration    | IPC protocol messages, agent synchronization                         |
| `specs/*`               | Unit                 | PIV, FIF, IDR, NIV parsing                                            |
| `test/fsm-simulations/` | FSM Simulation       | INIT → DISCOVERY → ENFORCE → FEEDBACK transitions                    |
| `test/integration/`     | Integration, Legacy  | FRRouting interop, AI + ML handoff                                   |

---

## 🛠️ Toolchain

| Tool        | Use Case                                         |
|-------------|--------------------------------------------------|
| `pytest`    | Python unit tests (control, ML, telemetry logic) |
| `gtest`     | C++ FSM and protocol logic validation            |
| `Mininet`   | Simulated ATZ topologies                         |
| `FRRouting` | Legacy interop validation                        |
| `FSM Sim`   | Custom test engine for zone behavior             |
| `Wireshark` | Packet-level inspection of FIF/PIV/IDR           |
| `ci.yml`    | GitHub Actions test automation                   |

---

## 🎯 Coverage Targets

| Area                    | Goal     |
|-------------------------|----------|
| FSM Transition Logic    | ≥ 85%    |
| Control Plane Decision  | ≥ 80%    |
| ML Inference Path       | ≥ 80%    |
| Packet Header Parsing   | 100%     |
| Telemetry FIF Propagation | Sample-verified |
| IPC + Queue Handling    | ≥ 90%    |

---

## 📦 Deliverables

- `docs/test_strategy.md` (this document)
- `test/unit/` coverage enforcement
- `test/fsm-simulations/` auto-triggers
- `test/integration/` CI hooks with scenario IDs
- Telemetry validation harness (`tools/telemetry`)
- CI badges + HTML reports

---

## ✅ Acceptance Criteria

- [ ] Testing layers are clearly defined and aligned with protocol components
- [ ] FSM simulation engine is included and functional
- [ ] CI triggers unit and integration tests on all commits
- [ ] Toolchain setup is documented and portable
- [ ] Strategy validated by protocol, AI, and ML leads

---

## 🔗 Related Work

- FSM implementation and behavior specification
- AI model engine and intent processing logic
- ML classification path and telemetry injection
- IPC framework and agent lifecycle design
- CI/CD infrastructure and code coverage reporting

---

## 👥 Review & Validation

| Role             | Reviewer      |
|------------------|---------------|
| Protocol Lead    | ✅ Required   |
| AI Architect     | ✅ Required   |
| ML Developer     | ✅ Required   |
| QA/Test Lead     | ✅ Required   |

---
