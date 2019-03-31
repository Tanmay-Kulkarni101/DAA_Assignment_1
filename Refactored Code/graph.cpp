
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

Node Graph::get_left_most_point(bool flag_lower,vector<Node> point_list){// if the flag is false we find the upper most point
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

Node Graph::get_right_most_point(bool flag_lower,vector<Node> point_list){// if the flag is false we find the upper most point
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
    fstream file_handle;
    file_handle.open("output.txt",std::ios::out);
	for(auto it=convex_hull.begin();it<convex_hull.end();it++){
		std::cout<<it->getPoint().getX()<<","<<it->getPoint().getY()<<std::endl;
		file_handle<<it->getPoint().getX()<<","<<it->getPoint().getY()<<std::endl;
	}
		file_handle<<convex_hull[0].getX()<<","<<convex_hull[0].getY()<<std::endl;
		file_handle.close();
}

bool Graph::compare_pairs(pair<Node,double> p1, pair<Node,double> p2){
	return (p1.second < p2.second);
}

void Graph::graham_scan(){
	// Code for graham scan, takes point_list as input and the output is in convex_hull
	Node corner_point = get_left_most_point(false,this->point_list); // Taking the highest point on the left side
	std::vector<Node> temp_point_list = point_list; // This does a deep copy and replaces the objects in the container

    std::vector<std::pair<Node,double>> polar_angles;
    polar_angles.push_back(std::make_pair(corner_point,-10));

    //finding polar angles wrt to all the points
    for(int i=0;i<point_list.size();i++){
        if(point_list[i] != corner_point)

            polar_angles.push_back(std::make_pair(point_list[i],polar_angler(corner_point,point_list[i])));
    }

    // STL sorting wrt to polar angles
    // for(int i=0;i<point_list.size()-1;i++){
    //     for(int j=i+1;j<point_list.size();j++){
    //         if(polar_angles[i].second > polar_angles[j].second){
    //             std::pair<Node,double> temp = polar_angles[i];
    //             polar_angles[i] = polar_angles[j];
    //             polar_angles[j] = temp;
    //         }
    //     }
    // }

    std::sort(polar_angles.begin(),polar_angles.end(),compare_pairs);

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

    for(int i=0;i<st.size();i++){
        std::cout<<st[i].first.getX()<<" "<<st[i].first.getY()<<" -> "<<st[i].second<<std::endl;
        convex_hull.push_back(st[i].first);
    }

}

void Graph::jarvis_march(){

    Node corner_point = get_left_most_point(false,this->point_list);
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
        //printf("the starting candidate is %lf %lf\n",candidate.getX(),candidate.getY());
        // if(candidate == corner_point)
        //     candidate = point_list[1];
        last_point = convex_hull[convex_hull.size()-1];
        int location = 0;
        for(int i=1;i<point_list.size();i++){
            if(get_orientation(last_point,candidate,point_list[i]) == false){
                //printf("get_orientation = %lf,%lf %lf,%lf %lf,%lf -> %d\n",last_point.getX(),last_point.getY(),candidate.getX(),candidate.getY(),point_list[i].getX(),point_list[i].getY(),get_orientation(last_point,candidate,point_list[i]));
                candidate = point_list[i];
                location = i;
            }
            else{
                //printf("get_orientation = %lf,%lf %lf,%lf %lf,%lf -> %d\n",last_point.getX(),last_point.getY(),candidate.getX(),candidate.getY(),point_list[i].getX(),point_list[i].getY(),get_orientation(last_point,candidate,point_list[i]));
            }
        }
        if(last_point != corner_point && get_orientation(last_point,candidate,corner_point) == false){
            //printf("entered termination with candidate: %lf,%lf\n", candidate.getX(),candidate.getY());
            break;

        }
        convex_hull.push_back(*(point_list.begin()+location));
        //printf("%lf %lf has been erased\n",(point_list.begin()+location)->getX(),(point_list.begin()+location)->getY());
        candidate = *(point_list.begin()+location);
        //printf("the ending candidate is %lf %lf\n",candidate.getX(),candidate.getY());
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
        // std::cin >> c;
        std::cout<<"***********************************\n";
    }
    std::cout<<"Das solution ist\n";
    for(int i=0;i<convex_hull.size();i++){
        std::cout<<convex_hull[i].getX()<<" "<<convex_hull[i].getY()<<std::endl;
    }
}

