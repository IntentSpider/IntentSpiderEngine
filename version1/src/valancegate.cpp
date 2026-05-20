#include "valandource.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <climits>
#include <fstream>
#include <numeric>
#include <random>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <cstring>
#include <utility>

using namespace std;
using ll= long long;
using ss= string;

namespace intentspider {

void cadencetracker::onkey(double now, bool isbackspace) {
if (lastkey >= 0.0) {
double dt = now - lastkey;
if (dt >= 0.0) {
sumdt += std::min(dt, cfg.dtcap);
++ndt;
}
}
lastkey = now;
++keys;
if (isbackspace) ++backspaces;
}

double cadencetracker::valence() const {
if (ndt == 0) return 0.0;
double dtavg = sumdt / staticcast<double>(ndt);
double kappa = correctionrate();








return std::tanh(cfg.vala * (dtavg - dtref) - cfg.valb * kappa);
}

double cadencetracker::correctionrate() const {
return keys ? staticcast<double>(backspaces) / staticcast<double>(keys)
