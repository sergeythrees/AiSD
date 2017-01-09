#pragma once
#include "stdafx.h"

void CheckFileAccess(std::ifstream &input)
{
	if (!input.is_open())
	{
		throw(std::exception("Не удается открыть входной файл"));
	}
}