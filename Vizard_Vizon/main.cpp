#include "data.h"
#include "graph.h"
#include <chrono>
// const long long number_of_test_cases = 30;
const double mean = 0;
const double variance = 10;
int main(){

	Data data; // calls default cnstr
	cout<<"Enter the number of points on the plane\n";
	int n;
	cin >> n;
	data.generateTestCases(n,mean,variance);

	for (int i=0;i<3;i++){

		Graph graph = Graph(data);
		if(i == 0){
			puts("KPS");
			auto start = std::chrono::system_clock::now();
			graph.kirk_patrick_seidel();
			auto end = std::chrono::system_clock::now();
			auto elapsed = end - start;
			std::cout << "KPS: "<< elapsed.count() << '\n';
		}
		else if(i == 1){
			puts("GS");
			auto start = std::chrono::system_clock::now();
			graph.graham_scan();
			auto end = std::chrono::system_clock::now();
			auto elapsed = end - start;
			std::cout<< "GS: " << elapsed.count() << '\n';
			graph.displayConvexHull();
		}
		else if(i == 2){
			puts("JM");
			auto start = std::chrono::system_clock::now();
			graph.jarvis_march();
			auto end = std::chrono::system_clock::now();
			auto elapsed = end - start;
			std::cout<< "JM: " << elapsed.count() << '\n';
			graph.displayConvexHull();
		}
	}

	return 0;
}
