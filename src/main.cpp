#include <string>
#include <iostream>
#include <boost/algorithm/hex.hpp>

#include "serial.h"

using namespace std;

vector<uint8_t> h2b(string s) {
	vector<uint8_t> res;
	boost::algorithm::unhex(s.begin(), s.end(), back_inserter(res));
	return res;
}

int main(int argc, const char* argv[])
{
	Serial port("/dev/ttyACM0", 115200, 1, 0, 1);
	string cmd = "0008";
	vector<uint8_t> request { 0x00, 0x08 };
	vector<uint8_t> response; // 0x00, 0x01, 0x80, 0x20, 0x04, 0x66, 0xCF, 0x4D, 0xC2

	if(argc > 1)
		cmd = argv[1];

	request = h2b(cmd);
	port.setCrc(true);
	response = port.write_read(request);
	return 0;
}
