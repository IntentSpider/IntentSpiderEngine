#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <array>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <random>
#include <utility>
#include <numeric>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <tuple>
#include <climits>
#include <cstring>

using namespace std;
using ll = long long;
using ss = string;

#pragma once

#ifndef _WIN32
#endif

namespace intentspider {




class rawterminal {
 public:
  rawterminal();
  ~rawterminal();
  rawterminal(const rawterminal&) = delete;
  rawterminal& operator=(const rawterminal&) = delete;

  
  int readkey();

