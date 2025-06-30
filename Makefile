# ===== ATROP Root Makefile =====

# Compiler settings
CXX := g++
CXXFLAGS := -std=c++17 -Wall -O2

# Submodules
DAEMON_SRC := daemon/control_plane/main.cpp daemon/data_plane/main.cpp daemon/ipc/main.cpp
BUILD_DIR := build

# Targets
CONTROL_PLANE_BIN := $(BUILD_DIR)/control_plane
DATA_PLANE_BIN := $(BUILD_DIR)/data_plane
IPC_BIN := $(BUILD_DIR)/ipc

# Default build target
all: $(CONTROL_PLANE_BIN) $(DATA_PLANE_BIN) $(IPC_BIN)

# Build rules for each binary
$(CONTROL_PLANE_BIN): daemon/control_plane/main.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(DATA_PLANE_BIN): daemon/data_plane/main.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(IPC_BIN): daemon/ipc/main.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

# Create build directory if needed
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Cleanup
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean

# ==== SDK C++ Section ====

SDK_CPP_DIR := sdk/c++
SDK_CPP_SRC := $(wildcard $(SDK_CPP_DIR)/*.cpp)
SDK_CPP_OBJ := $(patsubst $(SDK_CPP_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SDK_CPP_SRC))
SDK_CPP_BIN := $(BUILD_DIR)/sdk_cpp_demo

# Add SDK binary to default build
all: $(SDK_CPP_BIN)

# Compile object files
$(BUILD_DIR)/%.o: $(SDK_CPP_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link into final binary (or you can archive into lib if you prefer)
$(SDK_CPP_BIN): $(SDK_CPP_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

# ==== gRPC Stub Generation ====

PROTO_DIR := sdk/grpc
PROTO_FILE := $(PROTO_DIR)/atrop.proto

GRPC_PY_OUT := $(PROTO_DIR)/build_py
GRPC_CPP_OUT := $(PROTO_DIR)/build_cpp

generate-grpc-stubs: generate-grpc-py generate-grpc-cpp

generate-grpc-py:
	@echo "🧪 Generating Python gRPC stubs..."
	python -m grpc_tools.protoc -I$(PROTO_DIR) \
	  --python_out=$(GRPC_PY_OUT) \
	  --grpc_python_out=$(GRPC_PY_OUT) \
	  $(PROTO_FILE)

generate-grpc-cpp:
	@echo "⚙️ Generating C++ gRPC stubs..."
	protoc -I$(PROTO_DIR) \
	  --cpp_out=$(GRPC_CPP_OUT) \
	  --grpc_out=$(GRPC_CPP_OUT) \
	  --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` \
	  $(PROTO_FILE)

clean-grpc:
	rm -rf $(GRPC_PY_OUT) $(GRPC_CPP_OUT)

# ==== Python Tests ====

PYTHON_TEST_DIR := test/unit

test-python:
	@echo "🧪 Running Python tests in $(PYTHON_TEST_DIR)..."
	python -m pytest $(PYTHON_TEST_DIR)

# === C++ Unit Testing ===

GTEST_SRC := test/unit/c++/test_main.cpp test/unit/c++/test_sdk.cpp
GTEST_BIN := build/test_cpp

test-cpp: $(GTEST_BIN)
	@echo "🧪 Running C++ unit tests..."
	./$(GTEST_BIN)

$(GTEST_BIN): $(GTEST_SRC)
	$(CXX) $(CXXFLAGS) -lgtest -lgtest_main -pthread $^ -o $@

.PHONY: test-cpp
