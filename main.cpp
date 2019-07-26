#include "main.h"

int main(int argc, char** argv) {
	srand(time(NULL));
	if(argc != 2){
		std::cout << "ERROR: Incorrect Arguments for Input File" << std::endl;
	}
	else{
		std::ifstream file;
		file.open(argv[1]);
		if(!file){
			std::cout << "ERROR: File Not Found.\nPress any key to continue" << std::endl;
			std::cin.get();
		}
		else{
			char type;
			file.get(type);
			int vertices = 0;
			std::string line;
			getline(file, line);
			
			if(type == '0'){
				std::cout << "Reading undirected weighted graph from " << argv[1] << std::endl;
				line = "0" + line;
				vertices = std::count(line.begin(), line.end(), ',') + 1;
			}
			else if(type == 'X'){
				std::cout << "Reading directed unweighted graph from " << argv[1] << std::endl;
				vertices = std::count(line.begin(), line.end(), ',');
			}
			else{
				std::cout << "ERROR: Invalid File" << std::endl;
				return -1;
			}
			
			int matrix[vertices][vertices];
			
			if(type == '0'){
				for(int i = 0; i < vertices; i++){
					for(int j = vertices - 1; j >= 0; j--){
						std::string read = line.substr(line.find_last_of(",") + 1);
						if(read.front() == 'x') matrix[i][j] = -1;
						else matrix[i][j] = std::stoi(read);
						if(j == 0) getline(file, line);
						else line = line.substr(0, line.find_last_of(","));
					}
				}
			}
			else{
				for(int i = 0; i < vertices; i++){
					getline(file, line);
					line = line.substr(2);
					for(int j = vertices - 1; j >= 0; j--){
						std::string read = line.substr(line.find_last_of(",") + 1);
						matrix[i][j] = std::stoi(read) - 1;
						line = line.substr(0, line.find_last_of(","));
					}
				}
			}
			file.close();
			Graph graph(vertices, matrix, type == '0' ? 0 : 1);
			
			std::cout << "\nOutputting object's representation of graph." << std::endl;
			graph.printGraph();
			
			std::cout << "\nGet Number of Vertices: " << graph.getVertices() << std::endl;
			std::cout << "Get Number of Edges: " << graph.getEdges() << std::endl;
			std::cout << "Are Vertices Connected: ";
			if(graph.isConnected()) std::cout << "yes" << std::endl;
			else std::cout << "NO" << std::endl;
			
			std::cout << "Disconneced Vetices: " << std::endl;
			graph.listDisconnected();
			
			/*int testSize = vertices / 2;
			int test[testSize];
			for(int i = 0; i < testSize; i++){
				test[i] = random_range(1, vertices);
				std::cout << "\nBreadth First Search from " << test[i] << std::endl;
				graph.bfs(test[i]);
			}
			
			for(int i = 0; i < testSize; i++){
				std::cout << "\nDepth First Search from " << test[i] << std::endl;
				graph.dfs(test[i]);
			}*/

			
		}
	}
}

int random_range(int min, int max) {
    return (rand() % (max - min + 1)) +min;
}