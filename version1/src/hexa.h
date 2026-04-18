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

