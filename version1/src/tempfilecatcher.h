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


#include "otherconfigs.h"
#include "spider.h"

namespace intentspider {






struct embeddingresult {
std::unordered_map<uint32_t, std::array<double, 2>> pos;
std::array<double, 2> centroid{0.0, 0.0};


