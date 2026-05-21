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

#pragma once


#include "a.h"
#include "hexa.h"
#include "otherconfigs.h"
#include "spider.h"
#include "gettoc.h"
#include "valandource.h"

namespace intentspider {

struct suggestion {
uint32_t token = 0;
double score = 0.0;
};


struct debuginfo {
double valprime = 0.0; 

double entropy = 0.0; 
double hnorm = 0.0;
double necessity = 0.0; 
double arousal = 0.0; 
double alphaeff = 0.0; 
int streak = 0; 
int prey = 0; 

size_t substates = 0; 
bool gated = false; 
bool arbitrated = false;



bool shock = false; 
bool shockwindow = false;
};





class engine {
 public:
explicit engine(const config& cfg)
: cfg(cfg),
graph(cfg),
cadence(cfg),
support(cfg),
arousalt(cfg),
valstats(cfg),
clusters(cfg) {}



void onkey(double now, bool isbackspace) {
cadence.onkey(now, isbackspace);
arousalt.onkey(now);
}

void observetyped(const std::vector<uint32_t>& toks, double now);
std::vector<suggestion> predict(double now);

void accept(uint32_t token, double now);

const std::vector<uint32_t>& sentence() const { return sent; }
const std::vector<suggestion>& pendingsuggestions() const { return lastranked; }
std::string sentencetext() const;
void clearsentence();




const debuginfo& debug() const { return dbg; }



const std::unordered_map<uint32_t, double>& lastp() const { return lastp; }









std::unordered_map<uint32_t, double> diffusefor(
const std::vector<uint32_t>& toks, double now) const;


const intentgraph& graph() const { return graph; }




tokenizer& tokenizer() { return tok; }
const tokenizer& tokenizer() const { return tok; }

bool save(const std::string& path) const;
bool load(const std::string& path);
