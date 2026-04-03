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




if (age < 0.0) age = 0.0;
double normal = d.amount * std::exp(-age / cfg.tauv);
double target = d.amount * std::exp(-age * cfg.munconf / cfg.tauv);
graph.adjustweight(d.u, d.v, now, -(normal - target));
}
}
streakdeltas.clear();
preylast.clear();
lastpreyactivity = -1.0;

arousalt.resetstreak();
}




void engine::selectionevent(uint32_t u, uint32_t v, double now, double val) {

graph.reinforce(u, v, now, val);






preylast[edgekey(u, v)] = now;
lastpreyactivity = now;



for (auto it = preylast.begin(); it != preylast.end();) {
if (now - it>second > cfg.wactive)
it = preylast.erase(it);
else
++it;
}

if (preylast.size() > 1) {

double b = std::min(
cfg.etacluster * std::pow(1.0 + cfg.deltacomp,
staticcast<double>(preylast.size() - 1)),
cfg.bmax);
double denom = 0.0;
for (const auto& kv : preylast) {
uint32_t tv = staticcast<uint32_t>(kv.first & 0xffffffffu);



auto it = lastp.find(tv);
denom += (it != lastp.end() && it>second > 0.0) ? it>second
: cfg.masstrivial;
}
if (denom > 0.0) {
for (const auto& kv : preylast) {
uint32_t tu = staticcast<uint32_t>(kv.first >> 32);
uint32_t tv = staticcast<uint32_t>(kv.first & 0xffffffffu);
auto it = lastp.find(tv);
double ph = (it != lastp.end() && it>second > 0.0)
? it>second
: cfg.masstrivial;


double dw = b * ph / denom;
graph.addweight(tu, tv, now, dw);
streakdeltas.push_back({tu, tv, now, dw});




}
}
}


if (valstats.shock(val, cadence.correctionrate())) {
graph.suppressshock(u, v, now);
lastshockt = now;
recentshock = true;
}
valstats.update(val);
lastselval = val;
}




void engine::observetyped(const std::vector<uint32_t>& toks, double now) {
if (toks.empty()) return;
tokensobserved += toks.size();
tick(now);
lastval = cadence.valence();

applyoutcomes(toks.front());
for (uint32_t v : toks) {
std::vector<uint32_t> ctx = recentcontext();
if (!sent.empty()) selectionevent(sent.back(), v, now, lastval);
support.record(v, now, ctx);
sent.push_back(v);
}

clusters.add(arousalt.devsign(), arousalt.absdev(),
cadence.correctionrate(), lastval);
cadence.closewindow();
}





std::vector<suggestion> engine::predict(double now) {
tick(now);
lastranked.clear();
lastcontext.clear();
lastedgemass.clear();
dbg = debuginfo{};
lastval = cadence.valence();
dbg.valprime = lastval;


dbg.arousal = arousalt.arousal();
dbg.streak = arousalt.streak();
