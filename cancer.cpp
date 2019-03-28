#include <bits/stdc++.h>
#include "node.h"


using namespace std;
vector<string> split(const char *str, char c = ' ')
{
    vector<string> result;

    do
    {
        const char *begin = str;

        while(*str != c && *str)
            str++;

        result.push_back(string(begin, str));
    } while (0 != *str++);

    return result;
}

double polar_angler(pair<double,double> source, pair<double,double> target){
    return atan((target.second-source.second)/(target.first-source.first));
}

bool get_orientation(pair<double,double> p, pair<double,double> q, pair<double,double> r){
    double temp = (q.first-p.first)*(r.second-q.second) - (q.second-p.second)*(r.first-q.first);
    if(temp > 0) return true;
    else return false;
}

vector<pair<double,double>> graham_scan(vector<pair<double,double>> point_list){
    pair<double,double> corner_point = point_list[0];
    for(int i=1;i<point_list.size();i++){
        // printf("Looking at %lf %lf \n",point_list[i].first,point_list[i].second);
        if(corner_point.first > point_list[i].first){
            corner_point = point_list[i];
            // cout<<"New corner point"<<corner_point.first<<" "<<corner_point.second<<endl;
        }
        else if(corner_point.first == point_list[i].first && corner_point.second > point_list[i].second){
            corner_point = point_list[i];
            // cout<<"New corner point"<<corner_point.first<<" "<<corner_point.second<<endl;
        }
    }
    cout<<"The corner point is "<<corner_point.first<<" "<<corner_point.second<<endl;
    vector<pair<pair<double,double>,double>> polar_angles;
    polar_angles.push_back(make_pair(corner_point,-10));
    for(int i=0;i<point_list.size();i++){
        if(point_list[i] != corner_point)
            polar_angles.push_back(make_pair(point_list[i],polar_angler(corner_point,point_list[i])));
        printf("%lf\n",polar_angles[i].second);
    }
    // TODO STL sort
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
        cout<<polar_angles[i].first.first<<" "<<polar_angles[i].first.second<<" -> "<<polar_angles[i].second<<endl;
    }
    vector<pair<pair<double,double>,double>> st;
    st.push_back(polar_angles[0]);
    st.push_back(polar_angles[1]);
    for(int i=2;i<polar_angles.size();i++){
        while(st.size() > 1 && get_orientation(st[st.size()-2].first,st[st.size()-1].first,polar_angles[i].first) == false){
            cout<<"Removed from hull"<<st[st.size()-1].first.first<<" "<<st[st.size()-1].first.second<<endl;
            st.pop_back();
        }
        st.push_back(polar_angles[i]);
    }
    vector<pair<double,double>> solution;
    for(int i=0;i<st.size();i++){
        cout<<st[i].first.first<<" "<<st[i].first.second<<" -> "<<st[i].second<<endl;
        solution.push_back(st[i].first);
    }

    return solution;
}

