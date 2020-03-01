#include <fcntl.h>
#include <iomanip>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>

#include "unix_serial.h"
#include "misc.h"

using namespace std;

bool operator ==(const struct termios &a, const struct termios &b)
{
	if(a.c_iflag != b.c_iflag)
		return false;

	if(a.c_oflag != b.c_oflag)
		return false;

	if(a.c_cflag != b.c_cflag)
		return false;

	if(a.c_lflag != b.c_lflag)
		return false;

	for(int i = 0; i < NCCS; i++)
		if(a.c_cc[i] != b.c_cc[i])
			return false;

	return true;
}

UnixSerial::UnixSerial(string port/* = "/dev/ttyACM0"*/, int baudrate/* = 115200*/, int stop/* = 1*/, int parity/* = 0*/, int timeout/* = 10*/)
: fd(-1)
{
	fd = open(port.c_str(), O_RDWR);
	if(fd < 0) {
		cerr << "ERROR: could not open " << port << ". Error: " << hex << setw(8) << setfill('0') << errno << endl;
		return;
	}

	setParameters(baudrate, stop, parity, timeout);
}

UnixSerial::~UnixSerial()
{
	if(fd >= 0)
		close(fd);
}

bool UnixSerial::setParameters(int baudrate/* = 115200*/, int stop/* = 1*/, int parity/* = 0*/, int timeout/* = 10*/)
{
	struct termios ts;
	struct termios tmp;
	speed_t speed;

	if(fd < 0) {
		cerr << "ERROR: filedescriptor invalid. Could not set parameters" << endl;
		return false;
	}

	switch(baudrate) {
		case 9600: speed = B9600; break;
		default:
			cerr << "WARNING: unknown baudrate specified: " << dec << baudrate << ". Using default: 115200" << endl;
		case 115200: speed = B115200; break;
	}

	cfmakeraw(&ts);
	cfsetspeed(&ts, speed);

	if(stop == 2) // two stopbits
		ts.c_cflag |= CSTOPB;
	else  // one stopbits
		ts.c_cflag &= ~CSTOPB;

	if(parity == 1) { // with Even Parity
		ts.c_cflag |= PARENB;
		ts.c_cflag &= ~PARODD;
	}
	else if(parity == 2) { // with Odd Parity
		ts.c_cflag |= PARENB;
		ts.c_cflag |= PARODD;
	}
	else { // without any Parity
		ts.c_cflag &= ~PARENB;
		ts.c_cflag &= ~PARODD;
	}

	ts.c_cc[VMIN] = 0;
	ts.c_cc[VTIME] = timeout * 10; // entity: 1/10 seconds

	if(tcsetattr(fd, TCSAFLUSH, &ts) == 0) {
		tcgetattr(fd, &tmp);
		return ts == tmp;
	}
	return false;
}

int UnixSerial::_write(const vector<uint8_t> &data)
{
	return ::write(fd, (const void*)data.data(), (size_t)data.size());
}

int UnixSerial::_read()
{
    vector<uint8_t> data;
	int size = 0;

    data.resize(1024);
	size = ::read(fd, data.data(), (size_t)data.size());
    if(size < 0) {
        DEBUG;
        return std::vector<uint8_t>();
    }

    data.resize(size);
    return data;
}