#include <vector>
#include <fstream>
#include <boost/algorithm/string.hpp> 
#include <stdlib.h>
#include <iostream>
class Data{
	private:
	std::string filePath;
	std::string delim;
	public:
	static const int DATA_LINE_SIZE = 20; 
	int generateTestCases(){
		return 0;
	}
	inline std::string getDelim(){
		return delim;
	}
	inline std::string getFilePath(){
		return filePath;
	}
	Data(std::string filePath,char delim=','){
		this->filePath=filePath;
		this->delim=delim;
	}
};
// class Utilities{

// }
class Node{
	private:
	double x;
	double y;
	public:
	Node(double x,double y){
		this->x=x;
		this->y=y;
	}
};
class Edge{
	private:
	Node point1,point2;
};
class Graph{
	private:
	std::vector<Node> convexHull;
	std::vector<Node> pointList;
	// std::vector<Edge> edges;
	public:
	
	Graph(Data data){

		if(data.getFilePath().empty()==0){
			std::fstream fileDes;
			fileDes.open(data.getFilePath(),std::ios::in);
			std::string line;
			std::vector<std::string> coordinates;
			while(fileDes.eof() == 0){
				std::getline(fileDes,line);
				boost::split(coordinates,line,boost::is_any_of(data.getDelim()));
				if(coordinates.size()==2){
					std::cout<<"x:"<<coordinates.at(0)<<std::endl;
					pointList.push_back( Node ( std::stod(coordinates.at(0)),std::stod(coordinates.at(1) ) ) );
				}
				else{
					std::cerr<<"This file has been incorrectly formatted\n";
					exit(EXIT_FAILURE);
				}
			} 
		}

	}
};
int main(){
	Data data=Data("./test.txt");
	Graph graph=Graph(data);
	return 0;
}