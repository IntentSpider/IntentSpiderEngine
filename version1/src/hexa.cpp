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
