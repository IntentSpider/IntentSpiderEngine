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



class cadencetracker {
 public:
explicit cadencetracker(const config& cfg)
: cfg(cfg), dtref(cfg.dtrefinit) {}


void onkey(double now, bool isbackspace);


double valence() const;







double correctionrate() const;






void closewindow();

double baseline() const { return dtref; }
void setbaseline(double v) { if (v > 0.0) dtref = v; }







double lastkey() const { return lastkey; }
double sumdt() const { return sumdt; }
size_t intervalcount() const { return ndt; }
size_t keycount() const { return keys; }
size_t backspacecount() const { return backspaces; }




void setstate(double baseline, double lastkey, double sumdt, size_t ndt,
size_t keys, size_t backspaces);

 private:
const config& cfg;
double dtref; 
double lastkey = -1.0;
