Augustine Kwong : 35879155
--------------------------

Program functionality:
	- Verbose output mode (default false):
	  Outputs: -when a free runway is found
	  	   -the status of both queues after every minute
		   -the random numbers generated! (so we can make sure its float...ing)
		   
	- Arbitrary amount of Runways
	  * User inputs # of runways the airport has
	  * Array of pointers to runways (class) is allocated
	  * A Runway is aware of -> if and for how long they are occupied for
	- merge_two_queues integration
	  Since we have an arbitrarily large  airport, we can generate MULTIPLE requests
	  for landing/take off. Thus while the generated number is less than our rate
	  threshold, we keep generating more requests. We then merge all these requests
	  onto our master queue. Since our plane_ids are incremental, this appends.
	  

Consulted for floating point number generation:
http://stackoverflow.com/questions/686353/c-random-float-number-generation
