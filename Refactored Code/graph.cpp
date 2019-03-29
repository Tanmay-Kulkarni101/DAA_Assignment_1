
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

double Graph::polar_angler(Node source, Node target){
    return atan((target.getY()-source.getY())/(target.getX()-source.getX()));
}

void Graph::displayConvexHull(){
	std::cout << "The points present within the convex hull are" << '\n';
    if(convex_hull.size() == 0){
        printf("Convex hull is empty\n");
        return;
    }
	for(auto it=convex_hull.begin();it<convex_hull.end();it++){
		std::cout<<"X:"<<it->getPoint().getX()<<" Y:"<<it->getPoint().getY()<<std::endl;
	}
}

void Graph::graham_scan(){
	Node corner_point = get_left_most_point(false); // Taking the highest point on the left side
	std::vector<Node> temp_point_list = point_list; // This does a deep copy and replaces the objects in the container

	std::cout<<"The corner point is "<<corner_point.getX()<<" "<<corner_point.getY()<<'\n';
    std::vector<std::pair<Node,double>> polar_angles;
    polar_angles.push_back(std::make_pair(corner_point,-10));

    //finding polar angles wrt to all the points
    for(int i=0;i<point_list.size();i++){
        if(point_list[i] != corner_point)

            polar_angles.push_back(std::make_pair(point_list[i],polar_angler(corner_point,point_list[i])));
        printf("%lf\n",polar_angles[i].second);
    }

    // STL sorting wrt to polar angles
    for(int i=0;i<point_list.size()-1;i++){
        for(int j=i+1;j<point_list.size();j++){
            if(polar_angles[i].second > polar_angles[j].second){
                std::pair<Node,double> temp = polar_angles[i];
                polar_angles[i] = polar_angles[j];
                polar_angles[j] = temp;
            }
        }
    }

    for(int i=0;i<polar_angles.size();i++){
        std::cout<<polar_angles[i].first.getX()<<" "<<polar_angles[i].first.getY()<<" -> "<<polar_angles[i].second<<std::endl;
    }
    //apply the algorithm
    std::vector<std::pair<Node,double>> st;
    st.push_back(polar_angles[0]);
    st.push_back(polar_angles[1]);
    for(int i=2;i<polar_angles.size();i++){
        while(st.size() > 1 && get_orientation(st[st.size()-2].first,st[st.size()-1].first,polar_angles[i].first) == false){

            std::cout<<"Removed from hull"<<st[st.size()-1].first.getX()<<" "<<st[st.size()-1].first.getY()<<std::endl;
            st.pop_back();
        }
        st.push_back(polar_angles[i]);
    }
    // std::vector<pair<double,double>> solution;
    for(int i=0;i<st.size();i++){
        std::cout<<st[i].first.getX()<<" "<<st[i].first.getY()<<" -> "<<st[i].second<<std::endl;
        convex_hull.push_back(st[i].first);
    }

    // return solution;

}

void Graph::jarvis_march(){
    Node corner_point = get_left_most_point(false);
    std::cout<<"The corner point is "<<corner_point.getX()<<" "<<corner_point.getY()<<std::endl;
    //remove the corner point
    std::vector<Node>::iterator iterTemp = std::remove(point_list.begin(), point_list.end(), corner_point);
    // point_list.erase(point_list.begin()+location);
    // std::vector<Node> solution;
    convex_hull.push_back(corner_point);
    Node candidate = point_list[0], last_point = convex_hull[convex_hull.size()-1];
    //apply the algorithm
    while(true/*Reach the corner point again*/){
        candidate = point_list[0];
        printf("the starting candidate is %lf %lf\n",candidate.getX(),candidate.getY());
        // if(candidate == corner_point)
        //     candidate = point_list[1];
        last_point = convex_hull[convex_hull.size()-1];
        int location = 0;
        for(int i=1;i<point_list.size();i++){
            if(get_orientation(last_point,candidate,point_list[i]) == false){
                printf("get_orientation = %lf,%lf %lf,%lf %lf,%lf -> %d\n",last_point.getX(),last_point.getY(),candidate.getX(),candidate.getY(),point_list[i].getX(),point_list[i].getY(),get_orientation(last_point,candidate,point_list[i]));
                candidate = point_list[i];
                location = i;
            }
            else{
                printf("get_orientation = %lf,%lf %lf,%lf %lf,%lf -> %d\n",last_point.getX(),last_point.getY(),candidate.getX(),candidate.getY(),point_list[i].getX(),point_list[i].getY(),get_orientation(last_point,candidate,point_list[i]));
            }
        }
        if(last_point != corner_point && get_orientation(last_point,candidate,corner_point) == false){
            printf("entered termination with candidate: %lf,%lf\n", candidate.getX(),candidate.getY());
            break;

        }
        convex_hull.push_back(*(point_list.begin()+location));
        printf("%lf %lf has been erased\n",(point_list.begin()+location)->getX(),(point_list.begin()+location)->getY());
        candidate = *(point_list.begin()+location);
        printf("the ending candidate is %lf %lf\n",candidate.getX(),candidate.getY());
        // point_list.erase(point_list.begin()+location);
        point_list.erase(std::remove(point_list.begin(),point_list.end(),candidate),point_list.end());
        for(int i=0;i<point_list.size();i++){
            std::cout<<point_list[i].getX()<<" "<<point_list[i].getY()<<std::endl;
        }
        std::cout<<"**********Das temp solution ist********\n";
        for(int i=0;i<convex_hull.size();i++){
            std::cout<<convex_hull[i].getX()<<" "<<convex_hull[i].getY()<<std::endl;
        }
        char c;
        std::cin >> c;
        std::cout<<"***********************************\n";
    }
    std::cout<<"Das solution ist\n";
    for(int i=0;i<convex_hull.size();i++){
        std::cout<<convex_hull[i].getX()<<" "<<convex_hull[i].getY()<<std::endl;
    }
}



