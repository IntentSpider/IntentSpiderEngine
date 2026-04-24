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

#include "a.h"


namespace intentspider {

namespace {



double jaccard(const std::vector<uint32_t>& a, const std::vector<uint32_t>& b) {
if (a.empty() || b.empty()) return 0.0;
std::unordered_set<uint32_t> sa(a.begin(), a.end());
std::unordered_set<uint32_t> sb(b.begin(), b.end());


