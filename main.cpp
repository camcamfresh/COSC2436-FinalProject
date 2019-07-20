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
			char temp;
			file.get(temp);
			if(temp == '0'){
				std::cout << "undirected weighted graph" << std::endl;
				std::string line;
				getline(file, line);
				line = "0" + line;
				int vertices = std::count(line.begin(), line.end(), ',') + 1;

				int matrix[vertices][vertices];
				
				for(int i = 0; i < vertices; i++){
					for(int j = vertices - 1; j >= 0; j--){
						std::string read = line.substr(line.find_last_of(",") + 1);
						if(read.front() == 'x') matrix[i][j] = -1;
						else matrix[i][j] = std::stoi(read);
						if(j == 0) getline(file, line);
						else line = line.substr(0, line.find_last_of(","));
					}
				}				
				
				Graph graph(vertices, matrix, false);
				
			}
			else if(temp == 'X'){
				std::cout << "directed unweighted graph" << std::endl;
				std::string line;
				getline(file, line);
				int vertices = std::count(line.begin(), line.end(), ',');
				int matrix[vertices][vertices];
				for(int i = 0; i < vertices; i++){
					getline(file, line);
					line = line.substr(2);
					for(int j = vertices - 1; j >= 0; j--){
						std::string read = line.substr(line.find_last_of(",") + 1);
						matrix[i][j] = std::stoi(read) - 1;
						line = line.substr(0, line.find_last_of(","));
					}
				}
				
				Graph graph(vertices, matrix, true);

				
			}
			else std::cout << "ERROR: Invalid File" << std::endl;
			
			
			
			file.close();
		}
	}
}

int random_range(int min, int max) {
    return (rand() % (max - min + 1)) +min;
}