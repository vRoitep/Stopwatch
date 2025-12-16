CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = stopwatch
OBJS = main.o Stopwatch.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp Stopwatch.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Stopwatch.o: Stopwatch.cpp Stopwatch.h
	$(CXX) $(CXXFLAGS) -c Stopwatch.cpp

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean