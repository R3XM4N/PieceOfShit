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
void LList<T>::push_back(T* data_pointer){
    if (this->root == nullptr){
        this->root = new Node<T>{
            data_pointer, nullptr
        };
    }
    else{
        Node<T>* current_node = this->root;
        while (current_node->next != nullptr){
            current_node = current_node->next;
        }
        current_node->next = new Node<T>{
            data_pointer, nullptr
        };
    }
}
