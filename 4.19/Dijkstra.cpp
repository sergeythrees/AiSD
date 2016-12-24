#include "stdafx.h"
#include "Dijkstra.h"

using namespace std;

void Dijkstra(vector<vector<unsigned>> const &matrix, unsigned const &startNode, ostream &output)
{
	vector<unsigned> distance;
	vector<unsigned> parents(matrix.size());
	set<int> visited;
	unsigned currentNode = startNode;

	distance.assign(matrix.size(), INT_MAX);
	distance[startNode] = 0;

	output << endl << "Ищу кратчайшие пути от узла " << startNode+1 << " до всех других" << endl << endl;
	for (auto node : matrix)
	{
		unsigned minDistance = INT_MAX;
		size_t i = 0;
		for (auto current : distance)
		{
			if (visited.find(i) == visited.end() && current <= minDistance)
			{
				minDistance = current;
				currentNode = i;
			}
			++i;
		}
		visited.emplace(currentNode);


		output << "  Ближайшая из соседних к предыдущей вершине: " << currentNode + 1 << endl;
		i = 0;
		for (auto current : matrix[currentNode])
		{
			if (visited.find(i) == visited.end() && 
				current != 0 &&
				distance[currentNode] != INT_MAX &&
				distance[currentNode] + current < distance[i])
			{
				distance[i] = distance[currentNode] + current;
				parents[i] = currentNode;
				output << "    " << currentNode + 1 << " > " << i + 1 << " = " << current <<  endl;
			}
			++i;
		}

		output << "    Вычисленные пути: ";
		PrintCurrentDistances(distance, output);

		output << "  Кратчайший путь: ";
		if (distance[currentNode] < INT_MAX)
		{
			ShowPath(parents, currentNode, startNode, output);
			output << endl;
		}
		else
		{
			output << "отсутствует" << endl;
		}
		output << endl;
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
			output << -1 << " ";
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

