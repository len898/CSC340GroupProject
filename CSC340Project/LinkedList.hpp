//
//  LinkedList.hpp
//  CSC340GP
//
//  Created by e on 5/13/23.
//

#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP
#include "Node.hpp"
#include <iostream>
#include <string>
#include <sstream>

template<class T>
class LinkedList {
public:
    LinkedList();
    ~LinkedList();
    
    void clear();
    void insert(T data);
    void add(T data);
    void remove(T data);
    Node<T>* search(T data);
    std::string toString();
    void mergeSort();
    void addFromFile(std::string fileName, LinkedList<T>* list);
    void mergeLists(const LinkedList<T>* listTwo);
    void print();

private:
    Node<T>* head;
    Node<T>* tail;

    std::string to_string(const T& obj) {
        std::ostringstream oss{};
        oss << obj;
        return oss.str();
    }
};
#include "LinkedList.cpp"
#endif /* LinkedList_hpp */
