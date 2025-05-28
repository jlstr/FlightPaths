#include "./headers/string_helper.h"
using namespace std;

string StringHelper::toLower(const string& s) {
  string result = s;
  transform(result.begin(), result.end(), result.begin(), ::tolower);

  return result;
}

string StringHelper::trim(const string& s) {
  int left = 0, right = s.size() - 1;

  while (left < right && (isspace(s[left]) || isspace(s[right]))) {
    if (isspace(s[left]))
      left++;
    
    if (isspace(s[right]))
      right--;
  }

  string trimmed = s.substr(left, right - left + 1);

  return trimmed == " " ? "" : trimmed;
}