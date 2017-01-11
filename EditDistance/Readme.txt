Team:
 Name: Soham Sunil Kulkarni     (UCIID: 20005264 )
 Name: Sriram Vamsi Ilapakurthy (UCIID: 78605368)

Environment: gcc version 5.4.0 20160609 (Ubuntu 5.4.0-6ubuntu1~16.04.4) 

===============================================================================
Building the file command
===============================================================================
make eDistance

Sample build:
wolfvaline@ubuntu:~/workspace/Algorithms_project4/hw4$ make eDistance 
g++    -c -o eDistance.o eDistance.cpp
g++ -O3 -g -o eDistance eDistance.o
================================================================================
 
===============================================================================
Executing the program 
===============================================================================
Question1: The inputs for the question1 are provided in the file "Q1Input.txt"

Note:Sequence of steps are only printed for Question1

For Question1
./eDistance Q1Input.txt 

For Question2
./eDistance input1.txt 
./eDistance input2.txt 
./eDistance input3.txt
===============================================================================

===============================================================================
Question 3: Implementing a data structure with O(1) access
===============================================================================
Z is implemented as a linked list for the Edit Distance problem.
As the cursor is available at the given position the following operations can 
be accomplished in O(1) time.

Insert -> O(1) at the cursor location
Delete -> O(1) at the cursor location
Replace -> O(1) at the cursor location
Right -> O(1) at the cursor location 
==============================================================================


==============================================================================
Files: 
==============================================================================
eDistance.cpp -> Edit distance Algorithsm
Q1Input.txt   -> Input file for question1
input1.txt    -> Input file for question2
input2.txt    -> Input file for question2
input3.txt    -> Input file for question2

==============================================================================
Sample output for Question1
==============================================================================
Opening file:  Q1Input.txt : Success
Source count is 22
electrical engineering

Target count is 16
computer science

________________________________________________________
 (i,j):  OPER    |C| T| Z 
________________________________________________________
 (0,0):  INITIAL |0| 0| *electrical engineering
 (0,1):  DELETE |2| 2| *lectrical engineering
 (0,2):  DELETE |2| 4| *ectrical engineering
 (0,3):  DELETE |2| 6| *ctrical engineering
 (1,4):  RIGHT |0| 6| c*trical engineering
 (2,4):  INSERT |3| 9| co*trical engineering
 (3,4):  INSERT |3| 12| com*trical engineering
 (4,4):  INSERT |3| 15| comp*trical engineering
 (5,4):  INSERT |3| 18| compu*trical engineering
 (6,5):  RIGHT |0| 18| comput*rical engineering
 (7,5):  INSERT |3| 21| compute*rical engineering
 (8,6):  RIGHT |0| 21| computer*ical engineering
 (9,7):  REPLACE |4| 25| computer *cal engineering
 (10,7):  INSERT |3| 28| computer s*cal engineering
 (11,8):  RIGHT |0| 28| computer sc*al engineering
 (12,9):  REPLACE |4| 32| computer sci*l engineering
 (12,10):  DELETE |2| 34| computer sci* engineering
 (12,11):  DELETE |2| 36| computer sci*engineering
 (13,12):  RIGHT |0| 36| computer scie*ngineering
 (14,13):  RIGHT |0| 36| computer scien*gineering
 (15,14):  REPLACE |4| 40| computer scienc*ineering
 (15,15):  DELETE |2| 42| computer scienc*neering
 (15,16):  DELETE |2| 44| computer scienc*eering
 (15,17):  DELETE |2| 46| computer scienc*ering
 (16,18):  RIGHT |0| 46| computer science*ring
 (16,19):  DELETE |2| 48| computer science*ing
 (16,20):  DELETE |2| 50| computer science*ng
 (16,21):  DELETE |2| 52| computer science*g
 (16,22):  DELETE |2| 54| computer science*
---------------------------------- 
Total Cost = 54
---------------------------------- 

==============================================================================
