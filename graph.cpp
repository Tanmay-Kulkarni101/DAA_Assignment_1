#include <boost/algorithm/string.hpp>
#include "graph.h"
#include "data.h"

	Graph::Graph(Data data){

		if(data.getFilePath().empty()==0){
			std::fstream fileDes;
			fileDes.open(data.getFilePath(),std::ios::in);
			std::string line;
			std::vector<std::string> coordinates;
			while(fileDes.eof() == 0){
				std::getline(fileDes,line);
				boost::split(coordinates,line,boost::is_any_of(data.getDelim()));
				if(coordinates.size()==2){
					pointList.push_back( Node ( std::stod(coordinates.at(0)),std::stod(coordinates.at(1) ) ) );
				}
				else{
					std::cerr<<"This file has been incorrectly formatted\n";
					exit(EXIT_FAILURE);
				}
			}
		}

	}

	std::vector<Node> Graph::getPointList(){
		return pointList;
	}

	void Graph::setPointList(std::vector<Node> &pointList){
		this->pointList.swap(pointList);
	}

	void Graph::displayPointList(){
		for(auto it=pointList.begin();it<pointList.end();it++){
			std::cout<<"X:"<<it->getPoint().first<<" Y:"<<it->getPoint().second<<std::endl;
		}
	}
