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

#include "spidershellont.h"


#ifdef _WIN32
#else
#endif

namespace intentspider {

rawterminal::rawterminal() {
#ifndef _WIN32
if (tcgetattr(stdinfileno, &orig) == 0) {
termios raw = orig;
raw.clflag &= ~(icanon | echo);
raw.ccc[vmin] = 1;
raw.ccc[vtime] = 0;



if (tcsetattr(stdinfileno, tcsaflush, &raw) == 0) active = true;
}
#endif
}

rawterminal::~rawterminal() {
#ifndef _WIN32
if (active) tcsetattr(stdinfileno, tcsaflush, &orig);
#endif
}

int rawterminal::readkey() {
#ifdef _WIN32
return getch();
