# 🔌 ATROP gRPC Interface

This directory contains the **gRPC service definitions** (`.proto` files) for the ATROP protocol and the Makefile-based automation to generate gRPC stubs in both **Python** and **C++**.

---

## 📁 Directory Structure

```
sdk/grpc/
├── atrop.proto          # gRPC service definition
├── build_py/            # Generated Python stubs
├── build_cpp/           # Generated C++ stubs
├── README.md            # This file
```

---

## 🧱 Prerequisites

Ensure the following tools are installed:

### 🔧 Protocol Buffers Compiler

```bash
sudo apt install protobuf-compiler
```

### 🐍 Python gRPC Tools

```bash
pip install grpcio grpcio-tools
```

### ⚙️ C++ gRPC Tools

```bash
sudo apt install grpc-compiler libgrpc++-dev
```

---

## 🛠 Generating gRPC Stubs

From the root of the ATROP repository:

### 🔄 Full Stub Generation

```bash
make generate-grpc-stubs
```

This will produce:

- Python stubs in: `sdk/grpc/build_py/`
- C++ stubs in: `sdk/grpc/build_cpp/`

### 🐍 Python-Only

```bash
make generate-grpc-py
```

### ⚙️ C++-Only

```bash
make generate-grpc-cpp
```

---

## 🧹 Clean Generated Files

```bash
make clean-grpc
```

---

## 📜 Example `.proto` Declaration

```proto
syntax = "proto3";

package atrop;

service AtropService {
  rpc SayHello (HelloRequest) returns (HelloReply);
}

message HelloRequest {
  string name = 1;
}

message HelloReply {
  string message = 1;
}
```

---

## 👤 Author

Mahmoud Tawfeek  
[GitHub: @Mahmoudtawfeekie2024](https://github.com/Mahmoudtawfeekie2024)

---

## 📜 License

This gRPC interface is licensed under the [ATROP Project License](../../LICENSE).
