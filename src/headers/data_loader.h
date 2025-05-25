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
  bool isNumber(string s);
};