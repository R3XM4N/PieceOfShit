#ifndef DATAHANDLE_HPP
#define DATAHANDLE_HPP

#include <stdexcept>
#include <cstddef>

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
    //HELL
    
    struct iterator;
    T& operator[](unsigned long int n);
    const T& operator[](unsigned long int n) const;
    unsigned long int size();
    void push_back(T data);
    LList() = default;
    ~LList();
    iterator begin();
    iterator end();
};

template<typename T>
struct LList<T>::iterator{
    Node<T>* current_node{nullptr};

    explicit iterator(Node<T>* node_ptr = nullptr) : current_node(node_ptr) {}

    T& operator*() const {return current_node->data;}
    T* operator->() const {return &current_node->data;}

    iterator& operator++(){
        current_node = current_node->next;
        return *this;
    }
    bool operator==(const iterator& other) const {return current_node == other.current_node;}
    bool operator!=(const iterator& other) const {return current_node != other.current_node;}
};

#endif