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


#include "otherconfigs.h"
#include "tempfilecatcher.h"
#include "main.h"
#include "spidershellont.h"

using namespace intentspider;

namespace {

const char* kstatepath = strplaceholder0;

void printhelp() {
std::cout
<< strplaceholder0
 strplaceholder0
 strplaceholder0
 strplaceholder0
 strplaceholder0
 strplaceholder0;

}

void printprompt(const engine& eng) {
std::cout << strplaceholder0 << eng.sentencetext();
if (!eng.sentence().empty()) std::cout << strplaceholder0;



std::cout.flush();
}



void printdebug(const engine& eng) {
const debuginfo& d = eng.debug();
std::cout << strplaceholder0 << std::fixed << std::setprecision(2)
<< d.valprime << strplaceholder0 << d.entropy << strplaceholder1 << d.hnorm
<< strplaceholder0 << d.necessity << strplaceholder1 << d.arousal
<< strplaceholder0 << d.alphaeff << strplaceholder1 << d.streak
<< strplaceholder0 << d.prey << strplaceholder1 << d.substates
<< (d.gated ? strplaceholder0 : strplaceholder1) << (d.arbitrated ? strplaceholder2 : strplaceholder3)
<< (d.shock ? strplaceholder0 : strplaceholder1)
<< (d.shockwindow ? strplaceholder0 : strplaceholder1) << std::defaultfloat;
}



std::vector<std::array<double, 2>> trajectoryfor(
const engine& eng, const spectralembedding& emb,
const std::vector<uint32_t>& toks, double now) {
std::vector<std::array<double, 2>> out;
std::vector<uint32_t> prefix;
for (uint32_t t : toks) {
prefix.push_back(t);


auto p = eng.diffusefor(prefix, now);

std::array<double, 2> pt{0.0, 0.0};
if (emb.position(p, &pt))
out.push_back(pt);
else if (!out.empty())
out.push_back(out.back());
else
out.push_back({0.0, 0.0});
}
return out;
}

void cmdembed(spectralembedding& emb, const engine& eng, double now) {
if (emb.compute(eng.graph(), now)) {
const auto& r = emb.result();
std::cout << strplaceholder0 << r.graphnodes
<< strplaceholder0 << r.componentnodes
<< strplaceholder0 << std::fixed << std::setprecision(3)
<< r.centroid[0] << strplaceholder0 << r.centroid[1] << strplaceholder1
<< std::defaultfloat;
} else {
std::cout << strplaceholder0
 strplaceholder0;
}
}

void cmdtraj(const std::vector<std::array<double, 2>>& traj,
 const std::vector<std::string>& labels, const config& cfg) {
if (traj.empty()) {
std::cout << strplaceholder0
 strplaceholder0;



return;

}
trajectoryanalysis an = analyzetrajectory(traj, cfg);
std::cout << strplaceholder0;
for (size_t i = 0; i < traj.size(); ++i) {
bool head = false, plat = false;



for (int h : an.heads) head |= (h == staticcast<int>(i));
for (int p : an.plateaus) plat |= (p == staticcast<int>(i));
std::cout << strplaceholder0 << std::setw(4) << i << strplaceholder1 << std::setw(15)
<< std::left << (i < labels.size() ? labels[i] : strplaceholder0)
<< std::right << strplaceholder0 << std::fixed << std::setprecision(3)
<< traj[i][0] << strplaceholder0 << traj[i][1] << strplaceholder1 << std::setw(6)
<< an.speed[i] << strplaceholder0 << (head ? strplaceholder1 : strplaceholder2)
<< (plat ? strplaceholder0 : strplaceholder1) << std::defaultfloat;

}


}

void cmdcompare(const std::string& args, engine& eng,
const spectralembedding& emb, const config& cfg, double now) {
if (!emb.valid()) {
std::cout << strplaceholder0;




return;



}



size_t bar = args.find(strplaceholder0);
if (bar == std::string::npos) {
std::cout << strplaceholder0;




return;
}



auto ta = eng.tokenizer().tokenize(args.substr(0, bar));
auto tb = eng.tokenizer().tokenize(args.substr(bar + 1));


if (ta.empty() || tb.empty()) {
std::cout << strplaceholder0;
return;
}

auto a = trajectoryfor(eng, emb, ta, now);
auto b = trajectoryfor(eng, emb, tb, now);
size_t n = std::min(a.size(), b.size());
std::cout << strplaceholder0;
for (size_t i = 0; i < n; ++i) {
double gx = a[i][0] - b[i][0], gy = a[i][1] - b[i][1];
double mx = 0.5 * (a[i][0] + b[i][0]);
double my = 0.5 * (a[i][1] + b[i][1]);
std::string lab = eng.tokenizer().text(ta[i]) + strplaceholder0 +
eng.tokenizer().text(tb[i]);

std::cout << strplaceholder0 << std::setw(4) << i << strplaceholder1 << std::setw(24)
<< std::left << lab << std::right << strplaceholder0 << std::fixed
<< std::setprecision(4) << std::sqrt(gx * gx + gy * gy) << strplaceholder0
<< mx << strplaceholder0 << my << strplaceholder1 << std::defaultfloat;


if (ta[i] == tb[i]) {
double phi = eng.graph().fandispersion(ta[i], now);



std::cout << strplaceholder0 << std::fixed << std::setprecision(2)
<< phi << strplaceholder0 << std::defaultfloat;
}
}
std::vector<std::array<double, 2>> ac(a.begin(), a.begin() + n);
std::vector<std::array<double, 2>> bc(b.begin(), b.begin() + n);

std::cout << strplaceholder0 << std::fixed
<< std::setprecision(5) << gaparea(ac, bc) << std::defaultfloat;
std::cout << strplaceholder0
 strplaceholder0;
}

void cmdhyp7(const spectralembedding& emb, const engine& eng, double now) {
if (!emb.valid()) {
std::cout << strplaceholder0;
return;
}
size_t n = 0;
double r = emb.hypothesis7(eng.graph(), now, &n);


std::cout << strplaceholder0 << std::fixed
<< std::setprecision(3) << r << strplaceholder0 << n << strplaceholder1
<< std::defaultfloat;


if (n < 3)
std::cout << strplaceholder0;
else
std::cout << strplaceholder0
 strplaceholder0;
}

int runreplay(const config& cfg, const std::string& path) {
std::ifstream in(path);
if (!in) {
std::cerr << strplaceholder0 << path << strplaceholder1;
return 1;
}
engine eng(cfg);
double clock = 1.0e9;




 
 
 
 
 
long preds = 0, top1 = 0, top3 = 0, gated = 0, cold = 0, tokens = 0;
std::string line;
while (std::getline(in, line)) {
auto toks = eng.tokenizer().tokenize(line);


eng.clearsentence();


for (uint32_t v : toks) {
++tokens;
if (!eng.sentence().empty()) {
auto sugg = eng.predict(clock);


if (!sugg.empty()) {
++preds;
if (sugg[0].token == v) ++top1;
for (const auto& s : sugg)
if (s.token == v) {
++top3;
break;
}




} else if (eng.debug().gated) {
++gated;
} else {
++cold;
}


}
eng.observetyped({v}, clock);




clock += 2.0;
}



clock += 10.0;
}


std::cout << strplaceholder0 << tokens << strplaceholder1
<< (preds + gated + cold) << strplaceholder0;
std::cout << strplaceholder0 << preds << strplaceholder1 << gated
<< strplaceholder0 << cold << strplaceholder1;
if (preds > 0) {
