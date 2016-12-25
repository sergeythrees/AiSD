#pragma once

void ReadEdges(std::vector<std::vector<unsigned>> &matrix, std::ifstream &input, std::ostream &output);
bool IsValidEdge(int const &x, int const &y, int const &weight, std::ostream &output);
