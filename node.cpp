#include <iostream>
#include "node.h"

Node::Node(double x,double y){
	this->x=x;
	this->y=y;
}
std::pair<double,double> Node::getPoint(){
	return std::make_pair(x,y);
}
bool Node::compareX(void* a,void* b){
	Node val1=*((Node*)a);
	Node val2=*((Node*)b);
	
	if(val1.x<=val2.x){
		return true;
	}
	else{
		return false;
	}
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
		return ((this->x == operand2.getPoint().first) && (this->y == operand2.getPoint().second) ) ? true : false ;
	}
	bool Node::operator !=(Node operand2){
		return this->x != operand2.getPoint().first ? true : false ;
	}