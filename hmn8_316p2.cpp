#include "main.h"

//portion of these codes are referenced from Cracking The Coding Interview by Gaye Laakmann McDowell
//portion of these codes are reference from https://www.geeksforgeeks.org/greedy-algorithms-set-7-dijkstras-algorithm-for-adjacency-list-representation/

struct adjListNode* createNode(int destination, float dist){
	
	struct adjListNode* newNode = (struct adjListNode*) malloc(sizeof(struct adjListNode));
    newNode->destination = destination;
    newNode->distance = dist;
    newNode->next = NULL;
    return newNode;
}

void addEdge(struct Graph* g, int source, int destination, float dist){
	//directed graph can 1-way
	struct adjListNode* node = createNode(destination,dist);
	node->next = g->array[source].head;
	g->array[source].head = node;
	
}

struct Graph* createGraph(int Vert)
{
    struct Graph* g = (struct Graph*) malloc(sizeof(struct Graph));
    g->Vertices = Vert;
 
    // Create an array of adjacency lists.  Size of array will be V
    g->array = (struct adjList*) malloc(Vert * sizeof(struct adjList));
 
     // Initialize each adjacency list as empty by making head as NULL
    for (int i = 0; i < Vert; ++i)
        g->array[i].head = NULL;
 
    return g;
}

struct minHeap* createHeap(int cap){
    struct minHeap* Heap = (struct minHeap*) malloc(sizeof(struct minHeap));
    Heap->pos = (int *)malloc(cap * sizeof(int));
	Heap->size = 0;
    Heap->capacity = cap;
    Heap->array = (struct heapNode**) malloc(cap * sizeof(struct heapNode*));
    return Heap;	
}

struct heapNode* createHeapNode(int vert, float dist){
	struct heapNode* node = (struct heapNode*) malloc(sizeof(struct heapNode));
    node->v = vert;
    node->dist = dist;
    return node;
}

int isEmpty(struct minHeap* heap){
	return heap->size == 0;
}

void swap(struct heapNode** node1, struct heapNode** node2)
{
    struct heapNode* temp = *node1;
    *node1 = *node2;
    *node2 = temp;
}

struct heapNode* getRoot(struct minHeap* heap){
	
	if(isEmpty(heap)){
		return NULL;
	}
	
	//store root
	struct heapNode* root = heap->array[0];
	
	//get last node added in array and replace to root
	struct heapNode* lastNode = heap->array[heap->size - 1];//last node added in array
	heap->array[0] = lastNode;//swap lastNode to root
	
	//update positions
	heap->pos[root->v] = heap->size-1;
	heap->pos[lastNode->v] = 0;
	
	//heapify
	--heap->size;
	Heapify(heap,0);
	
	return root;
	
}

//check if vert exists
bool vertExists(struct minHeap*  heap, int v)
{
   if (heap->pos[v] < heap->size)
     return true;
   return false;
}

void updatePos(struct minHeap* heap, int vert, float dist){
	
	int i = heap->pos[vert];
	
	heap->array[i]->dist = dist;
	
	while(i && heap->array[i]->dist < heap->array[getParentIndex(i)]->dist){
		
		//swap child with parentNode
		heap->pos[heap->array[i]->v ] = getParentIndex(i);
		heap->pos[heap->array[getParentIndex(i)]->v] = i;
		
		swap(&heap->array[i], &heap->array[getParentIndex(i)]);
		
		i = getParentIndex(i);
		
	}
	
}



void Heapify(struct minHeap* heap, int index){
	
	int small, left, right;
	small = index;
	left = getLeftChildIndex(index);
	right = getRightChildIndex(index);
	
	if(left < heap->size && heap->array[left]->dist < heap->array[small]->dist )
		small = left;
	
	if(right < heap->size && heap->array[right]->dist < heap->array[small]->dist)
		small = right;
	
	if(small != index){
		
		//nodes being swapped 
		heapNode* shorterNode = heap->array[small];
		heapNode* parentNode = heap->array[index];
		
		//Update Positions
		heap->pos[shorterNode->v] = index;
		heap->pos[parentNode->v] = small;
		
		swap(&heap->array[small], &heap->array[index]);
		
		//do while heap is not ordered
		Heapify(heap,small);
		
		
	}
	
}

void printArr(float dist[], int n)
{
    printf("Vertex   Distance from Source\n");
	
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %f\n", i, dist[i]);
}

void dijkstra(struct Graph* g, int src){
	
	int V = g->Vertices;
	float dist[V];
	
	struct minHeap* heap = createHeap(V);
	
	//initialize heap 
	for(int i = 0; i < V; ++i){
		dist[i] = FLT_MAX;
		heap->array[i] = createHeapNode(src,dist[i]);
		heap->pos[i] = i;
	}
	
	//set starting point to traverse list
	heap->array[src] = createHeapNode(src,dist[src]);
	heap->pos[src] = src;
	dist[src] = 0;
	
	updatePos(heap, src, dist[src]);
	
	heap->size = V;
	
	//finalize distance/calculate distance
	while(!isEmpty(heap)){
		
		struct heapNode* node = getRoot(heap);
		int u = node->v;
		
		//traverse all connected nodes
		struct adjListNode* traverse = g->array[u].head;
		
		while(traverse != NULL){
			int v = traverse->destination;
			
			if(vertExists(heap,v) && dist[u] != FLT_MAX && (traverse->distance + dist[u]) < dist[v]){
				dist[v] = dist[u] + traverse->destination;
				
				//update distance in heap 
				updatePos(heap, v, dist[v]);
			}
			traverse = traverse->next;
		}
		
	}
	printArr(dist, V);
}

struct Graph* getFile(){
	
	std::ifstream inFile;
	std::string input;
	std::string line;
	
	
	std::cout << "Enter A Text File's Name With It's Extension (.txt) : ";
	std::cin.ignore();
	std::getline(std::cin, input);
	
	inFile.open(input);
		
	if(inFile.fail()){
		std::cout << "ERROR OPENING FILE\n\n";
	}
	else{
		std::cout << "\nOPEN FILE SUCCESS\n\n";
		
		
		int v, e, count = 0;
		std::getline(inFile,line);
		std::istringstream iss1(line);
		if(iss1 >> v >> e)
			std::cout << v << "\t" << e << '\n';
		
		struct Graph* graph = createGraph(v);
		
		while(std::getline(inFile, line) && count < e){
			
			std::istringstream iss(line);
			
			int a, b;
			float c;
			
			if(iss >> a >> b >> c){
				std::cout << a << "\t" << b << "\t" << c << '\n';
				addEdge(graph,a,b,c);
			}
			
			count++;
			
		}
		std::cout << "\n\n";
		inFile.close();
		return graph;
	}
	
}

	

// Driver program to test above functions
main()
{
	int input;
	int vert;
	struct Graph* g;
	
	do{
		std::cout << "1. Open File\n";
		std::cout << "2. Shortest Paths\n";
		std::cout << "3. QUIT\n";
	
	
		std::cout << "Enter Choice: ";
		std::cin >> input;
		
		if(input == 1){
			g = getFile();
		}
		else if(input == 2){
			std::cout << "Enter A Vertex: ";
			std::cin >> vert;
			dijkstra(g,vert);	
		}
		else if(input == 3){
			exit(EXIT_FAILURE);
		}
		
	}while(input != 3);
    
}