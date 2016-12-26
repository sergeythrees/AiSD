#include "stdafx.h"
#include "MergeSort.h"

using namespace std;

void Merge(std::vector<int>& numbers, size_t part1Begin, size_t part2Begin, size_t part2End)
{
	std::vector<int> temp;
	size_t begin = part1Begin;
	size_t medium = part2Begin;
	size_t end = part2End;

	while (temp.size() < end - begin)
	{
		if (part1Begin >= medium || (part2Begin < end && numbers[part2Begin] < numbers[part1Begin]))
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

void Merge2stSort(std::vector<int>& numbers, size_t begin, size_t end)
{
	size_t part2Begin = begin + (end - begin) / 2;
	
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

	Merge2stSort(numbers, begin, part2Begin);
	Merge2stSort(numbers, part2Begin, end);

	std::vector<int> temp;
	Merge(numbers, begin, part2Begin, end);

	copy(numbers.begin(), numbers.end(), ostream_iterator<int>(std::cout, " "));
	cout << endl;

}

void Merge4stSort(std::vector<int>& numbers, size_t begin, size_t end)
{
	size_t part2Begin = begin + (end - begin) / 4;
	size_t part3Begin = part2Begin + (end - begin) / 4;
	size_t part4Begin = part3Begin + (end - begin) / 4;

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
		Merge4stSort(numbers, begin, part2Begin);
		Merge4stSort(numbers, part2Begin, part3Begin);
		Merge4stSort(numbers, part3Begin, part4Begin);
		Merge4stSort(numbers, part4Begin, end);
	}
	else
	{
		Merge4stSort(numbers, begin, part2Begin);
	}

	Merge(numbers, begin, part2Begin, part3Begin);
	Merge(numbers, begin, part3Begin, part4Begin);
	Merge(numbers, begin, part4Begin, end);

	copy(numbers.begin(), numbers.end(), ostream_iterator<int>(std::cout, " "));
	cout << endl;

}
