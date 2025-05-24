#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "./headers/graph_builder.h"
#include "./headers/path_finder.h"
using namespace std;

bool isNumber(string s) {
  return !s.empty() && find_if(s.begin(),  s.end(), [](unsigned char c) {
    return !isdigit(c);
  }) == s.end();
}

vector<string> loadCities(istream& in) {
  vector<string> cities;
  string line;

  if (getline(in, line)) {
    int start, end = 0;
    char token = ',';

    while ((start = line.find_first_not_of(token, end)) != string::npos) {
      end = line.find(token, start);
      string city = line.substr(start, end - start);

      if (!city.empty())
        cities.push_back(city);
    }
  }

  return cities;
}

vector<vector<int>> loadCosts(istream& in) {
  vector<vector<int>> cost_matrix;
  string line;

  while (getline(in, line)) {
    int start, end = 0;
    char token = ',';
    vector<int> row;

    while ((start = line.find_first_not_of(token, end)) != string::npos) {
      end = line.find(token, start);
      string cost = line.substr(start, end - start);

      if (isNumber(cost))
        row.push_back(stoi(cost));
    }

    cost_matrix.push_back(row);
  }

  return cost_matrix;
}

int main() {
  ifstream file = ifstream("../test_data/cities.csv");

  if (!file) {
    std::cerr << "Failed to open cities.csv" << endl;
    return 1;
  }

  auto cities = loadCities(file);

  file = ifstream("../test_data/costs.csv");

  if (!file) {
    std::cerr << "Failed to open costs.csv" << endl;
    return 1;
  }

  auto cost_matrix = loadCosts(file);

  Graph graph = GraphBuilder::assemble(cost_matrix, cities);

  PathFinder* path_finder = new PathFinder(graph);
  auto result = path_finder->solve("Castle Black", "Winterfell");

  for (auto& [path, cost]: result)
    cout << path << ": " << cost << endl;

  return 0;
}