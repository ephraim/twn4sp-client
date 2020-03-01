#include <termios.h>
#include <unistd.h>
#include <stdint.h>
#include <vector>
#include <string>
#include "serial.h"

using namespace std;

class UnixSerial : public Serial {
public:
	UnixSerial(string port = "/dev/ttyACM0", int baudrate = 115200, int stop = 1, int parity = 0, int timeout = 20);
	virtual ~UnixSerial();

	bool setParameters(int baudrate = 115200, int stop = 1, int parity = 0, int timeout = 20);
	int _write(const vector<uint8_t> &v);
	vector<uint8_t> _read();

private:
	int fd;
};
