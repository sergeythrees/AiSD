#pragma once
#include "stdafx.h"

void CheckArgumentsCount(int argumensCount, int expectedArgumentsCount)
{
	if (argumensCount != expectedArgumentsCount)
	{
		std::stringstream mess;
		mess << "Wrong arguments count\n"
			<< "Usage: floyd.exe <input file>\n";
		throw(std::invalid_argument(mess.str()));
	}
}

void CheckInputAccess(std::ifstream &input)
{
	if (!input.is_open())
	{
		throw(std::exception("Can not open input file"));
	}
}