vector<pair<double,double>> jarvis_march(vector<pair<double,double>> point_list){
    pair<double,double> corner_point = point_list[0];
    int location = 0;
    for(int i=1;i<point_list.size();i++){
        // printf("Looking at %lf %lf \n",point_list[i].first,point_list[i].second);
        if(corner_point.first > point_list[i].first){
            corner_point = point_list[i];
            location = i;
            // cout<<"New corner point"<<corner_point.first<<" "<<corner_point.second<<endl;
        }
        else if(corner_point.first == point_list[i].first && corner_point.second > point_list[i].second){
            corner_point = point_list[i];
            location = i;
            // cout<<"New corner point"<<corner_point.first<<" "<<corner_point.second<<endl;
        }
    }
    cout<<"The corner point is "<<corner_point.first<<" "<<corner_point.second<<endl;
    point_list.erase(point_list.begin()+location);
    vector<pair<double,double>> solution;
    solution.push_back(corner_point);
    pair<double,double> candidate = point_list[0], last_point = solution[solution.size()-1];
    while(true/*Reach the corner point again*/){
        candidate = point_list[0];
        printf("the starting candidate is %lf %lf\n",candidate.first,candidate.second);
        // if(candidate == corner_point)
        //     candidate = point_list[1];
        last_point = solution[solution.size()-1];
        location = 0 ;
        for(int i=1;i<point_list.size();i++){
            if(get_orientation(last_point,candidate,point_list[i]) == false){
                printf("get_orientation = %lf,%lf %lf,%lf %lf,%lf -> %d\n",last_point.first,last_point.second,candidate.first,candidate.second,point_list[i].first,point_list[i].second,get_orientation(last_point,candidate,point_list[i]));
                candidate = point_list[i];
                location = i;
            }
            else{
                printf("get_orientation = %lf,%lf %lf,%lf %lf,%lf -> %d\n",last_point.first,last_point.second,candidate.first,candidate.second,point_list[i].first,point_list[i].second,get_orientation(last_point,candidate,point_list[i]));
            }
        }
        if(last_point!=corner_point && get_orientation(last_point,candidate,corner_point) == false)
            break;
        solution.push_back(*(point_list.begin()+location));
        printf("%lf %lf has been erased\n",(point_list.begin()+location)->first,(point_list.begin()+location)->second);
        candidate = *(point_list.begin()+location);
        printf("the candidate is %lf %lf\n",candidate.first,candidate.second);
        point_list.erase(point_list.begin()+location);
        for(int i=0;i<point_list.size();i++){
            cout<<point_list[i].first<<" "<<point_list[i].second<<endl;
        }
        cout<<"**********Das temp solution ist********\n";
        for(int i=0;i<solution.size();i++){
            cout<<solution[i].first<<" "<<solution[i].second<<endl;
        }
        char c;
        cin >> c;
        cout<<"***********************************\n";
    }
    cout<<"Das solution ist\n";
    for(int i=0;i<solution.size();i++){
        cout<<solution[i].first<<" "<<solution[i].second<<endl;
    }
    return point_list;
} 


template <typename T>
T median_of_median(vector<T> point_list){

    if(point_list.size() <= 5){
        for(int i = 0; i < point_list.size(); i++){
            for(int j = i+1; j < point_list.size()-1; j++){
                if(point_list[i].first > point_list[j].first){
                    T temp = point_list[i];
                    point_list[i] = point_list[j];
                    point_list[j] = temp;
                }
            }
        }
       
        return point_list[point_list.size()/2];
    }
    int num_buckets = (point_list.size() + 4)/5; // ceil of the values
    vector < vector < T > > grid;
    
    int bucket_index = 0;
    int current_bucket_size = 0; 
    vector<T> temp;

    for(int i = 0; i < point_list.size(); i++ ){
        
        temp.push_back(point_list[i]);
        current_bucket_size++;

        if(current_bucket_size == 4)
            bucket_index++;
            current_bucket_size = 0;
            grid.push_back(temp);
            temp.clear();
    }
    // sort the buckets dirtily
    for(int index = 0; index < num_buckets; index++){

        for(int i = 0; i < grid[index].size(); i++){
            for(int j = i+1; j < grid[index].size()-1; j++){
        
                if(grid[index][i] > grid[index][j]){
                    T temp = grid[index][i];
                    grid[index][i] = grid[index][j];
                    grid[index][j] = temp;
        
                }
            }
        }
    }

    vector<T> medians;
    for(int i = 0; i < num_buckets - 1; i++){
        medians.push_back(grid[i][grid[i].size()/2]);
    }
    return median_of_median(medians);
}
template <typename T>
T median(vector<T> point_list, int offset){

// get pivot
    T pivot = median_of_median(point_list);
    vector<T> left,right;
    for (int i = 0; i < point_list.size() ; i++ ){
        if (point_list[i] == pivot )
            continue;
        else if(point_list[i] <= pivot){
            left.push_back(point_list[i]);
        }
        else if(point_list[i] > pivot){
            right.push_back(point_list[i]);
        }
    }

    if(left.size()  < right.size()){
        offset -= left.size() + 1; // As we reduce our target by the number we eliminate and the pivot itself
        return median(right,offset);
    }
    else if(left.size() > right.size()){
        // offset remains the same
        return median(left,offset);
    }
    else{
        return pivot;
    }


// get partition
// recurse depending on cases

}


