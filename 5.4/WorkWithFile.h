#pragma once
#include "stdafx.h"

void CheckFileAccess(std::ifstream &input)
{
	if (!input.is_open())
	{
		throw(std::exception("Не удается открыть входной файл"));
	}
}

void ReadNumbers(std::vector<int> &numbers, std::ifstream &input)
{
	while (!input.eof() || !input.fail())
	{
		int x;
		if (input >> x)
		{
			numbers.push_back(x);
		}
		else
		{
			break;
		}
	}
	if (numbers.size() < 1)
		throw(std::logic_error("Файл не содержит корректных данных"));
}