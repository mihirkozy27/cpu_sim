# Makefile for SystemC CPU Simulator with modular structure

SYSTEMC_HOME ?= /home/mkozarek/systemc-3.0.1
SYSTEMC_INCLUDE = $(SYSTEMC_HOME)/include
SYSTEMC_LIB = $(SYSTEMC_HOME)/lib-linux64

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I$(SYSTEMC_INCLUDE)
LDFLAGS = -L$(SYSTEMC_LIB) -lsystemc -lm

# Source files
SRC = main.cpp \
      cpu.cpp \
      pipestages/Fetch.cpp \
      pipestages/Decode.cpp \
      pipestages/Execute.cpp \
      pipestages/Memory.cpp \
      pipestages/Writeback.cpp \
	  components/RegFile.cpp \
	  components/DataMemory.cpp

# Object files (same directory structure as SRC)
OBJ = $(SRC:.cpp=.o)

TARGET = cpu_sim

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)
