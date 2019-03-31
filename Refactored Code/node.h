#ifndef NODE
#define NODE
#include<utility>
#include<stdio.h>
class Node{
	private:
	double x;
	double y;
	public:
	Node(double x,double y);
	Node();
	Node getPoint();
	double getX();
	double getY();
	void print_node();
	bool is_equal (Node node2);
	bool operator <(Node operand2);
	bool operator >(Node operand2);
	bool operator <=(Node operand2);
	bool operator >=(Node operand2);
	bool operator ==(Node operand2);
	bool operator !=(Node operand2);
};

#endif
