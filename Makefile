TARGET = twn4sp-client

SOURCES = src/main.cpp src/serial.cpp
HEADERS = src/serial.h
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $(TARGET) $(OBJECTS)

$(OBJECTS): $(HEADERS)

.o: .cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJECTS)
