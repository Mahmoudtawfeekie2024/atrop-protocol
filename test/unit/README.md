# 🧪 ATROP Testing Overview

This document explains the testing infrastructure for the ATROP project, including Python and C++ unit test setup, execution instructions, and how to add new tests. The testing system is designed to support CLI, CI, and coverage workflows.

---

## 🗂 Folder Structure

```
test/
├── unit/                 # Python & C++ unit tests
│   ├── data_plane/       # Tests for daemon/data_plane
│   ├── sdk/              # Tests for Python SDK (atrop_sdk)
│   ├── c++/              # C++ unit tests (GTest)
│   ├── test_demo.py      # Example test
│   ├── __init__.py
│   └── README.md
├── integration/          # Multi-module or system-level integration tests
├── fsm-simulations/      # FSM scenario simulation and replay tests
```

---

## 🐍 Python Unit Tests

### 🔧 Requirements

- Python ≥ 3.8
- `pytest` (installed via `dev-requirements.txt`)

### ▶️ How to Run

**Locally:**

```bash
pytest test/unit/
```

**Via Makefile:**

```bash
make test-python
```

**In CI:**

Triggered automatically via `.github/workflows/ci.yml` on every push/PR.

---

## ⚙️ C++ Unit Tests (GTest)

### 🔧 Requirements

- g++ ≥ 9
- `libgtest-dev` (install via `sudo apt install libgtest-dev`)
- `make` (default) or `cmake` (optional)

### ▶️ How to Build & Run

**Via Makefile:**

```bash
make test-cpp         # Builds and runs GTest suite
make test             # Runs both Python + C++ tests
```

**Via CMake (optional path):**

```bash
cd test/unit/c++/
mkdir build && cd build
cmake ..
make
ctest --verbose
```

---

## 🧪 Adding New Unit Tests

### ✅ Python

- Place test files under `test/unit/<module>/`
- Filename must start with `test_`
- Each test function must start with `test_`

**Example:**

```python
# test/unit/sdk/test_core.py
def test_basic_import():
    from sdk.python.atrop_sdk import core
    assert core is not None
```

### ✅ C++

- Add `.cpp` test files to `test/unit/c++/`
- Register test in `Makefile` via `GTEST_SRC` or just place in directory (auto-built)
- Use GTest macros like:

```cpp
TEST(SDKTest, InitSuccess) {
    ASSERT_TRUE(true);
}
```

---

## 📈 Code Coverage

**To generate a C++ coverage report:**

```bash
make coverage-cpp
xdg-open build/coverage.html
```

**Planned:** Python coverage via `coverage.py`

---

## 🧪 CI Integration

Test workflows are defined in:

```text
.github/workflows/ci.yml
```

They run on every commit and PR:
- ✅ Python tests via `pytest`
- ✅ C++ tests via `g++` and `GTest`
- ✅ Unified via `make test`

---

## 🛠 Future Enhancements
- [x] HTML + JSON test reports
- [x] Code coverage with `gcovr`
- [ ] Test tags for selective runs (`@smoke`, `@regression`)
- [ ] Integration tests for FSM + real-time topology events

---

📌 **Contributing Tests?**  
See `CONTRIBUTING.md` for guidelines.
