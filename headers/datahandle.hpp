#ifndef DATAHANDLE_HPP
#define DATAHANDLE_HPP

#include <stdexcept>

template<typename T>
struct Node
{
    T data;
    Node* next;
};

template<typename T>
class LList
{
private:
    Node<T>* root  = nullptr;
public:
    T& operator[](unsigned long int n);
    const T& operator[](unsigned long int n) const;
    unsigned long int size();
    void push_back(T data_pointer);
    LList();
    ~LList();
};


#endif