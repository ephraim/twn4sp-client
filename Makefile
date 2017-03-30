TARGET = twn4sp-client

SOURCES = src/main.cpp
OBJECTS = src/main.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $(TARGET) $(OBJECTS)

.o: .cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
