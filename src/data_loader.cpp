#include "./headers/data_loader.h"
using namespace std;

DataLoader::DataLoader(string root): root(root) {}

vector<string> DataLoader::loadCities() {
  string full_path = root + "/test_data/cities.csv";
  ifstream file = ifstream(full_path);
  vector<string> cities;
  string line;

  if (!file)
    throw runtime_error("Failed to load: " + full_path);

  if (getline(file, line)) {
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

vector<vector<int>> DataLoader::loadCosts() {
  string full_path = root + "/test_data/costs.csv";
  ifstream file = ifstream(full_path);
  vector<vector<int>> cost_matrix;
  string line;

  if (!file)
    throw runtime_error("Failed to load: " + full_path);

  while (getline(file, line)) {
    int start, end = 0;
    char token = ',';
    vector<int> row;

    while ((start = line.find_first_not_of(token, end)) != string::npos) {
      end = line.find(token, start);
      string cost = line.substr(start, end - start);

      if (!isNumber(cost))
        throw runtime_error("Invalid test data: " + full_path + " - non numerical cost found");

      row.push_back(stoi(cost));
    }

    if (!cost_matrix.empty() && cost_matrix.back().size() != row.size())
      throw runtime_error("Invalid test data: " + full_path + " - rows incomplete or different sizes");

    cost_matrix.push_back(row);
  }

  if (cost_matrix.size() != cost_matrix.front().size())
    throw runtime_error("Invalid test data: " + full_path + " - rows and columns sizes don't match");

  return cost_matrix;
}

bool DataLoader::isNumber(string s) {
  return !s.empty() && find_if(s.begin(),  s.end(), [](unsigned char c) {
    return !isdigit(c);
  }) == s.end();
}