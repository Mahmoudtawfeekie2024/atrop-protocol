# ===== ATROP Root Makefile =====

CXX := g++
CXXFLAGS := -std=c++17 -Wall -O2

# Source files
DAEMON_TARGETS := control_plane data_plane ipc
BUILD_DIR := build

all: $(addprefix $(BUILD_DIR)/, $(DAEMON_TARGETS))

$(BUILD_DIR)/%: daemon/%/main.cpp | $(BUILD_DIR)
	@echo "🔧 Building $(@F)..."
	$(CXX) $(CXXFLAGS) $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
