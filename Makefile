CXX = g++
CXXFLAGS = -Wall -std=c++20 -Iinclude

SRC_DIR = src
BUILD_DIR = build
BIN_DIR = $(BUILD_DIR)/bin

TARGET = $(BIN_DIR)/main
SRCS = $(SRC_DIR)/main.cpp

all: $(TARGET)

$(TARGET): $(SRCS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(SRCS)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BUILD_DIR)
