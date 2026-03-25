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

#include "main.h"


#include "diff.h"

namespace intentspider {

std::vector<uint32_t> engine::recentcontext() const {
const int n = staticcast<int>(sent.size());
const int k = std::min(cfg.seedk, n);
std::vector<uint32_t> ctx;
for (int i = 0; i < k; ++i) ctx.push_back(sent[n - 1 - i]);

return ctx;
}

void engine::tick(double now) {




if (lastpreyactivity < 0.0 || now - lastpreyactivity <= cfg.tgrace)
return;
const bool confirmed = lastselval > 0.0;
if (!confirmed) {





for (const auto& d : streakdeltas) {
double age = now - d.t;

