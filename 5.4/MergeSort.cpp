#include "stdafx.h"
#include "MergeSort.h"

using namespace std;

void OutsideMergeSort(char *name)
{
	int a1, a2, k, i, j, kol, tmp;
	FILE *f, *f1, *f2;
	kol = 0;
	if ((f = fopen(name, "r")) == NULL)
		printf("\n�������� ���� �� ����� ���� ��������...");
	else {
		while (!feof(f)) {
			fscanf(f, "%d", &a1);
			kol++;
		}
		fclose(f);
	}
	k = 1;
	while (k < kol) {
		f = fopen(name, "r"); f1 = fopen("smsort_1", "w"); f2 = fopen("smsort_2", "w");

		if (!feof(f)) fscanf(f, "%d", &a1);
		while (!feof(f)) {
			for (i = 0; i < k && !feof(f); i++) {
				fprintf(f1, "%d ", a1);
				fscanf(f, "%d", &a1);
			}
			for (j = 0; j < k && !feof(f); j++) {
				fprintf(f2, "%d ", a1);
				fscanf(f, "%d", &a1);
			}
		}
		fclose(f2); fclose(f1); fclose(f);

		f = fopen(name, "w"); f1 = fopen("smsort_1", "r"); f2 = fopen("smsort_2", "r");

		if (!feof(f1)) fscanf(f1, "%d", &a1);
		if (!feof(f2)) fscanf(f2, "%d", &a2);
		while (!feof(f1) && !feof(f2)) {
			i = 0;
			j = 0;
			while (i < k && j < k && !feof(f1) && !feof(f2)) {
				if (a1 < a2) {
					fprintf(f, "%d ", a1);
					fscanf(f1, "%d", &a1);
					i++;
				}
				else {
					fprintf(f, "%d ", a2);
					fscanf(f2, "%d", &a2);
					j++;
				}
			}
			while (i < k && !feof(f1)) {
				fprintf(f, "%d ", a1);
				fscanf(f1, "%d", &a1);
				i++;
			}
			while (j < k && !feof(f2)) {
				fprintf(f, "%d ", a2);
				fscanf(f2, "%d", &a2);
				j++;
			}
		}
		while (!feof(f1)) {
			fprintf(f, "%d ", a1);
			fscanf(f1, "%d", &a1);
		}
		while (!feof(f2)) {
			fprintf(f, "%d ", a2);
			fscanf(f2, "%d", &a2);
		}
		fclose(f2);
		fclose(f1);
		fclose(f);
		k *= 2;
	}
	remove("smsort_1");
	remove("smsort_2");
}

//void Merge(std::vector<int>& numbers, size_t part1Begin, size_t part2Begin, size_t part2End)
//{
//	std::vector<int> temp;
//	size_t begin = part1Begin;
//	size_t medium = part2Begin;
//	size_t end = part2End;
//
//	while (temp.size() < end - begin)
//	{
//		if (part1Begin >= medium || (part2Begin < end && numbers[part2Begin] < numbers[part1Begin]))
//		{
//			temp.push_back(numbers[part2Begin]);
//			++part2Begin;
//		}
//		else
//		{
//			temp.push_back(numbers[part1Begin]);
//			++part1Begin;
//		}
//	}
//	for (size_t i = begin; i < end; ++i)
//		numbers[i] = temp[i - begin];
//}
//
//void Merge2stSort(std::vector<int>& numbers, size_t begin, size_t end)
//{
//	size_t part2Begin = begin + (end - begin) / 2;
//	
//	if (end - begin < 2)
//	{
//		return;
//	}
//	else if (end - begin == 2)
//	{
//		if (numbers[begin] > numbers[begin + 1])
//			std::swap(numbers[begin], numbers[begin + 1]);
//		return;
//	}
//
//	Merge2stSort(numbers, begin, part2Begin);
//	Merge2stSort(numbers, part2Begin, end);
//
//	std::vector<int> temp;
//	Merge(numbers, begin, part2Begin, end);
//
//	copy(numbers.begin(), numbers.end(), ostream_iterator<int>(std::cout, " "));
//	cout << endl;
//
//}
//
//void Merge4stSort(std::vector<int>& numbers, size_t begin, size_t end)
//{
//	size_t part2Begin = begin + (end - begin) / 4;
//	size_t part3Begin = part2Begin + (end - begin) / 4;
//	size_t part4Begin = part3Begin + (end - begin) / 4;
//
//	if (end - begin < 2)
//	{
//		return;
//	}
//	else if (end - begin == 2)
//	{
//		if (numbers[begin] > numbers[begin + 1])
//			std::swap(numbers[begin], numbers[begin + 1]);
//		return;
//	}
//	else if (end - begin >= 4)
//	{
//		Merge4stSort(numbers, begin, part2Begin);
//		Merge4stSort(numbers, part2Begin, part3Begin);
//		Merge4stSort(numbers, part3Begin, part4Begin);
//		Merge4stSort(numbers, part4Begin, end);
//	}
//	else
//	{
//		Merge4stSort(numbers, begin, part2Begin);
//	}
//
//	Merge(numbers, begin, part2Begin, part3Begin);
//	Merge(numbers, begin, part3Begin, part4Begin);
//	Merge(numbers, begin, part4Begin, end);
//
//	copy(numbers.begin(), numbers.end(), ostream_iterator<int>(std::cout, " "));
//	cout << endl;
//
//}
