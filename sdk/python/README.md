# 🐍 ATROP Python SDK

This module contains the **Python Software Development Kit (SDK)** for the **ATROP (Autonomous Topology-Optimized Routing Protocol)** project. It provides client-side libraries to interface with ATROP components, agents, and telemetry.

---

## 📦 Package Name

```
atrop-sdk
```

---

## 🧪 Development Setup

Install the SDK in **editable mode** so changes take effect without reinstalling:

```bash
pip install -e .
```

> Run this from within the `sdk/python/` directory or from project root using:
> ```bash
> pip install -e sdk/python/
> ```

---

## 🚀 Usage Example

```python
from atrop_sdk import say_hello

say_hello()
# Output: Hello from ATROP Python SDK!
```

---

## 📁 Directory Structure

```
sdk/python/
├── atrop_sdk/             # SDK Python package
│   ├── __init__.py
│   └── core.py
├── test_sdk.py            # Optional: test/demo script
├── setup.py               # Install configuration
└── README.md              # This file
```

---

## ✅ Features

- Lightweight Python client interface
- Modular structure (designed for future gRPC, telemetry, YANG binding support)
- Designed for cross-platform usage (Linux, WSL, Docker)

---

## 📚 Coming Soon

- gRPC bindings to ATROP IPC layer
- Model loader interface (telemetry + control)
- Auto-generated YANG models for configuration

---

## 🛠 Python Compatibility

- Python 3.7+
- Works in virtualenv, poetry, conda, or bare-metal installs

---

## 👤 Author

Mahmoud Tawfeek  
[GitHub: @Mahmoudtawfeekie2024](https://github.com/Mahmoudtawfeekie2024)

---

## 📜 License

This SDK is licensed under the [ATROP Project License](../../LICENSE).
