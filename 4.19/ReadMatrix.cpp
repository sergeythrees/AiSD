#include "stdafx.h"
#include "ReadMatrix.h"

using namespace std;

void ReadEdges(vector<vector<unsigned>> &matrix, std::ifstream &input, std::ostream &output)
{
	output << "Начинаю считывание: " << endl << endl;
	while (!input.eof())
	{
		unsigned x;
		unsigned y;
		unsigned weight;
		if (input >> x && input >> y && input >> weight)
		{
			if (IsValidEdge(x, y, weight, matrix.size(), output))
				matrix[x - 1][y - 1] = weight;
			else
				output << " - Пропущено  " << x << " " << y << " " << weight << endl;
				
		}
		else
		{
			break;
		}
	}
}

bool IsValidEdge(unsigned const &x, unsigned const &y, unsigned const &weight, unsigned const &maxValue, ostream &output)
{
	bool isValid = true;
	if (x <= 0 || x > maxValue)
	{
		isValid = false;
	}
	else if (y <= 0 || y > maxValue)
	{
		isValid = false;
	}
	else if (weight < 0)
	{
		isValid = false;
	}
	return isValid;
}

