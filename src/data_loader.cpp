#include "./headers/data_loader.h"
#include "./headers/string_helper.h"
using namespace std;

#define MAX_SIZE 8

DataLoader::DataLoader(string root): root(std::move(root)) {}

vector<string> DataLoader::loadCities() {
  string full_path = root + "/test_data/cities.csv";
  ifstream file(full_path);
  string line;
  vector<string> cities;

  if (!file)
    throw runtime_error("Failed to load: " + full_path);

  if (getline(file, line))
    cities = parseCsvLine(line);

  validateCities(cities, full_path);

  return cities;
}

vector<vector<int>> DataLoader::loadCosts() {
  string full_path = root + "/test_data/costs.csv";
  ifstream file(full_path);
  vector<vector<int>> cost_matrix;
  string line;

  if (!file)
    throw runtime_error("Failed to load: " + full_path);

  while (getline(file, line)) {
    vector<string> tokens = parseCsvLine(line);
    vector<int> row;

    for (const string& cost: tokens) {
      // cost matrix should contain numbers only
      if (!isNumber(cost))
        throw runtime_error("Invalid test data: " + full_path + " - integer numerical data required");
      
      int cost_n = stoi(cost);
      
      // Assuming negative numbers are not allowed either
      if (cost_n < 0)
        throw runtime_error("Invalid test data: " + full_path + " - negative value found");

      row.push_back(cost_n);
    }

    // At each step check if the rows loaded are the same size
    if (!cost_matrix.empty() && cost_matrix.back().size() != row.size())
      throw runtime_error("Invalid test data: " + full_path + " - row sizes not equal");

    cost_matrix.push_back(row);
  }

  validateMatrix(cost_matrix, full_path);

  return cost_matrix;
}

bool DataLoader::isNumber(const string& s) {
  return !s.empty() && all_of(s.begin(), s.end(), ::isdigit);
}

vector<string> DataLoader::parseCsvLine(const string& line) {
  vector<string> tokens;
  int start, end = 0;
  char delim = ',';

  while ((start = line.find_first_not_of(delim, end)) != string::npos) {
    end = line.find(delim, start);
    string token = StringHelper::trim(line.substr(start, end - start));

    if (!token.empty())
      tokens.push_back(token);
  }

  return tokens;
}

void DataLoader::validateMatrix(vector<vector<int>>& cost_matrix, const string& full_path) {
  if (cost_matrix.empty())
    throw runtime_error("Invalid test data: " + full_path + " - Empty matrix");

  if (cost_matrix.size() != cost_matrix.front().size())
    throw runtime_error("Invalid test data: " + full_path + " - Square Matrix required");

  if (cost_matrix.size() > MAX_SIZE)
    throw runtime_error("Invalid test data: " + full_path + " - Matrix Max size is 8x8");
}

void DataLoader::validateCities(vector<string>& cities, const string& full_path) {
  if (cities.empty())
    throw runtime_error("Invalid test data: " + full_path + " - no cities found");

  unordered_set<string> seen;

  for (auto& city: cities) {
    auto city_lowercased = StringHelper::toLower(city);
    if (seen.contains(city_lowercased))
      throw runtime_error("Invalid test data: " + full_path + " - cities must be unique");

    seen.insert(city_lowercased);
  }
}