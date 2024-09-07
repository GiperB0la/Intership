#pragma once
#include "Client.h"
#include <thread>


class PragmaSecond
{
public:
	PragmaSecond() = default;
	~PragmaSecond() = default;

public:
	void Start();

private:
	Client client;
};