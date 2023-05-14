//
//  LinkedList.cpp
//  CSC340GP
//
//  Created by e on 5/13/23.
//
#ifndef LINKEDLIST_CPP
#define LINKEDLIST_CPP
#include <fstream>
#include "LinkedList.hpp"

template<class T>
LinkedList<T>::LinkedList(){
    head = nullptr;
    tail = nullptr;
}

template<class T>
LinkedList<T>::~LinkedList() {
    clear();
}

template<class T>
void LinkedList<T>::clear() {
    Node<T>* nodeToDelete = head;
    while (head != nullptr) {
        head = head->getNextNode();
        delete nodeToDelete;
        nodeToDelete = head;
    }
}

//Update with binary search
template<class T>
void LinkedList<T>::insert(T data) {
    Node<T>* newNode = new Node<T>(data);
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        return;
    }
    if (data <= head->getData()) {
        newNode->setNextNode(head);
        head->setPrevNode(newNode);
        head = newNode;
        return;
    }
    if (data >= tail->getData()) {
        newNode->setPrevNode(tail);
        tail->setNextNode(newNode);
        tail = newNode;
        return;
    }
    Node<T>* temp = head;
    while (temp->getNextNode() != nullptr && temp->getNextNode()->getData() < data) {
        temp = temp->getNextNode();

    }

    newNode->setNextNode(temp->getNextNode());
    temp->setNextNode(newNode);
    newNode->setPrevNode(temp);
    newNode->getNextNode()->setPrevNode(newNode);
}

template<class T>
void LinkedList<T>::add(T data) {
    Node<T>* newNode = new Node<T>(data);

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    }
    else {
        tail->setNextNode(newNode);
        newNode->setPrevNode(tail);
        tail = newNode;
    }
}

template<class T>
void LinkedList<T>::remove(T data) {
    Node<T>* nodeToDelete = search(data);
    if (nodeToDelete != nullptr) {
        if (nodeToDelete == head) {
            head = head->getNextNode();
            head->setPrevNodeNull();
        }
        else if (nodeToDelete == tail) {
            tail = tail->getPrevNode();
            tail->setNextNodeNull();
        }
        else {
            Node<T>* prevNode = nodeToDelete->getPrevNode();
            Node<T>* nextNode = nodeToDelete->getNextNode();
            prevNode->setNextNode(nextNode);
            nextNode->setPrevNode(prevNode);
        }
        delete nodeToDelete;
    }
}

template<class T>
Node<T>* LinkedList<T>::search(T data) {
    Node<T>* temp = head;

    while (temp) {
        if (temp->getData() == data) {
            return temp;
        }

        temp = temp->getNextNode();
    }

    return nullptr;
}

template<class T>
std::string LinkedList<T>::toString() {
    std::string stringType = "NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE";

    Node<T>* temp = this->head;
    std::string output = "";

    while (temp != nullptr) {
        T val = temp->getData();
        std::string quote = (typeid(T).name() == stringType) ? "\"" : "";
        output += quote + to_string(val) + quote;
        temp = temp->getNextNode();
        if (temp != nullptr) {
            output += ", ";
        }
    }
    return "{" + output + "}";
}

template<class T>
void LinkedList<T>::mergeSort() {
    if (head == nullptr || head->getNextNode() == nullptr) {
        return;
    }

    Node<T>* subHead1 = head;
    Node<T>* subHead2 = head;

    int size = 0;
    while (subHead1 != nullptr) {
        subHead1 = subHead1->getNextNode();
        if (++size % 2 == 0) {
            subHead2 = subHead2->getNextNode();
        }
    }

    subHead1 = head;

    subHead2->getPrevNode()->setNextNodeNull();
    subHead2->setPrevNodeNull();

    head = subHead1;
    mergeSort();
    subHead1 = head;

    head = subHead2;
    mergeSort();
    subHead2 = head;

    head = nullptr;
    Node<T>* nodeptr = nullptr;

    while (subHead1 != nullptr && subHead2 != nullptr) {
        if (subHead1->getData() < subHead2->getData()) {
            if (head == nullptr) {
                head = subHead1;
                nodeptr = subHead1;
            }
            else {
                nodeptr->setNextNode(subHead1);
                subHead1->setPrevNode(nodeptr);
                nodeptr = subHead1;
            }
            subHead1 = subHead1->getNextNode();
        }
        else {
            if (head == nullptr) {
                head = subHead2;
                nodeptr = subHead2;
            }
            else {
                nodeptr->setNextNode(subHead2);
                subHead1->setPrevNode(nodeptr);
                nodeptr = subHead2;
            }
            subHead2 = subHead2->getNextNode();
        }
    }

    while (subHead1 != nullptr) {
        if (head == nullptr) {
            head = subHead1;
            nodeptr = subHead1;
        }
        else {
            nodeptr->setNextNode(subHead1);
            subHead1->setPrevNode(nodeptr);
            nodeptr = subHead1;
        }
        subHead1 = subHead1->getNextNode();
    }

    while (subHead2 != nullptr) {
        if (head == nullptr) {
            head = subHead2;
            nodeptr = subHead2;
        }
        else {
            nodeptr->setNextNode(subHead2);
            subHead2->setPrevNode(nodeptr);
            nodeptr = subHead2;
        }
        subHead2 = subHead2->getNextNode();
    }

    tail = nodeptr;
}

template<class T>
void LinkedList<T>::addFromFile (std::string fileName, LinkedList<T>* list) {
    std::ifstream file;
    T data;
    
    file.open(fileName);
    
    if (file.peek() == std::ifstream::traits_type::eof()) {
        std::cerr << "Error: File is empty" << std::endl;
        exit(1);
    }
    
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        exit(1);
    }
    
    while (file >> data) {
        if (file.eof()) {
            break;
        }
        
        list->add(data);
    }
    
    if (!file.eof()) {
        std::cerr << "Error reaching end of file" << std::endl;
        exit(1);
    }
    
    file.close();
}

//Modified the list from which it was called
//List 2 does not need to be sorted
//Calling list will be modified and sorted
//Second list remains unchanged
template<class T>
void LinkedList<T>::mergeLists(const LinkedList<T>* listTwo) {
    if (!this->head && !listTwo->head) {
        return;
    }
    else {
        Node<T>* temp = listTwo->head;
        while (temp != nullptr) {
            this->insert(temp->getData());
            temp = temp->getNextNode();
        }
    }
}

template<class T>
void LinkedList<T>::print() {
    Node<T>* temp = head;
    
    if (head == nullptr) {
        std::cout << "The linked list is empty." << std::endl;
        return;
    }
    
    while (temp != nullptr) {
        std:: cout << temp->getData() << " ";
        temp = temp->getNextNode();
    }
    
    std::cout << std::endl;
}
#endif
