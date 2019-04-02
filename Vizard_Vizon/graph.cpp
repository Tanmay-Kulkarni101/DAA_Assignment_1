
#include "graph.h"
const std::string Graph::GRAHM_SCAN_OUTPUT = "./visualizations/grahm_scan.txt";
const std::string Graph::JARVIS_MARCH_OUTPUT = "./visualizations/jarvis_march.txt";
const std::string Graph::KPS_OUTPUT = "./visualizations/kps.txt";

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
	std::cout << "The points present on the convex hull are" << '\n';
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
	return (p1.second < p2.second); // Compare with respect to the polar angle
}

void Graph::graham_scan(){
	// Code for graham scan, takes point_list as input and the output is in convex_hull

	if(point_list.size()<=2){ // Handle corner case
		std::cout<<"Convex hull is not possible\n";
		return ;
	}
	fstream file_handle;
	file_handle.open(GRAHM_SCAN_OUTPUT,std::ios::out);
	
	Node corner_point = get_left_most_point(false,this->point_list); // Taking the highest point on the left side
	std::vector<Node> temp_point_list = point_list; // This does a deep copy and replaces the objects in the container

    std::vector<std::pair<Node,double>> polar_angles;
    polar_angles.push_back(std::make_pair(corner_point,-10));
    //finding polar angles wrt to all the points
    for(int i=0;i<point_list.size();i++){
        if(point_list[i] != corner_point)

            polar_angles.push_back(std::make_pair(point_list[i],polar_angler(corner_point,point_list[i])));// Add if the angle is counter-clockwise
    }

    std::sort(polar_angles.begin(),polar_angles.end(),compare_pairs); // sort by polar angle

    //apply the algorithm
    std::vector<std::pair<Node,double>> st; // Build a stack to compare the points
    st.push_back(polar_angles[0]); // the first two points are taken by default
    st.push_back(polar_angles[1]);
	file_handle << polar_angles[0].first.to_string();
	file_handle << polar_angles[1].first.to_string();

    for(int i=2;i<polar_angles.size();i++){
		file_handle << polar_angles[i].first.to_string();
        while(st.size() > 1 && get_orientation(st[st.size()-2].first,st[st.size()-1].first,polar_angles[i].first) == false){
			file_handle << st[st.size()-1].first.to_string();
			st.pop_back(); // If they are in a clockwise orientation pop the point or for a collinear point
        }
        st.push_back(polar_angles[i]); // otherwise push the point into the stack
    }
	file_handle << corner_point.to_string();
	if(st.size()<3){
		std::cout<<"Convex hull is not possible as the points are collinear\n";
		return;
	}
	// for 3 or more points in the hull
    for(int i=0;i<st.size();i++){ // The points left in the stack will be the solution
        convex_hull.push_back(st[i].first);
    }
	file_handle.close();
}

void Graph::jarvis_march(){
	// Takes a list of points as input and gives the convex hull as the output
	// Code to implement jarvis march, this finds the most extreme poins in terms of polar angle and adds them to the hull
	if(point_list.size()<=2){ // Too few points for a convex hull
		std::cout<<"Convex Hull is not possible\n";
		return;
	}
	fstream file_handle;
	file_handle.open(JARVIS_MARCH_OUTPUT,std::ios::out);
    Node corner_point = get_left_most_point(false,this->point_list);
	file_handle << corner_point.to_string();

    //remove the corner point
    std::vector<Node>::iterator iterTemp = std::remove(point_list.begin(), point_list.end(), corner_point);
    point_list.erase(iterTemp,point_list.end());


    convex_hull.push_back(corner_point);
    Node candidate = point_list[0], last_point = convex_hull[convex_hull.size()-1];
    //apply the algorithm
    while(true/*Reach the corner point again*/){
		if(point_list.size()==0){
			break;
		}
        candidate = point_list[0]; // We always assume the first point to be the corner point
        file_handle<<candidate.to_string();
        last_point = convex_hull[convex_hull.size()-1];
        int location = 0;
        for(int i=1;i<point_list.size();i++){
			file_handle<<point_list[i].to_string();
            if(get_orientation(last_point,candidate,point_list[i]) == false){// If we find a point that is collinear or in a clockwise orientation
                file_handle<<candidate.to_string();
				candidate = point_list[i]; // update the candidate
                location = i;
			}
            else{
				file_handle << point_list[i].to_string();
				// Otherwise it is in counter-clockwise order, so the candidate is correct
            }
        }
        if(last_point != corner_point && get_orientation(last_point,candidate,corner_point) == false){ // This is the condition for termination:
			file_handle<<candidate.to_string();
            break;//if we find a point that is clockwise with respect to the original start, we terminate

        }
        convex_hull.push_back(*(point_list.begin()+location)); // Add the candidate that survives to the solution list
        candidate = *(point_list.begin()+location);

        point_list.erase(std::remove(point_list.begin(),point_list.end(),candidate),point_list.end()); // remove the candidate from further comparison
        
    }
	file_handle<<corner_point.to_string();
	if(convex_hull.size()<=2){
		std::cout<<"No solution as the points are collinear\n";
		convex_hull.clear();
		return ;
	}
	file_handle.close();
}

