#pragma once

#include "./graph.h"
using namespace std;

class PathFinder {
private:
  Graph graph;
  unordered_map<string, string> city_name_mapper;

public:
  PathFinder(Graph& graph);

  vector<pair<string, int>> solve(const string& start_city, const string& end_city);

private:
  void dfsTraversal(const string& city, const string& end_city, string curr_path, int cost,
    vector<pair<string, int>>& result);
};