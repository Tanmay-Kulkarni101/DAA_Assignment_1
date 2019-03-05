#include<vector>
#include<iostream>
#include "stack.h"
template <typename T>
void Stack<T>::push(T element){
    st.push_back(element);
}

template <typename T>
T Stack<T>::top(){
    return st.back();
}

template <typename T>
T Stack<T>::pop(){
    T temp = st.back();
    st.pop_back();
    return temp;
}
template <typename T>
int Stack<T>::size(){
    return st.size();
}
