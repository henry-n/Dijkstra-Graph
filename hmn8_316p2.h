#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>

//portion of these codes are referenced from Cracking The Coding Interview by Gaye Laakmann McDowell
//portion of these codes are reference from https://www.geeksforgeeks.org/greedy-algorithms-set-7-dijkstras-algorithm-for-adjacency-list-representation/

struct adjListNode{
	
	int destination;
	float distance;
	struct adjListNode* next;
}; 

struct adjList{
	struct adjListNode * head;
};

struct Graph
{
    int Vertices;
    struct adjList* array;
};

struct heapNode{
	int  v;
    int dist;
};


struct minHeap{
	
    int size;      // Number of heap nodes present currently
    int capacity;  // Capacity of min heap
    int *pos;     // This is needed for decreaseKey()
    struct heapNode **array;
	
};

int getLeftChildIndex(int parentIndex){return 2 * parentIndex + 1;}
int getRightChildIndex(int parentIndex){return 2 * parentIndex + 2;}
int getParentIndex(int childIndex){return (childIndex-1)/2;}

void Heapify(struct minHeap* heap, int index);

struct heapNode* getRoot(struct minHeap heap);

void menu();


#endif