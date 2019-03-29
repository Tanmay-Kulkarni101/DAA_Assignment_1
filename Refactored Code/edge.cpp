#include "edge.h"
#include <math.h>
Edge::Edge(Node point1, Node point2){
    this->point1 = point1;
    this->point2 = point2;
    this->slope = (point2.getY()-point1.getY())/(point2.getX()-point1.getX());
    this->angle = atan(slope);
}

double Edge::distance(){
    std::pair<double,double> p1 = point1.getPoint();
    std::pair<double,double> p2 = point2.getPoint();
    return sqrt(pow(p1.first - p2.first,2) + pow(p1.second - p2.second,2));
}

double Edge::get_slope(){
	return slope;
}

double Edge::get_angle(){
	return angle;
}
