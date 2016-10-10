#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

const string BRACKETS = "{()}";
struct charStack {
	char bracket;
	charStack *next;
};
charStack *stackTop, *stackCurrent;
vector<string> all;

bool IsValidArgumentsCount(int argumensCount)
{
	if (argumensCount != 3)
	{
		cout << "Wrong arguments count\n"
			<< "Usage: FixBrackets.exe <input file> <output file>\n";
		return false;
	}

	return true;
}

bool AreFilesOpened(const ifstream &input, const ofstream &output)
{
	if (!input.is_open())
	{
		cout << "Error with opening input file \n";
		return false;
	}

	if (!output.is_open())
	{
		cout << "Error with opening output file \n";
		return false;
	}
	return true;
}

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

bool CheckBrackets(const string &input, size_t &lineNumber)
{
	++lineNumber;
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
				cout << "Lishnaya skobka" << bracket << " v pos " << pos << " line " << lineNumber << endl;
				return false;
			}
	}
	return true;
}

void ReplaceBrackets(string &inputLine, const string &searchString, const string &replaceString)
{
	if (searchString == replaceString)
		return;
	size_t foundPosition = inputLine.find(searchString);
	if (foundPosition == inputLine.npos)
		return;

	size_t currentPosition = 0;
	string result;
	result.reserve(inputLine.length());

	while (foundPosition != inputLine.npos)
	{
		result.append(inputLine, currentPosition, foundPosition - currentPosition);
		result += replaceString;
		currentPosition = foundPosition + searchString.length();
		foundPosition = inputLine.find(searchString, currentPosition);
	}

	inputLine = result.append(inputLine, currentPosition, inputLine.length() - currentPosition);
}

bool IsStackEmpty()
{
	if (stackTop == nullptr)
		return true;

	size_t count = 0;
	while (stackTop != nullptr)
	{
		stackCurrent = stackTop;
		stackTop = stackTop->next;
		delete stackCurrent;
		++count;
	}
	cout << "Ne hvataet " << count << " zakryvayushih skobok" << endl;

	return false;
}

void FixBrackets(string &input)
{
	string result("");

	for (size_t pos = 0; pos < input.length(); ++pos)
	{
		char symbol = input[pos];
		if (symbol == '{')
		{
			if (stackTop == nullptr)
				result += '{';
			StackAdd('{');
		}
		else if (symbol == '}')
		{
			if (stackTop->next == nullptr)
				result += '}';
			StackDel('}');
		}
		else
			result += input[pos];
	}

	input.swap(result);
}

int main(int argc, char *argv[])
{
	if (!IsValidArgumentsCount(argc))
		return 1;

	ifstream input(argv[1]);
	ofstream output(argv[2]);

	if (!AreFilesOpened(input, output))
		return 1;

	stackTop = nullptr;
	string inputLine;
	size_t lineNumber = 0, position = 0;

	while (getline(input, inputLine))
	{
		if (!CheckBrackets(inputLine, lineNumber))
			return 0;
	}

	if (!IsStackEmpty())
		return 0;

	input.clear();
	input.seekg(0);

	while (getline(input, inputLine))
	{
		ReplaceBrackets(inputLine, "(*", "{");
		ReplaceBrackets(inputLine, "*)", "}");
		FixBrackets(inputLine);
		output << inputLine << endl;
	}

	return 0;
}