#pragma once
#include <string>
#include <algorithm>


class WorkingWithString
{
public:
	WorkingWithString() = default;
	~WorkingWithString() = default;

public:
	void ProcessingString(std::string& str);
	bool CheckingString(std::string& str);
};