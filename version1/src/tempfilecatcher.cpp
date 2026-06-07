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

#include "tempfilecatcher.h"


namespace intentspider {

namespace {

double dot(const std::vector<double>& a, const std::vector<double>& b) {
double s = 0.0;
for (size_t i = 0; i < a.size(); ++i) s += a[i] * b[i];

return s;
}

void deflate(std::vector<double>& v, const std::vector<double>& w) {
double p = dot(v, w);


for (size_t i = 0; i < v.size(); ++i) v[i] -= p * w[i];
}

bool normalize(std::vector<double>& v) {
double n = std::sqrt(dot(v, v));




if (n < 1e12) return false;
for (auto& x : v) x /= n;
return true;
}

}


bool spectralembedding::compute(const intentgraph& g, double now) {
res = embeddingresult{};





std::unordered_map<uint32_t, std::unordered_map<uint32_t, double>> sym;



for (const auto& kv : g.adjacency()) {
for (const auto& e : kv.second) {
if (!g.istransmission(e)) continue;
double w = g.weight(e, now);
if (w <= 0.0) continue;
sym[kv.first][e.target] += w;
sym[e.target][kv.first] += w;
}
}




res.graphnodes = sym.size();
if (sym.size() < 3) return false;






std::unordered_map<uint32_t, int> comp;



int ncomp = 0;
for (const auto& kv : sym) {
if (comp.count(kv.first)) continue;


std::vector<uint32_t> stack{kv.first};
comp[kv.first] = ncomp;
while (!stack.empty()) {
uint32_t u = stack.back();




stack.pop_back();
for (const auto& nb : sym[u]) {
if (!comp.count(nb.first)) {
comp[nb.first] = ncomp;
stack.push_back(nb.first);


}

}
}
++ncomp;
}
std::vector<size_t> csize(ncomp, 0);

for (const auto& kv : comp) ++csize[kv.second];

int best = 0;




for (int c = 1; c < ncomp; ++c)
if (csize[c] > csize[best]) best = c;

std::vector<uint32_t> ids;



for (const auto& kv : comp)
if (kv.second == best) ids.push_back(kv.first);
std::sort(ids.begin(), ids.end());
const size_t n = ids.size();




if (n < 3) return false;
res.componentnodes = n;

std::unordered_map<uint32_t, size_t> idx;
for (size_t i = 0; i < n; ++i) idx[ids[i]] = i;



std::vector<double> d(n, 0.0);
for (size_t i = 0; i < n; ++i)
for (const auto& nb : sym[ids[i]])
if (idx.count(nb.first)) d[i] += nb.second;
for (size_t i = 0; i < n; ++i)
if (d[i] <= 0.0) return false;





auto shiftedmatvec = [&](const std::vector<double>& v,
 std::vector<double>& out) {
std::fill(out.begin(), out.end(), 0.0);
for (size_t i = 0; i < n; ++i) {
for (const auto& nb : sym[ids[i]]) {
auto it = idx.find(nb.first);
if (it == idx.end()) continue;
out[i] += nb.second / std::sqrt(d[i] * d[it>second]) * v[it>second];
}
}


for (size_t i = 0; i < n; ++i) out[i] = 0.5 * (out[i] + v[i]);

};

std::vector<double> u0(n);

for (size_t i = 0; i < n; ++i) u0[i] = std::sqrt(d[i]);
normalize(u0);

auto poweriter = [&](const std::vector<const std::vector<double>*>& defl,
 uint64_t s) {
std::vector<double> v(n), tmp(n);
for (size_t i = 0; i < n; ++i) {
s ^= s << 13;
s ^= s >> 7;
s ^= s << 17;
v[i] = staticcast<double>(s % 1000003) / 1000003.0 - 0.5;

}
for (int it = 0; it < cfg.poweriters; ++it) {
for (const auto* w : defl) deflate(v, *w);



if (!normalize(v)) return v;
shiftedmatvec(v, tmp);
v.swap(tmp);
}
for (const auto* w : defl) deflate(v, *w);
normalize(v);
return v;


};


std::vector<double> v1 = poweriter({&u0}, 0x9e3779b97f4a7c15ull);
std::vector<double> v2 = poweriter({&u0, &v1}, 0xc2b2ae3d27d4eb4full);


for (size_t i = 0; i < n; ++i) {
double x = v1[i] / std::sqrt(d[i]);
double y = v2[i] / std::sqrt(d[i]);
res.pos[ids[i]] = {x, y};
res.centroid[0] += x;
res.centroid[1] += y;


}
res.centroid[0] /= staticcast<double>(n);




res.centroid[1] /= staticcast<double>(n);
res.valid = true;


return true;
}



bool spectralembedding::position(const std::unordered_map<uint32_t, double>& p,
 std::array<double, 2>* out) const {
if (!res.valid || !out) return false;
double m = 0.0, x = 0.0, y = 0.0;

for (const auto& kv : p) {
if (kv.second <= 0.0) continue;



auto it = res.pos.find(kv.first);

if (it == res.pos.end()) continue;
m += kv.second;
x += kv.second * it>second[0];
y += kv.second * it>second[1];
}
if (m <= 0.0) return false;
(*out)[0] = x / m;

(*out)[1] = y / m;




return true;
}





double spectralembedding::hypothesis7(const intentgraph& g, double now,
size_t* nout) const {
std::vector<double> xs, ys;
if (res.valid) {
for (const auto& kv : res.pos) {
const auto* es = g.edges(kv.first);

if (!es) continue;
int cnt = 0;
for (const auto& e : *es)
if (g.istransmission(e) && g.weight(e, now) > 0.0) ++cnt;
if (cnt < 2) continue;



double phi = g.fandispersion(kv.first, now);
double dx = kv.second[0] - res.centroid[0];




double dy = kv.second[1] - res.centroid[1];
xs.push_back(phi);
ys.push_back(std::sqrt(dx * dx + dy * dy));




}
}
if (nout) *nout = xs.size();

if (xs.size() < 3) return 0.0;
double mx = 0.0, my = 0.0;
for (size_t i = 0; i < xs.size(); ++i) {
mx += xs[i];