Edge Graph::upper_bridge(std::vector<Node> &point_list){
	// Takes a list of points as the input and gives the upper bridge as the output
	if(point_list.size() == 2){ // Base case where only two points remain where both necessarily belong to the hull, as the bridge always belongs to the hull
		Edge answer = Edge(point_list[0],point_list[1]);
		return answer;
	}
	Node the_median= Utilities<Node>::median(point_list,point_list.size()/2); // get the median for the points passed according to the x value
	std::vector<Node> left,right,candidates;

	printf("median: ");
	the_median.print_node();

	for(int i=0;i<point_list.size();i++){ //points to the left of the median
		if(point_list[i] < the_median){
			left.push_back(point_list[i]);
		}
		else if(point_list[i] >= the_median){ // the median points and the points to the right of the median
			right.push_back(point_list[i]);
		}
	}

	puts("left");
	for(auto it = left.begin();it < left.end();it++)
		it->print_node();
	
	puts("right");
	for(auto it = right.begin();it < right.end();it++)
		it->print_node();

	std::vector<Edge> lines; // arbitrarily take points together to form lines
	for(int i=0;i<point_list.size()-1;i+=2){ // if we have an even number of elements, we need to go to the second last one
		if(point_list[i] < point_list[i+1])
			lines.push_back(Edge(point_list[i],point_list[i+1]));
		else
			lines.push_back(Edge(point_list[i+1],point_list[i]));
	}
	if(point_list.size()%2==1){ // if a point is still unmatched
		candidates.push_back(point_list[point_list.size()-1]);
	}

	// puts("lines");
	// for(auto it = lines.begin();it < lines.end();it++)
	// 	it->print_edge();

	Edge median_line = Utilities<Edge>::median(lines,lines.size()/2); // obtain the median slope
	// printf("median line %lf",median_line.get_slope());
	// median_line.print_edge();

	std::vector<Edge> lower_slope_lines,higher_slope_lines,equal_slope_lines;
	//if we find a point that is clockwise with respect to the original start, we terminate
	for(int i=0;i<lines.size();i++){ // add those lines with smaller slope
		if(lines[i] < median_line){
			lower_slope_lines.push_back(lines[i]);
		}
		else if(lines[i] > median_line){
			higher_slope_lines.push_back(lines[i]);
		}
		else{
			equal_slope_lines.push_back(lines[i]);
		}
	}

	puts("lower slope lines");
	for(auto it = lower_slope_lines.begin();it < lower_slope_lines.end();it++){
		printf("slope %lf, ",it->get_slope());
		it->print_edge();
	}
	puts("higher slope lines");
	for(auto it = higher_slope_lines.begin();it < higher_slope_lines.end();it++){
		printf("slope %lf, ",it->get_slope());
		it->print_edge();
	}
	puts("equal slope lines");
	for(auto it = equal_slope_lines.begin();it < equal_slope_lines.end();it++){
		printf("slope %lf, ",it->get_slope());
		it->print_edge();
	}

	double slope = median_line.get_slope();
	Node node_min,node_max;
	double intercept = point_list[0].getY() - slope*point_list[0].getX();
	node_min = point_list[0];
	node_max = point_list[0];
	puts("node min, node max");
	node_min.print_node();
	node_max.print_node();
	for(int i=1;i<point_list.size();i++){
		double temp_intercept = point_list[i].getY() - slope*point_list[i].getX();
		printf("point: ");
		point_list[i].print_node();
		printf("temp_intercept %lf intercept %lf equality %d gareeb equality %d\n",temp_intercept,intercept,temp_intercept == intercept,abs(temp_intercept - intercept) < 0.0000001);
		printf("min %d, max %d\n",node_min>point_list[i],node_max<point_list[i]);
		if(!(abs(temp_intercept - intercept) < 0.0000001) && temp_intercept>intercept){
			intercept=temp_intercept;
			node_min = node_max = point_list[i];
		}
		else if(abs(temp_intercept - intercept) < 0.0000001){ // Gareeb equality test
			if(node_min>point_list[i]){
				node_min = point_list[i];
			}
			else if(node_max<point_list[i]){
				node_max = point_list[i];
			}
		}
	}
	puts("endpoints are");
	node_max.print_node();
	node_min.print_node();

	
	if(node_min < the_median && node_max >= the_median){
		return Edge(node_min,node_max);
	}
	else if(node_min < the_median && node_max < the_median){
		
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
	puts("about to recurse");
	return upper_bridge(candidates);
}

Edge Graph::lower_bridge(std::vector<Node> &point_list){
	
	if(point_list.size() == 2){
		
		Edge answer = Edge(point_list[0],point_list[1]);
		return answer;
	}
	Node the_median= Utilities<Node>::median(point_list,point_list.size()/2);
	std::vector<Node> left,right,candidates;

	for(int i=0;i<point_list.size();i++){
		if(point_list[i] < the_median){
			left.push_back(point_list[i]);
		}
		else if(point_list[i] >= the_median){
			right.push_back(point_list[i]);
		}
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

	Edge median_line = Utilities<Edge>::median(lines,lines.size()/2);
	
	std::vector<Edge> lower_slope_lines,higher_slope_lines,equal_slope_lines;
	
	for(int i=0;i<lines.size();i++){
		if(lines[i] < median_line){
			lower_slope_lines.push_back(lines[i]);
		}
		else if(lines[i] > median_line){
			higher_slope_lines.push_back(lines[i]);
		}
		else{
			equal_slope_lines.push_back(lines[i]);
		}
	}
	
	double slope = median_line.get_slope();
	Node node_min,node_max;
	double intercept = point_list[0].getY() - slope*point_list[0].getX();
	node_min = point_list[0];
	node_max = point_list[0];
	
	for(int i=1;i<point_list.size();i++){
		double temp_intercept = point_list[i].getY() - slope*point_list[i].getX();
		
		if(!(abs(temp_intercept - intercept) < 0.0000001) && temp_intercept<intercept){
			intercept=temp_intercept;
			node_min = node_max = point_list[i];
		}
		else if(abs(temp_intercept - intercept) < 0.000001){
			if(node_min>point_list[i]){
				node_min = point_list[i];
			}
			else if(node_max<point_list[i]){
				node_max = point_list[i];
			}
		}
	}


	if(node_min < the_median && node_max >= the_median){
		return Edge(node_min,node_max);
	}
	else if(node_min >= the_median && node_max >= the_median){
		
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

	return lower_bridge(candidates);
}

std::vector<Node> Graph::upper_hull(std::vector<Node> &point_list,Node p_min, Node p_max,fstream &file_handle){
	
	std::vector<Node> answer;

	if (p_min.getX() == p_max.getX() && p_min.getY() == p_max.getY()){
		answer.push_back(p_min); 
	}
	else{
		std::vector<Node> left_points,right_points;
		puts("finding the bridge");
		Edge the_bridge = upper_bridge(point_list);

		file_handle << "b:" << the_bridge.to_string();

		if(the_bridge.getX().is_equal(p_min) && the_bridge.getY().is_equal(p_max)){
			file_handle << "done\n";
			answer.push_back(p_min);
			answer.push_back(p_max);
			return answer;
		}
		
		if(!the_bridge.getX().is_equal(p_min) && !the_bridge.getY().is_equal(p_max)){
			Edge trapezoid_bottom = Edge(p_min,p_max);
			Edge trapezoid_left = Edge(p_min,the_bridge.getX());
			Edge trapezoid_right = Edge(the_bridge.getY(),p_max);
			
			file_handle << "e:" << trapezoid_bottom.to_string();
			file_handle << "e:" << trapezoid_left.to_string();
			file_handle << "e:" << trapezoid_right.to_string();

			for(auto it = point_list.begin(); it < point_list.end(); it++){
				// we ignore internal points

				if(	get_orientation(trapezoid_bottom.getX(),trapezoid_bottom.getY(),*it) && 
						!get_orientation(trapezoid_left.getX(),trapezoid_left.getY(),*it) && 
						!get_orientation(trapezoid_right.getX(),trapezoid_right.getY(),*it) && 
						!get_orientation(the_bridge.getX(),the_bridge.getY(),*it)){
						continue;		
				}
				else if(get_orientation(trapezoid_left.getX(),trapezoid_left.getY(),*it)){
					file_handle << "l:" << it->to_string();
					left_points.push_back(*it);
				}
				else if(get_orientation(trapezoid_right.getX(),trapezoid_right.getY(),*it)){
					file_handle << "r:" << it->to_string();
					right_points.push_back(*it);
				}
				else{
					// it is a vertex, ignore
				}
			}	
		}
		else{
			
			Edge triangle_bottom = Edge(p_min,p_max);
			Edge triangle_left ;
			Edge triangle_right ;
			if(p_min.is_equal(the_bridge.getX())){

				triangle_left = Edge(p_min,the_bridge.getY());
				triangle_right = Edge(the_bridge.getY(),p_max);
				
				file_handle << "e:" << triangle_right.to_string();
				file_handle << "e:" << triangle_bottom.to_string();

			}
			else{

				triangle_left = Edge(p_min,the_bridge.getX());
				triangle_right = Edge(the_bridge.getX(),p_max);
			
				file_handle << "e:" << triangle_left.to_string();
				file_handle << "e:" << triangle_bottom.to_string();
			}
			
			
			for(auto it=point_list.begin();it<point_list.end();it++){
				
				if(!get_orientation(triangle_left.getX(),triangle_left.getY(),*it) && 
					!get_orientation(triangle_right.getX(),triangle_right.getY(),*it) &&
					get_orientation(triangle_bottom.getX(),triangle_bottom.getY(),*it) ){
					
					continue;
				}
				else if(get_orientation(triangle_left.getX(),triangle_left.getY(),*it)){
					file_handle << "l:" << it->to_string();
					left_points.push_back(*it);
				}
				else if(get_orientation(triangle_right.getX(),triangle_right.getY(),*it) ){
					file_handle << "r:" << it->to_string();
					right_points.push_back(*it);
				}
				else{
					// ignore vertex
				}
			}
		}

		file_handle << "done\n";
		
		left_points.insert(left_points.begin(),p_min);
		left_points.push_back(the_bridge.getX());
		vector<Node> left_answer = upper_hull(left_points,p_min,the_bridge.getX(),file_handle);
		
		right_points.push_back(p_max);
		right_points.insert(right_points.begin(),the_bridge.getY());
		

		vector<Node> right_answer = upper_hull(right_points,the_bridge.getY(),p_max,file_handle);
		
		answer.insert(answer.end(),left_answer.begin(),left_answer.end());
		answer.insert(answer.end(),right_answer.begin(),right_answer.end());
	}
	return answer;
}

std::vector<Node> Graph::lower_hull(std::vector<Node> &point_list,Node p_min, Node p_max,fstream &file_handle){
	std::vector<Node> answer;

	if (p_min.getX() == p_max.getX() && p_min.getY() == p_max.getY()){
		answer.push_back(p_min); 
	}
	else{
		std::vector<Node> left_points,right_points;

		Edge the_bridge = lower_bridge(point_list);

		file_handle << "b:" << the_bridge.to_string();

		if(the_bridge.getX().is_equal(p_min) && the_bridge.getY().is_equal(p_max)){
			answer.push_back(p_min);
			answer.push_back(p_max);
			file_handle << "done\n";
			return answer;
		}
		Edge trapezoid_top = Edge(p_min,p_max);
		Edge trapezoid_left = Edge(p_min,the_bridge.getX());
		Edge trapezoid_right = Edge(the_bridge.getY(),p_max);

		file_handle << "e:" << trapezoid_top.to_string();
		file_handle << "e:" << trapezoid_left.to_string();
		file_handle << "e:" << trapezoid_right.to_string();

		if(!the_bridge.getX().is_equal(p_min) && !the_bridge.getY().is_equal(p_max)){
			for(auto it = point_list.begin(); it < point_list.end(); it++){
				
				// we ignore internal points
				if(		!get_orientation(trapezoid_top.getX(),trapezoid_top.getY(),*it) && 
						get_orientation(trapezoid_left.getX(),trapezoid_left.getY(),*it) && 
						get_orientation(trapezoid_right.getX(),trapezoid_right.getY(),*it) && 
						get_orientation(the_bridge.getX(),the_bridge.getY(),*it)){
						continue;		
					}
				else if( !get_orientation(trapezoid_left.getX(),trapezoid_left.getY(),*it) && 
						!(it->is_equal(trapezoid_left.getX()) || it->is_equal(trapezoid_left.getY() ) )  ){
					file_handle << "l:" << it->to_string();
					left_points.push_back(*it);
				}
				else if(!get_orientation(trapezoid_right.getX(),trapezoid_right.getY(),*it) && 
						!(it->is_equal(trapezoid_right.getX()) || it->is_equal(trapezoid_right.getY()))){
					file_handle << "r:" << it->to_string();
					right_points.push_back(*it);
				}
				else{
					// it is a vertex, ignore
				}
			}
		}
		else{
			
			Edge triangle_top = Edge(p_min,p_max);
			Edge triangle_left;
			Edge triangle_right;
			if(p_min.is_equal(the_bridge.getX())){
				triangle_left = Edge(p_min,the_bridge.getY());
				triangle_right = Edge(p_max,the_bridge.getY());

				file_handle << "e:" << triangle_right.to_string();
				file_handle << "e:" << triangle_top.to_string();
			}
			else{
				triangle_left = Edge(p_min,the_bridge.getX());
				triangle_right = Edge(p_max,the_bridge.getX());
				file_handle << "e:" << triangle_left.to_string();
				file_handle << "e:" << triangle_top.to_string();
			}



			for(auto it = point_list.begin(); it < point_list.end(); it++){
				
				// we ignore internal points 
				if(		!get_orientation(triangle_top.getX(),triangle_top.getY(),*it) && 
						get_orientation(triangle_left.getX(),triangle_left.getY(),*it) && 
						get_orientation(triangle_right.getX(),triangle_right.getY(),*it)){
						continue;		
					}
				else if( !get_orientation(triangle_left.getX(),triangle_left.getY(),*it) && !(it->is_equal(triangle_left.getX()) || it->is_equal(triangle_left.getY() ) )  ){
					file_handle << "l:" << it->to_string();
					left_points.push_back(*it);
				}
				else if(!get_orientation(triangle_right.getX(),triangle_right.getY(),*it) && !(it->is_equal(triangle_right.getX()) || it->is_equal(triangle_right.getY()))){
					file_handle << "r:" << it->to_string();
					right_points.push_back(*it);
				}
				else{
					// it is a vertex, ignore
				}
			}
		}

		file_handle << "done\n";

		left_points.insert(left_points.begin(),p_min);
		left_points.push_back(the_bridge.getX());
		vector<Node> left_answer = lower_hull(left_points,p_min,the_bridge.getX(),file_handle);
		right_points.push_back(p_max);
		right_points.insert(right_points.begin(),the_bridge.getY());
		vector<Node> right_answer = lower_hull(right_points,the_bridge.getY(),p_max,file_handle);
		
		answer.insert(answer.end(),left_answer.begin(),left_answer.end());
		answer.insert(answer.end(),right_answer.begin(),right_answer.end());
	}
	return answer;
}

void Graph::kirk_patrick_seidel(){

	fstream file_handle;
	file_handle.open(KPS_OUTPUT,std::ios::out);

	if (point_list.size() <= 2){
		puts("There is no solution");
		return;
	}

    std::vector<Node> upper_hull_points,lower_hull_points;
	
	Node left_top = get_left_most_point(false,this->point_list);
	Node right_top = get_right_most_point(false,this->point_list);

    upper_hull_points.push_back(left_top);

	point_list.erase(std::remove(point_list.begin(),point_list.end(),left_top),point_list.end());
	point_list.erase(std::remove(point_list.begin(),point_list.end(),right_top),point_list.end());

	

	double slope = Edge(left_top,right_top).get_slope();
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

	point_list.erase(std::remove(point_list.begin(),point_list.end(),left_bottom),point_list.end());
	point_list.erase(std::remove(point_list.begin(),point_list.end(),right_bottom),point_list.end());

    lower_hull_points.push_back(left_bottom);
    
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

    vector<Node> upper_solution = upper_hull(upper_hull_points,left_top,right_top,file_handle);
	
	
	vector<Node> lower_solution = lower_hull(lower_hull_points,left_bottom,right_bottom,file_handle);

	if(upper_solution[0].is_equal(lower_solution[0]) ){
		lower_solution.erase(lower_solution.begin());
	}
	if(upper_solution[upper_solution.size()-1].is_equal(lower_solution[lower_solution.size()-1]) ){
		lower_solution.pop_back();
	}

	vector<Node> solution;
	solution.insert(solution.end(),upper_solution.begin(),upper_solution.end());
	solution.insert(solution.end(),lower_solution.rbegin(),lower_solution.rend());

	if(solution.size() > 2){
		convex_hull = solution;
	}
	else{
		puts("No solution exists for this ");
	}
	file_handle.close();
}
