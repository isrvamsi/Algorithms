/**********************


*************/

#include <iostream>
#include <fstream>
#include "prims.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <vector>
#include "timer.h"
#include <assert.h>
#include <stdio.h>

using namespace std;

int totalNodes;     // Stores the total Nodes/vertices in the graph
int totalEdges;     //Stores the total edges in the graph
int heapsize;
void *inputGraph;   // Stores the input graph
void *adjList;      //Stores the Adj List

int adjNumber = 0;  // Count of the Adj list
vector<int> Bindex; //Stores the index of the Binary Heap

/********************************************************************************
 * Graph Functions
 *
 * */

/* Prims MST algorithms */

void MST(int i) {
	Node M;
	Node V;
	M = readNode(i);
	M.key = 0;
	writeNode(i, M);

	// Build a binary heap
	buildMinHeap();

	//While Queue is not empty
	while (heapsize > 0) {
		//Extract Minimum
		M = extractMin();

		// Traverse the adjacency list of M
		AdjNode A;
		if ((M.nodeid < totalNodes) && (M.nodeid >= 0)) {
			int adjcount = 0;
			adjcount = M.adjNumber;

			// Read the next element in the adjacency list
			A = readAdjList(adjcount);
			adjcount = M.adjNumber;

			while (adjcount != -1) {
				if (check(A.nodeid)) {
					V = readNode(Bindex.at(A.nodeid));
					if (A.nodewt < V.key) {

						// Assign the parent and new key
						V.parent = M.nodeid;
						V.key = A.nodewt;
						writeNode(Bindex.at(A.nodeid), V);

						// Do a decrease key on the heap
						decreaseKey(Bindex.at(A.nodeid));
					}
				}

				adjcount = A.adjNumber;
				if (adjcount != -1)
					A = readAdjList(A.adjNumber);
			}
		}

	}
}



/* Prints the MST by traversing each Node in the graph */
void printGraph() {
	Node N;
	AdjNode A;
	float sumCost = 0;
	int adjcount = 0;

	// Open an out file
	FILE *fp = fopen("Prims_Mst.txt", "wb");
	if (!fp)
		cout << "Not able to open output file" << endl;

	cout <<"Outputing MST to filename: Prims_Mst.txt" << endl;
	for (int i = 0; i < totalNodes; i++) {
		N = readNode(i);
		if (N.parent == -1 || ((N.parent >= 0) && (N.parent < totalNodes))) {
			if (!(((N.nodeid == 0) && (N.dest == 0)) || (N.parent == -1))) {
				fprintf(fp, "%d %d %.6f\n", N.nodeid, N.parent, N.key);
				sumCost += N.key;
			}
			adjcount = N.adjNumber;
			while (adjcount != -1) {
				A = readAdjList(adjcount);
				adjcount = A.adjNumber;

			}

		}
	}

	//Close the ouput file
	fclose(fp);

	//Print the MST weight on to the command line
	printf("MST-weight = %.2f \n", sumCost);

}


/* Prepares a adjacency list for each node */
void appendAdjList(int src, int dest, float wt) {
	AdjNode adj1, adj2;
	adj1.adjNumber = -1;
	adj1.nodeid = dest;
	adj1.nodewt = wt;
	memcpy((char *)adjList + (adjNumber * sizeof(adj1)), &adj1, sizeof(adj1));

	Node K = readNode(src);
	AdjNode temp, ptemp;
	if (K.adjNumber == -1) {
		K.adjNumber = adjNumber;
		writeNode(K.nodeid, K);

	} else { //It will return first elemnt of adjacency list of K;

		temp = readAdjList(K.adjNumber);
		ptemp.adjNumber = K.adjNumber;
		while (temp.adjNumber != -1) {
			ptemp = temp;
			temp = readAdjList(temp.adjNumber);
		}
		temp.adjNumber = adjNumber;
		writeAdjNode(ptemp.adjNumber, temp);

	}
	adjNumber++;

	adj2.adjNumber = -1;
	adj2.nodeid = src;
	adj2.nodewt = wt;

	memcpy((char *)adjList + (adjNumber * sizeof(adj2)), &adj2, sizeof(adj2));

	K = readNode(dest);
	// AdjNode temp,ptemp;
	if (K.adjNumber == -1) {
		K.adjNumber = adjNumber;
		writeNode(K.nodeid, K);
	} else { //It will return first elemnt of adjacency list of K;

		temp = readAdjList(K.adjNumber);
		ptemp.adjNumber = K.adjNumber;
		while (temp.adjNumber != -1) {
			ptemp = temp;
			temp = readAdjList(temp.adjNumber);
		}
		temp.adjNumber = adjNumber;
		writeAdjNode(ptemp.adjNumber, temp);

	}
	adjNumber++;
}

/* Creates a new node for each vertex */
void createNode(Node M) {
	memcpy((char *) inputGraph + sizeof(Node) * M.nodeid, &M, sizeof(Node));
}

/* Writes to a given node */
void writeNode(int i, Node M) {
	memcpy((char *) inputGraph + sizeof(Node) * i, &M, sizeof(Node));
}

/* Reads a given Node */
Node readNode(int i) {
	Node M;
	memcpy(&M, (char *) inputGraph + sizeof(Node) * i, sizeof(Node));
	return M;
}

/* Checks if the node exits in the input graph */
bool nodeExits(int i) {
	Node M;
	memcpy(&M, (char *) inputGraph + sizeof(Node) * i, sizeof(Node));
	return (M.nodeid == i && M.parent == -1);
}

/* Reads an element in the adjacency list */
AdjNode readAdjList(int i) {
	AdjNode M;
	memcpy(&M, (char *) adjList + sizeof(AdjNode) * i, sizeof(AdjNode));
	return M;
}

