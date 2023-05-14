//
//  Node.hpp
//  CSC340GP
//
//  Created by e on 5/13/23.
//

#ifndef NODE_HPP
#define NODE_HPP

template<class T>
class Node {
public:
    Node();
    Node(T data);
    ~Node();
    T getData();
    
    Node* getNextNode();
    Node* getPrevNode();
    
    void setData(T data);
    void setNextNode(Node* next);
    void setPrevNode(Node* prev);
    void setNextNodeNull();
    void setPrevNodeNull();
    
private:
    T data;
    Node<T>* next;
    Node<T>* prev;
};
#include "Node.cpp"
#endif /* Node_hpp */
