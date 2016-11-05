#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
const size_t MAX_LENGHT = 20;
const size_t EMPTY = 0;
const size_t BEGIN = 1;
const size_t END = 2;
const size_t END_BEGIN = 3;

using namespace std;

struct Tree
{
	string name;
	int level=0;
	size_t Stasus = EMPTY;
	Tree *fath;         // отец в исходном дереве
	Tree *left;
	Tree *right;
};

struct stack
{
	Tree *Node;
	stack *Next;
};

//stack *Top;
//stack *stackCurrent;

void StackAdd(Tree *Node, stack *Top)
{
	stack *temp = new stack;
	temp->Next = Top;
	temp->Node = Node;
	Top = temp;
}

void StackDel(stack *Top)
{
	stack *temp = Top;
	Top = Top->Next;
	delete temp;
}
string ReadName(string line, size_t &readPos)
{
	string name = "";

	for (; (line[readPos] != '\0') && (line[readPos] != ' '); readPos++)
		name += line[readPos];

	return name;
}

Tree* ReadNode(string &line)
{
	if (line.empty())
		return nullptr;

	size_t level = 0;
	while (line[level] == '.') level++;     // k-уровень вершины
	Tree *Node = new Tree;

	size_t readPos = level;
	Node->name = ReadName(line, readPos);
	line.clear();


	Node->level = level;
	Node->left = nullptr;
	Node->right = nullptr;

	return Node;
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
		if ((currentNode = ReadNode(currentLine)) == nullptr)
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

			//AddStask
			
			currentNode->fath = prevNode;
		}
		else if (currentNode->level == prevNode->level)            // тот же уровень
		{
			prevNode->right = currentNode;

			//AddStask;

			currentNode->fath = prevNode->fath;  // отец тот же
		}
		else        // подъем по дереву на m-k уровней
		{
			stackCurrent = new stack;
			//stackCurrent->Next = Top;
			stackCurrent->Node = prevNode;
			//Top = stackCurrent;
			prevEqualNode = prevNode;
			//while (stackCurrent->Node->level < prevLevel - currentNode->level)
			//{
			//StackDel;
			//}
			for (size_t i = 0; i < prevNode->level - currentNode->level; i++) prevEqualNode = prevEqualNode->fath;
			// q - предыдущая вершина того же уровня
			currentNode->fath = prevEqualNode->fath;   // отец тот же, что у брата
			prevEqualNode->right= currentNode;
													   //Top->Node->right = currentNode;
		}
		//prevLevel = level;      // текущий уровень
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
			Top->Node->Stasus += END;
			currentNode->Stasus += BEGIN;
			currentNode = Top->Node;

			//StackDel(Top);
			stackCurrent = Top;
			Top = Top->Next;
			delete stackCurrent;
		}

	}
	return Head;
}

string NodeInfo(Tree *node)
{
	if ((node == nullptr) || (node->level < 0))
		return "вершина не найдена";
	string result;
	for (size_t i = 0; i < node->level; ++i) result += ".";
	result += node->name;
	switch (node->Stasus)
	{
		case BEGIN:
			result += " ->" + node->right->name;
			break;
		case END:
			result += " <-";
			break;
		case END_BEGIN:
			result += " <- ->" + node->right->name;
			break;
		default:
				break;
	}

	return result;
}
void DelSubTree(Tree *Node)
{
	if (Node != nullptr)
	{
		DelSubTree(Node->left);
		DelSubTree(Node->right);
		delete Node;
	}
}
Tree* FindBeginThread(Tree *Root, Tree *EndNode)
{
	Tree *current;
	current = Root->left;
	while (current != EndNode)
	{
		while (current->left)
		{
			current = current->left;
		}
		if (current->right == EndNode)
			return current->right;
		current = current->right;
	}
}
Tree* FindLastRightThread(Tree *Top)
{
	Tree *current;
	current = Top->left;
	while (current->level > Top->level)
	{
		while (current->left)
		{
			current = current->left;
		}
		if (current->right->level <= Top->level)
			return current;
		current = current->right;
	}
}
Tree* FindCurrentNode(Tree *Top, string Name)
{
	Tree *current;
	current = Top;
	while ((current->level >= Top->level) && (current->name != Name) && (current!=nullptr))
	{
		while (current->left)
		{
			current = current->left;
		}
		current = current->right;
	}
	return current;
}
void DelThreadTree(Tree *Top, Tree *Parent)
{
	Tree* NodeBegin;
	Tree* LastRight;
	if ((Top->Stasus == END) || (Top->Stasus == END_BEGIN))
	{
		NodeBegin = FindBeginThread(Parent, Top);
		LastRight = FindLastRightThread(Top);
		NodeBegin->right = LastRight;
		LastRight->right->Stasus -= END;
		LastRight->right = nullptr;
	}
	else if (Top->Stasus == EMPTY)
	{
		if (Parent->right != nullptr)
			Parent->right->Stasus -= END;
		else
		{
			LastRight = FindLastRightThread(Top);
			Parent->right = LastRight->right;
			LastRight->Stasus = EMPTY;
			//LastRight->right = nullptr;
			LastRight->right = Parent->right;

		}
			
	}
	else if (Top->Stasus == BEGIN)
	{
		if (Parent->left != nullptr)
		{
			Parent->left->right = Top->right;
			Parent->left->Stasus = BEGIN;
		}
		else
		{
			if (Parent->right == nullptr)
				Parent->Stasus == Top->Stasus;
			Parent->right = Top->right;
		}
	}
	DelSubTree(Top);
}
void Print(Tree *tree)
{
	Tree *current;
	current = tree->left;
	while (current != tree)
	{
		while (current->left)
		{
			cout << NodeInfo(current) << endl;
			current = current->left;
		}
		cout << NodeInfo(current) << endl;
		current = current->right;
	}
}
int main()
{
	setlocale(LC_ALL, "rus");
	ifstream inputFile;
	inputFile.open("./res/tree.txt");
	if (!inputFile.is_open())
	{
		cout << "Can not open file" << endl;
		return -1;
	}
	Tree *root = nullptr;
	ReadFromFile(inputFile, &root);
	//DelSubTree(root);
	Print(ThreadingTree(root));
	cout << endl;
	string SearchNodename;
	while (getline(cin, SearchNodename))
	{
		cout << NodeInfo(FindCurrentNode(root, SearchNodename)) << endl;;
	}

	//FindBeginThread(root, ThreadingTree(root));
	//Tree *Head = ThreadingTree(root);
	//FindLastRightThread(Head);
	//DelThreadTree(root, Head);
    return 0;
}
