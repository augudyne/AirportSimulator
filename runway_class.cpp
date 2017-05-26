#include <iostream>
#include "runway.h"
using namespace std;


Runway::Runway(const int num_id = 9999, const int land = 99, const int launch = 99): num_id(num_id), landingTime(land), launchingTime(launch){};
  
bool Runway::inUse(){
  return isInUse;
}

void Runway::landPlane(const int flight_num){
  if(isInUse){
    throw "Runway is currently in use!";
  }
  cout << "Runway " << num_id << " : landing flight #" << flight_num << ".\n";
  occupiedCountdown = landingTime;
  isInUse = true;
}

  
void Runway::launchPlane(const int flight_num){
  if(isInUse){
    throw "Runway is currently in use!";
  }

  cout << "Runway " << num_id << " : launching flight #" << flight_num << ".\n";
  occupiedCountdown = launchingTime;
  isInUse = true;
}

void Runway::tickOnce(){
  if(isInUse){
    occupiedCountdown--;
    if(occupiedCountdown == 0){
      isInUse = false;
    }
  }
}

 
      
