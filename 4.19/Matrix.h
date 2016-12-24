#pragma once

void ReadEdges(std::vector<std::vector<unsigned>> &matrix, std::ifstream &input, std::ostream &output);
bool IsValidEdge(unsigned const &x, unsigned const &y, unsigned const &weight,
	unsigned const &maxValue, std::ostream &output);
