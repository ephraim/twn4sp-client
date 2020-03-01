#include "serial.h"
#include "misc.h"
#include <iostream>

std::vector<uint8_t> Serial::write_read(const std::vector<uint8_t> &payload)
{
	int i;
	i = write(payload);
	if(i != payload.size())
		return std::vector<uint8_t>();

	return read();
}

std::vector<uint8_t> Serial::generatePaketData(const std::vector<uint8_t> &payload)
{
	uint16_t crc;
	std::vector<uint8_t> data;
	int size = 0;

	crc = genCrc(payload);
	size = 2 + payload.size(); // + crc(2)

	data.push_back(size & 0xff);
	data.push_back(size >> 8);
	data.insert(data.end(), payload.begin(), payload.end());

	data.push_back(crc & 0xff);
	data.push_back(crc >> 8);

	return data;
}

int Serial::write(const std::vector<uint8_t> &payload)
{
	std::vector<uint8_t> data = generatePaketData(payload);
	int size = 0;

	std::cout << "WRITE(" << std::dec << data.size() << "): " << b2h(data) << std::endl;
	size = _write(data);

	if(size > 4)
		size -= 4; // - crc(2) - size(2)
	
	return size;
}

std::vector<uint8_t> Serial::read()
{
	std::vector<uint8_t> data;
	int size;
	uint16_t crc;
	uint16_t crc2 = 0;

	data = _read();

	if(data.size() < 2)
		return data;

	size = data[0] | data[1]<<8;
	if(size != (data.size() - 2)) {
		std::cout << "READ(" << std::dec << data.size() << "): " << b2h(data) << std::endl;
		std::cout << "retrieved data invalid in size." << std::endl;
		return std::vector<uint8_t>();
	}
	data.erase(data.begin(), data.begin() + 2); // remove size

	crc = data[data.size() - 2] | data[data.size() - 1]<<8;
	data.erase(data.end() - 2, data.end()); // remove crc

	if(data.size() > 0)
		crc2 = genCrc(data);

	if(crc != crc2) {
		std::cout << "CRC Error READ(" << std::dec << data.size() << "): " << b2h(data) << std::endl; 
		return std::vector<uint8_t>();
	}

	return data;
}

uint16_t Serial::genCrc(std::vector<uint8_t> v)
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