Edge Graph::upper_bridge(std::vector<Node> point_list){
	//printf("size of input is: %lu\n",point_list.size());
	if(point_list.size() == 2){
		Edge answer = Edge(point_list[0],point_list[1]);
		return answer;
	}
	Node the_median= Utilities<Node>::median(point_list,point_list.size()/2);
	//printf("the median is %lf,%lf\n",the_median.getX(),the_median.getY());
	std::vector<Node> left,right,candidates;

	for(int i=0;i<point_list.size();i++){
		if(point_list[i] < the_median){
			left.push_back(point_list[i]);
		}
		else if(point_list[i] >= the_median){
			right.push_back(point_list[i]);
		}
	}

		//printf("Left set has in M.O.M\n");
		for(int i=0;i<left.size();i++){
			//printf("%lf,%lf\n",left[i].getX(), left[i].getY());
		}

		//printf("Right set has in M.O.M\n");
		for(int i=0;i<right.size();i++){
			//printf("%lf,%lf\n",right[i].getX(), right[i].getY());
		}

		//printf("Candidates has\n");
		for(int i=0;i<candidates.size();i++){
			//printf("%lf,%lf\n",candidates[i].getX(), candidates[i].getY());
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

		//puts("candidates after forming a line");
		//printf("size of point list: %lu\n",point_list.size());
		for(auto it=candidates.begin(); it < candidates.end(); it++)
			it->print_node();

		//printf("Lines has \n");
		for(int i=0;i<lines.size();i++){
			//printf("slope: %lf, points:  %lf,%lf;%lf,%lf\n",lines[i].get_slope(),lines[i].getX().getX(),lines[i].getX().getY(),lines[i].getY().getX(),lines[i].getY().getY());
		}


		// replace this with lines and its slope with get_slope
		// std::vector<Edges> slopeMap;

		// for(int i=0;i<lines.size();i++){
		// 	double slope=(lines[i].second.second-lines[i].first.second)/(lines[i].second.first-lines[i].first.first);
		// 	slopeMap.push_back(make_pair(slope,lines[i]));
		// }

		Edge median_line = Utilities<Edge>::median(lines,lines.size()/2);
		//printf("The median slope is %lf:%lf,%lf;%lf,%lf\n",median_line.get_slope(),median_line.getX().getX(),median_line.getX().getY(),median_line.getY().getX(),median_line.getY().getY());

		std::vector<Edge> lower_slope_lines,higher_slope_lines,equal_slope_lines;
		//printf("The slopes for the lines are \n");
		for(int i=0;i<lines.size();i++){
			if(lines[i] < median_line){
				lower_slope_lines.push_back(lines[i]);
				//printf("lower: %lf:%lf,%lf;%lf,%lf\n",lines[i].get_slope(),lines[i].getX().getX(),lines[i].getX().getY(),lines[i].getY().getX(),lines[i].getY().getY());
			}
			else if(lines[i] > median_line){
				higher_slope_lines.push_back(lines[i]);
				//printf("higher: %lf:%lf,%lf;%lf,%lf\n",lines[i].get_slope(),lines[i].getX().getX(),lines[i].getX().getY(),lines[i].getY().getX(),lines[i].getY().getY());
			}
			else{
				equal_slope_lines.push_back(lines[i]);
				//printf("equal: %lf:%lf,%lf;%lf,%lf\n",lines[i].get_slope(),lines[i].getX().getX(),lines[i].getX().getY(),lines[i].getY().getX(),lines[i].getY().getY());
			}
		}

		double slope = median_line.get_slope();
		Node node_min,node_max;
		double intercept = point_list[0].getY() - slope*point_list[0].getX();
        node_min = point_list[0];
        node_max = point_list[0];
		for(int i=1;i<point_list.size();i++){
			double temp_intercept = point_list[i].getY() - slope*point_list[i].getX();
			if(temp_intercept>intercept){
				intercept=temp_intercept;
                node_min = node_max = point_list[i];
			}
            else if(abs(temp_intercept - intercept) < 0.000001){ // Gareeb equality test
                if(node_min>point_list[i]){
                    node_min = point_list[i];
                }
                else if(node_max<point_list[i]){
                    node_max = point_list[i];
                }
            }
		}

		//printf("Smaller slopes\n");
		for(int i=0;i<lower_slope_lines.size();i++){
			//printf("%lf: %lf,%lf;%lf,%lf\n",lower_slope_lines[i].get_slope(),lower_slope_lines[i].getX().getX(),lower_slope_lines[i].getX().getY(),lower_slope_lines[i].getY().getX(),lower_slope_lines[i].getY().getY());
		}

		//printf("Equal slopes\n");
		for(int i=0;i<equal_slope_lines.size();i++){
			//printf("%lf: %lf,%lf;%lf,%lf\n",equal_slope_lines[i].get_slope(),equal_slope_lines[i].getX().getX(),equal_slope_lines[i].getX().getY(),equal_slope_lines[i].getY().getX(),equal_slope_lines[i].getY().getY());
		}

		//printf("Higher slopes\n");
		for(int i=0;i<higher_slope_lines.size();i++){
			//printf("%lf: %lf,%lf;%lf,%lf\n",higher_slope_lines[i].get_slope(),higher_slope_lines[i].getX().getX(),higher_slope_lines[i].getX().getY(),higher_slope_lines[i].getY().getX(),higher_slope_lines[i].getY().getY());
		}

        //printf("The support line extrema are %lf and %lf\n",node_min.getX(),node_max.getX());


		if(node_min < the_median && node_max >= the_median){
			return Edge(node_min,node_max);
		}
		else if(node_min < the_median && node_max < the_median){
			//puts("bridge on the left");
			for(auto it = higher_slope_lines.begin(); it < higher_slope_lines.end(); it++){
				candidates.push_back(it->getY());
			}
			for(auto it = equal_slope_lines.begin(); it < equal_slope_lines.end(); it++){
				candidates.push_back(it->getY());
			}
			for(auto it = lower_slope_lines.begin(); it < lower_slope_lines.end(); it++){
				candidates.push_back(it->getX());
				candidates.push_back(it->getY());
			}
		}
		else if(node_min >= the_median && node_max >= the_median){
			//puts("bridge on the right");
			for(auto it = lower_slope_lines.begin(); it < lower_slope_lines.end(); it++){
				candidates.push_back(it->getX());
			}
			for(auto it = equal_slope_lines.begin(); it < equal_slope_lines.end(); it++){
				candidates.push_back(it->getX());
			}
			for(auto it = higher_slope_lines.begin(); it < higher_slope_lines.end(); it++){
				candidates.push_back(it->getX());
				candidates.push_back(it->getY());
			}
		}

		//puts("printing candidates");
		for(auto it = candidates.begin(); it < candidates.end(); it++){
			it->print_node();
		}
		//puts("About to recurse");
		return upper_bridge(candidates);
}

Edge Graph::lower_bridge(std::vector<Node> point_list){
	printf("size of input is: %lu\n",point_list.size());
	if(point_list.size() == 2){
		puts("entered base case for lower bridge");
		Edge answer = Edge(point_list[0],point_list[1]);
		return answer;
	}
	Node the_median= Utilities<Node>::median(point_list,point_list.size()/2);
	printf("the median is %lf,%lf\n",the_median.getX(),the_median.getY());
	std::vector<Node> left,right,candidates;

	for(int i=0;i<point_list.size();i++){
		if(point_list[i] < the_median){
			left.push_back(point_list[i]);
		}
		else if(point_list[i] >= the_median){
			right.push_back(point_list[i]);
		}
	}

		printf("Left set has in M.O.M\n");
		for(int i=0;i<left.size();i++){
			printf("%lf,%lf\n",left[i].getX(), left[i].getY());
		}

		printf("Right set has in M.O.M\n");
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

		puts("candidates after forming a line");
		printf("size of point list: %lu\n",point_list.size());
		for(auto it=candidates.begin(); it < candidates.end(); it++)
			it->print_node();

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
		//printf("The slopes for the lines are \n");
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
		printf("\n\nTheere ma ki chuth\n\n");
		double slope = median_line.get_slope();
		printf("\n\nThe slope before the intercept calculation %lf\n",slope);
		Node node_min,node_max;
		double intercept = point_list[0].getY() - slope*point_list[0].getX();
		printf("The initial intercept is %lf\n",intercept);
        node_min = point_list[0];
        node_max = point_list[0];
		for(int i=1;i<point_list.size();i++){
			double temp_intercept = point_list[i].getY() - slope*point_list[i].getX();
			printf("the temp intercept is %lf: %lf, %d ",temp_intercept,intercept,abs(temp_intercept - intercept) < 0.000001);
			point_list[i].print_node();
			if(temp_intercept<intercept){
				intercept=temp_intercept;
                node_min = node_max = point_list[i];
			}
            else if(abs(temp_intercept - intercept) < 0.000001){
                if(node_min>point_list[i]){
					printf("the new node min is:");
					point_list[i].print_node();
                    node_min = point_list[i];
                }
                else if(node_max<point_list[i]){
					printf("the new node max is:");
					point_list[i].print_node();
                    node_max = point_list[i];
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

        printf("The support line extrema are %lf and %lf\n",node_min.getX(),node_max.getX());


		if(node_min < the_median && node_max >= the_median){
			return Edge(node_min,node_max);
		}
		else if(node_min >= the_median && node_max >= the_median){
			puts("bridge on the right");
			for(auto it = higher_slope_lines.begin(); it < higher_slope_lines.end(); it++){
				candidates.push_back(it->getX());
			}
			for(auto it = equal_slope_lines.begin(); it < equal_slope_lines.end(); it++){
				candidates.push_back(it->getX());
			}
			for(auto it = lower_slope_lines.begin(); it < lower_slope_lines.end(); it++){
				candidates.push_back(it->getX());
				candidates.push_back(it->getY());
			}
		}
		else if(node_min < the_median && node_max < the_median){
			puts("bridge on the left");
			for(auto it = lower_slope_lines.begin(); it < lower_slope_lines.end(); it++){
				candidates.push_back(it->getY());
			}
			for(auto it = equal_slope_lines.begin(); it < equal_slope_lines.end(); it++){
				candidates.push_back(it->getY());
			}
			for(auto it = higher_slope_lines.begin(); it < higher_slope_lines.end(); it++){
				candidates.push_back(it->getX());
				candidates.push_back(it->getY());
			}
		}

		puts("printing candidates");
		for(auto it = candidates.begin(); it < candidates.end(); it++){
			it->print_node();
		}
		puts("About to recurse");
		return lower_bridge(candidates);
}

std::vector<Node> Graph::upper_hull(std::vector<Node> point_list,Node p_min, Node p_max){

	std::vector<Node> answer;

	if (p_min.getX() == p_max.getX() && p_min.getY() == p_min.getY()){
		answer.push_back(p_min); 
	}
	else{
		std::vector<Node> left_points,right_points;
		// left_points.push_back(p_min);
		// right_points.push_back(p_max);

		Edge the_bridge = upper_bridge(point_list);
		if(the_bridge.get_length() == 0)
			the_bridge = Edge(the_bridge.getX(),the_bridge.getX());
		//printf("************************************************************************************************************\n");
		//printf("The muthafukin bridge is \n");
		the_bridge.print_edge();
		//printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
		Edge trapezoid_bottom = Edge(p_min,p_max);
		Edge trapezoid_left = Edge(p_min,the_bridge.getX());
		Edge trapezoid_right = Edge(the_bridge.getY(),p_max);
		//puts("orientations");
		for(auto it = point_list.begin(); it < point_list.end(); it++){
			//printf("The point is: ");
			it->print_node();
			//printf("bottom\t %d\n",get_orientation(trapezoid_bottom.getX(),trapezoid_bottom.getY(),*it));
			//printf("left\t %d\n",get_orientation(trapezoid_left.getX(),trapezoid_left.getY(),*it));
			//printf("bridge\t %d\n",get_orientation(the_bridge.getX(),the_bridge.getY(),*it));
			//printf("right\t %d\n",get_orientation(trapezoid_right.getX(),trapezoid_right.getY(),*it));
			// we ignore internal points
			if(	get_orientation(trapezoid_bottom.getX(),trapezoid_bottom.getY(),*it) && 
					!get_orientation(trapezoid_left.getX(),trapezoid_left.getY(),*it) && 
					!get_orientation(trapezoid_right.getX(),trapezoid_right.getY(),*it) && 
					!get_orientation(the_bridge.getX(),the_bridge.getY(),*it)){
					//puts("ignore within");
					continue;		
				}
			else if(get_orientation(trapezoid_left.getX(),trapezoid_left.getY(),*it)){
				left_points.push_back(*it);
				//puts("entered left");
			}
			else if(get_orientation(trapezoid_right.getX(),trapezoid_right.getY(),*it)){
				//puts("entered left");
				right_points.push_back(*it);
			}
			else{
				// it is a vertex, ignore
				//puts("ignoring vertex");
			}
		}
		left_points.insert(left_points.begin(),p_min);
		left_points.push_back(the_bridge.getX());
		vector<Node> left_answer = upper_hull(left_points,p_min,the_bridge.getX());
		//printf("**********************************************************************************************************\n");
		//printf("The left part of the solution contains\n");
		for(auto it = left_answer.begin() ; it< left_answer.end();it++){
			it->print_node();
		}
		//printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
		right_points.push_back(p_max);
		right_points.insert(right_points.begin(),the_bridge.getY());
		vector<Node> right_answer = upper_hull(right_points,the_bridge.getY(),p_max);
		
		//printf("**********************************************************************************************************\n");
		//printf("The right part of the solution contains\n");
		for(auto it = right_answer.begin() ; it< right_answer.end();it++){
			it->print_node();
		}
		//printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
		answer.insert(answer.end(),left_answer.begin(),left_answer.end());
		answer.insert(answer.end(),right_answer.begin(),right_answer.end());
	}
	return answer;
}

std::vector<Node> Graph::lower_hull(std::vector<Node> point_list,Node p_min, Node p_max){
	std::vector<Node> answer;

	if (p_min.getX() == p_max.getX() && p_min.getY() == p_min.getY()){
		puts("entered base case for lower hull");
		answer.push_back(p_min); 
	}
	else{
		std::vector<Node> left_points,right_points;
		// left_points.push_back(p_min);
		// right_points.push_back(p_max);

		Edge the_bridge = lower_bridge(point_list);
		if(the_bridge.get_length() == 0)
			the_bridge = Edge(the_bridge.getX(),the_bridge.getX());
		printf("************************************************************************************************************\n");
		printf("The muthafukin bridge is \n");
		the_bridge.print_edge();
		printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
		Edge trapezoid_top = Edge(p_min,p_max);
		Edge trapezoid_left = Edge(p_min,the_bridge.getX());
		Edge trapezoid_right = Edge(the_bridge.getY(),p_max);
		puts("orientations");
		if(!the_bridge.getX().is_equal(p_min) && !the_bridge.getY().is_equal(p_max)){
			puts("this is a trapezoid");
			for(auto it = point_list.begin(); it < point_list.end(); it++){
				printf("The point is: ");
				it->print_node();
				printf("top\t %d\n",get_orientation(trapezoid_top.getX(),trapezoid_top.getY(),*it));
				printf("left\t %d\n",get_orientation(trapezoid_left.getX(),trapezoid_left.getY(),*it));
				printf("bridge\t %d\n",get_orientation(the_bridge.getX(),the_bridge.getY(),*it));
				printf("right\t %d\n",get_orientation(trapezoid_right.getX(),trapezoid_right.getY(),*it));
				// we ignore internal points
				if(		!get_orientation(trapezoid_top.getX(),trapezoid_top.getY(),*it) && 
						get_orientation(trapezoid_left.getX(),trapezoid_left.getY(),*it) && 
						get_orientation(trapezoid_right.getX(),trapezoid_right.getY(),*it) && 
						get_orientation(the_bridge.getX(),the_bridge.getY(),*it)){
						puts("ignore within");
						continue;		
					}
				else if( !get_orientation(trapezoid_left.getX(),trapezoid_left.getY(),*it) && !(it->is_equal(trapezoid_left.getX()) || it->is_equal(trapezoid_left.getY() ) )  ){
					left_points.push_back(*it);
					puts("entered left");
				}
				else if(!get_orientation(trapezoid_right.getX(),trapezoid_right.getY(),*it) && !(it->is_equal(trapezoid_right.getX()) || it->is_equal(trapezoid_right.getY()))){
					puts("entered right");
					right_points.push_back(*it);
				}
				else{
					// it is a vertex, ignore
					puts("ignoring vertex");
				}
			}
		}
		else{
			puts("this is a triangle");
			Edge triangle_top = Edge(p_min,p_max);
			Edge triangle_left;
			Edge triangle_right;
			if(p_min.is_equal(the_bridge.getX())){
				triangle_left = Edge(p_min,the_bridge.getY());
				triangle_right = Edge(p_max,the_bridge.getY());
			}
			else{
				triangle_left = Edge(p_min,the_bridge.getX());
				triangle_right = Edge(p_max,the_bridge.getX());
			}
			for(auto it = point_list.begin(); it < point_list.end(); it++){
				printf("The point is: ");
				it->print_node();
				printf("top\t %d\n",get_orientation(triangle_top.getX(),triangle_top.getY(),*it));
				printf("left\t %d\n",get_orientation(triangle_left.getX(),triangle_left.getY(),*it));
				printf("right\t %d\n",get_orientation(triangle_right.getX(),triangle_right.getY(),*it));
				// we ignore internal points 
				if(		!get_orientation(triangle_top.getX(),triangle_top.getY(),*it) && 
						get_orientation(triangle_left.getX(),triangle_left.getY(),*it) && 
						get_orientation(triangle_right.getX(),triangle_right.getY(),*it)){
						puts("ignore within");
						continue;		
					}
				else if( !get_orientation(triangle_left.getX(),triangle_left.getY(),*it) && !(it->is_equal(triangle_left.getX()) || it->is_equal(triangle_left.getY() ) )  ){
					left_points.push_back(*it);
					puts("entered left");
				}
				else if(!get_orientation(triangle_right.getX(),triangle_right.getY(),*it) && !(it->is_equal(triangle_right.getX()) || it->is_equal(triangle_right.getY()))){
					puts("entered right");
					right_points.push_back(*it);
				}
				else{
					// it is a vertex, ignore
					puts("ignoring vertex");
				}
			}
		}
		puts("left points are after orientation");
		for(auto it = left_points.begin(); it < left_points.end(); it++)
			it->print_node();
		puts("right points are after orientation");
		for(auto it = right_points.begin(); it < right_points.end(); it++)
			it->print_node();


		left_points.insert(left_points.begin(),p_min);
		left_points.push_back(the_bridge.getX());
		vector<Node> left_answer = lower_hull(left_points,p_min,the_bridge.getX());
		printf("**********************************************************************************************************\n");
		printf("The left part of the solution contains\n");
		for(auto it = left_answer.begin() ; it< left_answer.end();it++){
			it->print_node();
		}
		printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
		right_points.push_back(p_max);
		right_points.insert(right_points.begin(),the_bridge.getY());
		vector<Node> right_answer = lower_hull(right_points,the_bridge.getY(),p_max);
		
		printf("**********************************************************************************************************\n");
		printf("The right part of the solution contains\n");
		for(auto it = right_answer.begin() ; it< right_answer.end();it++){
			it->print_node();
		}
		printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
		answer.insert(answer.end(),left_answer.begin(),left_answer.end());
		answer.insert(answer.end(),right_answer.begin(),right_answer.end());
	}
	return answer;
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
	Node left_top = get_left_most_point(false,this->point_list);
	Node right_top = get_right_most_point(false,this->point_list);
	//puts("top points from left to right");
	left_top.print_node();
	right_top.print_node();


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
    point_list.push_back(right_top);
    point_list.push_back(left_top);
	Node left_bottom = get_left_most_point(true,this->point_list);
	Node right_bottom = get_right_most_point(true,this->point_list);

	puts("bottom points from left to right");
	left_bottom.print_node();
	right_bottom.print_node();
	//printf("The slope is %lf\n",Edge(left_bottom,right_bottom).get_slope());

    // //printf("The corner points are %lf,%lf and %lf,%lf\n",get<0>(corner_point_upper).first,get<0>(corner_point_upper).second,get<1>(corner_point_upper).first,get<1>(corner_point_upper).second);
    // //printf("The remaining are:\n");
    // for(int i=0;i<point_list.size();i++){
    // 	//printf("%lf,%lf\n",point_list[i].first,point_list[i].second);
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

	printf("The input to lower hull is \n");
	for(auto it = lower_hull_points.begin();it<lower_hull_points.end();it++){
		it->print_node();
	}

    // //printf("The corner points are %lf,%lf and %lf,%lf\n",get<0>(corner_point_lower).first,get<0>(corner_point_lower).second,get<1>(corner_point_lower).first,get<1>(corner_point_lower).second);
    // //printf("The remaining are:\n");
    // for(int i=0;i<point_list.size();i++){
    // 	//printf("%lf,%lf\n",point_list[i].first,point_list[i].second);
    // }

    // //printf("The upper hull points are:\n");
    // for(int i=0;i<upper_hull_points.size();i++){
    // 	//printf("%lf,%lf\n",upper_hull_points[i].first,upper_hull_points[i].second);
    // }

    // //printf("The Lower hull points are:\n");
    // for(int i=0;i<lower_hull_points.size();i++){
    // 	//printf("%lf,%lf\n",lower_hull_points[i].first,lower_hull_points[i].second);
    // }

    vector<Node> upper_solution = upper_hull(upper_hull_points,left_top,right_top);
	//printf("**********************************************************************************************************\n");
	//puts("upper hull is:");
	for(auto it = upper_solution.begin(); it < upper_solution.end(); it++)
		it->print_node();
	
	
	vector<Node> lower_solution = lower_hull(lower_hull_points,left_bottom,right_bottom);
	printf("**********************************************************************************************************\n");
	puts("lower hull is:");
	for(auto it = lower_solution.begin(); it < lower_solution.end(); it++)
		it->print_node();

	if(upper_solution[0].is_equal(lower_solution[0]) ){
		lower_solution.erase(lower_solution.begin());
	}
	if(upper_solution[upper_solution.size()-1].is_equal(lower_solution[lower_solution.size()-1]) ){
		lower_solution.pop_back();
	}

	vector<Node> solution;
	solution.insert(solution.end(),upper_solution.begin(),upper_solution.end());
	solution.insert(solution.end(),lower_solution.rbegin(),lower_solution.rend());

	printf("\n\n\n\n\nThe final solution is \n\n");
	for(auto it = solution.begin();it<solution.end();it++){
		it->print_node();
	}

	convex_hull = solution;
}
