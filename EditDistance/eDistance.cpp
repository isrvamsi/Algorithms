

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

/* Define the cost of various operations */
int iCost = 3;
int dCost = 2;
int rCost = 4;
int NOP = 0;

/* Structure for backtracing the steps in the algorithm */
struct backtraceStruct {
	int op;
	int i;
	int j;
};

/* Each node in the linkedlist */
struct Node {
	char c;
	Node *next;
};

/* Various pointers for dealing with the linked list */
Node *head;
Node *curr;
Node *prev;

/*Print the linked list */
void printList(Node * curr) {
	Node *temp = head;
	while (temp != NULL) {

		if (temp == curr)
			cout << "*";

		cout << temp->c;
		if ((prev->next == NULL) && (temp->next == NULL))
			cout << "*";
		temp = temp->next;

	}
	cout << endl;
}

int main(int argc, char* argv[]) {
	FILE* pfile;

	/* Check if the filename is given as command line args and open it */
	if (argc > 1) {

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

	/* Read inpust from the file */
	char c;
	int sCount;
	int tCount;

	/* Read the source string */
	rewind(pfile);
	fscanf(pfile, "%d ", &sCount);
	cout << "Source count is " << sCount << endl;
	char *source = (char *) malloc(sizeof(char) * sCount);

	for (int i = 0; i < sCount; i++) {
		fscanf(pfile, "%c", &c);
		source[i] = c;
		cout << source[i];
	}

	cout << endl;
	cout << endl;

	/* Read the target string from the file  */
	fscanf(pfile, "%d", &tCount);
	char *target = (char *) malloc(sizeof(char) * tCount);
	cout << "Target count is " << tCount << endl;
	fscanf(pfile, "%c", &c);
	for (int i = 0; i < tCount; i++) {
		fscanf(pfile, "%c", &c);
		target[i] = c;
		cout << target[i];
	}
	cout << endl;
	cout << endl;

	/* Load the source string in to a linkedlist to form a linkedlist Z */
	Node *temp;
	for (int i = 0; i <= sCount; i++) {
		temp = new Node;
		temp->c = source[i];
		temp->next = NULL;

		if (i == 0) {
			head = temp;
			prev = head;
			curr = head;
		} else {
			prev = curr;
			curr = temp;
			prev->next = curr;
		}

	}

	/* Initialise the cost and trace matrix */
	int mrows = tCount + 1;
	int mcols = sCount + 1;
	int cost[mrows][mcols];
	int trace[mrows][mcols];

	//Initialisation to zero;
	for (int i = 0; i < mrows; i++) {
		for (int j = 0; j < mcols; j++) {
			cost[i][j] = 0;
			trace[i][j] = -1;
		}
	}

	//Initialisation of NULL rows ;
	trace[0][0] = 0;
	for (int j = 1; j < mcols; j++) {
		cost[0][j] = cost[0][j - 1] + dCost;
		trace[0][j] = dCost;
	}

	//Initialisation of NULL column ;
	for (int j = 1; j < mrows; j++) {
		cost[j][0] = cost[j - 1][0] + iCost;
		trace[j][0] = iCost;
	}

	int min = 0;

	/*Update the cost matrix and the trace matrix */
	for (int i = 1; i < mrows; i++) {
		for (int j = 1; j < mcols; j++) {

			char sourcechar = source[j - 1];
			char targetchar = target[i - 1];

			if (sourcechar != targetchar) {

				//Delete pointer
				min = cost[i][j - 1] + dCost;
				trace[i][j] = dCost;

				//Insert
				if (min > (cost[i - 1][j] + iCost)) {
					min = cost[i - 1][j] + iCost;
					trace[i][j] = iCost;
				}

				if (min > (cost[i - 1][j - 1] + rCost)) {
					//Replace
					min = cost[i - 1][j - 1] + rCost;
					trace[i][j] = rCost;

				}

			} else {
				min = cost[i - 1][j - 1];
				trace[i][j] = NOP;

			}
			cost[i][j] = min;

		}
	}

	/* Initialise the traceback data structure */
	backtraceStruct tRoute[tCount + sCount];
	for (int k = 0; k < tCount + sCount; k++) {
		tRoute[k].i = -1;
		tRoute[k].j = -1;
		tRoute[k].op = -1;
	}

	int i = mrows - 1;
	int j = mcols - 1;
	int opindex = tCount + sCount - 1;
	while (i >= 0 && j >= 0) {

		if (trace[i][j] == iCost) {
			tRoute[opindex].i = i;
			tRoute[opindex].j = j;
			tRoute[opindex].op = iCost;
			i = i - 1;

		} else if (trace[i][j] == dCost) {
			tRoute[opindex].i = i;
			tRoute[opindex].j = j;
			tRoute[opindex].op = dCost;
			j = j - 1;

		} else if (trace[i][j] == rCost) {
			tRoute[opindex].i = i;
			tRoute[opindex].j = j;
			tRoute[opindex].op = rCost;
			j = j - 1;
			i = i - 1;
		} else {
			tRoute[opindex].i = i;
			tRoute[opindex].j = j;
			tRoute[opindex].op = NOP;
			j = j - 1;
			i = i - 1;
		}

		opindex--;

	}

	int totalCost = 0;

	bool isPrint = true;
	/* Print the output transformations only if the string lengths are small */
	if (tCount > 30 || sCount > 30)
		isPrint = false;

	/* Print the traceback */
	prev = head;
	curr = head;
	if (isPrint) {
		cout << "________________________________________________________"
				<< endl;
		cout << " (i,j):  OPER    |C| T| Z " << endl;
		cout << "________________________________________________________"
				<< endl;
	}
	for (int k = (opindex + 1); k < tCount + sCount; k++) {
		if (k == opindex + 1) {
			if (isPrint) {
				cout << " (" << tRoute[k].i << "," << tRoute[k].j
						<< "):  INITIAL |" << tRoute[k].op << "| " << totalCost
						<< "| ";
				printList(curr);
			}
			continue;
		}

		totalCost += tRoute[k].op;
		if (tRoute[k].op == iCost) {
			if (isPrint)
				cout << " (" << tRoute[k].i << "," << tRoute[k].j
						<< "):  INSERT |" << tRoute[k].op << "| " << totalCost
						<< "| ";
			Node *temp1 = new Node;
			temp1->c = target[tRoute[k].i - 1];
			if ((curr == head) && (prev == head)) {
				//1st node
				head = temp1;
				prev = temp1;
				prev->next = curr;
			} else {
				temp1->next = prev->next;
				prev->next = temp1;
				prev = temp1;
			}
		} else if (tRoute[k].op == rCost) {
			if (isPrint)
				cout << " (" << tRoute[k].i << "," << tRoute[k].j
						<< "):  REPLACE |" << tRoute[k].op << "| " << totalCost
						<< "| ";
			curr->c = target[tRoute[k].i - 1];
			prev = curr;
			curr = curr->next;
		} else if (tRoute[k].op == dCost) {
			if (isPrint)
				cout << " (" << tRoute[k].i << "," << tRoute[k].j
						<< "):  DELETE |" << tRoute[k].op << "| " << totalCost
						<< "| ";
			if ((prev == head) && (curr == head)) {
				head = head->next;
				prev = head;
				curr = head;
			} else {
				curr = curr->next;
				prev->next = curr;
			}
		} else if (tRoute[k].op == NOP) {
			if (isPrint)
				cout << " (" << tRoute[k].i << "," << tRoute[k].j
						<< "):  RIGHT |" << tRoute[k].op << "| " << totalCost
						<< "| ";
			if ((prev == head) && (curr == head)) {
				curr = prev->next;
			} else {
				prev = curr;
				curr = curr->next;
			}
		}
		// Print the sequence on to the console
		if (isPrint)
			printList(curr);
	}

	cout << "---------------------------------- " << endl;

	cout << "Total Cost = " << cost[mrows - 1][mcols - 1] << endl;

	cout << "---------------------------------- " << endl;

}

