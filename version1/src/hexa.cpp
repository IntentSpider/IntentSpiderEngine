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
}

double arousaltracker::zeta() const {

return 1.0 - std::exp(-staticcast<double>(streak) / cfg.l0);
}

double arousaltracker::alphaeffective() const {






return std::max(cfg.alpha * (1.0 - zeta()), cfg.alphamin);
}

double arousaltracker::devsign() const {
if (!havex || !havestats) return 0.0;
return x >= mu ? 1.0 : -1.0;
}

double arousaltracker::absdev() const {
if (!havex || !havestats) return 0.0;
return std::fabs(x - mu);
}

void arousaltracker::setstats(double mu, double var) {
if (mu > 0.0 && var > 0.0) {
mu = mu;
var = var;
havestats = true;
}
}

void arousaltracker::setstate(double lastkey, double rate, bool haverate,
double mu, double var, bool havestats,
int streak) {
lastkey = lastkey;
x = std::max(0.0, rate);
havex = haverate;
mu = mu;
var = std::max(0.0, var);
havestats = havestats && mu > 0.0 && var > 0.0;
streak = std::max(0, streak);
}

void valencestats::update(double val) {
double lam = n < 8 ? 0.25 : 0.05;
double d = val - mu;
mu += lam * d;
var += lam * (d * d - var);
++n;
