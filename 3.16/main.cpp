#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
const size_t EMPTY = 0;
const size_t BEGIN = 1;
const size_t END = 0;
const size_t END_BEGIN = 1;

using namespace std;

struct Tree
{
	string name;
	int level=0;
	size_t status = EMPTY;
	Tree *left;
	Tree *right;
};
Tree *root;


struct stack
{
	Tree *Node;
	stack *Next;
};
stack *stackTop;

void StackAdd(Tree *vertex)
{
	stack *stackCurrent = new stack;
	stackCurrent->Next = stackTop;
	stackCurrent->Node = vertex;
	stackTop = stackCurrent;
}

void StackDel()
{
	stack *stackCurrent;
	stackCurrent = stackTop;
	stackTop = stackTop->Next;
	delete stackCurrent;
}

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
	Tree *currentNode, *prevEqualNode, *prevNode;       // *root = 0             
	currentNode = prevNode = nullptr;

	stackTop = new stack;
	stackTop->Next = nullptr;

	while (getline(inputFile, currentLine))
	{
		if ((currentNode = ReadVertex(currentLine)) == nullptr)
			break;

		if (currentNode->level == 0)                    // корень
		{
			*root = currentNode;
			prevNode = *root;
			StackAdd(prevNode);
			continue;
		}
		if (currentNode->level > prevNode->level)
		{// переход на следующий уровень
			stackTop->Node->left = currentNode;
		}
		else if (currentNode->level == prevNode->level)            // тот же уровень
		{
			stackTop->Node->right = currentNode;
		}
		else        // подъем по дереву
		{
			prevEqualNode = stackTop->Node;
			while (prevEqualNode->level != currentNode->level)
			{
				StackDel();
				prevEqualNode = stackTop->Node;
			}
			prevEqualNode->right = currentNode;
		}
		prevNode = currentNode;      // текуща€ вершина
		StackAdd(prevNode);
	}
}

Tree* FindLastRightNode(Tree *Top)
{
	Tree *current;
	current = Top;
	while (current)
	{
		while (current->left)
		{
			current = current->left;
		}
		if (current->right)
		{
			if (current->right->level <= Top->level)
				return current;
		}
		if (current->right == nullptr)
			return current;
		current = current->right;

	}
	return current;
}

Tree* ThreadingTree(Tree *root)
{

	Tree *head = new Tree;
	head->name = "Head";
	head->left = root;
	head->level = -1;
	head->right = nullptr;

	stackTop = new stack;
	stackTop->Node = head;
	stackTop->Next = nullptr;

	Tree *currentNode = root;

	while (currentNode != head)
	{
		if (currentNode->left != nullptr)
		{
			if (currentNode->right != nullptr)
			{
				StackAdd(currentNode->right);
			}
			currentNode = currentNode->left;
		}
		else if (currentNode->right != nullptr)
		{
			currentNode = currentNode->right;
		}
		else if ((currentNode->left = currentNode->right) == nullptr)
		{
			currentNode->right = stackTop->Node;
			currentNode->status = BEGIN;
			currentNode = stackTop->Node;

			StackDel();
		}

	}
	FindLastRightNode(root)->status = EMPTY;
	return root;
}

string VertexInfo(Tree *vertex)
{
	if (vertex == nullptr) //|| (vertex->level < 0)
		return "> вершина не найдена";
	string result;
	for (size_t i = 0; i < vertex->level; ++i) result += ".";
	result += vertex->name;
	if (vertex->right && !vertex->left)
		result += " ->" + vertex->right->name;

	/*switch (vertex->status)
	{
		case BEGIN:
			result += " ->" + vertex->right->name;
			break;
		case END:
			result += " <-";
			break;
		case END_BEGIN:
			result += " <- ->" + vertex->right->name;
			break;
		default:
				break;
	}*/

	return result;
}

