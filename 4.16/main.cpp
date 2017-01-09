//19. Реализовать алгоритм поиска кратчайших путей Дейкстры и
//проиллюстрировать по шагам этапы его выполнения (10).

#include "stdafx.h"
#include "ReadMatrix.h"
#include "Dijkstra.h"
#include "WorkWithFiles.h"

using namespace std;

void FillPathsMatrix(vector<vector<unsigned>> &matrix, vector<vector<unsigned>> &paths);
void Floyd(vector<vector<unsigned>> &matrix, vector<vector<unsigned>> &paths);
void PrintMatrices(vector<vector<unsigned>> &matrix, vector<vector<unsigned>> &paths, ostream &output);
void PrintMinPath(unsigned a, unsigned b, vector<vector<unsigned>> &paths, ostream &output);

int main(int argc, char *argv[]) try
{
	setlocale(LC_ALL, "rus");
	ifstream input(argv[1]);
	CheckFileAccess(input);

	vector<vector<unsigned>> matrix;
	ReadEdges(matrix, input, cout);

	vector<vector<unsigned>> paths;
	FillPathsMatrix(matrix, paths);

	Floyd(matrix, paths);
	PrintMatrices(matrix, paths, cout);

	unsigned a;
	unsigned b;

	while (!cin.eof() && !cin.fail())
	{
		cin >> a;
		cin >> b;
		try
		{
			PrintMinPath(a, b, paths, cout);
			cout << " = " << matrix[a - 1][b - 1] << endl;
		}
		catch (const invalid_argument& ex)
		{
			cout << ex.what() << endl;
		}		
	}
	

	return EXIT_SUCCESS;
}
catch (const exception& ex)
{
	cout << ex.what() << endl;
	return EXIT_FAILURE;
}

void FillPathsMatrix(vector<vector<unsigned>> &matrix, vector<vector<unsigned>> &paths)
{
	paths.assign(matrix.size(), vector<unsigned>(matrix.size(), INT_MAX));
	for (unsigned i = 0; i < matrix.size(); ++i)
		for (unsigned j = 0; j < matrix.size(); ++j)
			if (matrix[i][j] != INT_MAX)
				paths[i][j] = j;
}
void Floyd(vector<vector<unsigned>> & matrix, vector<vector<unsigned>> &paths)
{
for (unsigned i = 0; i < matrix.size(); ++i)
	for (unsigned k = 0; k < matrix.size(); ++k)
		for (unsigned j = 0; j < matrix.size(); ++j)
		{
			if (i == j)
			{
				matrix[i][j] = INT_MAX;
				paths[i][j] = INT_MAX;
			}
			else
			{
				if (matrix[i][j] > (matrix[i][k] + matrix[k][j]))
				{
					matrix[i][j] = matrix[i][k] + matrix[k][j];
					paths[i][j] = paths[i][k];
				}
			}	
		}
}

void PrintMatrices(vector<vector<unsigned>> &matrix, vector<vector<unsigned>> &paths, ostream &output)
{
	output << endl << "  ";
	for (unsigned i = 1; i < matrix.size()+1; ++i)
		output << "_" << i << "_";
	output << "\t  ";
	for (unsigned i = 1; i < matrix.size() + 1; ++i)
		output << "_" << i << "_";
	output << endl << endl;

	for (unsigned i = 0; i < matrix.size(); ++i)
	{
		output << i + 1 << " ";
		for (unsigned k = 0; k < matrix.size(); ++k)
		{
			if (matrix[i][k] == INT_MAX)
				output << " *" << " ";
			else
			{
				if (matrix[i][k] < 10)
					output << " ";
				output << matrix[i][k] << " ";
			}
				
		}
		output << "\t";
		
		output << i + 1 << " ";
		for (unsigned k = 0; k < paths.size(); ++k)
		{
			if (paths[i][k] == INT_MAX)
				output << " *" << " ";
			else
			{
				if (paths[i][k] < 10)
					output << " ";
				output << paths[i][k] + 1 << " ";
			}
		}
		output << endl << "|                               |" << endl;
	}
	output << endl;
}

void PrintMinPath(unsigned a, unsigned b, vector<vector<unsigned>> &paths, ostream &output)
{
	stringstream msg;
	if (a > paths.size() ||
		b > paths.size() ||
		a == 0 || b == 0
		)
	{
		msg << "Вершина должна быть в диапазоне 1.." << paths.size() << endl;
		throw invalid_argument(msg.str());
	}
		

	if (paths[a - 1][b - 1] == INT_MAX)
	{
		output << "Пути " << a << ">" << b << " не существует" << endl;
		return;
	}
	
	--a; --b;

	output << "Кратчайший путь: " << a + 1;
	unsigned j = a;
	unsigned k = b;
	while (paths[j][k] != b)
	{
		output << ">" << paths[j][k] + 1;
		j = paths[j][k];
	}
	output << ">" << paths[j][k] + 1;
}
