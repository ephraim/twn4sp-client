TARGET = twn4sp-client

SOURCES = src/main.cpp src/serial.cpp src/simpleproto.cpp src/misc.cpp
HEADERS = src/serial.h src/simpleproto.h src/misc.h src/twn4.sys.h
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $(TARGET) $(OBJECTS)

$(OBJECTS): $(HEADERS)

.o: .cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJECTS)
