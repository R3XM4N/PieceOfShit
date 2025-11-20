#ifndef LIST_HPP
#define LIST_HPP

#include <stdexcept>
#include <cstddef>

#pragma region LL definitions
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
    void ReSized();
public:
    unsigned long int size = 0;
    T& operator[](unsigned long int n);
    const T& operator[](unsigned long int n) const;
    unsigned long int Size();
    void Add(T data);
    void push_back(T data);
    void DeleteAt(unsigned long int n);

    LList<T>& SelfRefrence();
    LList() = default;
    ~LList();
    
    struct iterator;
    iterator begin();
    iterator end();
};
#pragma endregion

#pragma region LL declaration
template<typename T>
LList<T>& LList<T>::SelfRefrence(){
    return *this;
}

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

template<typename T>
LList<T>::~LList(){
    while (this->root != nullptr){
        Node<T>* current_node = this->root;
        this->root = this->root->next;
        delete current_node;
    }
}
template<typename T>
unsigned long int LList<T>::Size(){
    return this->size;
}
template<typename T>
void LList<T>::ReSized(){
    if (this->root == nullptr) return;
    unsigned long int counter= 1; 
    Node<T>* current_node = this->root;
    while (current_node->next != nullptr){
        current_node = current_node->next;
        counter++;
    }
    this->size = counter;
}
template<typename T>
void LList<T>::Add(T data){
    if (this->root == nullptr){
        this->root = new Node<T>{
            data, nullptr
        };
    }
    else{
        Node<T>* current_node = this->root;
        while (current_node->next != nullptr){
            current_node = current_node->next;
        }
        current_node->next = new Node<T>{
            data, nullptr
        };
    }
    this->size++;
}
template<typename T>
void LList<T>::push_back(T data){
    this->Add(data);
}
template<typename T>
void LList<T>::DeleteAt(unsigned long int n){
    if (this->root == nullptr) return;
    if (n == 0){
        if (root->next == nullptr){
            delete this->root;
            this->root = nullptr;
            ReSized();
            return;
        }
        else{
            Node<T>* target = this->root;
            this->root = target->next;
            delete target;
            target = nullptr;
            ReSized();
            return;
        }
    }
    
    Node<T>* pre_target = this->root;
    for (unsigned long int i = 0; i < n - 1; i++){
        if (pre_target->next != nullptr){
            pre_target = pre_target->next;
        }
        else throw std::out_of_range("LList index out of range");
    }
    if (pre_target->next == nullptr){
        throw std::out_of_range("LList index out of range");
        return;
    }
    else{
        if (pre_target->next->next != nullptr){
            Node<T>* new_next = pre_target->next->next;
            delete pre_target->next;
            pre_target->next = new_next;
        }
        else{
            delete pre_target->next;
            pre_target->next = nullptr;
        }   
    }
    ReSized();
}

template<typename T>
T& LList<T>::operator[](unsigned long int n){
    if (this->root == nullptr) throw std::out_of_range("Can't access empty LList");
    Node<T>* current_node = this->root;
    for (unsigned long int i = 0; i < n; i++){
        if (current_node->next != nullptr){
            current_node = current_node->next;
        }
        else throw std::out_of_range("LList index out of range");
    }
    return current_node->data;
}
template<typename T>
const T& LList<T>::operator[](unsigned long int n) const{
    if (this->root == nullptr) throw std::out_of_range("Can't access empty LList");
    Node<T>* current_node = this->root;
    for (unsigned long int i = 0; i < n; i++){
        if (current_node->next != nullptr){
            current_node = current_node->next;
        }
        else throw std::out_of_range("LList index out of range");
    }
    return current_node->data;
}

template<typename T>
typename LList<T>::iterator LList<T>::begin() { return iterator(root);}
template<typename T>
typename LList<T>::iterator LList<T>::end() { return iterator(nullptr);}
#pragma endregion


#endif