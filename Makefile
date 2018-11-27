# Makefile
TARGET=lib
CXX=g++
CXXFLAGS=-std=c++14
OBJECTS=main.o resource.o member.o library.o

$(TARGET) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp
resource.o: resource.cpp
	$(CXX) $(CXXFLAGS) -c resource.cpp
library.o: library.cpp	
	$(CXX) $(CXXFLAGS) -c library.cpp
member.o: member.cpp
	$(CXX) $(CXXFLAGS) -c member.cpp
clean:
	rm $(OBJECTS) $(TARGET)
