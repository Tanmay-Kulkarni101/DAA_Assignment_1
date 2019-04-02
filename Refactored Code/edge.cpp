#include "edge.h"
/**
 * @brief Construct a new Edge:: Edge object
 * This default constructor makes an edge of zero length, which in turn consists of two default nodes
 * Again we take 0/0 to be ZERO!!
 */
Edge::Edge(){
    Node point1,point2;
    if(point1 > point2){
        Node temp = point1;
        point1 = point2;
        point2 = temp;  
    }
    
    this->point1 = point1;
    this->point2 = point2;
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

/**
 * @brief Construct a new Edge:: Edge object
 * This function defines a edge between two nodes
 * @param point1 
 * The first node henceforth referred to as X
 * @param point2 
 *  The second node, henceforth referred to as Y
 */
Edge::Edge(Node point1, Node point2){

    if(point1 > point2){
        Node temp = point1;
        point1 = point2;
        point2 = temp;  
    }
    
    this->point1 = point1;
    this->point2 = point2;
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
/**
 * @brief 
 * Getter for the slope of the edge
 * @return double 
 */
double Edge::get_slope(){
	return slope;
}
/**
 * @brief 
 * Setter for the slope of the edge
 * @return double 
 */
double Edge::get_angle(){
	return angle;
}
/**
 * @brief 
 * Getter for the length of the edge
 * @return double 
 */
double Edge::get_length(){
    return length;
}
/**
 * @brief 
 * Returns the first node of the edge
 * @return Node 
 */
Node Edge::getX(){
    return this->point1;
}
/**
 * @brief 
 * Returns the second node of the edge
 * @return Node 
 */
Node Edge::getY(){
    return this->point2;
}
/**
 * @brief 
 * prints the nodes of the edge
 */
void Edge::print_edge(){
    printf("(%lf , %lf) : (%lf , %lf)\n",this->getX().getX(),this->getX().getY(),this->getY().getX(),this->getY().getY());
}
/**
 * @brief 
 * Returns true if the slope of the first edge is lesser than the slope of the second edge
 * @param operand2 
 * @return true 
 * @return false 
 */
bool Edge::operator <(Edge operand2){
	return this->get_slope() < operand2.get_slope() ? true : false ;
}
/**
 * @brief 
 * Returns true if the slope of the first edge is greater than the slope of the second edge
 * @param operand2 
 * @return true 
 * @return false 
 */
bool Edge::operator >(Edge operand2){
	return this->get_slope() > operand2.get_slope() ? true : false ;
}
/**
 * @brief 
 * Returns true if the slope of the first edge is lesser than equal to the slope of the second edge
 * @param operand2 
 * @return true 
 * @return false 
 */
bool Edge::operator <=(Edge operand2){
	return this->get_slope() <= operand2.get_slope() ? true : false ;
}
/**
 * @brief 
 * Returns true if the slope of the first edge is greater than equal to the slope of the second edge
 * @param operand2 
 * @return true 
 * @return false 
 */
bool Edge::operator >=(Edge operand2){
	return this->get_slope() >= operand2.get_slope() ? true : false ;
}
/**
 * @brief 
 * It returns true if the slope of the first edge is the same as the slope of the second edge
 * @param operand2 
 * @return true 
 * @return false 
 */
bool Edge::operator ==(Edge operand2){
	return this->get_slope() == operand2.get_slope() ? true : false ;
}
/**
 * @brief 
 * It returns true if the slope of the first edge is not the same as the slope of the second edge
 * @param operand2 
 * @return true 
 * @return false 
 */
bool Edge::operator !=(Edge operand2){
	return this->get_slope() != operand2.get_slope() ? true : false ;
}
