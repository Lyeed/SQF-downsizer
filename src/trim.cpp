#include "trim.hpp"

std::string trim(const std::string &str)
{
	const std::string pattern = " \t\f\v\n\r";
	std::string ret = str;
	std::size_t found;

	found = ret.find_last_not_of(pattern);
	if (found == std::string::npos) {
		ret.clear();
	} else {
		ret.erase(found + 1, ret.length() - found);
	}

	found = ret.find_first_not_of(pattern);
	if (found == std::string::npos) {
		ret.clear();
	} else {
		ret.erase(0, found);
	}

    return ret;
}
