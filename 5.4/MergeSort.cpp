#include "stdafx.h"
#include "MergeSort.h"

using namespace std;

void MergeSort(std::vector<int>& numbers, size_t begin, size_t end)
{
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

	MergeSort(numbers, begin, begin + (end - begin) / 2);
	MergeSort(numbers, begin + (end - begin)/2, end);

	std::vector<int> temp;
	size_t part1Begin = begin;
	size_t part1End = begin + (end - begin) / 2;
	size_t part2Begin = part1End;
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
		numbers[i] = temp[i-begin];

	copy(numbers.begin(), numbers.end(), ostream_iterator<int>(std::cout, " "));
	cout << endl;

}
