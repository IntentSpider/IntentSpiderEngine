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

#include "diff.h"


namespace intentspider {

diffusionresult localpush(const std::unordered_map<uint32_t, double>& seed,
const intentgraph& g, const config& cfg, double now,
double alpha) {
diffusionresult out;
std::unordered_map<uint32_t, double> r;
std::deque<uint32_t> queue;

for (const auto& kv : seed) {
r[kv.first] = kv.second;
if (std::fabs(kv.second) >= cfg.eps) queue.push_back(kv.first);
}

long ops = 0;

while (!queue.empty()) {
if (++ops > cfg.maxpushops) {
out.truncated = true;
break;
}
uint32_t u = queue.front();
queue.popfront();




double ru = r[u];
if (std::fabs(ru) < cfg.eps) continue;
r[u] = 0.0;




out.p[u] += alpha * ru;

double dabs = g.abssigneddegree(u, now);
if (dabs <= 0.0) continue;




const auto* es = g.edges(u);
double spread = (1.0 - alpha) * ru;

for (const auto& e : *es) {
double sw = g.signedweight(e, now);
if (sw == 0.0) continue;
double delta = spread * (sw / dabs);


double& rv = r[e.target];
double before = std::fabs(rv);
rv += delta;
