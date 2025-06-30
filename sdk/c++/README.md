# ⚙️ ATROP C++ SDK

This directory contains the **C++ Software Development Kit (SDK)** for the ATROP protocol. It provides low-level interfaces and APIs for integrating C++ applications with ATROP control and data planes.

---

## 🛠 Requirements

- C++17 compatible compiler (`g++`, `clang++`, etc.)
- Make (or CMake, depending on your setup)
- Linux, WSL, or MinGW/MSYS2 on Windows

---

## 📁 Directory Layout

```
sdk/c++/
├── main.cpp       # Example or entry point
├── api.cpp        # Implementation of SDK functions
├── api.h          # Header file for SDK interface
└── README.md      # This file
```

---

## 🚀 Build Instructions

Assuming you're in the **project root**, and using the `Makefile` provided:

```bash
make            # Builds all binaries into /build/
./build/sdk_cpp_demo
```

If you want to build only the C++ SDK part:

```bash
make sdk_cpp_demo
```

> Output binary: `build/sdk_cpp_demo`

---

## ✅ Features

- Simple and modular design for core ATROP integration
- Extendable for gRPC hooks, IPC integration, telemetry stubs
- Aligned with `daemon/` structure and control/data plane services

---

## 📚 Coming Soon

- gRPC-based C++ interface for ATROP daemon interaction
- Packet/flow abstractions for protocol-level automation
- Cross-platform library packaging (static or dynamic)

---

## 🧪 Test

You can run the binary to test:

```bash
./build/sdk_cpp_demo
```

Expected output:

```
ATROP SDK C++ Demo started.
Hello from ATROP SDK C++ API!
```

---

## 👤 Author

Mahmoud Tawfeek  
[GitHub: @Mahmoudtawfeekie2024](https://github.com/Mahmoudtawfeekie2024)

---

## 📜 License

This SDK is licensed under the [ATROP Project License](../../LICENSE).
