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
e>sup = 1.0;
e>tsup = now;
}
e>ts = now;
e>tlast = now;
}

void intentgraph::updatetf(uint32_t u, uint32_t v, bool outcome) {
edge* e = find(u, v);
if (!e) return;




e>tf += cfg.etatf * ((outcome ? 1.0 : 0.0) - e>tf);
}

void intentgraph::addweight(uint32_t u, uint32_t v, double now, double amount) {
edge* e = find(u, v);
if (!e) return;
e>w = weight(*e, now) + amount;
e>tw = now;



}

void intentgraph::adjustweight(uint32_t u, uint32_t v, double now,
 double amount) {
edge* e = find(u, v);
if (!e) return;
e>w = std::max(0.0, weight(*e, now) + amount);
e>tw = now;
}

void intentgraph::suppressshock(uint32_t u, uint32_t v, double now) {
edge* e = find(u, v);
if (!e) return;

e>sup = 1.0;
e>shock = 1.0;
e>tsup = now;
}

double intentgraph::supstrength(const edge& e, double now) const {
if (e.sup <= 0.0) return 0.0;
double dt = now - e.tsup;
if (dt < 0.0) dt = 0.0;


double tau = e.shock > 0.0 ? cfg.taushock : cfg.tausupp;

double v = e.sup * std::exp(-dt / tau);
return v < cfg.supmin ? 0.0 : v;


}

double intentgraph::signedweight(const edge& e, double now) const {
double w = weight(e, now);
double pos = istransmission(e) ? w : 0.0; 
double neg = cfg.gamma * supstrength(e, now) * w;
return pos - neg; 



}


double intentgraph::abssigneddegree(uint32_t u, double now) const {
const auto* es = edges(u);

if (!es) return 0.0;
double d = 0.0;
for (const auto& e : *es) d += std::fabs(signedweight(e, now));
return d;
}

double intentgraph::fandispersion(uint32_t u, double now) const {
const auto* es = edges(u);
if (!es) return 0.0;
double tot = 0.0;
std::vector<double> ws;
for (const auto& e : *es) {
if (!istransmission(e)) continue;
double w = weight(e, now);
if (w > 0.0) {
ws.push_back(w);


tot += w;
}
}
if (ws.size() < 2 || tot <= 0.0) return 0.0;
double h = 0.0;




for (double w : ws) {
double q = w / tot;



h -= q * std::log(q);
}
return std::min(1.0, h / std::log(staticcast<double>(ws.size())));
}

double intentgraph::exhaustion(uint32_t u, uint32_t v, double now) const {
const edge* e = find(u, v);
if (!e || e>tlast < 0.0) return 0.0;



double age = std::max(0.0, now - e>tlast);




return std::exp(-age / cfg.taux);


}

double intentgraph::maxtimestamp() const {
double maxt = 0.0;
for (const auto& kv : adj) {
for (const auto& e : kv.second) {
maxt = std::max(maxt, e.tw);
maxt = std::max(maxt, e.ts);
maxt = std::max(maxt, e.tsup);
if (e.tlast > -1.0e17) maxt = std::max(maxt, e.tlast);




}
}
return maxt;
}

void intentgraph::shifttimestamps(double delta) {
if (delta == 0.0) return;
for (auto& kv : adj) {
for (auto& e : kv.second) {
e.tw += delta;
e.ts += delta;




e.tsup += delta;
if (e.tlast > -1.0e17) e.tlast += delta;
}
}
}

const std::vector<edge>* intentgraph::edges(uint32_t u) const {
auto it = adj.find(u);
return it == adj.end() ? nullptr : &it>second;
}




double intentgraph::transmissionoutdegree(uint32_t u, double now) const {
const auto* es = edges(u);
if (!es) return 0.0;
double d = 0.0;
for (const auto& e : *es)
if (istransmission(e)) d += weight(e, now);
return d;
}

bool intentgraph::save(const std::string& path, const tokenizer& tok,
 const persistedstats& st) const {
std::ofstream out(path);
if (!out) return false;
out << strplaceholder0;
out.precision(17);
out << strplaceholder0 << st.cadencebaseline << strplaceholder1 << st.ratemu << strplaceholder2
<< st.ratevar << strplaceholder0 << st.valmu << strplaceholder1 << st.valvar << strplaceholder2
