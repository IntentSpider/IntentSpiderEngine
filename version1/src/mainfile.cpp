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
dbg.prey = staticcast<int>(preylast.size());
dbg.substates = clusters.count();
dbg.shock = recentshock;
recentshock = false;
if (sent.empty()) return {};


std::unordered_map<uint32_t, double> seed;

const int n = staticcast<int>(sent.size());



const int k = std::min(cfg.seedk, n);
double total = 0.0;
for (int i = 0; i < k; ++i) {
uint32_t u = sent[n - 1 - i];




lastcontext.push_back(u);
double phi = graph.fandispersion(u, now);
double wgt =
(1.0 - phi) * std::exp(-staticcast<double>(i) / cfg.tauseed);



if (wgt > 0.0) {
seed[u] += wgt;

total += wgt;
}


}


double alphaeff = arousalt.alphaeffective();
dbg.alphaeff = alphaeff;

std::vector<suggestion> ranked;
lastp.clear();
if (total > 0.0) {
for (auto& kv : seed) kv.second /= total;




diffusionresult res = localpush(seed, graph, cfg, now, alphaeff);
lastedgemass = std::move(res.edgemass);
dbg.entropy = res.entropy;


std::unordered_set<uint32_t> exclude(lastcontext.begin(),
 lastcontext.end());


size_t positive = 0;
for (const auto& kv : res.p) {
if (kv.second <= 0.0) continue;
++positive;
lastp[kv.first] = kv.second;
if (!exclude.count(kv.first)) ranked.push_back({kv.first, kv.second});
}
std::sort(ranked.begin(), ranked.end(),
[](const suggestion& a, const suggestion& b) {
return a.score > b.score;
});

dbg.hnorm =
positive > 1
? std::min(1.0,
 res.entropy / std::log(staticcast<double>(positive)))
: 0.0;


if (ranked.size() >= 2) {
double rtop = residue(ranked[0].token, now);



double rsecond = residue(ranked[1].token, now);
if (rtop > 0.0 && rsecond < rtop) {
double sup = support.support(ranked[1].token, now, lastcontext);

if (sup > cfg.ccal * rtop) {
std::swap(ranked[0], ranked[1]);
dbg.arbitrated = true;
}
}



}
if (staticcast<int>(ranked.size()) > cfg.topn) ranked.resize(cfg.topn);
}


if (staticcast<int>(ranked.size()) < cfg.topn) {
std::unordered_set<uint32_t> exclude(lastcontext.begin(),
lastcontext.end());


const auto* es = graph.edges(sent.back());
if (es) {
std::vector<suggestion> hop;


for (const auto& e : *es) {
if (exclude.count(e.target)) continue;


if (graph.supstrength(e, now) > 0.0) continue;
bool seen = false;
for (const auto& s : ranked)
if (s.token == e.target) { seen = true; break; }
if (!seen) hop.push_back({e.target, graph.weight(e, now)});
}
std::sort(hop.begin(), hop.end(),
[](const suggestion& a, const suggestion& b) {
return a.score > b.score;
});
for (const auto& s : hop) {
if (staticcast<int>(ranked.size()) >= cfg.topn) break;
ranked.push_back(s);
}




}
}

lastranked = ranked;
if (ranked.empty()) return {};



double urgency = std::max(0.0, -lastval);
double exh = 0.0;
for (uint32_t u : lastcontext)
exh = std::max(exh, graph.exhaustion(u, ranked[0].token, now));
double n = cfg.beta1 * (1.0 - dbg.hnorm) + cfg.beta2 * urgency -
 cfg.beta3 * exh;
dbg.necessity = n;
bool inshockwindow = now - lastshockt <= cfg.wshock;
dbg.shockwindow = inshockwindow;

double kappat = cfg.kappan + (inshockwindow ? cfg.dkappashock : 0.0);
if (n <= kappat) {
dbg.gated = true;
return {};
}
return ranked;



}



std::unordered_map<uint32_t, double> engine::diffusefor(
const std::vector<uint32_t>& toks, double now) const {
std::unordered_map<uint32_t, double> out;


if (toks.empty()) return out;


std::unordered_map<uint32_t, double> seed;
const int n = staticcast<int>(toks.size());
const int k = std::min(cfg.seedk, n);

double total = 0.0;
for (int i = 0; i < k; ++i) {
uint32_t u = toks[n - 1 - i];




double phi = graph.fandispersion(u, now);
double wgt =
(1.0 - phi) * std::exp(-staticcast<double>(i) / cfg.tauseed);
if (wgt > 0.0) {
seed[u] += wgt;



total += wgt;
}

}
if (total <= 0.0) return out;
for (auto& kv : seed) kv.second /= total;
diffusionresult res = localpush(seed, graph, cfg, now, cfg.alpha);




for (const auto& kv : res.p)
if (kv.second > 0.0) out[kv.first] = kv.second;




return out;
}

void engine::accept(uint32_t token, double now) {
++tokensobserved;
tick(now);
if (!sent.empty()) selectionevent(sent.back(), token, now, lastval);
applyoutcomes(token);
support.record(token, now, lastcontext);
sent.push_back(token);
lastcontext.clear();
clusters.add(arousalt.devsign(), arousalt.absdev(),
cadence.correctionrate(), lastval);
cadence.closewindow();
}




void engine::applyoutcomes(uint32_t selected) {
if (lastranked.empty()) {
lastedgemass.clear();
return;
}

std::unordered_set<uint32_t> cands;


for (const auto& s : lastranked) cands.insert(s.token);
for (const auto& kv : lastedgemass) {
if (kv.second < cfg.masstrivial) continue;
uint32_t u = staticcast<uint32_t>(kv.first >> 32);
uint32_t v = staticcast<uint32_t>(kv.first & 0xffffffffu);
if (v == selected)
graph.updatetf(u, v, true);
