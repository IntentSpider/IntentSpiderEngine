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


size_t inter = 0;
for (uint32_t x : sa)
if (sb.count(x)) ++inter;
size_t uni = sa.size() + sb.size() - inter;
return uni ? staticcast<double>(inter) / staticcast<double>(uni) : 0.0;
}



}

void supportindex::record(uint32_t token, double now,
const std::vector<uint32_t>& ctx) {
auto& dq = events[token];
dq.push_back({now, ctx});
while (staticcast<int>(dq.size()) > cfg.historycap) dq.popfront();
}

void supportindex::shifttimestamps(double delta) {
if (delta == 0.0) return;




for (auto& kv : events)
for (auto& ev : kv.second) ev.t += delta;




}

double supportindex::support(uint32_t token, double now,
 const std::vector<uint32_t>& ctx) const {
auto it = events.find(token);
if (it == events.end()) return 0.0;
double total = 0.0;
for (const auto& ev : it>second) {
double r = std::exp(-(now - ev.t) / cfg.tau0);
double s = jaccard(ev.ctx, ctx);
