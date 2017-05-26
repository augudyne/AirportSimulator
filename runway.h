#ifndef _RUNWAY_H_
#define _RUNWAY_H_


class Runway{
 public:
  Runway();
  //Constructor
  Runway(const int, const int, const int);
  //ticks a minute forward
  void tickOnce();
  //returns if in use
  bool inUse();
  //lands a plane with a given number
  void landPlane(const int);
  //launches a plane with given number
  void launchPlane(const int);
  
  
 private:
  bool isInUse;
  int occupiedCountdown;
  int num_id;
  bool damaged;
  int landingTime;
  int launchingTime;
};
#endif

  
