#include <bits/stdc++.h>
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
    for(int i=0;i<st.size();i++){
        cout<<st[i].first.first<<" "<<st[i].first.second<<" -> "<<st[i].second<<endl;
    }
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
        vector<pair<double,double>> convex_hull = graham_scan(point_list);
    }
    else{
        printf("Unable to open the file\n");
    }
    return 0;
}