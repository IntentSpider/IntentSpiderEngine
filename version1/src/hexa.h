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





class arousaltracker {
 public:
explicit arousaltracker(const config& cfg) : cfg(cfg) {}

void onkey(double now);

double arousal() const;
int streak() const { return streak; }

double zeta() const; 
double alphaeffective() const; 
void resetstreak() { streak = 0; }
void setstreak(int s) { streak = s; }


double devsign() const;
double absdev() const;


double mu() const { return mu; }
double var() const { return var; }


void setstats(double mu, double var);






double lastkey() const { return lastkey; }




double rate() const { return x; }
bool haverate() const { return havex; }
bool havestats() const { return havestats; }
void setstate(double lastkey, double rate, bool haverate, double mu,
double var, bool havestats, int streak);

 private:
const config& cfg;
double lastkey = -1.0;
double x = 0.0;
bool havex = false;
double mu = 0.0;
double var = 0.0;


bool havestats = false;



int streak = 0;
};



class valencestats {
 public:
explicit valencestats(const config& cfg) : cfg(cfg) {}
void update(double val);
bool shock(double val, double correctionrate) const;
double mu() const { return mu; }
double var() const { return var; }
int count() const { return n; }




void setstats(double mu, double var);
void setstate(double mu, double var, int count);

 private:
const config& cfg;
double mu = 0.0;
double var = 0.25;
int n = 0;


};







class substateclusters {
 public:
explicit substateclusters(const config& cfg) : cfg(cfg) {}


void add(double signdev, double absdev, double kappa, double val);

size_t count() const { return centroids.size(); }
const std::vector<std::array<double, 4>>& centroids() const { return centroids; }
const std::vector<size_t>& sizes() const { return sizes; }



