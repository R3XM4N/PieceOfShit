#ifndef LIST_HPP
#define LIST_HPP

#include <stdexcept>
#include <cstddef>
#include <memory>

#pragma region LL definitions
template<typename T>
struct Node
{
    T data;
    std::unique_ptr<Node<T>> next;
};

template<typename T>
class LList
{
private:
    std::unique_ptr<Node<T>> root  = nullptr;
    // void ReSized();
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
    ~LList() = default;
    
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
unsigned long int LList<T>::Size(){
    return this->size;
}
// template<typename T>
// void LList<T>::ReSized(){
//     if (this->root == nullptr) return;
//     unsigned long int counter= 1; 
//     Node<T>* current_node = this->root;
//     while (current_node->next != nullptr){
//         current_node = current_node->next;
//         counter++;
//     }
//     this->size = counter;
// }
template<typename T>
void LList<T>::Add(T data){
    std::unique_ptr<Node<T>> new_node = std::make_unique<Node<T>>();
    new_node->data = std::move(data);
    if (!this->root) root = std::move(new_node);    
    else{
        Node<T>* current_node = root.get();
        while (current_node->next){
            current_node = current_node->next.get();
        }
        current_node->next = std::move(new_node);
    }
    this->size++;
}
template<typename T>
void LList<T>::push_back(T data){
    this->Add(data);
}
template<typename T>
void LList<T>::DeleteAt(unsigned long int n){
    if (!this->root) return;
    if (n == 0){
        this->root = std::move(this->root->next);
        this->size--;
        return;
    }
    Node<T>* pre_target = this->root.get();
    for (unsigned long int i = 0; i < n - 1 && pre_target->next; i++){
        pre_target = pre_target->next.get();
    }
    if (pre_target->next == nullptr){
        throw std::out_of_range("LList index out of range");
    }
    pre_target->next = std::move(pre_target->next.next);
    size--;
    // ReSized();
}

template<typename T>
T& LList<T>::operator[](unsigned long int n){
    if (!this->root) throw std::out_of_range("Can't access empty LList");
    Node<T>* current_node = this->root.get();
    for (unsigned long int i = 0; i < n; i++){
        if (!current_node->next) throw std::out_of_range("LList index out of range");
        else 
            current_node = current_node->next.get();
    }
    return current_node->data;
}
template<typename T>
const T& LList<T>::operator[](unsigned long int n) const{
    if (!this->root) throw std::out_of_range("Can't access empty LList");
    Node<T>* current_node = this->root.get();
    for (unsigned long int i = 0; i < n; i++){
        if (!current_node->next) throw std::out_of_range("LList index out of range");
        else 
            current_node = current_node->next.get();
    }
    return current_node->data;
}

template<typename T>
typename LList<T>::iterator LList<T>::begin() { return iterator(root.get());}
template<typename T>
typename LList<T>::iterator LList<T>::end() { return iterator(nullptr);}
#pragma endregion


#endif