/*--- LQueue.cpp ----------------------------------------------------------
  This file implements LQueue member functions.
  From:  "ADTs, Data Structures, and Problem Solving with C++", 2nd edition
  by Larry Nyhoff
  -------------------------------------------------------------------------*/
 
#include <iostream>
using namespace std;

#include "LQueue.h"

//--- Definition of Queue constructor
Queue::Queue()
: myFront(0), myBack(0)
{}

//--- Definition of Queue copy constructor
Queue::Queue(const Queue & original)
{
  myFront = myBack = 0;
  if (!original.empty())
    {
      // Copy first node
      myFront = myBack = new Queue::Node(original.front());

      // Set pointer to run through original's linked list
      Queue::NodePointer origPtr = original.myFront->next;
      while (origPtr != 0)
	{
	  myBack->next = new Queue::Node(origPtr->data);
	  myBack = myBack->next;
	  origPtr = origPtr->next;
	}
    }
}

//--- Definition of Queue destructor
Queue::~Queue()
{ 
  // Set pointer to run through the queue
  Queue::NodePointer prev = myFront,
    ptr;
  while (prev != 0)
    {
      ptr = prev->next;
      delete prev;
      prev = ptr;
    }
}

//--- Definition of assignment operator
const Queue & Queue::operator=(const Queue & rightHandSide)
{
  if (this != &rightHandSide)         // check that not q = q
    {
      this->~Queue();                  // destroy current linked list
      if (rightHandSide.empty())       // empty queue
	myFront = myBack = 0;
      else
	{                                // copy rightHandSide's list
	  // Copy first node
	  myFront = myBack = new Queue::Node(rightHandSide.front());

	  // Set pointer to run through rightHandSide's linked list
	  Queue::NodePointer rhsPtr = rightHandSide.myFront->next;
	  while (rhsPtr != 0)
	    {
	      myBack->next = new Queue::Node(rhsPtr->data);
	      myBack = myBack->next;
	      rhsPtr = rhsPtr->next;
	    }
	}
    }
  return *this;
}

//--- Definition of empty()
  bool Queue::empty() const
  { 
    return (myFront == 0); 
  }

//--- Definition of enqueue()
void Queue::enqueue(const QueueElement & value)
{
  Queue::NodePointer newptr = new Queue::Node(value);
  if (empty())
    myFront = myBack = newptr;
  else
    {
      myBack->next = newptr;
      myBack = newptr;
    }
}

//--- Definition of display()
void Queue::display(ostream & out) const
{
  Queue::NodePointer ptr;
  for (ptr = myFront; ptr != 0; ptr = ptr->next)
    out << ptr->data << "  ";
  out << endl;
}

//--- Definition of front()
QueueElement Queue::front() const
{
  if (!empty())
    return (myFront->data);
  else
    {
      return 0;
    }
}

//--- Definition of dequeue()
void Queue::dequeue()
{
  if (!empty())
    {
      Queue::NodePointer ptr = myFront;
      myFront = myFront->next;
      delete ptr;
      if (myFront == 0)     // queue is now empty
	myBack = 0;
    }   
  else
    cerr << "*** Queue is empty -- can't remove a value ***\n";
}

//--- Defintion of move_to_front()
void Queue::move_to_front(int key){
  Queue::NodePointer ptr = myFront;
  if(ptr->data == key) return; //already at front
  
  for(; ptr != 0; ptr = ptr->next){
    if(ptr->next != 0 && ptr->next->data == key){ //guard to make sure we're not messing with NULLS
      Queue::NodePointer toMove = ptr->next; //pointer to object to move
      ptr->next = ptr->next->next; //set pointer to skip over object
      toMove->next = myFront; //set object to point to front
      myFront = toMove; //set to front
    }
  }
}

void Queue::merge_two_queues(Queue& lq1, Queue& lq2){
  Queue * temp = new Queue();                 //create temp queue(allows comparisons of two queue .fronts) which will be copied into q1
  while(!lq1.empty() &&  !lq2.empty()){       //while both have elements (two-one-of structure)
    if(lq1.front() <= lq2.front()){           
      temp->enqueue(lq1.front());
      lq1.dequeue();
    } else{

      
      temp->enqueue(lq2.front());
      lq2.dequeue();
      
    }
  }

  if(lq1.empty()){                         //l2 has more elements
    while(!lq2.empty()){
      temp->enqueue(lq2.front());
      lq2.dequeue();
    }
  }
  if(lq2.empty()){                        //l1 has more elements
    while(!lq1.empty()){
      temp->enqueue(lq1.front());
      lq1.dequeue();
    }
  }
   
  lq1 = *temp;
  delete temp;
}


    
    
      

      
  



      
