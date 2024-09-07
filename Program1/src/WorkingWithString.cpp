#include "../include/WorkingWithString.h"


void WorkingWithString::ProcessingString(std::string& str)
{
	std::sort(str.begin(), str.end(), std::greater<char>());

	std::string newStr;
	for (size_t i = 0; i < str.size(); i++) {
		if ((str.at(i) - '0') % 2 == 0)
			newStr += "KB";
		else
			newStr += str.at(i);
	}
	str = std::move(newStr);
}

bool WorkingWithString::CheckingString(std::string& str)
{
	if (str.size() > 64) {
		return false;
	}

	for (char c : str) {
		if (!std::isdigit(static_cast<unsigned char>(c))) {
			return false;
		}
	}
	ProcessingString(str);

	return true;
}