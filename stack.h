#ifndef STACK
#define STACK
#include <vector>
#include<vector>
#include<iostream>

template <class T>
class Stack{
private:
    std::vector<T> st;
public:
    void push(T element);
    T pop();
    T top();
    int size();
};

#endif
