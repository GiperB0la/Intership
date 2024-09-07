#pragma once
#include <mutex>
#include <iostream>
#include <string>
#include <condition_variable>
#include "Socket.h"


class ThreadSecond
{
public:
	ThreadSecond() = default;
	~ThreadSecond() = default;

public:
	void WorkThreadSecond(bool WorkThreadFirstFlag, std::mutex& mt, std::condition_variable& cv, bool& dataFlag, std::string& buffer, Socket* SocketObject);
};