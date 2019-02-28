#ifndef UTILITY
#define UTILITY

class Utilities{
	public:
	Utilities();

	template <typename T>
	void sort(std::vector<T> &array,bool (*compare)(void* a,void* b) );

	void mom();
};

#endif