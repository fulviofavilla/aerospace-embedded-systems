# SPDX-License-Identifier: MIT
# Copyright (c) 2022 Fulvio Favilla (@fulviofavilla)

CXX      := g++
CXXFLAGS := -Wall -Wextra -Werror -std=c++17 -Iinclude -O2
LDFLAGS  := -pthread

# Directories
SRC_DIR  := src
OBJ_DIR  := obj
BIN_DIR  := bin

# Targets
ENGINE_TARGET := $(BIN_DIR)/telemetry_engine
CLIENT_TARGET := $(BIN_DIR)/test_client

# Source files
ENGINE_SRCS   := $(SRC_DIR)/TelemetryServer.cpp $(SRC_DIR)/TelemetryLogger.cpp $(SRC_DIR)/main.cpp
CLIENT_SRCS   := $(SRC_DIR)/TelemetryClient.cpp test_client.cpp

# Object files
ENGINE_OBJS   := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(ENGINE_SRCS)))
CLIENT_OBJS   := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(CLIENT_SRCS)))

.PHONY: all clean directories engine client

# Default build: compiles both
all: directories engine client

engine: $(ENGINE_TARGET)
client: $(CLIENT_TARGET)

directories:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

# Link Engine (Server)
$(ENGINE_TARGET): $(ENGINE_OBJS)
	$(CXX) $(ENGINE_OBJS) -o $@ $(LDFLAGS)
	@echo "Built Aerospace Telemetry Engine: $@"

# Link Test Client
$(CLIENT_TARGET): $(CLIENT_OBJS)
	$(CXX) $(CLIENT_OBJS) -o $@ $(LDFLAGS)
	@echo "Built Telemetry Test Client: $@"

# Compile Engine Sources
$(OBJ_DIR)/TelemetryServer.o: $(SRC_DIR)/TelemetryServer.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile Client Sources
$(OBJ_DIR)/TelemetryClient.o: $(SRC_DIR)/TelemetryClient.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/test_client.o: test_client.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile Logger
$(OBJ_DIR)/TelemetryLogger.o: $(SRC_DIR)/TelemetryLogger.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Update Engine Linker to include the logger object
$(ENGINE_TARGET): $(ENGINE_OBJS)
	$(CXX) $(ENGINE_OBJS) -o $@ $(LDFLAGS)

clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)
	@unlink /tmp/aerospace_telemetry.sock 2>/dev/null || true
	@echo "Project cleaned."
