#include <iostream>
#include "runway.h"
using namespace std;


Runway::Runway(const int num_id = 9999, const int land = 99, const int launch = 99): num_id(num_id), landingTime(land), launchingTime(launch), isInUse(false), occupiedCountdown(0){};

//Function returns whether or not it is in use
bool Runway::inUse(){
  return isInUse;
}

//Uses the land plane function. Thus will be occupied for landTime minutes.
void Runway::landPlane(const int flight_num){
  if(isInUse){
    throw "Runway is currently in use!";
  }
  cout << "\t Runway " << num_id << " : landing flight #" << flight_num << ".\n";
  occupiedCountdown = landingTime;
  isInUse = true;
}

//Launches a plane. Thus will be occupied for launchTime minutes
void Runway::launchPlane(const int flight_num){
  if(isInUse){
    throw "Runway is currently in use!";
  }

  cout << "\t Runway " << num_id << " : launching flight #" << flight_num << ".\n";
  occupiedCountdown = launchingTime;
  isInUse = true;
}

//advances the time by one minute (updates occupied countdown timer)
void Runway::tickOnce(){
  if(occupiedCountdown > 0){
    occupiedCountdown--;
  }
  if(occupiedCountdown == 0){
      isInUse = false;
  }
}

 
      
