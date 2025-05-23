#pragma once

#include <string>
#include <vector>
#include "./graph.h"
using namespace std;

class GraphBuilder {
public:
  static Graph assemble(vector<vector<int>>& cost_matrix, vector<string>& cities);
};