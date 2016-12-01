#include "stdafx.h"

const size_t EMPTY = 0;
const size_t BEGIN = 1;
const size_t END = 0;
const size_t END_BEGIN = 1;

struct Tree
{
	std::string name;
	int level = 0;
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

void StackAdd(stack &stackTop, Tree *vertex);
void StackDel(stack &stackTop);
Tree* ThreadingTree(Tree *root);
std::string VertexInfo(Tree *vertex);
void DelSubTree(Tree *vertex, stack &stackTop);
Tree* FindBegin(Tree *endNode, Tree *root);
Tree* FindLastRightNode(Tree *Top);
Tree* FindLeftBro(Tree *root, Tree *vertex);
Tree* FindCurrentNode(std::string Name, Tree *root);
void Print(Tree *root);
void DelThreadSubTree(Tree *vertex, Tree *root, stack &stackTop);