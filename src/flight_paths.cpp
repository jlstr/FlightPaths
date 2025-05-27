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
    cerr << "Invalid number of arguments. Passed: " << argc - 1 << ". Required: " << 2 << endl;
    return EXIT_FAILURE;
  }

  // Program's main pipeline starts here
  //
  // 1. capture input cities
  const string& start_city = string(argv[1]);
  const string& end_city = string(argv[2]);

  // get a hold of the absolute path of the current working directory 
  fs::path root = fs::current_path();

  // Handle CMake internal build edge case
  if (root.string().find("build") != string::npos)
    root = root.parent_path();

  // DataLoader is the main class with the File Loading Logic
  DataLoader data_loader(root.string());
  vector<string> cities;
  vector<vector<int>> cost_matrix;

  // 2. Load test data from the CSV files located at /test_data
  try {
    cities = data_loader.loadCities();
    cost_matrix = data_loader.loadCosts();
  } catch (runtime_error error) {
    cerr << error.what() << endl;
    return EXIT_FAILURE;
  }

  // Graph will be a Directed Acyclic Graph (DAG) that will assembled
  // from the test data CSV files
  Graph graph;
  vector<pair<string, int>> result;

  // 3. Assemble Graph and pass it to the PathFinder class  to find possible
  // resulting paths
  try {
    graph = GraphBuilder::assemble(cost_matrix, cities);
    PathFinder* path_finder = new PathFinder(graph);
    result = path_finder->solve(start_city, end_city);
  } catch (runtime_error error) {
    cerr << error.what() << endl;
    return EXIT_FAILURE;
  }

  // 4. Output paths to C++'s Standard Output Stream
  for (auto& [path, cost]: result)
    cout << path << ": " << cost << endl;

  return EXIT_SUCCESS;
}