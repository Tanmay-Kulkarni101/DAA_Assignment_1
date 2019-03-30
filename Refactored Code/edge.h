#ifndef EDGE
#define EDGE
#include "node.h"
#include <math.h>
#include <limits>
#include<stdio.h>
class Edge{
	private:
		Node point1,point2;
		double slope;
		double angle;
		double length;
	public:
		Edge(Node point1, Node point2);
		double get_slope();
		double get_angle();
		double get_length();
		// IF YOU HAVE BETTER IDEAS PLEASE CHANGE THIS (DONE FOR CONSISTENCY IN MED_OF_MED).
		Node getX();
		Node getY();
		void print_edge();
		bool operator <(Edge operand2);
		bool operator >(Edge operand2);
		bool operator <=(Edge operand2);
		bool operator >=(Edge operand2);
		bool operator ==(Edge operand2);
		bool operator !=(Edge operand2);
};
#endif
