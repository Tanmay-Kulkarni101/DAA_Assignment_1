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
	std::pair<double,double> getPoint();
	double getX();
	double getY();
	static bool compareX(void* a,void* b);
    static double polar_angler(Node source, Node target);
    static bool get_orientation(Node p, Node q, Node r);
	bool operator <(Node operand2);
	bool operator >(Node operand2);
	bool operator <=(Node operand2);
	bool operator >=(Node operand2);
	bool operator ==(Node operand2);
	bool operator !=(Node operand2);
};

#endif
