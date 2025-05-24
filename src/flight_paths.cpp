#include <iostream>
#include <vector>
#include <string>
#include "./headers/graph_builder.h"
#include "./headers/path_finder.h"
#include "./headers/data_loader.h"
using namespace std;

int main() {
  DataLoader data_loader;
  ifstream file = ifstream("../test_data/cities.csv");

  if (!file) {
    cerr << "Failed to open cities.csv" << endl;
    return 1;
  }

  auto cities = data_loader.loadCities(file);

  file = ifstream("../test_data/costs.csv");

  if (!file) {
    cerr << "Failed to open costs.csv" << endl;
    return 1;
  }

  auto cost_matrix = data_loader.loadCosts(file);

  Graph graph = GraphBuilder::assemble(cost_matrix, cities);
  PathFinder* path_finder = new PathFinder(graph);
  auto result = path_finder->solve("Castle Black", "Riverrun");

  for (auto& [path, cost]: result)
    cout << path << ": " << cost << endl;

  return 0;
}