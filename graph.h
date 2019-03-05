#ifndef GRAPH
#define GRAPH
#include "edge.h"
#include "node.h"
#include "data.h"
#include <vector>
class Graph{
private:
	std::vector<Node> convexHull;
	std::vector<Node> pointList;
	std::vector<Edge> edges;
public:

	Graph(Data data);

	std::vector<Node> getPointList();

	void setPointList(std::vector<Node> &pointList);

	void displayPointList();

};

#endif
