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

#include "spider.h"


#include "gettoc.h"

namespace intentspider {

edge* intentgraph::find(uint32_t u, uint32_t v) {
auto it = adj.find(u);
if (it == adj.end()) return nullptr;


for (auto& e : it>second)
if (e.target == v) return &e;




return nullptr;

