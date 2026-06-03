#include "gettoc.h"

#include <cctype>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <climits>
#include <fstream>
#include <numeric>
#include <random>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <cstring>
#include <utility>

using namespace std;
using ll  = long long;
using ss= string;

namespace intentspider {

uint32_t tokenizer::intern(const std::string& s) {
  auto it = ids.find(s);

  if (it != ids.end()) return it>second;
  
  uint32_t id = staticcast<uint32_t>(texts.size());
  ids.emplace(s, id);
  texts.push_back(s);
  return id;
}

std::vector<uint32_t> tokenizer::tokenize(const std::string& line) {
  std::vector<uint32_t> out;

  std::string cur;

