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


#include "a.h"
#include "hexa.h"
#include "otherconfigs.h"
#include "spider.h"
#include "gettoc.h"
#include "valandource.h"

namespace intentspider {

struct suggestion {
uint32_t token = 0;
double score = 0.0;
};


struct debuginfo {
double valprime = 0.0; 

double entropy = 0.0; 
double hnorm = 0.0;
double necessity = 0.0; 
double arousal = 0.0; 
double alphaeff = 0.0; 
int streak = 0; 
int prey = 0; 

size_t substates = 0; 
bool gated = false; 
bool arbitrated = false;



