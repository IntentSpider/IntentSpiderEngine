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
