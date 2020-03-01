#include <iostream>

#include "simpleproto.h"
#include "misc.h"

#define MAKEFIRMWARE
#include "twn4.sys.h"

SimpleProtocolClient::SimpleProtocolClient(string port/* = "/dev/ttyACM0"*/)
#ifdef _WIN32
: WindowsSerial
#else
: UnixSerial
#endif
(port, 115200, 1, 0, 50)
{
	GPIOConfigureOutputs(REDLED | GREENLED, GPIO_PUPD_NOPULL, GPIO_OTYPE_PUSHPULL); // Led Green => GPIO1 => 0x02, Led Red => GPIO0 => 0x01
}

SimpleProtocolClient::~SimpleProtocolClient()
{
}

void SimpleProtocolClient::GPIOConfigureOutputs(uint8_t GPOs, uint8_t PullUpDown, uint8_t OutputType)
{
	write_read({ 0x04, 0x00, GPOs, PullUpDown, OutputType });
}

void SimpleProtocolClient::beep(uint8_t volume/* = 85*/, uint16_t frequence/* = 2000*/, uint16_t ontime/* = 0x80*/, uint16_t offtime/* = 0x80*/)
{
	vector<uint8_t> request { 0x04, 0x07, volume,
		(uint8_t)(frequence & 0xFF), (uint8_t)(frequence >> 8),
		(uint8_t)(ontime & 0xFF), (uint8_t)(ontime >> 8),
		(uint8_t)(offtime & 0xFF), (uint8_t)(offtime >> 8) };
	vector<uint8_t> response;

	response = write_read(request);
}

void SimpleProtocolClient::diagLEDToggle()
{
	write_read({ 0x04, 0x0A });
}

void SimpleProtocolClient::greenLED(bool on)
{
	vector<uint8_t> v { 0x04, 0x00, 0x02 };
	v[1] = (on == true ? 0x02 : 0x03);
	write_read(v);
}

void SimpleProtocolClient::yellowLED(bool on)
{
	vector<uint8_t> v { 0x04, 0x00, 0x04 };
	v[1] = (on == true ? 0x02 : 0x03);
	write_read(v);
}

void SimpleProtocolClient::redLED(bool on)
{
	vector<uint8_t> v { 0x04, 0x00, 0x01 };
	v[1] = (on == true ? 0x02 : 0x03);
	write_read(v);
}

void SimpleProtocolClient::setTagTypes(uint32_t lfTagTypes, uint32_t hiTagTypes)
{
	vector<uint8_t> v { 0x05, 0x02 };

	v.push_back(lfTagTypes & 0xFF);
	v.push_back((lfTagTypes>>8) & 0xFF);
	v.push_back((lfTagTypes>>16) & 0xFF);
	v.push_back((lfTagTypes>>24) & 0xFF);
	v.push_back(hiTagTypes & 0xFF);
	v.push_back((hiTagTypes>>8) & 0xFF);
	v.push_back((hiTagTypes>>16) & 0xFF);
	v.push_back((hiTagTypes>>24) & 0xFF);

	write_read(v);
}

void SimpleProtocolClient::getTagTypes(uint32_t &lfTagTypes, uint32_t &hiTagTypes)
{
	vector<uint8_t> v;
	v = write_read({ 0x05, 0x03 });

	cout << "read: " << b2h(v) << endl;
	if(v.size() != 9)
		return;

	lfTagTypes = v[1];
	lfTagTypes |= v[2]<<8;
	lfTagTypes |= v[3]<<16;
	lfTagTypes |= v[4]<<24;
	hiTagTypes = v[5];
	hiTagTypes |= v[6]<<8;
	hiTagTypes |= v[7]<<16;
	hiTagTypes |= v[8]<<24;
}

bool SimpleProtocolClient::searchTag(vector<uint8_t>& tagID)
{
	bool ret;
	vector<uint8_t> response;
	uint8_t tagType;
	uint8_t bits;
	uint8_t bytes;

	response =  write_read({ 0x05, 0x00, 0x28 });
	if(response.size() < 4)
		return false;

	ret     = response[1] == 0 ? false : true;
	tagType = response[2];
	bits    = response[3];
	bytes   = response[4];
	tagID.clear();
	tagID.insert(tagID.begin(), response.begin() + 5, response.end());

	cout << "ret: " << (int)ret << ", tagType: 0x" << hex << (int)tagType << ", bits: " << dec << (int)bits << ", bytes: " << dec << (int)bytes << endl;
	return ret;
}
