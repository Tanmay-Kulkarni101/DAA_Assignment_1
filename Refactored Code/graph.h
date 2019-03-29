#ifndef GRAPH
#define GRAPH
#include "node.h"
#include "data.h"
#include <vector>
#include <cstdlib>
class Graph{
private:
	std::vector<Node> convexHull;
	std::vector<Node> pointList;

public:

	Graph(Data data);

	std::vector<Node> getPointList();

	void setPointList(std::vector<Node> &pointList);

	void displayPointList();

	bool get_orientation(Node p,Node q,Node r);

	Node get_left_most_point(bool flag_lower);

	Node get_right_most_point(bool flag_lower);

	void grahm_scan();

	void jarvis_march();

};

#endif
