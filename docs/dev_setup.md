# ⚙️ ATROP Developer Setup Guide

This guide provides the full setup instructions and environment specifications required to build, test, and extend the ATROP Protocol codebase.

---

## 📦 Requirements

### 🧠 Python (for SDK, tests, stubs)

- Minimum version: **Python 3.8**
- Recommended: Use a virtual environment

Install dependencies:
```bash
pip install -r dev-requirements.txt
```

### ⚙️ C++ Toolchain

- Minimum: **g++ 9.0**
- Optional: `cmake 3.15+` (future support)
- Required: `make`

### 🛠 Protobuf / gRPC

- `protoc` version: **3.15+**
- `grpcio-tools` (Python): **1.42+**
- C++ gRPC plugin: `protoc-gen-grpc` (optional for full C++ IPC build)

---

## 🧪 Local Build Commands

Run from the project root:

```bash
make              # Build all daemon and SDK components
make test         # Run both Python and C++ tests
make clean        # Remove all build artifacts
```

---

## 🧪 Python SDK (Editable Mode)

Install:
```bash
pip install -e sdk/python/
```

Test:
```bash
pytest test/unit/
```

---

## 🧪 C++ Unit Tests

Ensure `libgtest-dev` is installed. Then:
```bash
make test-cpp
```

---

## 🐳 Docker Build (Optional)

To build in a clean container:

```bash
docker build -t atrop-dev .
docker run -it --rm atrop-dev
```

Use this if you don’t want to install toolchains locally.

---

## 🧩 Minimum Tool Versions

| Tool / Dependency      | Minimum Version | Notes                                 |
|------------------------|-----------------|----------------------------------------|
| Python                 | `3.8`            | For SDK, tests, gRPC, and CLI tools    |
| pip                    | `22.0`           | For dependency installation            |
| g++ (GNU Compiler)     | `9.0`            | For C++17 support                      |
| cmake (optional)       | `3.15`           | For future C++ builds if adopted       |
| protoc (protobuf)      | `3.15`           | For .proto to stub conversion          |
| grpcio-tools (Python)  | `1.42`           | For Python stub generation             |
| libgtest-dev / gtest   | `1.10`           | For C++ unit testing                   |
| make                   | `4.2`            | Required to run root Makefile          |
| Docker (optional)      | `20.10`          | For building portable environments     |

---

## 📂 Build Output Structure

- `/build/` → All compiled files
- `/sdk/grpc/build_py/` → Python gRPC stubs
- `/sdk/grpc/build_cpp/` → C++ gRPC stubs
- `/bin/` → (Reserved for future CLI utilities)

---

## 👤 Author

Mahmoud Tawfeek  
[GitHub: @Mahmoudtawfeekie2024](https://github.com/Mahmoudtawfeekie2024)

---

## 📜 License

This project is licensed under the [ATROP Project License](../LICENSE).
