#ifndef NODE
#define NODE
#include<utility>
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
	bool operator <(Node operand2);
	bool operator >(Node operand2);
	bool operator <=(Node operand2);
	bool operator >=(Node operand2);
	bool operator ==(Node operand2);
	bool operator !=(Node operand2);
};

#endif
