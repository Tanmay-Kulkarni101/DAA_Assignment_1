#include "edge.h"
#include <math.h>
Edge::Edge(Node point1, Node point2){
    this->point1 = point1;
    this->point2 = point2;
    this->slope = (point2.getY()-point1.getY())/(point2.getX()-point1.getX());
    this->angle = atan(slope);
    Node p1 = point1.getPoint();
    Node p2 = point2.getPoint();
    length = sqrt(pow(p1.getX() - p2.getX(),2) + pow(p1.getY() - p2.getY(),2));
}

double Edge::get_slope(){
	return slope;
}

double Edge::get_angle(){
	return angle;
}

double Edge::get_length(){
    return length;
}
