#ifndef NODE
#define NODE

class Node{
	private:
	double x;
	double y;
	public:
	Node(double x,double y);
	std::pair<double,double> getPoint();
	static bool compareX(void* a,void* b);
};

#endif