/* Writes an element in the adjacenct list */
void writeAdjNode(int i, AdjNode M) {
	memcpy((char *) adjList + sizeof(AdjNode) * i, &M, sizeof(AdjNode));
}

/********************************************************************************
 * Priority Queue as a Binary heap
 *
 * */


/* Prints the index for the binary heap  */
void printIndex() {
	//cout << "Print Index" << endl;
	for (int i = 0; i < totalNodes; i++)
		cout << i << "->" << Bindex.at(i) << endl;
	cout << "______________________" << endl;
}

/* Builds an index for the binary Heap */
void buildIndex() {
	for (int i = 0; i < totalNodes; i++)
		Bindex.push_back(i);
}

/*Extracts the minimum element from the graph*/
Node extractMin() {
	Node zero;

	if (heapsize < 1) {
		cout << "Heap Underflow" << endl;
	} else {
		zero = readNode(0);
		if (zero.key == INFINITY) {
			zero.key = 0;
			writeNode(0, zero);
		}

		exchange(0, heapsize - 1);
		heapsize--;
		minHeapify(0);
	}

	return zero;
}

/* Checks if the element exists in the Heap     */
bool check(int i) {
	return (Bindex.at(i) < heapsize);
}


/* Exchange two elements in a Heap */
void exchange(int i, int j) {
	Node M, N;

	//cout << "Exchanging " << i << " and " << j << endl;
	M = readNode(i);
	N = readNode(j);
	writeNode(i, N);
	Bindex.at(N.nodeid) = i;
	writeNode(j, M);
	Bindex.at(M.nodeid) = j;
}

/*Obtain the parent index in the Binary Heap  */
int parent(int i) {
	return (int) ((i - 1) / 2);
}

/*Obtain the left index in the Binary Heap  */
int left(int i) {
	return (2 * i + 1);
}

/*Obtain the right index in the Binary Heap  */
int right(int i) {
	return (2 * i + 2);
}

/* Do minHeapify on the graph        */
void minHeapify(int i) {
	int l;
	int r;
	l = left(i);
	r = right(i);
	Node L, R, C, leastNode;
	int least;
	if (l < heapsize)
		L = readNode(l);

	if (r < heapsize)
		R = readNode(r);

	C = readNode(i);
	if (l < heapsize && C.key > L.key)
		least = l;
	else
		least = i;
	leastNode = readNode(least);

	if (r < heapsize && R.key < leastNode.key)
		least = r;
	if (least != i) {
		exchange(i, least);
		minHeapify(least);
	}
}

/* Builds a binary heap from the given edges */
void buildMinHeap() {
	heapsize = totalNodes;

	//MinHeapify
	for (int t = (int) ((heapsize / 2) - 1); t >= 0; t--)
		minHeapify(t);
}

/* Decrease key  on the Heap */
void decreaseKey(int i) {
	Node N, NParent;
	N = readNode(i);
	int heapParent = parent(i);
	NParent = readNode(heapParent);

	while ((i > 0) && (NParent.key > N.key)) {
		exchange(i, heapParent);
		i = heapParent;
		N = readNode(i);
		heapParent = parent(i);
		NParent = readNode(heapParent);

	}

}

/********************************************************************************
 * Main function
 *
 * */

int main(int argc, char* argv[]) {
	FILE* pfile;

	// Check if the filename is given as command line args and open it
	if (argc > 1) {
		ifstream readfile;
		cout << "Opening file:  " << argv[1];
		pfile = fopen(argv[1], "rw");
		if (pfile != NULL) {
			cout << " : Success" << endl;
		} else {
			cout << "Could not open the file" << endl;
		}

	} else {
		cout << "Please specify the input file" << endl;
		return 0;
	}

	// Init the stop watch
	stopwatch_init();
	struct stopwatch_t* timer = stopwatch_create();
	stopwatch_start(timer);

	//Scan the number of Nodes in the file
	int read;
	rewind(pfile);
	read=fscanf(pfile, "%d", &totalNodes);

	Node N, K;
	totalEdges = 0;

	//Initially count the number of edges in the file
	while (fscanf(pfile, "%d %d %f", &N.nodeid, &N.dest, &N.nodewt) == 3) {
		totalEdges++;

	}

	//Allocate memory for the MST nodes
	inputGraph = malloc(totalNodes * sizeof(Node));
	adjList = malloc(totalEdges * 2 * sizeof(AdjNode));

	//Open the files to read the nodes
	pfile = fopen(argv[1], "rw");
	rewind(pfile);
	read=fscanf(pfile, "%d", &totalNodes);

	// Scans the input and stores it and creates a adjacency list for it
	while ((fscanf(pfile, "%d %d %f", &N.nodeid, &N.dest, &N.nodewt)) == 3) {
		N.adjNumber = -1;
		N.key = INFINITY;
		N.parent = -1;

		//Check if theobject already exists
		if (!(nodeExits(N.nodeid))) {
			createNode(N);
		}

		if (!(nodeExits(N.dest))) {
			K.adjNumber = -1;
			K.parent = -1;
			K.key = INFINITY;
			K.dest = N.nodeid;
			K.nodeid = N.dest;
			K.nodewt = N.nodewt;
			createNode(K);

		}
		appendAdjList(N.nodeid, N.dest, N.nodewt);
	}

	//Build an index for the binary heap
	buildIndex();

	// Call the Prim's MST
	MST(0);

	// Print the output to the file
	printGraph();

	//Stop the stopwatch and print the time
	long double t_std = stopwatch_stop(timer);
	printf("Time taken = %Lg seconds \n", t_std);

	// Free the memory buffers
	free(inputGraph);
	free(adjList);

}

