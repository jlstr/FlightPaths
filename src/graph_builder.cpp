#include <string>
#include <vector>
#include "./headers/graph_builder.h"
using namespace std;

Graph GraphBuilder::assemble(vector<vector<int>>& cost_matrix, vector<string>& cities) {
  int num_cities = cities.size();
  Graph graph;

  for (auto& city: cities)
    graph[city] = vector<pair<string, int>>();

  for (int i = 0; i < cost_matrix.size(); ++i) {
    if (cost_matrix[i].size() != num_cities)
      throw runtime_error("Invalid Input Matrix. Number of columns must match number of cities");

    for (int j = i + 1; j < cost_matrix[i].size(); ++j) {
      if (cost_matrix[i][j] > 0)
        graph[cities[i]].push_back({ cities[j], cost_matrix[i][j] });
    }
  }

  return graph;
}