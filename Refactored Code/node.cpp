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

Node Node::getPoint(){
	return *this;
}
double Node::getX(){
	return x;
}
double Node::getY(){
	return y;
}



bool Node::operator <(Node operand2){
	return this->x < operand2.getPoint().getX() ? true : false ;
}
bool Node::operator >(Node operand2){
	return this->x > operand2.getPoint().getX() ? true : false ;
}
bool Node::operator <=(Node operand2){
	return this->x <= operand2.getPoint().getX() ? true : false ;
}
bool Node::operator >=(Node operand2){
	return this->x >= operand2.getPoint().getX() ? true : false ;
}
bool Node::operator ==(Node operand2){
	return this->x == operand2.getPoint().getX() ? true : false ;
}
bool Node::operator !=(Node operand2){
	return this->x != operand2.getPoint().getX() ? true : false ;
}
