#include "./headers/data_loader.h"
using namespace std;

vector<string> DataLoader::loadCities(istream& in) {
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

vector<vector<int>> DataLoader::loadCosts(istream& in) {
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

bool DataLoader::isNumber(string s) {
  return !s.empty() && find_if(s.begin(),  s.end(), [](unsigned char c) {
    return !isdigit(c);
  }) == s.end();
}