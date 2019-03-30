/*
The order of the includes is important, look at the dependencies file before making changes.
*/
#ifndef GRAPH
#define GRAPH
#include "node.h"
#include "data.h"
#include "utilities.h"
#include "edge.h"
#include <math.h>
#include <vector>
#include <cstdlib>
#include <algorithm>
class Graph{
private:
	std::vector<Node> convex_hull;
	std::vector<Node> point_list;

public:

	Graph(Data data);

	std::vector<Node> getPointList();

	void setPointList(std::vector<Node> &point_list);

	void displayPointList();

    void displayConvexHull();

	bool get_orientation(Node p,Node q,Node r);

    double polar_angler(Node source, Node target);

	Node get_left_most_point(bool flag_lower,vector<Node> point_list);

	Node get_right_most_point(bool flag_lower,vector<Node> point_list);

	void graham_scan();

	void jarvis_march();

	Edge upper_bridge(std::vector<Node> point_list);
	Edge lower_bridge(std::vector<Node> point_list);
	std::vector<Node> upper_hull(std::vector<Node> point_list,Node p_min, Node p_max);
	std::vector<Node> lower_hull(std::vector<Node> point_list,Node p_min, Node p_max);
    void kirk_patrick_seidel();
};

#endif
