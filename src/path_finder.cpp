#include "./headers/path_finder.h"
using namespace std;

PathFinder::PathFinder(Graph& graph) {
  this->graph = graph;
}

vector<pair<string, int>> PathFinder::solve(const string& start_city, const string& end_city) {
  vector<pair<string, int>> result;
  dfsTraversal(start_city, end_city, "", 0, result);

  return result;
}

void PathFinder::dfsTraversal(const string& city, const string& end_city, string curr_path, int cost,
  vector<pair<string, int>>& result) {
  curr_path = curr_path + city + " -> ";

  if (city == end_city) {
    result.push_back({ curr_path.substr(0, curr_path.size() - 4), cost });
    return;
  }

  for (auto& [next_city, next_cost]: graph[city])
    dfsTraversal(next_city, end_city, curr_path, cost + next_cost, result);
}