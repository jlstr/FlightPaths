#pragma once

#include <vector>
#include <string>
#include <fstream>
using namespace std;

class DataLoader {
public:
  vector<string> loadCities(istream& in);
  vector<vector<int>> loadCosts(istream& in);

private:
  bool isNumber(string s);
};