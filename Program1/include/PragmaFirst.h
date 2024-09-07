#pragma once
#include <string>
#include <mutex>

#include "ThreadFirst.h"
#include "ThreadSecond.h"
#include "Socket.h"


class PragmaFirst
{
public:
	PragmaFirst() : buffer(), mt(), cv(), ThreadFirstObject(), ThreadSecondObject(),
		dataFlag(false), WorkThreadFirstFlag(true), WorkThreadSecondFlag(true), SocketObject(new Socket) {};
    ~PragmaFirst() = default;

public:
    void Start();

private:
	std::string buffer;
	std::mutex mt;
	std::condition_variable cv;
	bool dataFlag;
	bool WorkThreadFirstFlag;
	bool WorkThreadSecondFlag;

private:
	Socket* SocketObject;
	ThreadFirst ThreadFirstObject;
	ThreadSecond ThreadSecondObject;
};