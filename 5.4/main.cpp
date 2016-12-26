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

	cout << "�������� ������ �����:" << endl;
	copy(numbers.begin(), numbers.end(), ostream_iterator<int>(std::cout, " "));
	cout << endl << endl;

	cout << "������� ���������� ��������, � ���������� �� 2 ����� (�����):" << endl;
	Merge2stSort(vector<int>(numbers), 0, numbers.size());
	cout << endl;

	cout << "������� ���������� ��������, � ���������� �� 4 ����� (�����):" << endl;
	Merge4stSort(numbers, 0, numbers.size());
	cout << endl;

    return EXIT_SUCCESS;
}
catch (const exception& ex)
{
	cerr << ex.what() << endl;
	return EXIT_FAILURE;
}

