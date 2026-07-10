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

inline uint64_t edgekey(uint32_t u, uint32_t v) {
return (staticcast<uint64_t>(u) << 32) | v;
}

struct diffusionresult {
std::unordered_map<uint32_t, double> p;
 
std::unordered_map<uint64_t, double> edgemass;
 
double entropy = 0.0;

bool truncated = false;
};








diffusionresult localpush(const std::unordered_map<uint32_t, double>& seed,
const intentgraph& g, const config& cfg, double now,
double alpha);

}