tuple<pair<double,double>,pair<double,double>,int,int > get_corner_points(vector<pair<double,double>> point_list,bool flag_upper){
    pair<double,double> min = point_list[0];
    pair<double,double> max = point_list[0];
    int location_min=0,location_max=0;
    for (int i=1;i < point_list.size();i++){
        if(min.first > point_list[i].first){
            min= point_list[i];
            location_min = i;
        }
        else if( min.first == point_list[i].first && flag_upper == true && min.second < point_list[i].second){
            min = point_list[i];
            location_min = i;
        }
        else if(min.first == point_list[i].first && flag_upper == false && min.second > point_list[i].second){
            min = point_list[i];
            location_min = i;
        }

        if(max.first < point_list[i].first){
            max = point_list[i];
            location_max = i;
        }
        else if( max.first == point_list[i].first && flag_upper == true && max.second < point_list[i].second){
            max = point_list[i];
            location_max = i;
        }
        else if(max.first == point_list[i].first && flag_upper == false && max.second > point_list[i].second){
            max = point_list[i];
            location_max = i;
        }
    }

    tuple<pair<double,double>,pair<double,double>,int,int > answer = make_tuple(min,max,location_min,location_max);
    return  answer;
}
vector<pair<double,double>> KPS(vector<pair<double,double>> point_list){
    // pmin and pmax
    // Call Upper Hull -> Upper Bridge
    // Call Lower Hull -> Lower Bridge
    // Join them
    vector<pair<double,double>> upper_hull_points,lower_hull_points;
    
    tuple<pair<double,double>,pair<double,double>,int,int > corner_point_upper = get_corner_points(point_list,true);
    upper_hull_points.push_back(get<0>(corner_point_upper));
    double slope = (get<0>(corner_point_upper).second - get<1>(corner_point_upper).second ) / ( get<0>(corner_point_upper).first - get<1>(corner_point_upper).first  );
    double intercept = (get<0>(corner_point_upper).second - slope * get<0>(corner_point_upper).first);
    for(int i=0;i<point_list.size();i++){
        if(point_list[i].second - slope* point_list[i].first > intercept){
            upper_hull_points.push_back(point_list[i]);
        }
    }
    
    point_list.erase(point_list.begin()+get<2>(corner_point_upper));
    point_list.erase(point_list.begin()+get<3>(corner_point_upper));

    upper_hull_points.push_back(get<1>(corner_point_upper));

    tuple<pair<double,double>,pair<double,double>,int,int > corner_point_lower = get_corner_points(point_list,false);
    
    
    return point_list;
}

int main(){
    fstream file;
    string line, x_coord, y_coord;
    file.open("./data/DataPoints.txt",ios::in);
    vector<pair<double,double>> point_list;
    if(file.is_open()){
        while(getline(file,line)){
            vector<string> temp = split(line.c_str());
            pair<double,double> point;
            char* ptr;
            //truncate to float
            point.first = strtod(temp[0].c_str(),&ptr);
            point.second = strtod(temp[1].c_str(),&ptr);
            point_list.push_back(point);
            cout<<point.first<<" "<<point.second<<endl;
        }
        file.close();
        vector<pair<double,double>> convex_hull = KPS(point_list);

        pair<double,double> answer = median(point_list,point_list.size());
        printf("\n\nThe median is %lf %lf\n", answer.first,answer.second);
    }
    else{
        printf("Unable to open the file\n");
    }
    // Node n1=Node(1,1),n2=Node(2,1);
    // cout<< ( n1 < n2 ) << endl;
    return 0;
}