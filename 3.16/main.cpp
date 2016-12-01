#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include "ThreadedTreeFunctions.h"

using namespace std;




string ReadName(string line, size_t &readPos)
{
	string name;

	for (; (line[readPos] != '\0') && (line[readPos] != ' '); readPos++)
		name += line[readPos];

	return name;
}

Tree* ReadVertex(string &line)
{
	if (line.empty())
		return nullptr;

	size_t level = 0;
	while (line[level] == '.') level++;     // k-уровень вершины
	Tree *newVertex = new Tree;

	size_t readPos = level;
	newVertex->name = ReadName(line, readPos);
	line.clear();


	newVertex->level = level;
	newVertex->left = nullptr;
	newVertex->right = nullptr;

	return newVertex;
}

void ReadFromFile(ifstream & inputFile, Tree **root)
{
	string currentLine;
	size_t level = 0;
	size_t  prevLevel = 0; // уровень предыдущей вершины
	Tree *currentNode, *prevEqualNode, *prevNode;       // *root = 0             
	currentNode = prevNode = nullptr;

	stack *Top = new stack;
//	stack *stackCurrent;
	Top->Next = nullptr;

	while (getline(inputFile, currentLine))
	{
		if ((currentNode = ReadVertex(currentLine)) == nullptr)
			break;
		
		if (currentNode->level == 0)                    // корень
		{
			*root = currentNode;
			prevNode = *root;
			continue;
		}
		if (currentNode->level > prevNode->level)
		{// переход на следующий уровень
			prevNode->left = currentNode;
			currentNode->fath = prevNode;
		}
		else if (currentNode->level == prevNode->level)            // тот же уровень
		{
			prevNode->right = currentNode;
			currentNode->fath = prevNode->fath;  // отец тот же
		}
		else        // подъем по дереву на m-k уровней
		{
			prevEqualNode = prevNode;
			for (size_t i = 0; i < prevNode->level - currentNode->level; i++) prevEqualNode = prevEqualNode->fath;
			// q - предыдуща€ вершина того же уровн€
			currentNode->fath = prevEqualNode->fath;   // отец тот же, что у брата
			prevEqualNode->right= currentNode;
													   //Top->Node->right = currentNode;
		}
		prevNode = currentNode;      // текуща€ вершина
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	ifstream inputFile;
	inputFile.open("./res/tree.txt");
	if (!inputFile.is_open())
	{
		std::cout << "Ќе получаетс€ открыть файл " << endl;
		return -1;
	}

	Tree *root = nullptr;
	stack *stackTop = nullptr;

	ReadFromFile(inputFile, &root);
	ThreadingTree(root);
	Print(root);
	std::cout << endl;
	string SearchNodename;
	Tree* Nod;
	FindLastRightNode(root)->right = nullptr;
	while (getline(cin, SearchNodename))
	{
		if (SearchNodename.empty()) break;
		if (Nod = FindCurrentNode(SearchNodename, root))
		{
			cout << "> будет удалена вершина | " << VertexInfo(Nod) << " |"<< endl << endl;
			DelThreadSubTree(Nod, root, *stackTop);
		}
		else
			cout << "> вершина не найдена" << endl;
		Print(root);
		std::cout << endl << endl << endl;
	}

    return 0;
}
