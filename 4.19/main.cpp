//19. Реализовать алгоритм поиска кратчайших путей Дейкстры и
//проиллюстрировать по шагам этапы его выполнения (10).

#include "stdafx.h"
#include "Matrix.h"
#include "Dijkstra.h"
#include "WorkWithFiles.h"

using namespace std;

void MainLoop(vector<vector<unsigned>> const &matrix, ostream &output);

int main(int argc, char *argv[])
{
		setlocale(LC_ALL, "rus");
		ifstream input(argv[1]);
		if (!IsFileOpened(input))
			return EXIT_FAILURE;

	unsigned nodesCount;
	cout << "Введите количество узлов: ";
	cin >> nodesCount;

	vector<vector<unsigned>> matrix(nodesCount, vector<unsigned>(nodesCount, 0));

	ReadEdges(matrix, input, cout);

	MainLoop(matrix, cout);

	return EXIT_SUCCESS;
}

void MainLoop(vector<vector<unsigned>> const & matrix, ostream &output)
{
	while (!cin.eof() || !cin.fail())
	{
		unsigned startNode;
		cout << endl << "Введите начальный узел: ";
		if (cin >> startNode)
		{
			if (startNode < 1 || startNode >= matrix.size()+1)
			{
				cout << "Начальный узел должен быть в диапазоне (1.." << matrix.size() << ")" << endl;
				continue;
			}
			
			Dijkstra(matrix, startNode - 1, output);
		}
	}
}

