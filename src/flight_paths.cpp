#include <iostream>
#include <vector>
#include <string>
#include "./headers/graph.h"
#include "./headers/graph_builder.h"
#include "./headers/path_finder.h"
using namespace std;

int main() {
  vector<vector<int>> cost_matrix = {
    { 0, 15, 80, 90 },
    { 0, 0, 40, 50 },
    { 0, 0, 0, 70 },
    { 0, 0, 0, 0 },
  };

  vector<string> cities = { "Castle Black", "Winterfell", "Riverrun", "King's Landing" };
  Graph graph = GraphBuilder::assemble(cost_matrix, cities);
  PathFinder* path_finder = new PathFinder(graph);
  auto result = path_finder->solve("Castle Black", "Winterfell");

  for (auto& [path, cost]: result)
    cout << path << ": " << cost << endl;

  return 0;
}