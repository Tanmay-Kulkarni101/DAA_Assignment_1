
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

Edge Graph::upper_bridge(std::vector<Node> point_list){
	Node the_median= Utilities<Node>::median(point_list,point_list.size()/2);
	printf("the median is %lf,%lf\n",the_median.getX(),the_median.getY());
	std::vector<Node> left,right,candidates;
	Node top_most_median = the_median;
	for(int i=0;i<point_list.size();i++){
		if(point_list[i] < the_median){
			left.push_back(point_list[i]);
		}
		else if(point_list[i] > the_median){
			right.push_back(point_list[i]);
		}
		else{
			if(point_list[i].getY()>top_most_median.getY()){
				top_most_median=point_list[i];
			}
		}
	}

		candidates.push_back(top_most_median);
		printf("Left has\n");
		for(int i=0;i<left.size();i++){
			printf("%lf,%lf\n",left[i].getX(), left[i].getY());
		}

		printf("Right has\n");
		for(int i=0;i<right.size();i++){
			printf("%lf,%lf\n",right[i].getX(), right[i].getY());
		}

		printf("Candidates has\n");
		for(int i=0;i<candidates.size();i++){
			printf("%lf,%lf\n",candidates[i].getX(), candidates[i].getY());
		}

		std::vector<Edge> lines;
		for(int i=0;i<point_list.size()-1;i+=2){ // if we have an even number of elements, we need to go to the second last one
			if(point_list[i] < point_list[i+1])
				lines.push_back(Edge(point_list[i],point_list[i+1]));
			else
				lines.push_back(Edge(point_list[i+1],point_list[i]));
		}
		if(point_list.size()%2==1){
			candidates.push_back(point_list[point_list.size()-1]);
		}

		printf("Lines has \n");
		for(int i=0;i<lines.size();i++){
			printf("slope: %lf, points:  %lf,%lf;%lf,%lf\n",lines[i].get_slope(),lines[i].getX().getX(),lines[i].getX().getY(),lines[i].getY().getX(),lines[i].getY().getY());
		}


		// replace this with lines and its slope with get_slope
		// std::vector<Edges> slopeMap;

		// for(int i=0;i<lines.size();i++){
		// 	double slope=(lines[i].second.second-lines[i].first.second)/(lines[i].second.first-lines[i].first.first);
		// 	slopeMap.push_back(make_pair(slope,lines[i]));
		// }

		Edge median_line = Utilities<Edge>::median(lines,lines.size()/2);
		printf("The median slope is %lf:%lf,%lf;%lf,%lf\n",median_line.get_slope(),median_line.getX().getX(),median_line.getX().getY(),median_line.getY().getX(),median_line.getY().getY());

		std::vector<Edge> lower_slope_lines,higher_slope_lines,equal_slope_lines;
		printf("The slopes for the lines are \n");
		for(int i=0;i<lines.size();i++){
			if(lines[i] < median_line){
				lower_slope_lines.push_back(lines[i]);
				printf("lower: %lf:%lf,%lf;%lf,%lf\n",lines[i].get_slope(),lines[i].getX().getX(),lines[i].getX().getY(),lines[i].getY().getX(),lines[i].getY().getY());
			}
			else if(lines[i] > median_line){
				higher_slope_lines.push_back(lines[i]);
				printf("higher: %lf:%lf,%lf;%lf,%lf\n",lines[i].get_slope(),lines[i].getX().getX(),lines[i].getX().getY(),lines[i].getY().getX(),lines[i].getY().getY());
			}
			else{
				equal_slope_lines.push_back(lines[i]);
				printf("equal: %lf:%lf,%lf;%lf,%lf\n",lines[i].get_slope(),lines[i].getX().getX(),lines[i].getX().getY(),lines[i].getY().getX(),lines[i].getY().getY());
			}
		}

		double slope = median_line.get_slope();
		double x_min,x_max;
		double intercept = point_list[0].getY() - slope*point_list[0].getX();
        x_min = point_list[0].getX();
        x_max = point_list[0].getX();
		for(int i=1;i<point_list.size();i++){
			double temp_intercept = point_list[i].getY() - slope*point_list[i].getX();
			if(temp_intercept>intercept){
				intercept=temp_intercept;
                x_min = x_max = point_list[i].getX();
			}
            else if(temp_intercept==intercept){
                if(x_min>point_list[i].getX()){
                    x_min = point_list[i].getX();
                }
                else if(x_max<point_list[i].getX()){
                    x_max = point_list[i].getX();
                }
            }
		}

		printf("Smaller slopes\n");
		for(int i=0;i<lower_slope_lines.size();i++){
			printf("%lf: %lf,%lf;%lf,%lf\n",lower_slope_lines[i].get_slope(),lower_slope_lines[i].getX().getX(),lower_slope_lines[i].getX().getY(),lower_slope_lines[i].getY().getX(),lower_slope_lines[i].getY().getY());
		}

		printf("Equal slopes\n");
		for(int i=0;i<equal_slope_lines.size();i++){
			printf("%lf: %lf,%lf;%lf,%lf\n",equal_slope_lines[i].get_slope(),equal_slope_lines[i].getX().getX(),equal_slope_lines[i].getX().getY(),equal_slope_lines[i].getY().getX(),equal_slope_lines[i].getY().getY());
		}

		printf("Higher slopes\n");
		for(int i=0;i<higher_slope_lines.size();i++){
			printf("%lf: %lf,%lf;%lf,%lf\n",higher_slope_lines[i].get_slope(),higher_slope_lines[i].getX().getX(),higher_slope_lines[i].getX().getY(),higher_slope_lines[i].getY().getX(),higher_slope_lines[i].getY().getY());
		}

        printf("The support line extrema are %lf and %lf\n",x_min,x_max);
		//other shit


		std::vector<Node> answer;
		if(candidates.size() <= 3){
			if(candidates.size() == 2){
				if(candidates[0] < candidates[1]){
					answer.push_back(candidates[0]);
					answer.push_back(candidates[1]);
				}
				else{// Both can't be equal as we eliminate such cases
					answer.push_back(candidates[1]);
					answer.push_back(candidates[0]);
				}
			}
			else{// size is one or three
				answer.push_back(candidates[0]);
			}
			return Edge(answer[0],answer[1]);
		}

}

