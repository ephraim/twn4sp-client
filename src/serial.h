#include <string>
#include <vector>

class Serial {
public:
	virtual bool setParameters(int baudrate = 115200, int stop = 1, int parity = 0, int timeout = 20) = 0;

	int write(const std::vector<uint8_t> &payload);
	std::vector<uint8_t> read();
	std::vector<uint8_t> write_read(const std::vector<uint8_t> &payload);

protected:
	std::vector<uint8_t> generatePaketData(const std::vector<uint8_t> &payload);
	uint16_t genCrc(std::vector<uint8_t> v);
	virtual int _write(const std::vector<uint8_t> &data) = 0;
	virtual std::vector<uint8_t> _read() = 0;
};
