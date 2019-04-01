#include "data.h"
#include "graph.h"
#include <chrono>

int main(){
	
	Data data; // calls default cnstr
	data.generateTestCases(1000,0,10000);
	Graph graph = Graph(data);
	
	for (int i=0;i<3;i++){

		Graph graph = Graph(data);
		if(i == 0){
			auto start = std::chrono::system_clock::now();
			graph.kirk_patrick_seidel();
			auto end = std::chrono::system_clock::now();
			auto elapsed = end - start;
			std::cout << "KPS: "<< elapsed.count() << '\n';
		}
		else if(i == 1){
			auto start = std::chrono::system_clock::now();
			graph.graham_scan();
			auto end = std::chrono::system_clock::now();
			auto elapsed = end - start;
			std::cout<< "GS: " << elapsed.count() << '\n';
		}
		else if(i == 2){
			auto start = std::chrono::system_clock::now();
			graph.jarvis_march();
			auto end = std::chrono::system_clock::now();
			auto elapsed = end - start;
			std::cout<< "JM: " << elapsed.count() << '\n';
		}
	}
		
	return 0;
}
