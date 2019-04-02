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
#include <fstream>
class Graph{
private:
	std::vector<Node> convex_hull;
	std::vector<Node> point_list;

public:
	const static std::string GRAHM_SCAN_OUTPUT;
	const static std::string JARVIS_MARCH_OUTPUT ;
	const static std::string KPS_OUTPUT ;
	Graph(Data data);

	std::vector<Node> getPointList();

	void setPointList(std::vector<Node> &point_list);

	void displayPointList();

    void displayConvexHull();

	bool get_orientation(Node p,Node q,Node r);

    	double polar_angler(Node source, Node target);

	Node get_left_most_point(bool flag_lower,vector<Node> point_list);

	Node get_right_most_point(bool flag_lower,vector<Node> point_list);
	
	static bool compare_pairs(pair<Node,double> p1, pair<Node,double> p2);
	
	void graham_scan();

	void jarvis_march();

	Edge upper_bridge(std::vector<Node> &point_list);
	Edge lower_bridge(std::vector<Node> &point_list);
	std::vector<Node> upper_hull(std::vector<Node> &point_list,Node p_min, Node p_max,fstream &file_handle);
	std::vector<Node> lower_hull(std::vector<Node> &point_list,Node p_min, Node p_max,fstream &file_handle);
    void kirk_patrick_seidel();
};

#endif
