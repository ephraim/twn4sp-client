#include <boost/algorithm/hex.hpp>
#include <string>
#include <vector>

#ifndef __MISC_H__
#define __MISC_H__
std::string b2h(std::vector<uint8_t> v);
std::vector<uint8_t> h2b(std::string s);
#endif
