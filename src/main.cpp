#include <string>
#include <iostream>

#include "serial.h"

using namespace std;

int main(int argc, const char* argv[])
{
	Serial port("/dev/ttyACM0", 115200, 1, 0, 1);
	vector<uint8_t> request { 0x00, 0x08 };
	vector<uint8_t> response; // 0x00, 0x01, 0x80, 0x20, 0x04, 0x66, 0xCF, 0x4D, 0xC2

	port.setCrc(false);
	response = port.write_read(request);
	return 0;
}
