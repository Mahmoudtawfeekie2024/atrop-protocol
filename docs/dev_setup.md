
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


## 🧾 Configuration File Usage

ATROP supports JSON and YAML configuration files that are automatically loaded at runtime by each daemon via the internal `ConfigLoader`.

### ✅ Supported Formats

- `.json` (preferred)
- `.yaml` / `.yml` (optional)

### 📍 Default Lookup Paths

Each daemon searches for configuration in this order:

1. File path from environment variable (e.g., `ATROP_CONFIG_PATH`)
2. Default location: `config.json` or `config.yaml` in working directory
3. Hardcoded fallback defaults

### 🧠 Structure Expectations

Configuration keys follow a **dot notation** flattened schema:

```json
{
  "module.port": 9090,
  "module.timeout": 30,
  "paths.log_dir": "/var/log/atrop",
  "environment.mode": "dev"
}
```

The same applies to YAML:

```yaml
module.port: 9090
module.timeout: 30
paths.log_dir: "/var/log/atrop"
environment.mode: "dev"
```

### 🛑 Required Fields

Some daemons require specific fields:

| Field            | Description                     |
|------------------|---------------------------------|
| `module.port`    | Port number for server/listener |
| `paths.log_dir`  | Directory to write logs         |

Missing required fields trigger either:
- fallback to a default, or
- error exit (based on daemon logic)

### ⚠️ Validation Behavior

- If config is **invalid JSON/YAML**, the process fails.
- If config is **missing**, daemons fallback to embedded defaults.
- All configs are validated on startup and logged.

### 📁 Example Files

Sample configs live under:

```bash
test/unit/sdk/config/
```
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

---

### 🐳 Docker Build and Run Instructions

To build the container image:

```bash
docker build -t atrop-dev .
```

To run interactively with local volumes mounted:

```bash
docker run -it --rm   -v $(pwd)/daemon:/app/daemon   -v $(pwd)/sdk:/app/sdk   -v $(pwd)/test:/app/test   -v $(pwd)/models:/app/models   -v $(pwd)/docs:/app/docs   atrop-dev
```

---

### 🧷 Required Dockerfile Dependencies

The container installs:

- Python 3.10, pip, virtualenv, `pytest`, `black`, `mypy`, `grpcio`
- g++, make, cmake, libgtest-dev, bash-completion
- Developer tools: `curl`, `htop`, `tcpdump`, `net-tools`

> ✅ All tools are preinstalled when you build the image via `Dockerfile`

---

### 🧠 VS Code Remote Container (`.devcontainer/`) Support

You can launch the ATROP Dev Container in VS Code using:

```
.devcontainer/devcontainer.json
```

**Steps**:
1. Open the ATROP repo in VS Code.
2. Use Command Palette → “Reopen in Container”.
3. It mounts:
   - `daemon/`, `sdk/`, `test/`, `models/`, and `docs/` into `/app/`
4. The shell runs with developer aliases (`ll`, `gs`, `cdsdk`, `atest`)

---

### 🗃 Volume Mount Structure

When running the container, ensure the following folders are mounted from host to container:

| Host Folder    | Container Path     |
|----------------|--------------------|
| `daemon/`      | `/app/daemon`      |
| `sdk/`         | `/app/sdk`         |
| `test/`        | `/app/test`        |
| `models/`      | `/app/models`      |
| `docs/`        | `/app/docs`        |

This ensures full source mapping and live development support.

---

### 🧰 Common Errors & Troubleshooting

| Problem                                  | Resolution                                                               |
|------------------------------------------|---------------------------------------------------------------------------|
| `pytest` not found                       | Ensure `dev-requirements.txt` is installed or container is built         |
| `protoc` or `grpc_cpp_plugin` missing    | Confirm Dockerfile completed successfully — retry `docker build`         |
| `/app/daemon not found` in container     | Make sure `-v $(pwd)/daemon:/app/daemon` is included in `docker run`     |
| `clang-format` missing                   | Add `apt install clang-format` or run outside container                  |
| Tests show “no tests collected”          | Make sure test filenames start with `test_` and functions use `def test_`


---

## 🧪 Containerized Dev Environment (Docker)

### 🐳 Docker Build and Run Instructions

To build the container image:

```bash
docker build -t atrop-dev .
```

To run interactively with local volumes mounted:

```bash
docker run -it --rm \
  -v $(pwd)/daemon:/app/daemon \
  -v $(pwd)/sdk:/app/sdk \
  -v $(pwd)/test:/app/test \
  -v $(pwd)/models:/app/models \
  -v $(pwd)/docs:/app/docs \
  atrop-dev
```

---

### 🧷 Required Dockerfile Dependencies

The container installs:

- Python 3.10, pip, virtualenv, `pytest`, `black`, `mypy`, `grpcio`
- g++, make, cmake, libgtest-dev, bash-completion
- Developer tools: `curl`, `htop`, `tcpdump`, `net-tools`

> ✅ All tools are preinstalled when you build the image via `Dockerfile`

---

### 🧠 VS Code Remote Container (`.devcontainer/`) Support

To open this repo in a dev container via VS Code:

1. Open the repo in **VS Code**.
2. Use Command Palette → “**Reopen in Container**”.
3. Ensure you have `.devcontainer/devcontainer.json` in place.

Mounted volumes inside the container:
- `daemon/` → `/app/daemon`
- `sdk/` → `/app/sdk`
- `test/` → `/app/test`
- `models/` → `/app/models`
- `docs/` → `/app/docs`

Shell launches with common developer aliases preloaded (`ll`, `gs`, `cdsdk`, `atest`, etc.)

---

### 🗃 Volume Mount Structure

| Host Folder    | Container Path     |
|----------------|--------------------|
| `daemon/`      | `/app/daemon`      |
| `sdk/`         | `/app/sdk`         |
| `test/`        | `/app/test`        |
| `models/`      | `/app/models`      |
| `docs/`        | `/app/docs`        |

---

### 🧰 Common Errors & Troubleshooting

| Problem                                  | Resolution                                                               |
|------------------------------------------|---------------------------------------------------------------------------|
| `pytest` not found                       | Ensure `dev-requirements.txt` is installed or container is built         |
| `protoc` or `grpc_cpp_plugin` missing    | Confirm Dockerfile completed successfully — retry `docker build`         |
| `/app/daemon not found` in container     | Make sure volume mounts are present using `-v` in `docker run`           |
| `clang-format` missing                   | Add `apt install clang-format` or run it from host OS                    |
| Tests show “no tests collected”          | Make sure test filenames start with `test_` and functions use `def test_`|

