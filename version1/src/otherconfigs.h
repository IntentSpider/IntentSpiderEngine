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

namespace intentspider {




struct config {
  
  double eta = 0.5;           
  double tauv = 86400.0;     

  
  double etatf = 0.2;        
  double thetatf = 0.35;     
  double tfinit = 0.5;       

  
  double taux = 30.0;        




  
  double alpha = 0.15;        
  double eps = 1e4;          
  long maxpushops = 200000; 
  double gamma = 0.8;         
  double masstrivial = 1e3; 

  
  double tauseed = 2.0;      




  int seedk = 3;             

  
  double vala = 4.0;         
  double valb = 6.0;         



  double dtrefinit = 0.28;  


  double dtrefema = 0.05;   
  double dtcap = 2.0;        




  
  double tprime = 3600.0;    



  double thetas = 0.8;       
  double tausupp = 604800.0; 



  double supmin = 0.05;      

  
  double rho = 0.5;           
  double tau0 = 600.0;       
  double ccal = 1.0;         
  int historycap = 20;       




