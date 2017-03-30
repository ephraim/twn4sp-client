#include <fcntl.h>
#include <iomanip>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <boost/algorithm/hex.hpp>

#include "serial.h"

using namespace std;

string b2h(vector<uint8_t> v) {
	string res;
	boost::algorithm::hex(v.begin(), v.end(), back_inserter(res));
	return res;
}

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

Serial::Serial(string port/* = "/dev/ttyACM0"*/, int baudrate/* = 115200*/, int stop/* = 1*/, int parity/* = 0*/, int timeout/* = 1*/)
: fd(-1), withCrc(true)
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

bool Serial::setParameters(int baudrate/* = 115200*/, int stop/* = 1*/, int parity/* = 0*/, int timeout/* = 1*/)
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
	int size = 0;

	if(withCrc) {
		crc = genCrc(v);
	 	size = 2; // + crc(2)
	}

	size += v.size();

	data.push_back(size & 0xff);
	data.push_back(size >> 8);
	data.insert(data.end(), v.begin(), v.end());

	if(withCrc) {
		data.push_back(crc & 0xff);
		data.push_back(crc >> 8);
	}

	cout << "WRITE: " << b2h(data) << endl;
	size = ::write(fd, (const void*)data.data(), (size_t)data.size());

	if((withCrc && (size >= 4)) || (!withCrc && (size >= 2)))
		size -= withCrc ? 4 : 2; // - crc(2) - size(2)

	return size;
}

vector<uint8_t> Serial::read(int i/* = 0*/)
{
	vector<uint8_t> v;
	int r = -1;

	if(i == 0)
		i = 0xFF;

	v.resize(i);
	r = ::read(fd, v.data(), (size_t)v.size());
	v.resize(r);

	cout << "READ: " << b2h(v) << endl;
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
