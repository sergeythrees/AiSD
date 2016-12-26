// 5.4. В текстовом файле задана последовательность целых чисел.
//Отсортировать файл методом простого слияния с 4 лентами(8).

#include "stdafx.h"
#include <ctime>
#include "MergeSort.h"

using namespace std;


int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "rus");

	size_t beginTime = clock();
	OutsideMergeSort(argv[1]);
	size_t endTime = clock();
	cout << "Примерное время сортировки: " << ((endTime - beginTime) / 1000.0) << " c" << endl;

    return EXIT_SUCCESS;
}

