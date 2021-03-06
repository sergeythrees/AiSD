#include "stdafx.h"
#include "ReadMatrix.h"

using namespace std;

void ReadEdges(vector<vector<unsigned>> &matrix, std::ifstream &input, std::ostream &output)
{
	multimap<pair<unsigned, unsigned>, unsigned> table;
	set<unsigned> uniqueNodes;

	output << "�������� ������ � �����" << endl << endl;

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
				uniqueNodes.emplace(y);
			}
			else
				output << ", ����� " << x << ">" << y << " ����� ���������" << endl;
				
		}
		else
		{
			break;
		}
	}
	if (uniqueNodes.size() < 1)
		throw(logic_error("���� �� �������� ���������� ������"));
	matrix.assign(uniqueNodes.size(), vector<unsigned>(uniqueNodes.size(), INT_MAX));
	for (auto current : table)
	{
		matrix[current.first.first - 1][current.first.second - 1] = current.second;		
	}
}

bool IsValidEdge(int const &x, int const &y, int const &weight, ostream &output)
{
	bool isValid = true;
	if (x <= 0)
	{
		isValid = false;
		output << " - ������� " << x << " <= 0";
	}
	else if (y <= 0)
	{
		isValid = false;
		output << " - ������� " << y << " <= 0";
	}
	else if (weight < 0)
	{
		isValid = false;
		output << " - ��� " << weight << " < 0";
	}
	return isValid;
}

