#include "data.h"
#include "graph.h"
int main(){
	Data data; // calls default cnstr
	// data.generateTestCases(30000,0,1);
	Graph graph = Graph(data);
	graph.displayPointList();

	// graph.kirk_patrick_seidel();
	// graph.graham_scan();
	graph.jarvis_march();

    graph.displayConvexHull();
}
