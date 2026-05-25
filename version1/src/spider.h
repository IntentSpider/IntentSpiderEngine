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







void reinforce(uint32_t u, uint32_t v, double now, double valprime);


void updatetf(uint32_t u, uint32_t v, bool outcome);


void addweight(uint32_t u, uint32_t v, double now, double amount);


void adjustweight(uint32_t u, uint32_t v, double now, double amount);



void suppressshock(uint32_t u, uint32_t v, double now);





const edge* edge(uint32_t u, uint32_t v) const { return find(u, v); }


bool hasedge(uint32_t u, uint32_t v) const { return find(u, v) != nullptr; }


bool istransmission(const edge& e) const { return e.tf > cfg.thetatf; }


double weight(const edge& e, double now) const;



double supstrength(const edge& e, double now) const;


