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


#include "otherconfigs.h"

namespace intentspider {

class tokenizer;


struct edge {
uint32_t target = 0;
double w = 0.0; 
double tf = 0.0;
double s = 0.0; 

double negacc = 0.0; 
double sup = 0.0; 
double shock = 0.0; 
double tw = 0.0; 
double ts = 0.0; 
double tsup = 0.0; 
double tlast = -1.0e18;
};



struct persistedstats {
double cadencebaseline = -1.0;



double ratemu = -1.0; 
double ratevar = -1.0;
double valmu = 0.0; 
double valvar = -1.0; 
uint64_t tokensobserved = 0;
};



class intentgraph {
 public:
explicit intentgraph(const config& cfg) : cfg(cfg) {}


