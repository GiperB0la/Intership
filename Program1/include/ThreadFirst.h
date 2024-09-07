#pragma once
#include <string>
#include <mutex>
#include <condition_variable>
#include <iostream>

#include "WorkingWithString.h"


class ThreadFirst
{
public:
	ThreadFirst() : WorkingWithStringObj() {};
	~ThreadFirst() = default;

public:
	void WorkThreadFirst(bool WorkThreadSecondFlag, std::mutex& mt, std::condition_variable& cv, bool& dataFlag, std::string& buffer);

private:
	WorkingWithString WorkingWithStringObj;
};