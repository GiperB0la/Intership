#pragma once
#include "Client.h"


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