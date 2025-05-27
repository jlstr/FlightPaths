#include <iostream>
#include "./headers/path_finder.h"
#include "./headers/string_helper.h"
using namespace std;

PathFinder::PathFinder(Graph& graph) {
  this->graph = graph;

  for (auto& [city_key, _]: graph)
    city_name_mapper[StringHelper::toLower(city_key)] = city_key;
}

vector<pair<string, int>> PathFinder::solve(const string& start_city, const string& end_city) {
  string start_city_lowercased = StringHelper::toLower(start_city);
  string end_city_lowercased = StringHelper::toLower(end_city);
  vector<pair<string, int>> result;

  if (!city_name_mapper.contains(start_city_lowercased))
    throw runtime_error(start_city + " not found in test data");

  if (!city_name_mapper.contains(end_city_lowercased))
    throw runtime_error(end_city + " not found in test data");

  dfsTraversal(city_name_mapper[start_city_lowercased], city_name_mapper[end_city_lowercased], "", 0, result);

  if (result.empty())
    throw runtime_error("No paths found between " + start_city + " and " + end_city);

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