Edge Graph::lower_bridge(std::vector<Node> point_list){

}

std::vector<Node> Graph::upper_hull(std::vector<Node> point_list){

	std::vector<Node> answer;
	printf("The input to upper_hull is\n");
	for(int i=0;i<point_list.size();i++){
		printf("%lf,%lf\n",point_list[i].getX(),point_list[i].getY());
	}
	if(point_list.size()==1){
		answer.push_back(point_list[0]);
		return answer;
	}
	else if(point_list.size()==2){
		if(point_list[0] < point_list[1]){
			answer.push_back(point_list[0]);
			answer.push_back(point_list[1]);
			return answer;
		}
		else if(point_list[0] > point_list[1]){
			answer.push_back(point_list[1]);
			answer.push_back(point_list[0]);
			return answer;
		}
		else{// If both have the same x value
			if(point_list[0].getY() > point_list[1].getY()){
				answer.push_back(point_list[0]);
				return answer;
			}
			else if(point_list[0].getY() <= point_list[1].getY()){
				answer.push_back(point_list[1]);
				return answer;
			}
		}
	}
	else{
		upper_bridge(point_list);
	}
	return point_list;
}

std::vector<Node> Graph::lower_hull(std::vector<Node> point_list){
	return point_list;
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


    std::vector<Node> upper_hull_points,lower_hull_points;

    // tuple<pair<double,double>,pair<double,double>,int,int > corner_point_upper = get_corner_points(point_list,true);
	Node left_top = get_left_most_point(false);
	Node right_top = get_right_most_point(false);
	Node left_bottom = get_left_most_point(true);
	Node right_bottom = get_right_most_point(true);

    upper_hull_points.push_back(left_top);

	point_list.erase(std::remove(point_list.begin(),point_list.end(),left_top),point_list.end());
	point_list.erase(std::remove(point_list.begin(),point_list.end(),right_top),point_list.end());

	double slope = Edge(left_top,right_top).get_slope();
	// double slope = (get<0>(corner_point_upper).second - get<1>(corner_point_upper).second ) / ( get<0>(corner_point_upper).first - get<1>(corner_point_upper).first  );
    double intercept = (left_top.getY() - slope * left_top.getX());
    for(int i=0;i<point_list.size();i++){
        if(point_list[i].getY() - slope* point_list[i].getX() > intercept){
            upper_hull_points.push_back(point_list[i]);
            point_list.erase(point_list.begin()+i); // This will get rid of all the upper hull points
            i--;
        }
    }



    upper_hull_points.push_back(right_top);

    // printf("The corner points are %lf,%lf and %lf,%lf\n",get<0>(corner_point_upper).first,get<0>(corner_point_upper).second,get<1>(corner_point_upper).first,get<1>(corner_point_upper).second);
    // printf("The remaining are:\n");
    // for(int i=0;i<point_list.size();i++){
    // 	printf("%lf,%lf\n",point_list[i].first,point_list[i].second);
    // }

    // tuple<pair<double,double>,pair<double,double>,int,int > corner_point_lower = get_corner_points(point_list,false);

    // point_list.erase(point_list.begin()+get<2>(corner_point_lower));
    // point_list.erase(point_list.begin()+get<3>(corner_point_lower));
	point_list.erase(std::remove(point_list.begin(),point_list.end(),left_bottom),point_list.end());
	point_list.erase(std::remove(point_list.begin(),point_list.end(),right_bottom),point_list.end());

    lower_hull_points.push_back(left_bottom);
    // slope = (get<0>(corner_point_lower).second - get<1>(corner_point_lower).second ) / ( get<0>(corner_point_lower).first - get<1>(corner_point_lower).first  );
	slope = Edge(left_bottom,right_bottom).get_slope();
    intercept = (left_bottom.getY() - slope * left_bottom.getX());
    for(int i=0;i<point_list.size();i++){
        if(point_list[i].getY() - slope* point_list[i].getX() < intercept){
            lower_hull_points.push_back(point_list[i]);
            point_list.erase(point_list.begin()+i);
            i--;
        }
    }

    lower_hull_points.push_back(right_bottom);

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
