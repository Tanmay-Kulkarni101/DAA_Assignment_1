#include <vector>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <stdlib.h>
#include <iostream>
#include <math.h>
// #include "data.cpp"
// #include "node.cpp"
// #include "utilities.cpp"
// #include "stack.cpp"
// #include "edge.cpp"
// #include "graph.cpp"
#define DEFAULT_CAPACITY 100

template <class T>
class List{
private:
	int capacity;
	int size;
	T* array;
public:
	List(int capacity){
		this->capacity = capacity;
		this->size = 0;
		this->array = new T [capacity];
	}
	List(){
		this->size = 0;
		this->capacity = DEFAULT_CAPACITY;
		this->array = new T [capacity];
	}

	T getElementAt(int index){
		if(size == 0){
			std::cerr<<"!!!!!!!Array does not have any elements!!!!!!!!!!!!!!\n" ;
			exit(EXIT_FAILURE);
		}
		if(index == -1){
			T temp = array[size];
			return temp;
		}
		else if(index > size || index < -1){
			std::cerr<<"!!!!!!!Array index out of bounds!!!!!!!!!!!!!!\n" ;
			exit(EXIT_FAILURE);
		}
		else{
			T temp = array[index];
			return temp;
		}
	}

	void append(T element){
		if(size+1 > capacity){
			T* temp = new T [2*capacity];
			for(int i=0;i<size;i++){
				temp[i] = array[i];
			}
			delete[] array;
			array = temp;
			array[size++] = element;
			return;
		}
		array[size++] = element;
	}

	T remove(int index){
		if(size == 0){
			std::cerr<<"!!!!!!!Array does not have any elements!!!!!!!!!!!!!!\n" ;
			exit(EXIT_FAILURE);
		}
		if(index == -1){
			T temp = array[--size];
			return temp;
		}
		else if(index > size || index < -1){
			std::cerr<<"!!!!!!!Array index out of bounds!!!!!!!!!!!!!!\n" ;
			exit(EXIT_FAILURE);
		}
		else{
			T temp = array[index];
			for(int i = index;i<size-1;i++){
				array[i] = array[i+1];
			}
			size--;
			return temp;
		}
	}

	void printList(){
		if(size == 0){
			std::cout<<"Array is empty\n";
			return;
		}
		for(int i=0;i<size;i++){
			std::cout<<getElementAt(i)<<" ";
			std::cout<<std::endl;
		}
	}
};

class Data{
private:
	std::string filePath;
	std::string delim;
	public:
	static const int DATA_LINE_SIZE = 20;
	int generateTestCases();
	std::string getDelim();
	std::string getFilePath();
	Data(std::string filePath,char delim=',');
};

static const int DATA_LINE_SIZE = 20;
int Data::generateTestCases(){
	return 0;
}
std::string Data::getDelim(){
	return delim;
}
std::string Data::getFilePath(){
	return filePath;
}
Data::Data(std::string filePath,char delim){
	this->filePath=filePath;
	this->delim=delim;
}




class Node{
private:
	double x;
	double y;
public:
	// Node(){
	// 	std::cout<<"sads";
	// }
	Node(double x,double y){
		this->x=x;
		this->y=y;
	}
	std::pair<double,double> getPoint();
	static bool compareX(void* a,void* b);
};

// Node::Node(double x,double y){
//
// }
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

class Edge{
	private:
		Node point1,point2;
	public:
		// Edge(Node point1, Node point2);
		// double distance();
		Edge(Node &point1, Node &point2)
		: point1(point1), point2(point2)
		{
			// this->point1 = point1;
			// this->point2 = point2;
		}
		double distance(){
			std::pair<double,double> p1 = point1.getPoint();
			std::pair<double,double> p2 = point2.getPoint();
			return sqrt(pow(p1.first - p2.first,2) + pow(p1.second - p2.second,2));
		}

};




class Graph{
private:
	std::vector<Node> convexHull;
	std::vector<Node> pointList;
	std::vector<Edge> edges;
public:

	Graph(Data data);

	std::vector<Node> getPointList();

	void setPointList(std::vector<Node> &pointList);

	void displayPointList();

	std::vector<Node> jarvisMarchConvexHull(){

	}
};


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

class Utilities{
	public:
	Utilities();

	template <typename T>
	void sort(std::vector<T> &array,bool (*compare)(void* a,void* b) );

	void mom();
};

Utilities::Utilities(){

}


template <typename T>
void Utilities::sort(std::vector<T> &array,bool (*compare)(void* a,void* b) ){
	if (array.size()<=1){
		return;
	}

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
			left++;
		}
		else{
			temp.push_back(*right);
			right++;
		}
	}
	while(left<low.end()){
		temp.push_back(*left);
		left++;
	}
	while(right<high.end()){
		temp.push_back(*right);
		right++;
	}

	typename std::vector<T>::iterator iter1,iter2;
	for(iter1=temp.begin(),iter2=array.begin();iter1<temp.end();iter1++,iter2++){
		*iter2=*iter1;
	}
}

void Utilities::mom(){

}


int main(){
	Data data=Data("./test.txt");
	Graph graph=Graph(data);
	Utilities utility=Utilities();

	std::vector<Node> pointList=graph.getPointList();
	utility.sort(pointList,(&Node::compareX) );
	graph.setPointList(pointList);

	graph.displayPointList();
	List<int> list;
	list.append(1);
	list.append(2);
	list.printList();
	return 0;
}
