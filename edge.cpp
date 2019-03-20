#include "edge.h"
#include "node.cpp"
#include <math.h>
Edge::Edge(Node point1, Node point2){
    this->point1 = point1;
    this->point2 = point2;
}

double Edge::distance(Node point1,Node point2){
    std::pair<double,double> p1 = point1.getPoint();
    std::pair<double,double> p2 = point2.getPoint();
    return sqrt(pow(p1.first - p2.first,2) + pow(p1.second - p2.second,2));
}
