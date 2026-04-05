#include "hexa.h"

#include <algorithm>
#include <cmath>

namespace intentspider {

void arousaltracker::onkey(double now) {
if (lastkey >= 0.0) {
double dt = now - lastkey;
if (dt > 0.0) {
double inst = 1.0 / std::max(dt, 0.05);
x = havex ? x + cfg.rateema * (inst - x) : inst;
havex = true;
if (!havestats) {
mu = x;
var = 0.25 * x * x + 1e3;
havestats = true;
} else {
double d = x - mu;
mu += cfg.statsema * d;
var += cfg.statsema * (d * d - var);
}

streak = arousal() > cfg.thetaa ? streak + 1 : 0;
}
}
lastkey = now;
}

double arousaltracker::arousal() const {
if (!havex || !havestats) return 0.0;
double sigma = std::sqrt(std::max(var, 1e6));


return std::min(std::fabs(x - mu) / sigma, cfg.arousalcap);
