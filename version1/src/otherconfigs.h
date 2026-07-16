/* 
Copyright (c) 2025-2026 IntentSpider Webnet. All rights reserved. 
Copyright (c) 2008-2026 Neksha DeSilva and https://intentspider.nekshadesilva.com. All rights reserved.
IntentSpider is the Advanced Fluid Language Web For Textual Tension and Prediction. 
Contact - https://intentspider.nekshadesilva.com/contactform 
*/
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





  
  double beta1 = 0.6;         
  double beta2 = 0.3;         
  double beta3 = 0.4;         
  double kappan = 0.10;      

  
  double arousalcap = 4.0;   
  double rateema = 0.3;      
  double statsema = 0.02;    

  
  double thetaa = 1.5;       
  double l0 = 20.0;           
  double alphamin = 0.02;    



                              
                              

  
  double etacluster = 0.25;  


  double deltacomp = 0.35;   
  double bmax = 2.0;         
  double wactive = 20.0;     

  
  double tgrace = 60.0;      




  double munconf = 3.0;      

  
  double kshock = 2.0;       
  double kappaburst = 0.25;  
  double taushock = 2592000.0; 
  double wshock = 120.0;     
  double dkappashock = 0.2;  

  
  double deltacluster = 1.0; 
  int maxclusters = 12;      

  
  int tembedevents = 50;    
                              
                              
                              
  int poweriters = 300;      
  double thetahead = 0.05;   
  double epsplateau = 0.02;  




  int nplateau = 3;          



  
  int topn = 3;              




};

}  

