CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Istructures
TARGET   := dbms

SRCS := main.cpp commands.cpp \
        structures/array.cpp \
        structures/slist.cpp \
        structures/dlist.cpp \
        structures/stack.cpp \
        structures/queue.cpp \
        structures/blackredtree.cpp

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) *.o structures/*.o