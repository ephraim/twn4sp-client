#include "serial.h"
#include <Windows.h>

class WindowsSerial : public Serial {
public:
	WindowsSerial(std::string port = "COM1", int baudrate = CBR_115200, int stop = ONESTOPBIT, int parity = NOPARITY, int timeout = 20);
	~WindowsSerial();

	bool setParameters(int baudrate = CBR_115200, int stop = ONESTOPBIT, int parity = NOPARITY, int timeout = 20);
	int _write(const std::vector<uint8_t> &v);
	std::vector<uint8_t> _read();
protected:
	HANDLE hSerial;
};
