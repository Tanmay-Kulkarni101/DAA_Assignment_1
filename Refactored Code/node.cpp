#include <iostream>
#include "node.h"

Node::Node(double x,double y){
	this->x=x;
	this->y=y;
}
Node::Node(){
	this->x=0;
	this->y=0;
}
std::pair<double,double> Node::getPoint(){
	return std::make_pair(x,y);
}
double Node::getX(){
	return x;
}
double Node::getY(){
	return y;
}
static bool Node::compareX(void* a,void* b){
	Node val1=*((Node*)a);
	Node val2=*((Node*)b);

	if(val1.x<=val2.x){
		return true;
	}
	else{
		return false;
	}
}

static double Node::polar_angler(Node source, Node target){
    return atan((target.getY()-source.getY())/(target.getX()-source.getX()));
}

static bool Node::get_orientation(Node p, Node q, Node r){
    double temp = (q.getX()-p.getX())*(r.gety()-q.gety()) - (q.gety()-p.gety())*(r.getX()-q.getX());
    if(temp > 0) return true;
    else return false;
}

bool Node::operator <(Node operand2){
	return this->x < operand2.getPoint().first ? true : false ;
}
bool Node::operator >(Node operand2){
	return this->x > operand2.getPoint().first ? true : false ;
}
bool Node::operator <=(Node operand2){
	return this->x <= operand2.getPoint().first ? true : false ;
}
bool Node::operator >=(Node operand2){
	return this->x >= operand2.getPoint().first ? true : false ;
}
bool Node::operator ==(Node operand2){
	return this->x == operand2.getPoint().first ? true : false ;
}
bool Node::operator !=(Node operand2){
	return this->x != operand2.getPoint().first ? true : false ;
}
