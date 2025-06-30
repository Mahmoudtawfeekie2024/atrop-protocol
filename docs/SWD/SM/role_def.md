# 🧑‍🔬 SME Role Definitions for ATROP

## 1. **Protocol Logic & FSM**

**Scope:**

* Define the ATROP finite state machines (INIT → DISCOVERY → … → CORRECT → EXIT)
* Implement per-node behavior transitions and state logic
* Design message handling for Discovery, Decision, Observation, Correction packets
  **Keywords:** `state_machines/`, `daemon/control_plane/`, `specs/protocol/`
  **SME Profile:** Protocol engineer or routing architect with FSM and low-level protocol experience

---

## 2. **AI Control Plane (GNN, Policy Enforcement)**

**Scope:**

* Build AI model engine (e.g., Graph Neural Network or Reinforcement Learning)
* Manage intent processing and policy-to-routing translation
* Handle federated learning integration and fallback logic
  **Keywords:** `models/pretrained/`, `specs/ai_control_plane/`, `daemon/control_plane/`
  **SME Profile:** AI/ML researcher with GNN/RL experience, ideally in graph-topology or network inference

---

## 3. **ML Data Plane (Inference, Telemetry)**

**Scope:**

* Implement inline inference agent for flow classification
* Assign per-flow trust scores and generate Feedback Injection Fields (FIF)
* Manage lightweight ML models (e.g., Decision Trees, CNNs) and telemetry feedback
  **Keywords:** `daemon/data_plane/`, `specs/ml_data_plane/`, `test/unit/ml_data_plane/`
  **SME Profile:** ML engineer with experience in real-time inference, telemetry, or embedded ML

---

## 4. **Platform Integration (eBPF, Netlink, systemd)**

**Scope:**

* Connect ATROP services to system hooks: Netlink sockets, eBPF, kernel modules
* Ensure native integration with Linux-based NOS platforms
* Manage daemon lifecycle via systemd and enforce security profiles
  **Keywords:** `daemon/ipc/`, `examples/ubuntu-integration/`, `tools/`
  **SME Profile:** Systems engineer or Linux kernel developer with networking stack familiarity

---

## 5. **SDK/API Layer (Python, C++, gRPC, Telemetry)**

**Scope:**

* Build SDK libraries and developer APIs (Python, C++, gRPC)
* Define interfaces for model loader, telemetry, and external integrations
* Support vendor hooks and observability extensions
  **Keywords:** `sdk/python/`, `sdk/c++/`, `sdk/grpc/`, `sdk/telemetry/`
  **SME Profile:** API/backend engineer with multi-language SDK and gRPC/YANG experience

---

## 6. **Testing & CI**

**Scope:**

* Establish unit, integration, and FSM simulation testing infrastructure
* Integrate CI triggers for GitHub Actions and regression testing
* Define test coverage, metrics, and reporting outputs
  **Keywords:** `test/`, `.github/workflows/`, `tools/validator/`
  **SME Profile:** QA/Test automation engineer with CI/CD pipelines and network testbed experience

---

## 7. **Documentation & Standards Alignment**

**Scope:**

* Maintain architecture docs, IETF-style specifications, and RFC alignment
* Track IETF/IEEE standards compliance (e.g., RFC 3552, 6811, IEEE 802.1X)
* Prepare whitepaper drafts, markdown specs, and contribution templates
  **Keywords:** `docs/architecture/`, `docs/standards/`, `docs/whitepaper/`, `README.md`
  **SME Profile:** Technical writer or protocol expert familiar with open standards and doc tooling

---
