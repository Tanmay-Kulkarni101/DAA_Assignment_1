
#include "graph.h"

	Graph::Graph(Data data){
		pointList = data.get_data_from_file();
	}

	std::vector<Node> Graph::getPointList(){
		return pointList;
	}

	void Graph::setPointList(std::vector<Node> &pointList){
		this->pointList.swap(pointList);
	}

	void Graph::displayPointList(){
		std::cout << "The points present within the graph are" << '\n';
		for(auto it=pointList.begin();it<pointList.end();it++){
			std::cout<<"X:"<<it->getPoint().first<<" Y:"<<it->getPoint().second<<std::endl;
		}
	}

	bool Graph::get_orientation(Node p,Node q,Node r){
		double temp = (q.getX()-p.getX())*(r.getY()-q.getY()) - (q.getY()-p.getY())*(r.getX()-q.getX());
		if(temp > 0){ // for anti-clockwise
			return true;
		}
		else { // for collinear and clockwise
			return false;
		}
	}

	Node Graph::get_left_most_point(bool flag_lower){// if the flag is false we find the upper most point
		if(pointList.size()==0){ // Size check
			std::cout << "The size of the list is zero" << '\n';
			exit(EXIT_FAILURE);
		}
		Node answer = pointList[0];

		for (int i=1; i<pointList.size();i++){
			if(answer>pointList[i]){// Remember:We check only x by default
				answer = pointList[i];
			}
			else if(pointList[i] == answer){ // WARNING!! Definition has been changed
				if(flag_lower == true){
					if(answer.getY()>pointList[i].getY()){
						answer = pointList[i];
					}
				}
				else{ // obtain the highest
					if(answer.getY()<pointList[i].getY()){
						answer = pointList[i];
					}
				}
			}
		}

		return answer;
	}

	Node Graph::get_right_most_point(bool flag_lower){// if the flag is false we find the upper most point
		if(pointList.size()==0){ // Size check
			std::cout << "The size of the list is zero" << '\n';
			exit(EXIT_FAILURE);
		}
		Node answer = pointList[0];

		for (int i=1; i<pointList.size();i++){
			if(answer<pointList[i]){// Remember:We check only x by default
				answer = pointList[i];
			}
			else if(pointList[i] == answer){ // WARNING!! Definition has been changed
				if(flag_lower == true){
					if(answer.getY()>pointList[i].getY()){
						answer = pointList[i];
					}
				}
				else{ // obtain the highest
					if(answer.getY()<pointList[i].getY()){
						answer = pointList[i];
					}
				}
			}
		}

		return answer;
	}

	void Graph::grahm_scan(){

	}

	void Graph::jarvis_march(){

	}
