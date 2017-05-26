#include <cstdlib>
#include "LQueue.h"
#include "LQueue.c"
#include "runway.h"
#include <ctime>

using namespace std;



void runSimulation(const int, const int, const int, const int, const int, const int);
void tickOnce(Queue&, Queue&, Runway**);
void updateQueues(Queue&, Queue&, int&, int, int);
int runwayAvailable(Runway**);

int main(int argc, char **argv){
  double LAND_RATE;
  double TAKE_OFF_RATE;
  int RUNWAYS;
  int MAX_TIME;
  int LAND_SPEED;
  int TAKE_OFF_SPEED;
  cout << "Input the number of runways for the airport : ";
  cin >> RUNWAYS; 
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
  runSimulation(RUNWAYS,LAND_SPEED, TAKE_OFF_SPEED, LAND_RATE, TAKE_OFF_RATE, MAX_TIME);
}


void runSimulation(const int RUNWAYS, const int LAND_SPEED, const int TAKE_OFF_SPEED, const int LAND_RATE, const int TAKE_OFF_RATE, const int MAX_TIME){
  //Master counters
  Runway *runways[RUNWAYS];
  int minutes = 0;
  int plane_id = 1000;
  int to_mins_waited = 0;
  int land_mins_waited = 0;
  //Master Queues
  Queue * landQueue = new Queue();
  Queue * takeOffQueue = new Queue();

  //populate array with new runways
  for(int x = 0; x < RUNWAYS; x++){
    runways[x] = new Runway(x, LAND_SPEED, TAKE_OFF_SPEED);
  }

  //run simulation
  while(minutes < MAX_TIME){
    cout << "\nTime elapsed: \t" << minutes << endl;
    updateQueues(*landQueue, *takeOffQueue, plane_id, TAKE_OFF_RATE, LAND_RATE);
    tickOnce(*landQueue, *takeOffQueue, runways);
    minutes++;
  }

  cout << endl << "Simulation has completed." << endl;
  
}

void tickOnce(Queue& landQueue, Queue& takeOffQueue, Runway *runways[]){
  if(!landQueue.empty()){
    int findRunway = runwayAvailable(runways);
    while(findRunway >= 0){
      runways[findRunway]->landPlane(landQueue.front());
      landQueue.dequeue();
      findRunway = runwayAvailable(runways);
    }
    if(!takeOffQueue.empty()){
      findRunway = runwayAvailable(runways);
      while(findRunway >= 0){
	//runway not in use -> fielding a takeoff
        runways[findRunway]->launchPlane(takeOffQueue.front());
	takeOffQueue.dequeue();
	findRunway = runwayAvailable(runways);
      }
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

//returns index of first available runway, otherwise return -1
int runwayAvailable(Runway **runways){
  int i = 0;
  for(unsigned int p = 0; p < sizeof(runways)/sizeof(**runways); p++){
    if(runways[i]->inUse()){
      return i;
    }
    i++;
  }

  return -1;
}
  
  
    
  
  
