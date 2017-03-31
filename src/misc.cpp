#include "misc.h"

std::string b2h(std::vector<uint8_t> v) {
	std::string res;
	boost::algorithm::hex(v.begin(), v.end(), back_inserter(res));
	return res;
}

std::vector<uint8_t> h2b(std::string s) {
	std::vector<uint8_t> res;
	boost::algorithm::unhex(s.begin(), s.end(), back_inserter(res));
	return res;
}
