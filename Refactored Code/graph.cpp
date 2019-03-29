
#include "graph.h"

Graph::Graph(Data data){
	point_list = data.get_data_from_file();
}

std::vector<Node> Graph::getPointList(){
	return point_list;
}

void Graph::setPointList(std::vector<Node> &point_list){
	this->point_list.swap(point_list);
}

void Graph::displayPointList(){
	std::cout << "The points present within the graph are" << '\n';
	for(auto it=point_list.begin();it<point_list.end();it++){
		std::cout<<"X:"<<it->getPoint().getX()<<" Y:"<<it->getPoint().getY()<<std::endl;
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
	if(point_list.size()==0){ // Size check
		std::cout << "The size of the list is zero" << '\n';
		exit(EXIT_FAILURE);
	}
	Node answer = point_list[0];

	for (int i=1; i<point_list.size();i++){
		if(answer>point_list[i]){// Remember:We check only x by default
			answer = point_list[i];
		}
		else if(point_list[i] == answer){ // WARNING!! Definition has been changed
			if(flag_lower == true){
				if(answer.getY()>point_list[i].getY()){
					answer = point_list[i];
				}
			}
			else{ // obtain the highest
				if(answer.getY()<point_list[i].getY()){
					answer = point_list[i];
				}
			}
		}
	}

	return answer;
}

Node Graph::get_right_most_point(bool flag_lower){// if the flag is false we find the upper most point
	if(point_list.size()==0){ // Size check
		std::cout << "The size of the list is zero" << '\n';
		exit(EXIT_FAILURE);
	}
	Node answer = point_list[0];

	for (int i=1; i<point_list.size();i++){
		if(answer<point_list[i]){// Remember:We check only x by default
			answer = point_list[i];
		}
		else if(point_list[i] == answer){ // WARNING!! Definition has been changed
			if(flag_lower == true){
				if(answer.getY()>point_list[i].getY()){
					answer = point_list[i];
				}
			}
			else{ // obtain the highest
				if(answer.getY()<point_list[i].getY()){
					answer = point_list[i];
				}
			}
		}
	}

	return answer;
}

void Graph::graham_scan(){
	Node corner_point = get_left_most_point(false); // Taking the highest point on the left side
	std::vector<Node> temp_point_list = point_list; // This does a deep copy and replaces the objects in the container

	std::cout<<"The corner point is "<<corner_point.getX()<<" "<<corner_point.getY()<<'\n';
    vector<pair<Node,double>> polar_angles;
    polar_angles.push_back(make_pair(corner_point,-10));

    //finding polar angles wrt to all the points
    for(int i=0;i<point_list.size();i++){
        if(point_list[i] != corner_point)
            polar_angles.push_back(make_pair(point_list[i],Node::polar_angler(corner_point,point_list[i])));
        printf("%lf\n",polar_angles[i].second);
    }

    // STL sorting wrt to polar angles
    for(int i=0;i<point_list.size()-1;i++){
        for(int j=i+1;j<point_list.size();j++){
            if(polar_angles[i].second > polar_angles[j].second){
                pair<pair<double,double>,double> temp = polar_angles[i];
                polar_angles[i] = polar_angles[j];
                polar_angles[j] = temp;
            }
        }
    }

    for(int i=0;i<polar_angles.size();i++){
        cout<<polar_angles[i].first.getX()<<" "<<polar_angles[i].first.getY()<<" -> "<<polar_angles[i].second<<endl;
    }

    vector<pair<Node,double>> st;
    st.push_back(polar_angles[0]);
    st.push_back(polar_angles[1]);
    for(int i=2;i<polar_angles.size();i++){
        while(st.size() > 1 && get_orientation(st[st.size()-2].first,st[st.size()-1].first,polar_angles[i].first) == false){
            cout<<"Removed from hull"<<st[st.size()-1].first.getX()<<" "<<st[st.size()-1].first.getY()<<endl;
            st.pop_back();
        }
        st.push_back(polar_angles[i]);
    }
    // vector<pair<double,double>> solution;
    for(int i=0;i<st.size();i++){
        cout<<st[i].first.getX()<<" "<<st[i].first.getY()<<" -> "<<st[i].second<<endl;
        convex_hull.push_back(st[i].first);
    }

    // return solution;

}

void Graph::jarvis_march(){

}
