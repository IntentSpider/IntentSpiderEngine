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
