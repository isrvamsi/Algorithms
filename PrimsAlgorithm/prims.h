/*
 * prims.h
 *
 *  Created on: Nov 12, 2016
 *      Author: wolfvaline
 */

#ifndef PRIMS_H_
#define PRIMS_H_
struct AdjNode
{
	int nodeid;
	float nodewt;
	int adjNumber;
};

struct Node
{
	int nodeid;
	int parent;
	float key;
	int dest;
	float nodewt;
	int adjNumber;

};

/* Heap functions */
void buildMinHeap();
void minHeapify(int i);
void exchange(int i, int j);
int parent(int i);
int right(int i);
int left(int i);
Node extractMin();
bool check(int i);
void printIndex();
void buildIndex();

/* Graph functions */
void printGraph();
void appendAdjList(int src, int dest, float wt);
void createNode(Node M);
void writeNode(int i, Node M);
Node readNode(int i);
bool nodeExits(int i);
AdjNode readAdjList(int i);
void writeAdjNode(int i, AdjNode M);


/*Prims */
void MST(int i);
void decreaseKey(int i);



#endif /* PRIMS_H_ */
