#include "Graph3.h"

main(){
	
	int input;
	int vert;
	Graph g(0);
	
	do{
		cout << "1. Open File\n";
		cout << "2. Shortest Paths\n";
		cout << "3. QUIT\n";
	
	
		cout << "Enter Choice: ";
		cin >> input;
		
		if(input == 1){
			ifstream inFile;
			string input;
			string line;
	
	
			cout << "Enter A Text File's Name With It's Extension (.txt) : ";
			cin.ignore();
			getline(std::cin, input);
	
			inFile.open(input);
		
			if(inFile.fail()){
				std::cout << "ERROR OPENING FILE\n\n";
			}
			else{
				std::cout << "\nOPEN FILE SUCCESS\n\n";
		
		
				int v, e, count = 0;
				getline(inFile,line);
				istringstream iss1(line);
				if(iss1 >> v >> e)
					std::cout << v << "\t" << e << '\n';
		
				Graph graph(v);
		
				while(getline(inFile, line) && count < e){
			
				istringstream iss(line);
			
				int a, b;
				int c;
			
				if(iss >> a >> b >> c){
					cout << a << "\t" << b << "\t" << c << '\n';
					graph.addEdge(a,b,c);
				}
			
				count++;
			
				}
				cout << "\n\n";
				inFile.close();
				g = graph;
			}
		}
		else if(input == 2){
			cout << "Enter A Vertex: ";
			cin >> vert;
			g.Dijkstra(vert);	
		}
		else if(input == 3){
			exit(EXIT_FAILURE);
		}
		
	}while(input != 3);
	
	
	
}