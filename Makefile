CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Istructures

all: dbms

dbms: main.cpp commands.cpp $(wildcard structures/*.cpp) $(wildcard structures/*.h)
	$(CXX) $(CXXFLAGS) main.cpp commands.cpp structures/*.cpp -o dbms

clean:
	rm -f dbms

.PHONY: all clean
