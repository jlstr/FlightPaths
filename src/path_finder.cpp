#pragma once
#include <vector>
#include <string>
#include "./headers/graph.h"
#include "./graph_builder.cpp"
using namespace std;

class PathFinder {
private:
  Graph graph;

public:
  PathFinder(Graph& graph) {
    this->graph = graph;
  }

  vector<string> solve(const string& start_city, const string& end_city) {
    vector<string> result;
    dfsTraversal(start_city, end_city, "", result);

    return result;
  }

private:
  void dfsTraversal(const string& city, const string& end_city, string curr_path, vector<string>& result) {
    curr_path = curr_path + city + " -> ";

    if (city == end_city) {
      result.push_back(curr_path.substr(0, curr_path.size() - 4));
      return;
    }

    for (auto& [next_city, next_cost]: graph[city])
      dfsTraversal(next_city, end_city, curr_path, result);
  }
};