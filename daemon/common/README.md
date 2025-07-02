# 🧾 ATROP Logging Architecture – `daemon/common/`

> 🧠 Intelligent Logging | 📂 Structured Output | 🐞 Debug-First Design

This module defines ATROP’s **unified logging mechanism**, built to serve **modular daemons**, **multi-format pipelines**, and **configurable outputs** across the **Control Plane** and **Data Plane** domains.

It integrates with the ATROP Configuration Loader to offer **context-aware log formatting**, **per-module log isolation**, and **support for both JSON and plain-text output** — all essential for ATROP’s observability and troubleshooting infrastructure.

---

## 🔧 Purpose

The `logger.[hpp|cpp]` component provides:

- ✅ Centralized and consistent logging API for all daemon modules
- 🧩 Configurable output: supports text and JSON
- 🗂 Automatic log file creation per role (`atrop-control.log`, `atrop-data.log`, etc.)
- 🧪 Integration with unit tests, CI environments, and container logs
- 🧠 Smart log-level control from runtime config (YAML/JSON)

---

## 🧬 Logger Behavior

The logger initializes once per daemon instance via `init_logger(...)` and attaches its behavior dynamically depending on loaded config.

### Supported Fields from Config:

| Field              | Type    | Default          | Description                          |
|--------------------|---------|------------------|--------------------------------------|
| `paths.log_dir`    | string  | `./logs/`        | Directory where logs are written     |
| `logger.format`    | string  | `"text"`         | `"json"` or `"text"`                 |
| `logger.level`     | string  | `"info"`         | `debug`, `info`, `warn`, `error`     |
| `logger.file`      | string  | `"atrop.log"`    | Filename to use for log output       |
| `environment.mode` | string  | `"dev"`          | Affects verbosity in future roadmap  |

---

## 💡 Example: Text Output

```
[2025-07-02 17:23:04] [INFO] [ATROP.Control] Logger initialized from 'config.yaml'
[2025-07-02 17:23:04] [INFO] [ATROP.Control] Selected Config: Port=9090 Timeout=30
```

## 💡 Example: JSON Output

```
{"ts":"2025-07-02 17:23:04","level":"INFO","name":"ATROP.Control","msg":"Logger initialized from config.yaml"}
{"ts":"2025-07-02 17:23:04","level":"INFO","name":"ATROP.Control","msg":"Selected Config: Port=9090 Timeout=30"}
```

---

## 🧪 Unit Testing Support

Logger is validated under:

- `test/unit/logger/test_logger.py`
- `test/unit/logger/test_logger.cpp`

You can run them with:

```bash
pytest test/unit/logger/test_logger.py -v
# Or
ctest --output-on-failure -R logger
```

---

## 📁 Files in This Module

| File             | Description                                      |
|------------------|--------------------------------------------------|
| `logger.hpp`     | Public logger API and format declarations        |
| `logger.cpp`     | Implementation using spdlog and format hooks     |
| `logger.py`      | Python logger (used for SDK tests & fallback)    |

---

## 🛠 Dependencies

- `spdlog` (via vcpkg or system)
- `nlohmann-json` (for config parsing)
- ATROP config loader (`config_loader.hpp`)

---

## 🧬 Roadmap for Logging

- [ ] Log rotation
- [ ] Syslog / journald stream support
- [ ] gRPC telemetry log push
- [ ] Structured tracing metadata (eventid, zone, hop)

---

## 🧑‍💻 Author

Mahmoud Tawfeek  
[GitHub](https://github.com/Mahmoudtawfeekie2024) • [LinkedIn](https://www.linkedin.com/in/mahmoud-tawfeek-5a790b363/)

---

> *“If ATROP speaks, the logger listens.”*
