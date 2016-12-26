#include "stdafx.h"
#include "MergeSort.h"

using namespace std;

void Merge(std::vector<int>& numbers, size_t part1Begin, size_t part1End, size_t part2Begin, size_t part2End)
{
	std::vector<int> temp;
	size_t begin = part1Begin;
	size_t end = part2End;

	while (temp.size() < end - begin)
	{
		if (part1Begin >= part1End || (part2Begin < end && numbers[part2Begin] < numbers[part1Begin]))
		{
			temp.push_back(numbers[part2Begin]);
			++part2Begin;
		}
		else
		{
			temp.push_back(numbers[part1Begin]);
			++part1Begin;
		}
	}
	for (size_t i = begin; i < end; ++i)
		numbers[i] = temp[i - begin];
}

void MergeSort(std::vector<int>& numbers, size_t begin, size_t end)
{
	size_t part1Begin = begin;
	size_t part1End = begin + (end - begin) / 4;
	size_t part2Begin = part1End;
	size_t part2End = part2Begin + (end - begin) / 4;
	size_t part3Begin = part2End;
	size_t part3End = part3Begin + (end - begin) / 4;
	size_t part4Begin = part3End;
	size_t part4End = end;

	if (end - begin < 2)
	{
		return;
	}
	else if (end - begin == 2)
	{
		if (numbers[begin] > numbers[begin + 1])
			std::swap(numbers[begin], numbers[begin + 1]);
		return;
	}
	else if (end - begin >= 4)
	{
		MergeSort(numbers, part1Begin, part1End);
		MergeSort(numbers, part2Begin, part2End);
		MergeSort(numbers, part3Begin, part3End);
		MergeSort(numbers, part4Begin, part4End);
	}
	else
	{
		MergeSort(numbers, part1Begin, part1End);
	}

	Merge(numbers, part1Begin, part1End, part2Begin, part2End);
	Merge(numbers, part1Begin, part2End, part3Begin, part3End);
	Merge(numbers, part1Begin, part3End, part4Begin, part4End);

	copy(numbers.begin(), numbers.end(), ostream_iterator<int>(std::cout, " "));
	cout << endl;

}
