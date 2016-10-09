#include <iostream>
#include <vector>
using namespace std;

const string BRACKETS = "{()}";
struct charStack {
	char bracket;
	charStack *next;
};
charStack *stackTop, *stackCurrent;
vector<string> all;
void StackAdd(const char &bracket)
{
	stackCurrent = new charStack;
	stackCurrent->next = stackTop;
	stackCurrent->bracket = bracket;
	stackTop = stackCurrent;
}
bool StackDel(const char bracket)
{
	if (stackTop == nullptr)
		return false;
	if (bracket == '}')
		if (stackTop->bracket != '{')
			return false;
	if (bracket == ')')
		if (stackTop->bracket != '(')
			return false;

	stackCurrent = stackTop;
	stackTop = stackTop->next;
	delete stackCurrent;

	return true;
}
bool CheckBrackets(const string &input)
{
	for (size_t pos = 0; pos < input.length(); ++pos)
	{
		if (BRACKETS.find(input[pos]) == string::npos)
			continue;
		if (input[pos] == '(')
			if (input[pos + 1] != '*')
				continue;
		if (input[pos] == ')')
			if (input[pos - 1] != '*')
				continue;
		char bracket = input[pos];
		if ((bracket == '{') || (bracket == '('))
			StackAdd(bracket);
		if ((bracket == '}') || (bracket == ')'))
			if (!StackDel(bracket))
			{
				cout << "error in pos: " << pos << endl;
				return false;
			}
	}
	return true;
}
void ReplaseBrackets(string &input)
{
	string result("");
	for (size_t pos = 0; pos < input.length(); ++pos)
	{
		if (BRACKETS.find(input[pos]) == string::npos)
			result += input[pos];
		if (input[pos] == '(')
			if (input[pos + 1] != '*')
				result += input[pos];
		if (input[pos] == ')')
			if (input[pos - 1] != '*')
				result += input[pos];
		char bracket = input[pos];
		if ((bracket == '{') || (bracket == '('))
		{
			if (stackTop == nullptr)
				result += input[pos];
			else
				if (bracket == '(')
					++pos;
			StackAdd(bracket);
		}
		if ((bracket == '}') || (bracket == ')'))
		{
			if (stackTop->next != nullptr)
			{
				StackDel(bracket);
				if (bracket == ')')
					result[result.length() - 1] = '\0';
				continue;
			}
			if (StackDel(bracket))
				result += input[pos];
			else
				if (bracket == ')')
					result[result.length()] = '\0';
		}
	}
	input.swap(result);

}
int StackPrint()
{
	if ((stackCurrent = stackTop) == nullptr)
		return 1;
	cout << stackCurrent->bracket;
	while ((stackCurrent = stackCurrent->next) != nullptr)
	{
		cout << stackCurrent->bracket << " ";
	}
	cout << endl;
	return 0;
}
int main()
{
	string input;
	cin >> input;

	stackTop = nullptr;

	while ((input != "...") && CheckBrackets(input))
	{
		all.push_back(input);
		cout << endl;
		cin >> input;
	}

	if (stackTop != nullptr)
	{
		cout << "Не хватает закрывающей скобки" << endl;
		StackPrint();
		return 1;
	}

	stackTop = nullptr;

	for (vector<string>::iterator iter = all.begin(); iter != all.end(); iter++)
	{
		ReplaseBrackets(*iter);
		cout << *iter << endl;
	}
	return 0;
}