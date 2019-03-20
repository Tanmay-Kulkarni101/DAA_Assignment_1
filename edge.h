#ifndef EDGE
#define EDGE
#include "node.cpp"
class Edge{
	private:
		Node point1,point2;
	public:
		Edge(Node point1, Node point2);
		double distance();
};
#endif
