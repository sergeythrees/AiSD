#pragma once
#include "stdafx.h"

bool IsFileOpened(std::ifstream &input)
{
	if (!input.is_open())
	{
		std::cerr << "Не удается открыть входной файл" << std::endl;
		return false;
	}
	return true;
}