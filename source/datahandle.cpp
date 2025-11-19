#include "../headers/datahandle.hpp"

template<typename T>
LList<T>::LList(){

}
template<typename T>
LList<T>::~LList(){
    while (this->root != nullptr){
        Node<T>* current_node = this->root;
        this->root = this->root->next;
        delete current_node;
    }
}
template<typename T>
unsigned long int LList<T>::size(){
    if (this->root == nullptr) return 0;
    unsigned long int counter= 1; 
    Node<T>* current_node = this->root;
    while (current_node->next != nullptr){
        current_node = current_node->next;
        counter++;
    }
    return counter;
}
template<typename T>
void LList<T>::push_back(T data){
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