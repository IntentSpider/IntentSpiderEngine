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



struct selectionevent {
double t = 0.0;
std::vector<uint32_t> ctx;
};






class supportindex {
 public:
explicit supportindex(const config& cfg) : cfg(cfg) {}

void record(uint32_t token, double now, const std::vector<uint32_t>& ctx);




double support(uint32_t token, double now,
 const std::vector<uint32_t>& ctx) const;

const std::unordered_map<uint32_t, std::deque<selectionevent>>& events() const {
return events;
}
void clear() { events.clear(); }


void restore(uint32_t token, double now, const std::vector<uint32_t>& ctx) {
record(token, now, ctx);
}




void shifttimestamps(double delta);

 private:
const config& cfg;
std::unordered_map<uint32_t, std::deque<selectionevent>> events;


};


