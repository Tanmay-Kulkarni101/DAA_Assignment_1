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

	
class Node{
	private:
	double x;
	double y;
	public:
	Node(double x,double y){
		this->x=x;
		this->y=y;
	}
	std::pair<double,double> getPoint(){
		return std::make_pair(x,y);
	}
	static bool compareX(void* a,void* b){
		Node val1=*((Node*)a);
		Node val2=*((Node*)b);
		if(val1.x<=val2.x){
			return true;
		}
		else{
			false;
		}
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

	std::vector<Node> getPointList(){
		return pointList;
	}

};

class Utilities{
	public:
	Utilities(){

	}

	template <typename T>
	void sort(std::vector<T> array,bool (*compare)(void* a,void* b) ){
		std::size_t const mid=array.size()/2;
		std::vector<T> low(array.begin(),array.begin()+mid);
		std::vector<T> high(array.begin()+mid,array.end());
		sort(low,compare);
		sort(high,compare);

		std::vector<T> temp;
		typename std::vector<T>::iterator left=low.begin();
		typename std::vector<T>::iterator right=high.begin();
		while(left<low.end() && right<high.end()){
			if( (*compare) ( (void*)&*left,(void*)&*right ) ) {//left smaller than right
				temp.push_back(*left);
			}
			else{
				temp.push_back(*right);
			}
		}
		while(left<low.end()){
			temp.push_back(*left);
		}
		while(right<high.end()){
			temp.push_back(*right);
		}

		typename std::vector<T>::iterator iter1,iter2;
		for(iter1=temp.begin(),iter2=array.begin();iter1<temp.end();iter1++,iter2++){
			*iter2=*iter1;
		}
	}

	void mom(){

	}
};


int main(){
	Data data=Data("./test.txt");
	Graph graph=Graph(data);
	Utilities utility=Utilities();
	utility.sort(graph.getPointList(),(&Node::compareX) );
	std::vector<Node>::iterator it= graph.getPointList().begin();
	for(;it<graph.getPointList().end();it++){
		std::cout<<it->getPoint().first<<" "<<it->getPoint().second<<std::endl;
	}
	return 0;
}