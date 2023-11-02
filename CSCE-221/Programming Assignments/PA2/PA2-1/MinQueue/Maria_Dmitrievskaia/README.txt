Maria Dmitrievskaia, UIN : 927009911, Section 511, User Name : dmimar382, Email : dmimar382@tamu.edu

Sources used: N/A

I certify that I have listed all the sources that I used to develop the solutions and code to the
submitted work. On my honor as an Aggie, I have neither given nor received any unauthorized help
on this academic work.
Maria Dmitrievskaia 03/04/20

No known problems with the code. 


Pseudocode: The written code represents a minQueue implemented with a templated doubly linked list class.I use the adapter design pattern
to implement the minQueue class that has the capability of enqueue, dequeue, find the size of the queue and find the minimum value in the
queue. The output operator allows the user to see what values are currently stored in the queue.

All of the functions have a running time of O(1), except for the min function. In order to keep track of the size of the queue, a count variable 
is initialized. If enqueue is called, count is incremented by 1. If dequeue is called, count is decremented by 1. If the queue is empty and
dequeue is called, then count is left as zero and and exception is thrown. The minimum function does not have a running time of O(1) as we need 
to traverse through every node in the queue to find the minimum value. 

 
Program testing:
While writing the program, I tested every function to ensure its propper operation. For more details, please see Minqueue.cpp. 


