#ifndef NODE
#define NODE
#include<utility>
#include<stdio.h>
/**
 * @brief 
 * This call encompasses all the properties for a node.
 * It allows us to get the x and y coordinates or print the node for debugging purposes
 */
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
