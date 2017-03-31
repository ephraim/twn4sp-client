#include <string>
#include <vector>

#include "serial.h"

using namespace std;

class SimpleProtocolClient : public Serial
{
public:
	SimpleProtocolClient(string port = "/dev/ttyACM0");
	virtual ~SimpleProtocolClient();

	void beep(uint8_t volume = 85, uint16_t frequence = 2000, uint16_t ontime = 0x80, uint16_t offtime = 0x80);
	void diagLEDToggle();
	void greenLED(bool on);
	void yellowLED(bool on);
	void redLED(bool on);
	void getTagTypes(uint32_t &lfTagTypes, uint32_t &hiTagTypes);
	void setTagTypes(uint32_t lfTagTypes, uint32_t hiTagTypes);
	bool searchTag(vector<uint8_t>& tagID);
protected:
	void GPIOConfigureOutputs(uint8_t GPOs, uint8_t PullUpDown, uint8_t OutputType);
};
