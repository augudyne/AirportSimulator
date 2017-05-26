#include <cstdlib>
#include "LQueue.h"
#include "LQueue.c"
#include <ctime>

using namespace std;



void runSimulation(const int, const int, const int, const int, const int);
void tickOnce(int&, Queue&, Queue&);
void updateQueues(Queue&, Queue&);

int main(int argc, char **argv){
  double LAND_RATE;
  double TAKE_OFF_RATE;
  int MAX_TIME;
  int LAND_SPEED;
  int TAKE_OFF_SPEED;

  cout << "Optimizing runway for : \n\t Time for plane to land (in minutes) : ";
  cin >> LAND_SPEED;
  cout << "\t Time for a plane to takeOff (in minutes) : ";
  cin >> TAKE_OFF_SPEED;
  cout << "\t Landing rate (planes per hour) : ";
  cin >> LAND_RATE;
  cout << "\t TakeOff rate (planes per hour) : ";
  cin >> TAKE_OFF_RATE;
  cout << "\t Time to run simulation (in minutes) : ";
  cin >> MAX_TIME;

  cout << "Landing Rate " << (LAND_RATE/60.0);
  runSimulation(LAND_SPEED, TAKE_OFF_SPEED, LAND_RATE, TAKE_OFF_RATE, MAX_TIME);
}


void runSimulation(const int LAND_SPEED, const int TAKE_OFF_SPEED, const int LAND_RATE, const int TAKE_OFF_RATE, const int MAX_TIME){
  //Master counters
  int minutes = 0;
  int plane_id = 1000;
  int inUse = 0;
  int to_mins_waited = 0;
  int land_mins_waited = 0;


  //Master Queues
  Queue * landQueue = new Queue();
  Queue * takeOffQueue = new Queue();



  while(minutes < MAX_TIME){
      cout << "\nTime elapsed: \t" << minutes << endl;

      updateQueues(landQueue, takeOffQueue, &plane_id, TAKE_OFF_RATE, LAND_RATE);
    tickOnce(inUse, landQueue, takeOffQueue);
    minutes++;
  }

  cout << endl << "Simulation has completed." << endl;
  
}

void tickOnce(int& inUse, Queue& landQueue, Queue& takeOffQueue){
  


  if(!landQueue.empty()){
    if(inUse == 0){
      //runway not in use -> fielding a landing 
      inUse = LAND_SPEED;
      cout << "Landing plane # " << landQueue.front() << endl;
      landQueue.dequeue();
      inUse--;
      return;
    } else {
      inUse--;
      cout << "Runway is in use for another " << inUse << "minutes \n";
    
    }
    if(!takeOffQueue.empty()){
      if(inUse == 0){
	//runway not in use -> fielding a takeoff
	inUse = TAKE_OFF_SPEED;
	cout << "Launching plane # " << takeOffQueue.front() << endl;
	takeOffQueue.dequeue();
      }
      inUse--;
      return;
    }

    cout << "Both queues are empty...control operators are lonely :( " << endl;
    return;
  }
}


void updateQueues(Queue& landQueue, Queue& takeOffQueue, int& plane_id, int TAKE_OFF_RATE, int LAND_RATE){
  double d = ((float) rand() / RAND_MAX);
  double e = ((float) rand() / RAND_MAX);
  if(d < (TAKE_OFF_RATE/60.0)){
    takeOffQueue.enqueue(plane_id);
    cout << "Plane # " << plane_id << " has requested takeoff" << endl;
    ++plane_id;
  }
  if(e < (LAND_RATE/60.0)){
    landQueue.enqueue(plane_id);
    cout << "Plane # " << plane_id << "has requested landing" << endl;
    ++plane_id;
  }
}

  
    
  
  
