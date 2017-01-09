#include "stdafx.h"
#include "Dijkstra.h"

using namespace std;

void Dijkstra(std::vector<std::vector<unsigned>> &matrix, unsigned const &startNode, std::ostream &output)
{
	for (unsigned i = 0; i < matrix.size(); ++i)
		for (unsigned k = 0; k < matrix.size(); ++k)
			for (unsigned j = 0; j < matrix.size(); ++j)
			{
				if (i == j )
					matrix[i][j] = INT_MAX;
				else
					matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
			}
}


void PrintCurrentDistances(vector<unsigned> const &distance, ostream &output)
{
	for (auto position : distance)
	{
		if (position != INT_MAX)
		{
			output << position << " ";
		}
		else
		{
			output << "*" << " ";
		}
	}
	output << endl;
}

void ShowPath(vector<unsigned> &parents, unsigned const &node, unsigned const &startNode, ostream &output)
{
	vector<int> path;
	for (int v = node; v != startNode; v = parents[v])
		path.push_back(v + 1);
	path.push_back(startNode + 1);
	reverse(path.begin(), path.end());

	output << startNode + 1;
	if (path.size() == 1)
	{
		output << ">" << path[0];
	}
	for (int i = 1; i < path.size();++i)
	{
		output << ">" << path[i];
	}
}

