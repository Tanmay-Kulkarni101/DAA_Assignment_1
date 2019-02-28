#include <iostream>
#include <vector>
#include "utilities.h"

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
