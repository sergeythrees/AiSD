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
	Tree *fath;         // отец в исходном дереве
	Tree *left;
	Tree *right;
};

struct stack
{
	Tree *Node;
	stack *Next;
};
stack *stackTop = nullptr;
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
	size_t level = 0;
	size_t  prevLevel = 0; // уровень предыдущей вершины
	Tree *currentNode, *prevEqualNode, *prevNode;       // *root = 0             
	currentNode = prevNode = nullptr;

	stack *Top = new stack;
	stack *stackCurrent;
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
			// q - предыдущая вершина того же уровня
			currentNode->fath = prevEqualNode->fath;   // отец тот же, что у брата
			prevEqualNode->right= currentNode;
													   //Top->Node->right = currentNode;
		}
		prevNode = currentNode;      // текущая вершина
	}
}

Tree* ThreadingTree(Tree *root)
{
	Tree *Head = new Tree;
	Head->name = "Head";
	Head->left = root;
	Head->level = -1;
	Head->right = nullptr;

	stack *Top = new stack;
	stack *stackCurrent;
	Top->Node = Head;
	Top->Next = nullptr;

	Tree *currentNode = root;

	while (currentNode != Head)
	{
		if (currentNode->left != nullptr)
		{
			if (currentNode->right != nullptr)
			{
				//StackAdd(currentNode->right, Top);
				stackCurrent = new stack;
				stackCurrent->Next = Top;
				stackCurrent->Node = currentNode->right;
				Top = stackCurrent;
			}
			currentNode = currentNode->left;
		}
		else if (currentNode->right != nullptr)
		{
			currentNode = currentNode->right;
		}
		else if ((currentNode->left = currentNode->right) == nullptr)
		{
			currentNode->right = Top->Node;
			Top->Node->status += END;
			currentNode->status += BEGIN;
			currentNode = Top->Node;

			//StackDel(Top);
			stackCurrent = Top;
			Top = Top->Next;
			delete stackCurrent;
		}

	}
	return root;
}

string VertexInfo(Tree *vertex)
{
	if ((vertex == nullptr) || (vertex->level < 0))
		return "вершина не найдена";
	string result;
	for (size_t i = 0; i < vertex->level; ++i) result += ".";
	result += vertex->name;
	if (vertex->status == BEGIN)
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

//void DelSubTree(Tree *vertex)
//{
//	if (vertex != nullptr)
//	{
//		DelSubTree(vertex->left);
//		DelSubTree(vertex->right);
//		delete vertex;
//	}
//}
void DelSubTree(Tree *vertex)
{
	Tree *current = vertex;
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
	while (stackTop)
	{
		current = stackTop->Node;
		current = nullptr;
		delete current;
		StackDel();
	}
}
Tree* FindBegin(Tree *root, Tree *endNode)
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

Tree* FindCurrentNode(Tree *root, string Name)
{
	Tree *current;
	current = root;
	while ((current->level >= root->level) && (current->name != Name) && (current!=nullptr))
	{
		while (current->left)
		{
			current = current->left;
			if (current->name == Name) 
				return current;
		}
		current = current->right;
	}
	if (current->level < 0)
		return nullptr;
	return current;
}

void Print(Tree *root)
{
	Tree *current;
	current = root;
	while ((current->level >= root->level) && (current != nullptr))
	{
		std::cout << VertexInfo(current) << endl;
		while (current->left)
		{
			current = current->left;
			std::cout << VertexInfo(current) << endl;
		}
		current = current->right;
	}
}

void DelThreadSubTree(Tree *vertex, Tree *root)
{
	Tree* NodeBegin = FindBegin(root, vertex);
	Tree* LastRight = FindLastRightNode(vertex);
	if (NodeBegin == vertex)
	{
		DelSubTree(vertex);
		return;
	}




	//if ((vertex->status == END) || (vertex->status == END_BEGIN))
	//{
	//	NodeBegin = FindBegin(root, vertex);
	//	LastRight = FindLastRightNode(vertex);
	//	NodeBegin->right = LastRight->right;
	//	LastRight->right->status = EMPTY;
	//	LastRight->right = nullptr;
	//}
	//else // if (Top->status == EMPTY)
	//{
	//	NodeBegin = FindBegin(root, vertex);
	//	LastRight = FindLastRightNode(vertex);

	//	if (NodeBegin->left == vertex)
	//		if (LastRight->right->name == "Head")
	//			NodeBegin->left = nullptr;
	//		else
	//			NodeBegin->left = LastRight->right;
	//	else if (NodeBegin->right == vertex)
	//		NodeBegin->right = LastRight->right;
	//	NodeBegin->status += vertex->status;
	//	LastRight->status = EMPTY;
	//	LastRight->right = nullptr;	
	//}

	DelSubTree(vertex);
}

int main()
{
	setlocale(LC_ALL, "rus");
	ifstream inputFile;
	inputFile.open("./res/tree.txt");
	if (!inputFile.is_open())
	{
		std::cout << "Can not open file" << endl;
		return -1;
	}
	Tree *root = nullptr;
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
		if (Nod = FindCurrentNode(root, SearchNodename))
		{
			std::cout << VertexInfo(Nod) << endl << endl;
			DelThreadSubTree(Nod, root);
		}
		else
			cout << "вершина не найдена" << endl;
		Print(root);
		std::cout << endl << endl << endl;
	}

    return 0;
}
