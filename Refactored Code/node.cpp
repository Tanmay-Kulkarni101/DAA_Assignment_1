#include <iostream>
#include "node.h"

/**
 * @brief Construct a new Node:: Node object
 * 
 * @param x the x coordinate
 * @param y the y coordinate
 */
Node::Node(double x,double y){
	this->x=x;
	this->y=y;
}

/**
 * @brief Construct a new Node:: Node object
 * 
 */
Node::Node(){
	this->x=0;
	this->y=0;
}


/**
 * @brief This is used to return the Node object
 * 
 * @return Node 
 */
Node Node::getPoint(){
	return *this;
}

/**
 * @brief retruns the x coordinate
 * 
 * @return double x
 */
double Node::getX(){
	return x;
}

/**
 * @brief returns the y coordinate
 * 
 * @return double y
 */
double Node::getY(){
	return y;
}


/**
 * @brief auxilary method for printing the node
 * 
 */
void Node::print_node(){
	printf("%lf,%lf\n",this->x,this->y);
}

/**
 * @brief overriden comparator for comparing two nodes based on the equality of both the  coordinates 
 * 
 * @param node2 
 * @return true 
 * @return false 
 */
bool Node::is_equal(Node node2){
	if(this->x == node2.getX() && this->y == node2.getY()){
		return true;
	}
	else{
		return false;
	}
}
/**
 * @brief 
 * Does a less than comparison based on the x coordinate
 * @param operand2 
 * @return true 
 * @return false 
 */
bool Node::operator <(Node operand2){
	return this->x < operand2.getPoint().getX() ? true : false ;
}

/**
 * @brief overriden comparator for comparing two nodes based on the x coordinate, returns true if the second node is smaller
 * 
 * @param operand2 
 * @return true 
 * @return false 
 */
bool Node::operator >(Node operand2){
	return this->x > operand2.getPoint().getX() ? true : false ;
}

/**
 * @brief overriden comparator for comparing two nodes based on the x coordinate, returns true if the second node is greater or equal to the first
 * 
 * @param operand2 
 * @return true 
 * @return false 
 */
bool Node::operator <=(Node operand2){
	return this->x <= operand2.getPoint().getX() ? true : false ;
}

/**
 * @brief overriden comparator for comparing two nodes based on the x coordinate, returns true if the second node is smaller or equal to the first
 * 
 * @param operand2 
 * @return true 
 * @return false 
 */
bool Node::operator >=(Node operand2){
	return this->x >= operand2.getPoint().getX() ? true : false ;
}

/**
 * @brief overriden comparator for comparing two nodes based on the x coordinate, returns true if the second node has the same x coordinate as the first
 * 
 * @param operand2 
 * @return true 
 * @return false 
 */
bool Node::operator ==(Node operand2){
	return this->x == operand2.getPoint().getX() ? true : false ;
}

/**
 * @brief overriden comparator for comparing two nodes based on the x coordinate, returns true if the second node has a different x coordinate as the first
 * 
 * @param operand2 
 * @return true 
 * @return false 
 */
bool Node::operator !=(Node operand2){
	return this->x != operand2.getPoint().getX() ? true : false ;
}
