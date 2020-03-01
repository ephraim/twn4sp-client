TARGET = twn4sp-client

SOURCES = src/main.cpp src/serial.cpp src/simpleproto.cpp src/misc.cpp
HEADERS = src/serial.h src/simpleproto.h src/misc.h src/twn4.sys.h
OBJECTS = $(SOURCES:.cpp=.o)

CXXFLAGS += -Isrc

ifeq ($(OS),Windows_NT)
	SOURCES += src/windows_serial.cpp
	HEADERS += src/windows_serial.h
	CXXFLAGS += -IC:\Users\thilo\Documents\Projekte\boost_1_72_0
else
	SOURCES += src/unix_serial.cpp
	HEADERS += src/unix_serial.h
endif

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $(TARGET) $(OBJECTS)

$(OBJECTS): $(HEADERS)

.o: .cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJECTS)