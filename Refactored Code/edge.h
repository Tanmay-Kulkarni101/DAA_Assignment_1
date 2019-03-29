#ifndef EDGE
#define EDGE
#include "node.cpp"
class Edge{
	private:
		Node point1,point2;
		double slope;
		double angle;
	public:
		Edge(Node point1, Node point2);
		double distance();
		double get_slope();
		double get_angle();
};
#endif
