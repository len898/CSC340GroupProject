#ifndef NODE_CPP
#define NODE_CPP

#include "Node.hpp"
template<class T>
Node<T>::Node() {
    this->data = "";
    this->next = nullptr;
    this->prev = nullptr;
}

template<class T>
Node<T>::Node(T data) {
    this->data = data;
    this->next = nullptr;
    this->prev = nullptr;
}

template<class T>
Node<T>::~Node() {
    next = nullptr;
    prev = nullptr;
}

// getters
template<class T>
T Node<T>:: getData() {return this->data;}

template<class T>
Node<T>* Node<T>::getNextNode() {return next;}

template<class T>
Node<T>* Node<T>::getPrevNode() {return prev;}

template<class T>
void Node<T>::setData(T data) {this->data = data;}

template<class T>
void Node<T>::setNextNode(Node* next) {this->next = next;}

template<class T>
void Node<T>::setPrevNode(Node* prev) {this->prev = prev;}

template<class T>
void Node<T>::setNextNodeNull() {this->next = nullptr;}

template<class T>
void Node<T>::setPrevNodeNull() {this->prev = nullptr;}
#endif
