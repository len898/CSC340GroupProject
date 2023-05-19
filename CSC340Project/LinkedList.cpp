/**
 * A LinkedList class used to store multiple elements.
 * Dynamically links elements together so that they
 * do not need to be next to sequential in memory.
 */

#ifndef LINKEDLIST_CPP
#define LINKEDLIST_CPP
#include <fstream>
#include "LinkedList.hpp"

template<class T>
LinkedList<T>::LinkedList(){
    this->head = nullptr;
    this->tail = nullptr;
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

template<class T>
void LinkedList<T>::insert(T data) {
    Node<T>* newNode = new Node<T>(data);
    if (this->head == nullptr) {
        this->head = newNode;
        this->tail = newNode;
        return;
    }
    if (data <= this->head->getData()) {
        newNode->setNextNode(head);
        this->head->setPrevNode(newNode);
        this->head = newNode;
        return;
    }
    if (data >= tail->getData()) {
        newNode->setPrevNode(tail);
        this->tail->setNextNode(newNode);
        this->tail = newNode;
        return;
    }
    Node<T>* temp = this->head;
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
    
    if (this->head == nullptr) {
        this->head = newNode;
        this->tail = newNode;
    }
    else {
        this->tail->setNextNode(newNode);
        newNode->setPrevNode(tail);
        this->tail = newNode;
    }
}

template<class T>
void LinkedList<T>::remove(T data) {
    Node<T>* nodeToDelete = search(data);
    if (nodeToDelete != nullptr) {
        if (nodeToDelete == this->head) {
            this->head = head->getNextNode();
            this->head->setPrevNodeNull();
        }
        else if (nodeToDelete == this->tail) {
            this->tail = tail->getPrevNode();
            this->tail->setNextNodeNull();
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
    Node<T>* temp = this->head;
    
    while (temp) {
        if (temp->getData() == data) {
            return temp;
        }
        
        temp = temp->getNextNode();
    }
    
    return nullptr;
}

/**
 * Returns the string representation of the LinkedList
 * in the form of an array.
 */
template<class T>
std::string LinkedList<T>::toString() {
    Node<T>* temp = this->head;
    std::string output = "";
    std::string quote = (typeid(T).name() == typeid(std::string("")).name()) ? "\"" : "";
    
    while (temp != nullptr) {
        T val = temp->getData();
        output += quote + to_string(val) + quote;
        temp = temp->getNextNode();
        if (temp != nullptr) {
            output += ", ";
        }
    }
    return "{" + output + "}";
}

/**
 * Sorts the LinkedList using the merge sort algorithm.
 */
template<class T>
void LinkedList<T>::mergeSort() {
    // base case: 1 or 0 Nodes
    if (this->head == nullptr || this->head->getNextNode() == nullptr) {
        return;
    }
    
    // split the LinkedList in half
    Node<T>* subHead1 = this->head;
    Node<T>* subHead2 = findMid(this->head, this->tail);
    Node<T>* subTail1 = subHead2->getPrevNode();
    Node<T>* subTail2 = this->tail;
    
    // detach the two halves
    subTail1->setNextNodeNull();
    subHead2->setPrevNodeNull();
    
    // recurse first half
    this->head = subHead1;
    this->tail = subTail1;
    mergeSort();
    subHead1 = this->head;
    subTail1 = this->tail;
    
    // recurse second half
    this->head = subHead2;
    this->tail = subTail2;
    mergeSort();
    subHead2 = this->head;
    subTail2 = this->tail;
    
    // merge both halves
    this->head = nullptr;
    Node<T>* nodeptr = nullptr;
    
    // compare head of both halves
    while (subHead1 != nullptr && subHead2 != nullptr) {
        if (subHead1->getData() < subHead2->getData()) {
            if (this->head == nullptr) {
                this->head = subHead1;
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
            if (this->head == nullptr) {
                this->head = subHead2;
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
    
    // add the rest of first half to the main LinkedList
    while (subHead1 != nullptr) {
        if (this->head == nullptr) {
            this->head = subHead1;
            nodeptr = subHead1;
        }
        else {
            nodeptr->setNextNode(subHead1);
            subHead1->setPrevNode(nodeptr);
            nodeptr = subHead1;
        }
        subHead1 = subHead1->getNextNode();
    }
    
    // add the rest of second half to the main LinkedList
    while (subHead2 != nullptr) {
        if (this->head == nullptr) {
            this->head = subHead2;
            nodeptr = subHead2;
        }
        else {
            nodeptr->setNextNode(subHead2);
            subHead2->setPrevNode(nodeptr);
            nodeptr = subHead2;
        }
        subHead2 = subHead2->getNextNode();
    }
    
    this->tail = nodeptr;
}

/**
 * Sorts the LinkedList using the bubble sort algorithm.
 */
template<class T>
void LinkedList<T>::bubbleSort() {
    // do not sort if empty or one
    if (this->head == nullptr || this->head->getNextNode() == nullptr)
        return;
    
    bool swap;
    Node<T>* current = this->head;
    Node<T>* sorttail = nullptr;
    
    while (current != sorttail){
        swap = false;
        Node <T>* current2 = this->head;
        
        while (current2->getNextNode () != sorttail){
            if (current2->getData() > current2->getNextNode()->getData()){
                T temp = current2 -> getData();
                current2->setData(current2->getNextNode()->getData());
                current2->getNextNode()->setData(temp);
                swap = true;
            }
            current2 = current2->getNextNode();
        }
        sorttail = current2; // update tail to last swap
        if (!swap)
            break; // if no swap the list is already sorted
    }
}

template<class T>
void LinkedList<T>::addFromFile (std::string fileName) {
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
        
        this->add(data);
    }
    
    if (!file.eof()) {
        std::cerr << "Error reaching end of file" << std::endl;
        exit(1);
    }
    
    file.close();
}

/**
 * Modified the LinkedList from which it was called.
 * Calling LinkedList will be modified and sorted.
 *
 * @param listTwo Does not need to be sorted and remains unchanged.
 */
template<class T>
void LinkedList<T>::mergeLists(const LinkedList<T>* listTwo) {
    if (!this->head && !listTwo->head) {
        return;
    }
    else {
        mergeSort();
        Node<T>* temp = listTwo->head;
        while (temp != nullptr) {
            this->insert(temp->getData());
            temp = temp->getNextNode();
        }
    }
}

template<class T>
void LinkedList<T>::print() {
    Node<T>* temp = this->head;
    
    if (this->head == nullptr) {
        std::cout << "The linked list is empty." << std::endl;
        return;
    }
    
    while (temp != nullptr) {
        std:: cout << temp->getData() << " ";
        temp = temp->getNextNode();
    }
    
    std::cout << std::endl;
}

/**
 * Searches for a value using binary search.
 * Requires the list to be sorted to work.
 *
 * @param target The value to look for.
 */
template<class T>
Node<T>* LinkedList<T>::binarySearch(T target) {
    Node<T>* searchHead = this->head;
    Node<T>* searchTail = this->tail;
    Node<T>* searchMid = findMid(searchHead, searchTail);
    if (searchHead) {
        while (searchHead->getData() <= searchTail->getData()) {
            if (target == searchHead->getData()) {
                return searchHead;
            }
            else if (target == searchMid->getData()) {
                return searchMid;
            }
            else if (target == searchTail->getData()) {
                return searchTail;
            }
            
            if (target < searchMid->getData()) {
                searchHead = searchHead->getNextNode();
                searchTail = searchMid->getPrevNode();
                searchMid = findMid(searchHead, searchTail);
            }
            else if (target < searchMid->getData()) {
                searchHead = searchMid->getNextNode();
                searchTail = searchTail->getPrevNode();
                searchMid = findMid(searchHead, searchTail);
            }
        }
    }
    
    return nullptr;
}

#endif
