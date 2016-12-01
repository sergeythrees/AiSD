#include "stdafx.h"
#include "ThreadedTreeFunctions.h"

using namespace std;

void StackAdd(stack &stackTop, Tree *vertex)
{
	stack *stackCurrent = new stack;
	stackCurrent->Next = &stackTop;
	stackCurrent->Node = vertex;
	stackTop = *stackCurrent;
}

void StackDel(stack &stackTop)
{
	stack *stackCurrent;
	stackCurrent = &stackTop;
	stackTop = *(stackTop.Next);
	delete stackCurrent;
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
	if (vertex == nullptr) //|| (vertex->level < 0)
		return "> вершина не найдена";
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

void DelSubTree(Tree *vertex, stack &stackTop)
{
	Tree *current = vertex;
	while (current)
	{
		StackAdd(stackTop, current);
		while (current->left)
		{
			current = current->left;
			StackAdd(stackTop, current);
		}
		current = current->right;
	}
	while (&stackTop)
	{
		current = stackTop.Node;
		current->left = nullptr;
		current->right = nullptr;
		delete current;


		StackDel(stackTop);
	}
}

Tree* FindBegin(Tree *endNode, Tree *root)
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

Tree* FindLeftBro(Tree *root, Tree *vertex)
{
	Tree *current;
	current = root;
	while (current)
	{
		while (current->left)
		{
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

Tree* FindCurrentNode(string Name, Tree *root)
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

void Print(Tree *root)
{
	Tree *current;
	current = root;
	while ((current != nullptr) && (current->level >= root->level))
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

void DelThreadSubTree(Tree *vertex, Tree *root, stack &stackTop)
{
	Tree* NodeBegin = FindBegin(vertex, root);
	Tree* LastRight = FindLastRightNode(vertex);
	if (vertex == root)
	{
		DelSubTree(vertex, stackTop);
		root = nullptr;
		return;
	}

	if (NodeBegin->left == vertex)
	{
		if (vertex->right) //vertex have bro
		{
			NodeBegin->left = vertex->right;
			if (vertex->right->left)
			{
				LastRight->status = EMPTY;
				LastRight->right = nullptr;

			}
		}
		else
		{
			if (NodeBegin->right) // parent have bro
			{
				LastRight->status = EMPTY;
				LastRight->right = nullptr;
			}
			else
			{
				NodeBegin->right = LastRight->right;
				NodeBegin->status = LastRight->status;
				LastRight->status = EMPTY;
				LastRight->right = nullptr;
			}
		}

	}
	else if (NodeBegin->right == vertex)
	{
		if (vertex->right) //vertex have bro
		{
			Tree* leftBro = FindLeftBro(root, vertex)->right = vertex->right;
			LastRight->right = vertex->right;
			//if (leftBro->left)
			//{
			//	LastRight->right = = vertex->right;
			//}

		}
		else
		{
			NodeBegin->right = LastRight->right; //проверить чтобы nodeBegin была LastNodeBegin
			NodeBegin->status = LastRight->status;
			LastRight->status = EMPTY;
			LastRight->right = nullptr;
		}
	}

	DelSubTree(vertex, stackTop);


	//if (ver)
	//if ((vertex->status == END) || (vertex->status == END_BEGIN))
	//{
	//	NodeBegin = FindBegin(vertex);
	//	LastRight = FindLastRightNode(vertex);
	//	NodeBegin->right = LastRight->right;
	//	LastRight->right->status = EMPTY;
	//	LastRight->right = nullptr;
	//}
	//else // if (Top->status == EMPTY)
	//{
	//	NodeBegin = FindBegin(vertex);
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


}