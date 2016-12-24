#pragma once
#include "stdafx.h"

void Dijkstra(std::vector<std::vector<unsigned>> const &matrix, unsigned const &startNode, std::ostream &output);
void PrintCurrentDistances(std::vector<unsigned> const &distance, std::ostream &output);
void ShowPath(std::vector<unsigned> &parents, unsigned const &node, unsigned const &startNode, std::ostream &output);