void DelSubTree(Tree *vertex, Tree *parent)
{
	Tree *current = vertex;
	stackTop = new stack;
	stackTop = nullptr;
	while (current)
	{
		StackAdd(current);
		while (current->left)
		{
			current = current->left;
			StackAdd(current);
		}
		current = current->right;
	}

	if (vertex != root)
	{
		if (parent->left == vertex)
			parent->left = nullptr;
		else if (parent->right == vertex)
			parent->right = nullptr;
	}
	else
		root = nullptr;

	while (stackTop)
	{
		current = (*stackTop).Node;
		current->left = nullptr;
		current->right = nullptr;
		delete current;
		StackDel();
	}
}

Tree* FindBegin(Tree *endNode)
{
	Tree *current;
	current = root;
	while (current != endNode)
	{
		while (current->left)
		{
			if (current->left == endNode)
				return current;
			current = current->left;


		}
		if (current->right == endNode)
			return current;
		current = current->right;
	}
	return nullptr;
}

Tree* FindLeftBro(Tree *root, Tree *vertex)
{
	Tree *current;
	current = root;
	while (current)
	{
		while (current->left)
		{
			if (current->right == vertex)
				return current;
			current = current->left;
		}
		if (current->right)
		{
			if (current->right == vertex)
				return current;
		}
		current = current->right;
	}
	return current;
}

Tree* FindCurrentNode(string Name)
{
	Tree *current;
	current = root;
	while ((current != nullptr) && (current->level >= root->level) && (current->name != Name))
	{
		while (current->left)
		{
			current = current->left;
			if (current->name == Name) 
				return current;
		}
		current = current->right;
	}
	if (current != nullptr)
		if (current->level < 0)
			return nullptr;
	return current;
}

void Print()
{
	Tree *current;
	current = root;
	if (!root)
		std::cout << "ƒерево пустое" << endl;
	while ((current != nullptr))
	{
		if (current->level >= root->level)
		{
			std::cout << VertexInfo(current) << endl;
			while (current->left)
			{
				current = current->left;
				std::cout << VertexInfo(current) << endl;
			}
			current = current->right;
		}
		else
			break;
	}
}

void DelThreadSubTree(Tree *vertex)
{
	Tree* NodeBegin = FindBegin(vertex);
	Tree* LastRight = FindLastRightNode(vertex);
	if (vertex == root)
	{
		DelSubTree(vertex, nullptr);
		root = nullptr;
		return;
	}

	if (NodeBegin->left == vertex)
	{
		if (vertex->right && vertex->status !=BEGIN) //vertex have bro
		{
			NodeBegin->left = vertex->right;
			if (vertex->right->left)
			{
				LastRight->status = EMPTY;
			}
		}
		else
		{
			if (NodeBegin->right) // parent have bro
			{
				LastRight->status = EMPTY;
			}
			else
			{
				NodeBegin->right = LastRight->right;
				NodeBegin->status = LastRight->status;
				LastRight->status = EMPTY;
			}
		}
	}
	else if (NodeBegin->right == vertex)
	{
		if (vertex->right) //vertex have bro
		{
			Tree* leftBro = FindLeftBro(root, vertex);
			NodeBegin->right = vertex->right;
			if (leftBro)
			{
				leftBro->right = LastRight->right;
			}
		}
		else
		{
			NodeBegin->right = LastRight->right; //проверить чтобы nodeBegin была LastNodeBegin
			NodeBegin->status = LastRight->status;
			LastRight->status = EMPTY;
		}
	}
	LastRight->right = nullptr;
	DelSubTree(vertex, NodeBegin);
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

	root = new Tree;
	ReadFromFile(inputFile, &root);
	ThreadingTree(root);
	FindLastRightNode(root)->right = nullptr;
	Print();

	std::cout << endl;
	string SearchNodename;
	Tree* Nod;
	cout << "¬едите им€ вершины дл€ удалени€: ";
	while (getline(cin, SearchNodename))
	{
		if (SearchNodename.empty()) break;
		if (Nod = FindCurrentNode(SearchNodename))
		{
			cout << "- поддерево удалено -" << endl << endl;
			DelThreadSubTree(Nod);
		}
		else
			cout << "- данна€ вершина не найдена -" << endl << endl;
		Print();
		cout << endl;
		cout << "¬едите им€ вершины дл€ удалени€: ";
	}
    return 0;
}
