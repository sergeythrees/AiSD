// 5.4. � ��������� ����� ������ ������������������ ����� �����.
//������������� ���� ������� �������� ������� � 4 �������(8).

#include "stdafx.h"
#include "WorkWithFile.h"
#include "MergeSort.h"

using namespace std;

int main(int argc, char *argv[]) try
{
	setlocale(LC_ALL, "rus");
	ifstream input(argv[1]);
	CheckFileAccess(input);

	vector<int> numbers;
	ReadNumbers(numbers, input);
	copy(numbers.begin(), numbers.end(), ostream_iterator<int>(std::cout, " "));

	cout << endl;

	MergeSort(numbers, 0, numbers.size());
	/*copy(numbers.begin(), numbers.end(), ostream_iterator<int>(std::cout, " "));
	cout << endl;*/

    return EXIT_SUCCESS;
}
catch (const exception& ex)
{
	cerr << ex.what() << endl;
	return EXIT_FAILURE;
}

