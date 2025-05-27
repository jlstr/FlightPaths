#include "./headers/string_helper.h"
using namespace std;

string StringHelper::toLower(const string& s) {
  string result = s;
  transform(result.begin(), result.end(), result.begin(), ::tolower);

  return result;
}