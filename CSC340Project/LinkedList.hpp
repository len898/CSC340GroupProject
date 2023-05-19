
#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP
#include "Node.hpp"
#include <iostream>
#include <string>
#include <sstream>

template<class T>
class LinkedList {
public:
    //! Constructor
    //!
    LinkedList();
    //! Deconstructor
    ~LinkedList();
    //! This function removes all allocated memory used byLinked List
    void clear();
    //! This function inserts a Node that contains the specific data in Linked List in order
    //! @param data - the data a Node contains
    void insert(T data);
    //! This function adds a Node containing the data passed
    //! @param data - the data a Node contains
    void add(T data);
    //! This function removes a Node from the Linked List containing the data passed
    //! @param data - the data a Node contains
    void remove(T data);
    //! This function searches for a Node containing the data passed and returns a reference to Node
    //! @param data - the data a Node contains
    //! @return Node reference to Node that contains data passed, if not found, returns nullptr
    Node<T>* search(T data);
    std::string toString();
    void mergeSort();
    void bubbleSort();
    //! This function adds data from a txt file into Linked List
    //! @param fileName - name of the txt file. File name must include .txt extension
    void addFromFile(std::string fileName);
    void mergeLists(const LinkedList<T>* listTwo);
    //! This function prints each Node's data in Linked List to console
    void print();
    Node<T>* binarySearch(T target);
    
private:
    Node<T>* head; //!< a Node pointer that will reference the head of the linked list
    Node<T>* tail; //!< a Node pointer that will reference the tail of the linked list
    
    /**
     * Custom to_string that allows a string to string convertion.
     * Used to fix compatibility with LinkedList<std::string> type.
     */
    std::string to_string(const T& obj) {
        std::ostringstream oss{};
        oss << obj;
        return oss.str();
    }
    
    /**
     * A function that finds the middle Node between two given Nodes.
     * This is a private function so we will assume that Nodes are within
     * the LinkedList and do not have to worry about Nodes that do not belong.
     *
     * @param start The Node where we start our search from
     * @param end The Node where we end our search from
     */
    static Node<T>* findMid(Node<T>* start, Node<T>* end) {
        bool flip = true;
        while (start != end) {
            if (flip) {
                start = start->getNextNode();
            }
            else {
                end = end->getPrevNode();
            }
            flip = flip ? false : true;
        }
        
        return start;
    }
};
#include "LinkedList.cpp"
#endif /* LinkedList_hpp */