void Graph::kirk_patrick_seidel(){
    // pmin and pmax
    // Call Upper Hull -> Upper Bridge
    // Call Lower Hull -> Lower Bridge
    // Join them

	// if (point_list.size() <= 2)
	// 	return NULL;

	// if size == 3 sort w.r.t x coordinate and return
	//TO DO Collinearity check


    std::vector<pair<double,double>> upper_hull_points,lower_hull_points;

    tuple<pair<double,double>,pair<double,double>,int,int > corner_point_upper = get_corner_points(point_list,true);
    upper_hull_points.push_back(get<0>(corner_point_upper));

    point_list.erase(point_list.begin()+get<2>(corner_point_upper));
    point_list.erase(point_list.begin()+get<3>(corner_point_upper));

    double slope = (get<0>(corner_point_upper).second - get<1>(corner_point_upper).second ) / ( get<0>(corner_point_upper).first - get<1>(corner_point_upper).first  );
    double intercept = (get<0>(corner_point_upper).second - slope * get<0>(corner_point_upper).first);
    for(int i=0;i<point_list.size();i++){
        if(point_list[i].second - slope* point_list[i].first > intercept){
            upper_hull_points.push_back(point_list[i]);
            point_list.erase(point_list.begin()+i); // This will get rid of all the upper hull points
            i--;
        }
    }



    upper_hull_points.push_back(get<1>(corner_point_upper));

    // printf("The corner points are %lf,%lf and %lf,%lf\n",get<0>(corner_point_upper).first,get<0>(corner_point_upper).second,get<1>(corner_point_upper).first,get<1>(corner_point_upper).second);
    // printf("The remaining are:\n");
    // for(int i=0;i<point_list.size();i++){
    // 	printf("%lf,%lf\n",point_list[i].first,point_list[i].second);
    // }

    tuple<pair<double,double>,pair<double,double>,int,int > corner_point_lower = get_corner_points(point_list,false);

    point_list.erase(point_list.begin()+get<2>(corner_point_lower));
    point_list.erase(point_list.begin()+get<3>(corner_point_lower));

    lower_hull_points.push_back(get<0>(corner_point_lower));
    slope = (get<0>(corner_point_lower).second - get<1>(corner_point_lower).second ) / ( get<0>(corner_point_lower).first - get<1>(corner_point_lower).first  );
    intercept = (get<0>(corner_point_lower).second - slope * get<0>(corner_point_lower).first);
    for(int i=0;i<point_list.size();i++){
        if(point_list[i].second - slope* point_list[i].first < intercept){
            lower_hull_points.push_back(point_list[i]);
            point_list.erase(point_list.begin()+i);
            i--;
        }
    }

    lower_hull_points.push_back(get<1>(corner_point_lower));

    // printf("The corner points are %lf,%lf and %lf,%lf\n",get<0>(corner_point_lower).first,get<0>(corner_point_lower).second,get<1>(corner_point_lower).first,get<1>(corner_point_lower).second);
    // printf("The remaining are:\n");
    // for(int i=0;i<point_list.size();i++){
    // 	printf("%lf,%lf\n",point_list[i].first,point_list[i].second);
    // }

    // printf("The upper hull points are:\n");
    // for(int i=0;i<upper_hull_points.size();i++){
    // 	printf("%lf,%lf\n",upper_hull_points[i].first,upper_hull_points[i].second);
    // }

    // printf("The Lower hull points are:\n");
    // for(int i=0;i<lower_hull_points.size();i++){
    // 	printf("%lf,%lf\n",lower_hull_points[i].first,lower_hull_points[i].second);
    // }

    upper_hull(upper_hull_points);

}
