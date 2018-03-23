#include <vector>
#include <limits.h>
#include <queue>
#include <list>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <iostream>
using namespace std;

//portions of these code were referenced from 
//Cracking The Coding Interview by Gaye Laakmann McDowell
//https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-set-in-stl/


class Graph{
	private:
		int Vert;
		typedef pair<int, int> edgePair;
		list< pair<int,int> > *adj;
		
	public:
		Graph(int V) : Vert(V){
			adj = new list<edgePair>[Vert];
		}
		
		//connect vertecies
		addEdge(int src, int dest, int weight){
			//create bidirectional edge
			adj[src].push_back(make_pair(dest, weight));
			adj[dest].push_back(make_pair(src, weight));
		}
		
		void Dijkstra(int Vertex);
	
};

void Graph::Dijkstra(int Vertex){
	
	// http://geeksquiz.com/implement-min-heap-using-stl/ syntax reference
	priority_queue< edgePair, vector<edgePair>, greater<edgePair>  > priQ;
	
	//create vector for distances and initialize all edges to infinity/not known
	vector<int> dist(Vert, INT_MAX);
	
	priQ.push(make_pair(0, Vertex));
	dist[Vertex] = 0;
	
	while(!priQ.empty()){
		
		//first vert in pair is min dist from vertex
		//variable to sort and keep track of dist
		int minDist = priQ.top().second;
		priQ.pop();
		
		list< pair<int, int> >::const_iterator it;
		
		for(it = adj[minDist].begin(); it != adj[minDist].end(); it++){
			
			//check neighbor/connected vertecies
			int conVert = (*it).first;
			int distance = (*it).second;
			
			//if shorter path detected
			if(dist[conVert] > dist[minDist] + distance){
				
				//update distance
				dist[conVert] = dist[minDist] + distance;
				//push update to queue
				priQ.push(make_pair(dist[conVert], conVert));
				
			}
			
		}
	}
	
	
	cout << "Vertex \t Distance from Source [" << Vertex << "]\n";
	for(int i = 0; i < Vert; i++){
		std::cout << i << "\t\t" << dist[i] << "\n";
	}
	
}