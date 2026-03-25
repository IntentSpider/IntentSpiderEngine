#include "hexa.h"

#include <algorithm>
#include <cmath>

namespace intentspider {

void arousaltracker::onkey(double now) {
if (lastkey >= 0.0) {
double dt = now - lastkey;
if (dt > 0.0) {
