# Makefile for Meta Hacker Cup solution

CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

TARGET = main
SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
