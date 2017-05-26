#include <cstdlib>
#include "LQueue.h"
#include "runway.h"
#include <ctime>
#include <iomanip>
using namespace std;

//global variable for output cleanness
bool isVerboseOutput(false);

//prototypes (declaration)
void runSimulation(const int, const int, const int, const int, const int, const int);
void tickOnce(Queue&, Queue&, Runway**, int&, int&, int&, int&, int&, int&, const int);
void updateQueues(Queue&, Queue&, int&, int, int, int&, int& );
int runwayAvailable(Runway**, const int);

int main(int argc, char **argv){
  //Define Constants for input
  double LAND_RATE;
  double TAKE_OFF_RATE;
  int RUNWAYS;
  int MAX_TIME;
  int LAND_SPEED;
  int TAKE_OFF_SPEED;
  char isVerbose;
  
  
  //set verbose output state
  cout << "Verbose output -- default false -- ? (y/n): ";
  cin >> isVerbose;
  if(isVerbose == 'y' || isVerbose == 'Y'){
    isVerboseOutput = true;
  }

  //get constants from input
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
  //launch simulation using constants defined
  runSimulation(LAND_SPEED, TAKE_OFF_SPEED, LAND_RATE, TAKE_OFF_RATE, MAX_TIME, RUNWAYS);
}


/* Begins a simulation with user defined parameters 
   PRE: All parameters are valid values for defining a given airport:
   PRE: LAND_SPEED is the time (minutes) needed by a plane to land on a runway 
   PRE: TAKE_OFF_SPEED is the time (minutes) needed by a plane to launch on a runway
   PRE: LAND_RATE is the rate (planes in an hour) that requests to land (on avg)
   PRE: TAKE_OFF_RATE is the rate (planes in an hour) that requests to launch (on avg)
   PRE: MAX_TIME is the number of minutes to run the simulation (inclusive)
   PRE: num_runways is the number of runways at our airport
   POST: Simulation is complete -- MAX_TIME has elapsed, stats printed out, and program ready to end */
void runSimulation(const int LAND_SPEED, const int TAKE_OFF_SPEED, const int LAND_RATE, const int TAKE_OFF_RATE, const int MAX_TIME, const int num_runways){
  //Master counters
  Runway *runways[num_runways];
  int minutes = 0;
  int plane_id = 1000;
  int inLandQueue = 0;
  int inLaunchQueue =0;
  int MAX_IN_LAUNCH = 0;
  int MAX_IN_LAND = 0;
  int waitInLand = 0;
  int waitInLaunch = 0;
  int planesLaunched = 0;
  int planesLanded = 0;
  //output width (for stats)
  int WIDTH = 40;
  //Master Queues
  Queue * landQueue = new Queue();
  Queue * takeOffQueue = new Queue();

  //populate array with new runways
  for(int x = 0; x < num_runways; x++){
    runways[x] = new Runway(x, LAND_SPEED, TAKE_OFF_SPEED);
  }
  
  srand(time(NULL));
  //begin simulation
  while(minutes <= MAX_TIME){
    cout << "Time elapsed: \t" << minutes << endl;
    
    //Generate planes for the queue
    updateQueues(*landQueue, *takeOffQueue, plane_id, LAND_RATE, TAKE_OFF_RATE,  inLandQueue, inLaunchQueue);
    //update MAX IN QUEUE statistics
    if(inLaunchQueue > MAX_IN_LAUNCH){
      MAX_IN_LAUNCH = inLaunchQueue;
    }
    if(inLandQueue > MAX_IN_LAND){
      MAX_IN_LAND = inLandQueue;
    }

    //Process the queue and delegate planes to runways
    tickOnce(*landQueue, *takeOffQueue, runways, inLandQueue, inLaunchQueue, waitInLand, waitInLaunch, planesLanded, planesLaunched,num_runways);
    for(int x = 0; x < num_runways; x++){
      runways[x]->tickOnce();
    }
    if(isVerboseOutput){
      cout << "There are " << inLandQueue << " planes still waiting to land\n";
      cout << "There are " << inLaunchQueue << " planes still waiting to launch\n\n";
    }
    minutes++;
  }

  //Simulation is complete, print out statistics
  cout.setf(ios::left);
  cout << endl << "Simulation has completed." << endl;
  cout << "\n\nSTATISTICS: \n\n";
  cout << setw(WIDTH) << right << "Planes Landed: " << planesLanded << endl;
  cout << setw(WIDTH) << right << "Planes Launched: " << planesLaunched << endl;
  cout << setw(WIDTH) << right << "Max In Land Queue: " << MAX_IN_LAND << endl;
  cout << setw(WIDTH) << right << "Max In Launch Queue: " << MAX_IN_LAUNCH << endl;
  
  if(planesLanded == 0)
    cout << setw(WIDTH) << "Average Land Wait Time(mins): " << "*No Planes Requested Landing"  << endl;
  else
    cout << setw(WIDTH) << "Average Land Wait Time(mins): " << (float) waitInLand/planesLanded << endl;
  
  
  if(planesLaunched == 0)
    cout << setw(WIDTH) << "Average Launch Wait Time(mins): " << "*No Planes Requested Launch*"  << endl;
   else 
    cout << setw(WIDTH) << "Average Launch Wait Time(mins): " << (float) waitInLaunch/planesLaunched << endl;
  
  
}

  /* Delegates planes to runways by searching for open runway, dequeuing, and updating stat counters
     PRE: Queues(landQueue and takeOffQueue) are updated to the current time elapsed
     PRE: runways is array of pointers to runways, each of which is being used or not
     PRE: Other parameters are references to statistics that are updated as planes are delegated to runways
     POST: All planes in queue have been delegated to a runway IF POSSIBLE -> Landing takes priority */
  
