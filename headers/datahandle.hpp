#ifndef DATAHANDLE_HPP
#define DATAHANDLE_HPP

template<typename T>
struct Node
{
    T* data_pointer;
    Node* next;
};


template<typename T>
class LList
{
private:
    Node<T>* root  = nullptr;
public:
    unsigned long int size();
    void push_back(T* data_pointer);
    LList();
    ~LList();
};


#endif