/**
 *  \file insertion-sort.cc
 *
 *  \brief Implement your insertion sort in this file.
 */
 
 /*****************************************************************************
  *   Worked in Team of 2
  *   1) Sriram Vamsi Ilapakurthy (ID: 78605368)
  *   2) Snehal Srinivas Gandham  (ID: 79007757)
  *
  *
  ******************************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.hh"



/*******************************************************************************
  *1.Start with a particular position j in the array.
  *2.Use a binary search to find the position of the position to insert.
  *3.Move the existing elements to their new positions.
  *4.Copy the key to the searched location.

********************************************************************************/


int binarySearch(int *start, int *end,keytype *A,keytype *key)
{
    int mid;

    /* Calculate the mid of the array */
    mid = (*start +*end)/2;

    /* If key is greater than the highest element return end */
    if(A[*end] < *key)
    {
    	return *end;
    }

    /* If key is less than least element return start */
    if(A[*start]> *key)
    {
    	return (*start-1);
    }

    /* If the key is equal to mid of the array return mid */
    if(A[mid]== *key)
    {
    	return mid;
    }

    /* If the key is less than the mid of the array recursively call binary search with end = mid-1 */
    if(A[mid]> *key)
    {
    	*end = mid -1;
    	 return binarySearch(start,end,A,key);
    }

    /* If the key is greater than the mid of the array recursively call binary search with start = mid+1 */
    if(A[mid]< *key)
    {
       	*start = mid +1;
       	return binarySearch(start,end,A,key);
    }


}


void
insertionSort (int N, keytype* A)
{
  /* Lucky you, you get to start from scratch */
 int start;
 int mid;
 int end;
 keytype *key;
 keytype backupkey;
 int posInsert;

 int i;
 int j;

 for(j=1;j<N;j++)
 {
    key = &A[j];
    backupkey = A[j];
    start =0;
    end=j-1;
    posInsert = binarySearch(&start,&end,A,key);

    /* Shift the existing members if a position to insert is different from the member's position  */
    if((posInsert+1)!= j)
    {
    
    /* Shift all the elements from the insertion position to j using memmove operation */   
    memmove(A+posInsert+2,A+posInsert+1,(j-(posInsert +1))*sizeof(keytype));
    
    /* Copy the key to the insertion position using the memcpy operation */
    memcpy(A+posInsert+1,&backupkey,sizeof(keytype));
    }
    else
    {
       /*No move operation is required, element is in the correct position*/
    }
 }

   return;
}


