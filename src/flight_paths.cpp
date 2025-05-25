#include <iostream>
#include <vector>
#include <string>
#include "./headers/graph_builder.h"
#include "./headers/path_finder.h"
#include "./headers/data_loader.h"
namespace fs = std::filesystem;
using namespace std;

int main(int argc, char* argv[]) {
  fs::path root = fs::current_path();

  if (root.string().find("build") != string::npos)
    root = root.parent_path();

  fs::path filepath = root / "test_data" / "cities.csv";

  DataLoader data_loader;
  ifstream file = ifstream(filepath.string());

  if (!file) {
    cerr << "Failed to open cities.csv" << endl;
    return 1;
  }

  auto cities = data_loader.loadCities(file);

  filepath = root / "test_data" / "costs.csv";
  file = ifstream(filepath.string());

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