#include <vector>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <stdlib.h>
#include <iostream>
#include "data.h"
#include "node.h"
#include "utilities.h"
#include "stack.h"
#include "edge.h"
#include "graph.h"

// class Edge{
// 	private:
// 	Node point1,point2;
// };

// class Graph{
// 	private:
// 	std::vector<Node> convexHull;
// 	std::vector<Node> pointList;
// 	// std::vector<Edge> edges;
// 	public:
//
// 	Graph(Data data){
//
// 		if(data.getFilePath().empty()==0){
// 			std::fstream fileDes;
// 			fileDes.open(data.getFilePath(),std::ios::in);
// 			std::string line;
// 			std::vector<std::string> coordinates;
// 			while(fileDes.eof() == 0){
// 				std::getline(fileDes,line);
// 				boost::split(coordinates,line,boost::is_any_of(data.getDelim()));
// 				if(coordinates.size()==2){
// 					pointList.push_back( Node ( std::stod(coordinates.at(0)),std::stod(coordinates.at(1) ) ) );
// 				}
// 				else{
// 					std::cerr<<"This file has been incorrectly formatted\n";
// 					exit(EXIT_FAILURE);
// 				}
// 			}
// 		}
//
// 	}
//
// 	std::vector<Node> getPointList(){
// 		return pointList;
// 	}
//
// 	void setPointList(std::vector<Node> &pointList){
// 		this->pointList.swap(pointList);
// 	}
//
// 	void displayPointList(){
// 		for(auto it=pointList.begin();it<pointList.end();it++){
// 			std::cout<<"X:"<<it->getPoint().first<<" Y:"<<it->getPoint().second<<std::endl;
// 		}
// 	}
//
// };




int main(){
	Data data=Data("./test.txt");
	Graph graph=Graph(data);
	Utilities utility=Utilities();

	std::vector<Node> pointList=graph.getPointList();
	utility.sort(pointList,(&Node::compareX) );
	graph.setPointList(pointList);

	graph.displayPointList();
	return 0;
}
