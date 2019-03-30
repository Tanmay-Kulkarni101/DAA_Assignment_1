#include "edge.h"

Edge::Edge(Node point1, Node point2){
    this->point1 = point1;
    this->point2 = point2;

    if(point1 > point2){
        Node temp = point1;
        point1 = point2;
        point2 = temp;  
    }
    if(point2.getX() != point1.getX())
        this->slope = (point2.getY()-point1.getY())/(point2.getX()-point1.getX());
    else if(point2.getY() > point1.getY())
        this->slope = std::numeric_limits<double>::infinity();
    else if(point2.getY() < point1.getY())
        this->slope = -std::numeric_limits<double>::infinity();
    else if(point2.getY() == point1.getY()) // a point
        this->slope = 0;
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

Node Edge::getX(){
    return this->point1;
}
Node Edge::getY(){
    return this->point2;
}

void Edge::print_edge(){
    printf("(%lf , %lf) : (%lf , %lf)\n",this->getX().getX(),this->getX().getY(),this->getY().getX(),this->getY().getY());
}

bool Edge::operator <(Edge operand2){
	return this->get_slope() < operand2.get_slope() ? true : false ;
}
bool Edge::operator >(Edge operand2){
	return this->get_slope() > operand2.get_slope() ? true : false ;
}
bool Edge::operator <=(Edge operand2){
	return this->get_slope() <= operand2.get_slope() ? true : false ;
}
bool Edge::operator >=(Edge operand2){
	return this->get_slope() >= operand2.get_slope() ? true : false ;
}
bool Edge::operator ==(Edge operand2){
	return this->get_slope() == operand2.get_slope() ? true : false ;
}
bool Edge::operator !=(Edge operand2){
	return this->get_slope() != operand2.get_slope() ? true : false ;
}
