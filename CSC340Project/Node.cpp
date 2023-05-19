/**
 * A Node class used to in the LinkedList class.
 */

#ifndef NODE_CPP
#define NODE_CPP

#include "Node.hpp"

/**
 * Node constructor function.
 * Initializes the next and prev to nullptr.
 * 
 *
 */
template<class T>
Node<T>::Node() {
    this->data = "";
    this->next = nullptr;
    this->prev = nullptr;
}

/**
 * Node constructor function
 * @param data - the data that the node will hold.
 */
template<class T>
Node<T>::Node(T data) {
    this->data = data;
    this->next = nullptr;
    this->prev = nullptr;
}

/**
 * Node deconstructor function.
 * Resets the next and prev to nullptr.
 */
template<class T>
Node<T>::~Node() {
    this->next = nullptr;
    this->prev = nullptr;
}

// getters
template<class T>
T Node<T>:: getData() {return this->data;}

template<class T>
Node<T>* Node<T>::getNextNode() {return this->next;}

template<class T>
Node<T>* Node<T>::getPrevNode() {return this->prev;}

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
