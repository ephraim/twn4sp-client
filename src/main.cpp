#include <string>
#include <unistd.h>
#include <iostream>
#include <boost/algorithm/hex.hpp>
#include "simpleproto.h"
#include "misc.h"

#define MAKEFIRMWARE
#include "twn4.sys.h"

using namespace std;

int main(int argc, const char* argv[])
{
	SimpleProtocolClient spc(argv[1]);
	vector<uint8_t> v;

	spc.beep(100, 2000, 0x100, 0x100);
	spc.greenLED(false);
	spc.setTagTypes(0, TAGMASK(HFTAG_MIFARE));

	for(int i = 0; i < 10; ) {
		if(spc.searchTag(v)) {
			cout << "TagID: " << b2h(v) << endl;
			spc.greenLED(true);
			spc.beep(100, 2000, 0x100, 0x100);
			spc.greenLED(false);
			i++;
		}
	}

	return 0;
}
