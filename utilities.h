#ifndef UTILITY
#define UTILITY
#include<vector>
class Utilities{
	public:
	Utilities();

	template <typename T>
	void sort(std::vector<T> &array,bool (*compare)(void* a,void* b) );

	void mom();
};

#endif