void tickOnce(Queue& landQueue, Queue& takeOffQueue, Runway *runways[], int& inLandQueue, int& inLaunchQueue, int& waitInLand, int& waitInLaunch, int& planesLanded, int& planesLaunched, const int num_runways){

  //locate an open runway to land planes
  int findRunway = runwayAvailable(runways, num_runways);
  while(findRunway >= 0 && !landQueue.empty()){
    //unoccupied runway found AND there are planes waiting to land
    //Delegate landing to runway, dequeue from queue, and update stats
    if(isVerboseOutput)
      cout << "Runway " << findRunway << " is available \n";
    Runway *rw = runways[findRunway];
    rw->landPlane(landQueue.front());
    landQueue.dequeue();
    planesLanded++;
    inLandQueue--;
    findRunway = runwayAvailable(runways, num_runways);
  }
	  
  while(findRunway >= 0 && !takeOffQueue.empty()){
    //unoccupied runway found AND there are planes waiting to launch
    //delegate launch to runway, dequeue from queue, and update stats
    if(isVerboseOutput)
      cout << "Runway " << findRunway << " is available \n";
    runways[findRunway]->launchPlane(takeOffQueue.front());
    takeOffQueue.dequeue();
    planesLaunched++;
    inLaunchQueue--;
    findRunway = runwayAvailable(runways, num_runways);
  }

  //Check if there are planes in the queue:
  // - if there are, we add one minute to total time waiting in queue FOR EACH PLANE IN THE QUEUE
  if(!takeOffQueue.empty()){
    //still planes inside LaunchQueue
    waitInLaunch += inLaunchQueue;
  }

  if(!landQueue.empty()){
    //still planes inside LandQueue;
    waitInLand += inLandQueue;
  }

  
  if(isVerboseOutput && findRunway < 0){
    cout << "All runways are now occupied\n";
    /* for(int x = 0; x < RUNWAYS; x++){ */
    /*   cout << "Runway " << x << " is in use?  " << boolalpha <<  runways[x]->inUse() << endl;} */  
  }      
}

/* Generates a queue of landing/launch requests and merges them into the existing one 
   NOTE: Since plane_ids are incremental, the merging is always appending the generated queue to the existing
   PRE: rand() is already seeded with time in initialization of simulation
   PRE: At the 'beginning' of a minute, it is time to update the queues with requests
   POST: Our master land and takeOff queue have the generated queues appended to them (new requests are added to queue)*/
void updateQueues(Queue& landQueue, Queue& launchQueue, int& plane_id, int LAND_RATE, int TAKE_OFF_RATE, int& inLandQueue, int& inLaunchQueue){
  //define a temporary queue 
  Queue * temp = new Queue();
  //generate initial random values
  double d = ((float) rand() / RAND_MAX);
  double e = ((float) rand() / RAND_MAX);
  //continuously generates requests until random number fails to be higher than takeoffrate
  //makes sense -> higher take off rates will generate more because higher chance of failing to stop loop
  while(d < (TAKE_OFF_RATE/60.0)){
    temp->enqueue(plane_id);
    if(isVerboseOutput){
      cout << "Randomly generated float: " << d << " is less than " << (TAKE_OFF_RATE/60.0) << endl;
      cout << "Plane # " << plane_id << " has requested takeoff" << endl;
    }
    inLaunchQueue++;
    ++plane_id;
    d = ((float) rand() / RAND_MAX);
  }
  if(isVerboseOutput)
    cout << "\t *HALT LAUNCH REQUEST GENERATION* Randomly generated float: " << d << " is larger than " << (TAKE_OFF_RATE/60.0) << endl;
  launchQueue.merge_two_queues(launchQueue, *temp);
  //assert *temp is empty now. 

  //same as above, but with landing queue
  while(e < (LAND_RATE/60.0)){
    temp->enqueue(plane_id);

    if(isVerboseOutput){
      cout << "Randomly generated float: " << e << " is less than " << (LAND_RATE/60.0) << endl;
      cout << "Plane # " << plane_id << " has requested landing" << endl;     
    }
    inLandQueue++;
    ++plane_id;
    e = ((float) rand() / RAND_MAX);
  }
  if(isVerboseOutput)
     cout << "\t *HALT LAND REQUEST GENERATION* Randomly generated float: " << e << " is larger than " << (LAND_RATE/60.0) << endl;
  landQueue.merge_two_queues(landQueue, *temp);
  
  //Queue is no longer needed
  delete temp;
}
 
/* Returns index of first available runway, otherwise return -1
   PRE: All runways have their inUse flag updated to the current minute*/
 
int runwayAvailable(Runway *rws[], const int num_runways){
  for(int i = 0; i < num_runways; i++){
    if(!(rws[i]->inUse())){
      return i;
    }
  }
  return -1;
}
  
  
    
  
  
