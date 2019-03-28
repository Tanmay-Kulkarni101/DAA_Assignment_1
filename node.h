#ifndef NODE
#define NODE
#include<utility>
class Node{
	private:
	double x;
	double y;
	public:
	Node(double x,double y);
	std::pair<double,double> getPoint();
	static bool compareX(void* a,void* b);
	bool operator <(Node operand2);
	bool operator >(Node operand2);
	bool operator <=(Node operand2);
	bool operator >=(Node operand2);
	bool operator ==(Node operand2);
	bool operator !=(Node operand2);
};

#endif
