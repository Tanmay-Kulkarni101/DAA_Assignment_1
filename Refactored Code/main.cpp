#include "data.h"
#include "graph.h"
int main(){
	Data data; // calls default cnstr
	data.generateTestCases(1000,0,10);
	Graph graph = Graph(data);
	graph.displayPointList();

	graph.kirk_patrick_seidel();
    // graph.displayConvexHull();
}
