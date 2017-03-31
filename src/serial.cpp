#include <fcntl.h>
#include <iomanip>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>

#include "serial.h"
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

Serial::Serial(string port/* = "/dev/ttyACM0"*/, int baudrate/* = 115200*/, int stop/* = 1*/, int parity/* = 0*/, int timeout/* = 10*/)
: fd(-1)
{
	fd = open(port.c_str(), O_RDWR);
	if(fd < 0) {
		cerr << "ERROR: could not open " << port << ". Error: " << hex << setw(8) << setfill('0') << errno << endl;
		return;
	}

	setParameters(baudrate, stop, parity, timeout);
}

Serial::~Serial()
{
	if(fd >= 0)
		close(fd);
}

bool Serial::setParameters(int baudrate/* = 115200*/, int stop/* = 1*/, int parity/* = 0*/, int timeout/* = 10*/)
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

vector<uint8_t> Serial::write_read(vector<uint8_t> v)
{
	int i;
	i = write(v);
	if(i != v.size())
		return vector<uint8_t>();

	return read();
}

int Serial::write(const vector<uint8_t> &v)
{
	uint16_t crc;
	vector<uint8_t> data;
	int size = 2; // + crc(2)

	crc = genCrc(v);
	size += v.size();

	data.push_back(size & 0xff);
	data.push_back(size >> 8);
	data.insert(data.end(), v.begin(), v.end());

	data.push_back(crc & 0xff);
	data.push_back(crc >> 8);

	// cout << "WRITE(" << dec << data.size() << "): " << b2h(data) << endl;
	size = ::write(fd, (const void*)data.data(), (size_t)data.size());

	if(size >= 4)
		size -= 4; // - crc(2) - size(2)

	return size;
}

vector<uint8_t> Serial::read()
{
	vector<uint8_t> v;
	uint16_t size = 0;
	uint16_t count;
	uint16_t crc;
	uint16_t crc2;
	vector<uint8_t> tmp;

	tmp.resize(2);
	::read(fd, tmp.data(), (size_t)tmp.size());
	size = tmp[0] | tmp[1]<<8;

	tmp.clear();
	tmp.resize(size);
	while(size != v.size()) {
		count = ::read(fd, tmp.data(), (size_t)tmp.size());
		v.insert(v.end(), tmp.begin(), tmp.begin() + count);
	}
	// cout << "READ(" << dec << v.size() << "): " << b2h(v) << endl;
	crc = v[v.size() - 2] | v[v.size() - 1]<<8;
	v.erase(v.end() - 2, v.end());

	crc2 = genCrc(v);
	if(crc != genCrc(v))
		return vector<uint8_t>();

	return v;
}

uint16_t Serial::genCrc(vector<uint8_t> v)
{
	uint16_t ret = 0xFFFF;
	uint16_t b;
	int i;

	for(int i = 0; i < v.size(); i++) {
		b = v[i];
		b ^= (uint8_t)ret;
		b ^= (uint8_t)(b << 4);
		ret = (uint16_t)(((b << 8) | (ret >> 8)) ^ (b >> 4) ^ (b << 3));
	}

	return ret;
}
