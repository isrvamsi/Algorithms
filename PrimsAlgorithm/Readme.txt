Team:
 Name: Soham Sunil Kulkarni     (UCIID: 20005264 )
 Name: Sriram Vamsi Ilapakurthy (UCIID: 78605368)

Environment: gcc version 5.4.0 20160609 (Ubuntu 5.4.0-6ubuntu1~16.04.4) 

===============================================================================
Building the file command
===============================================================================
make prims

Sample build:
wolfvaline@ubuntu:~/workspace/PDM_project3/database/src/HW_package$ make prims 
g++    -c -o timer.o timer.c
g++  -O3 -g -o prims.o -c prims.cc
g++ -O3 -g -o prims timer.o prims.o
================================================================================
 
===============================================================================
Executing the program 
===============================================================================
./prims filename

Sample execution for dense_100000.txt :
wolfvaline@ubuntu:~/workspace/PDM_project3/database/src/HW_package$ ./prims dense_100000.txt 
Opening file:  dense_100000.txt : Success
Timer: gettimeofday
Timer resolution: ~ 1 us (?)
Outputing MST to filename: Prims_Mst.txt
MST-weight = 12011.15 
Time taken = 1.08774 seconds 

Sample execution for sparse_100000.txt :
wolfvaline@ubuntu:~/workspace/PDM_project3/database/src/HW_package$ ./prims sparse_100000.txt 
Opening file:  sparse_100000.txt : Success
Timer: gettimeofday
Timer resolution: ~ 1 us (?)
Outputing MST to filename: Prims_Mst.txt
MST-weight = 32881.41 
Time taken = 0.35335 seconds
===============================================================================

===============================================================================
Question 5: Running time for sparse and dense graphs
===============================================================================
 The running time analysis for above algorithms which uses binary Heap for prims is

1) Build-min-heap => O(V);
2) Extract-min => O(VlgV);
3) Total time for entire algorithms => O(VlgV + ElgV) => O(ElgV)

Observed Running time for running "dense_100000.txt" => 1.08774 seconds  
Observed Running time for running "sparse_100000.txt" => 0.35335 seconds
==============================================================================


==============================================================================
Files: 
==============================================================================
prims.cc prims algorithsm
prims.h  header file
timer.c  timer 
timer.h  header

==============================================================================
