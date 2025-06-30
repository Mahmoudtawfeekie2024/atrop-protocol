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
