#pragma once

#include <vector>
#include <string>
#include <fstream>
using namespace std;

class DataLoader {
private:
  string root;

public:
  DataLoader(string root);
  vector<string> loadCities();
  vector<vector<int>> loadCosts();

private:
  bool isNumber(const string& s);
  static vector<string> parseCsvLine(const string& line);
  void validateMatrix(vector<vector<int>>& cost_matrix, const string& full_path);
};