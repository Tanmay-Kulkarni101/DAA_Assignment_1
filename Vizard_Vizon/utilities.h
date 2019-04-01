#ifndef UTILITIES
#define UTILITIES

using namespace std;

template <class T>
class Utilities{
public:
    static T median_of_median(vector<T> point_list){
        if(point_list.size() <= 5 && point_list.size() > 0){
            for(int i = 0; i < point_list.size()-1; i++){
                for(int j = i+1; j < point_list.size(); j++){
                    if(point_list[i] > point_list[j]){
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
        // sort the buckets directly
        for(int index = 0; index < num_buckets; index++){

            for(int i = 0; i < grid[index].size()-1; i++){
                for(int j = i+1; j < grid[index].size(); j++){

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
    static T median(vector<T> point_list, int offset){

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


            if(left.size() == offset){
                    // printf("completed\n");
                    return pivot;
                }
            else if(left.size() < offset){
                return median(right, offset - left.size() - 1);
            }
            else{
                return median(left, offset);
            }
    }
};
#endif
