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



}

const edge* intentgraph::find(uint32_t u, uint32_t v) const {
auto it = adj.find(u);
if (it == adj.end()) return nullptr;
for (const auto& e : it>second)
if (e.target == v) return &e;
return nullptr;
}


double intentgraph::weight(const edge& e, double now) const {
double dt = now - e.tw;
if (dt < 0.0) dt = 0.0;
return e.w * std::exp(-dt / cfg.tauv);
}

void intentgraph::reinforce(uint32_t u, uint32_t v, double now,
double valprime) {
if (u == v) return;




edge* e = find(u, v);
if (!e) {
adj[u].push_back(edge{});




e = &adj[u].back();
e>target = v;


e>tf = cfg.tfinit;
e>tw = now;
e>ts = now;
}

e>w = weight(*e, now) + cfg.eta;



e>tw = now;

double dt = now - e>ts;
if (dt < 0.0) dt = 0.0;

double snew = e>s * std::exp(-dt / cfg.tauv) + cfg.eta * valprime;




e>s = std::max(-1.0, std::min(1.0, snew));







e>negacc = e>negacc * std::exp(-dt / cfg.tprime) + std::max(0.0, -e>s);
if (e>negacc > cfg.thetas) {
