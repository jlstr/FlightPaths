#include <string>
#include <vector>
#include "./headers/graph_builder.h"
using namespace std;

Graph GraphBuilder::assemble(vector<vector<int>>& cost_matrix, vector<string>& cities) {
  Graph graph;

  for (int i = 0; i < cost_matrix.size(); ++i) {
    for (int j = i + 1; j < cost_matrix[i].size(); ++j) {
      if (cost_matrix[i][j] > 0)
        graph[cities[i]].push_back({ cities[j], cost_matrix[i][j] });
    }
  }

  return graph;
}