#include <iostream>
#include <vector>
#include <string>
#include "./headers/graph_builder.h"
#include "./headers/path_finder.h"
#include "./headers/data_loader.h"
namespace fs = std::filesystem;
using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 3) {
    // cerr << "Invalid number of arguments. Passed: " << argc - 1 << ". Required: " << 2 << endl;
    // return EXIT_FAILURE;
    // return 0;
  }

  fs::path root = fs::current_path();

  // Handle CMake internal build edge case
  if (root.string().find("build") != string::npos)
    root = root.parent_path();

  DataLoader data_loader(root.string());
  vector<string> cities;
  vector<vector<int>> cost_matrix;

  try {
    cities = data_loader.loadCities();
    cost_matrix = data_loader.loadCosts();
  } catch (runtime_error error) {
    cerr << error.what() << endl;
    return EXIT_FAILURE;
  }

  Graph graph;
  vector<pair<string, int>> result;

  try {
    graph = GraphBuilder::assemble(cost_matrix, cities);
    PathFinder* path_finder = new PathFinder(graph);
    result = path_finder->solve("Castle Black", "Riverrun");
  } catch (runtime_error error) {
    cerr << error.what() << endl;
    return EXIT_FAILURE;
  }

  for (auto& [path, cost]: result)
    cout << path << ": " << cost << endl;

  return EXIT_SUCCESS;
}