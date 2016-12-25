#include "stdafx.h"
#include "ReadMatrix.h"

using namespace std;

void ReadEdges(vector<vector<unsigned>> &matrix, std::ifstream &input, std::ostream &output)
{
	multimap<pair<unsigned, unsigned>, unsigned> table;
	set<unsigned> uniqueNodes;

	output << "Считываю данные с файла" << endl << endl;

	while (!input.eof() || !input.fail())
	{
		int x;
		int y;
		int weight;
		if (input >> x && input >> y && input >> weight)
		{
			if (IsValidEdge(x, y, weight, output))
			{
				table.emplace(make_pair(x, y), weight);
				uniqueNodes.emplace(x);
			}
			else
				output << ", ребро " << x << ">" << y << " будет пропущено" << endl;
				
		}
		else
		{
			break;
		}
	}
	if (uniqueNodes.size() < 1)
		throw(logic_error("Файл не содержит корректных данных"));
	matrix.assign(uniqueNodes.size(), vector<unsigned>(uniqueNodes.size(), 0));
	for (auto current : table)
	{
		if (uniqueNodes.count(current.first.first) && uniqueNodes.count(current.first.second))
		{
			matrix[current.first.first - 1][current.first.second - 1] = current.second;
		}
		else
		{
			stringstream msg;
			msg << "Обнаружена ссылка на несуществующую вершину " << current.first.first << ">" << current.first.second;
			throw(out_of_range(msg.str()));
		}
		
	}
}

bool IsValidEdge(int const &x, int const &y, int const &weight, ostream &output)
{
	bool isValid = true;
	if (x <= 0)
	{
		isValid = false;
		output << " - Вершина " << x << " <= 0";
	}
	else if (y <= 0)
	{
		isValid = false;
		output << " - Вершина " << y << " <= 0";
	}
	else if (weight < 0)
	{
		isValid = false;
		output << " - Вес " << weight << " < 0";
	}
	return isValid;
}

