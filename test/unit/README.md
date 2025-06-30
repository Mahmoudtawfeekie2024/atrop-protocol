# 🧪 Unit Test Discovery and Execution

This section outlines how unit tests in the ATROP project are structured, discovered, and executed using standard tools for Python and C++ environments.

---

## 🐍 Python Unit Tests

### 📂 Directory Structure

All Python unit tests are placed under:

```
test/
├── control_plane/
├── data_plane/
├── ipc/
├── telemetry/
└── __init__.py
```

Each test module follows this naming convention:
- Files must begin with `test_`
- Functions must begin with `test_`

Example:
```python
# test/control_plane/test_ai_decision.py

def test_policy_fallback_on_low_confidence():
    ...
```

### ▶️ How to Run

**Locally (dev):**
```bash
pytest test/
```

**In CI (GitHub Actions):**
Triggered automatically on push or PR to `main`. Results will appear in job logs and future HTML/JSON reporters.

---

## ⚙️ C++ Unit Tests

### 📂 Directory Structure

All C++ unit tests are under:

```
test/cpp/
├── fsm/
├── ipc/
├── parser/
└── CMakeLists.txt
```

### ▶️ How to Build & Run

**Build with CMake:**
```bash
cd test/cpp/
mkdir build && cd build
cmake ..
make
./runAllTests
```

GTest will automatically discover all tests compiled from sources that use:
```cpp
TEST(FSMTransitionTest, ValidStateChange) {
    ...
}
```

CI integration is planned in future workflows (`g++`, `cmake`, `gtest`).

---

## 🛠 Future Enhancements

- ✅ JSON and HTML test reports
- ✅ Integration with code coverage tools (e.g., `coverage.py`, `gcov`)
- ✅ Tag-based test selection (e.g., `@smoke`, `@regression`)

---

## 📦 Test Entry Points (CI)

GitHub Actions workflow:
```
.github/workflows/ci.yml
```

This file runs:
- Python tests via `pytest`
- Placeholder hooks for C++ builds
- CI logs include `warnings` for missing or failing tests during early stages

---
