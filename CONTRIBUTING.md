
# 🌐 Contributing to ATROP

Thank you for your interest in contributing to **ATROP** — the Autonomous Topology-Optimized Routing Protocol.

ATROP is a conceptual AI/ML-native routing architecture designed for vendor-neutral, scalable, and secure deployment across all network domains. This repository hosts research, design artifacts, specifications, and early test frameworks — not production code.

We welcome engineers, researchers, architects, vendors, and students to contribute ideas, improvements, and collaboration.

---

## ✅ What You Can Contribute

This is a **design-stage protocol**, so contributions are **not limited to code**. You can help by:

- 💡 Suggesting enhancements to protocol state machines, headers, or behavior logic
- 📐 Designing or editing diagrams (FSMs, feedback loops, learning pipelines)
- 🧠 Proposing AI/ML model optimizations for control or data plane behavior
- ✍️ Improving documentation (README, whitepapers, spec formatting)
- 📦 Providing test cases, Mininet topologies, or FRRouting integration
- 🗣 Sharing use cases, deployment models, or vendor integration concerns
- 🔒 Suggesting improvements to the trust/security model

---

## 🧭 Guidelines

### 1. 📂 Fork This Repository
Create your own copy to propose changes:
```
git clone https://github.com/Mahmoudtawfeekie2024/atrop-protocol.git
```

### 2. 🛠 Work in a New Branch

Use a descriptive branch name:

```
git checkout -b fix-fsm-transition
```

### 3. 📥 Make Your Changes

* Keep file structure clean and consistent.
* Use Markdown or PlantUML for diagrams.
* If modifying AI/ML logic, describe model type, input/output, and use case.
* Include comments for all technical additions.

### 4. ✅ Test and Document

If you add code (e.g., daemon or model logic):

* Add unit or integration tests in `/test`
* Update README or specs with your change

### 5. 📬 Submit a Pull Request

Push to your fork and open a PR:

```
git push origin fix-fsm-transition
```

When submitting:

* Use a clear title and summary
* Link to related issue(s) if applicable
* Mark whether it’s **experimental**, **conceptual**, or **ready for review**

---

## 📂 Repo Structure Overview

| Folder      | Purpose                                  |
| ----------- | ---------------------------------------- |
| `/specs`    | Protocol logic, packet format, FSMs      |
| `/sdk`      | Developer tools and interface examples   |
| `/daemon`   | Experimental routing agents              |
| `/models`   | ML/AI models for inference or training   |
| `/examples` | Mininet, FRR, Ubuntu integration         |
| `/docs`     | Diagrams, architecture docs, whitepapers |
| `/test`     | Simulations, unit/integration testing    |

---

## 🤝 Attribution & IP Note

ATROP is © 2025 by Mahmoud Tawfeek.
This project is **conceptual** and contributions are considered **collaborative input to a non-commercial, early-stage protocol design**.

If you're contributing on behalf of a vendor, university, or research lab, please add attribution in your PR description.

---

## 🔐 Code of Conduct

All contributors must follow our [Code of Conduct](./CODE_OF_CONDUCT.md). Be respectful, collaborative, and constructive.

---

## 📫 Questions or Suggestions?

* Open an [Issue](https://github.com/yourname/atrop-protocol/issues)
* Use GitHub Discussions if enabled
* Contact Mahmoud Tawfeek directly for vendor collaborations or strategic contributions

Together, we’re building a smarter, autonomous routing future.

---

## 🧪 Running Lint and Tests Locally

Before submitting a pull request, contributors must validate code quality **locally** using the same tools that CI runs.

---

### 🧼 Python Lint (ruff)

Run linting on all Python modules:

```bash
pip install ruff
ruff check daemon/ sdk/ tools/ test/ models/
```

---

### 🧪 Python Unit Tests

Run all unit tests with `pytest`:

```bash
pip install pytest
export PYTHONPATH=$(pwd)/sdk/python
pytest test/unit/
```

---

### 🧼 C++ Lint (clang-tidy)

Install and run C++ linter:

```bash
sudo apt install clang-tidy
clang-tidy daemon/control_plane/*.cpp
clang-tidy daemon/ipc/*.cpp
```

---

### 🧪 C++ Unit Tests

Build and test with `cmake` and `ctest`:

```bash
sudo apt install cmake g++
mkdir -p build
cd build
cmake ..
make
ctest --output-on-failure
```

---

### ✅ Contributor CI Expectations

- All PRs must pass CI before merging.
- Code must be clean (no lint errors).
- All existing and new tests must pass.
- PRs should be small, scoped, and reviewed by at least one reviewer.
- `main` is a protected branch — direct pushes are not allowed.

For detailed build and test flow, see the [README.md](./README.md) or CI logs under the **Actions** tab.
