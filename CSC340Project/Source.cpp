#include <iostream>
#include <string>

template<typename T>
class Node {
public:
	// constructors
	Node() {
		this->data = "";
		this->next = nullptr;
		this->prev = nullptr;
	}
	Node(T data) {
		this->data = data;
		this->next = nullptr;
		this->prev = nullptr;
	}

	// deconstructor
	~Node() {
		next = nullptr;
		prev = nullptr;
	}

	// getters
	T getData() {
		return this->data;
	}

	Node* getNextNode() {
		return this->next;
	}

	Node* getPrevNode() {
		return this->prev;
	}

	// setters
	void setData(T data) {
		this->data = data;
	}

	void setNextNode(Node* next) {
		this->next = next;
	}

	void setPrevNode(Node* prev) {
		this->prev = prev;
	}

	void setNextNodeNull() {
		this->next = nullptr;
	}
	void setPrevNodeNull() {
		this->prev = nullptr;
	}

private:
	T data;
	Node<T>* next;
	Node<T>* prev;
};

template<typename T>
class LinkedList {
public:
	// constructor
	LinkedList() {
		this->head = nullptr;
		this->tail = nullptr;
	}

	// deconstructor
	~LinkedList() {
		clear();
	}

	void clear() {
		Node<T>* nodeToDelete = head;
		while (head != nullptr) {
			head = head->getNextNode();
			delete nodeToDelete;
			nodeToDelete = head;
		}
	}

    void insert (T data){
        Node<T>* newNode = new Node<T>(data);
        if(head == nullptr){
            head = newNode;
            tail = newNode;
            return;
        }
        if (data <= head->getData()) {
            newNode -> setNextNode(head);
            head -> setPrevNode(newNode);
            head = newNode;
            return;
        }
        if(data >= tail->getData()){
            newNode->setPrevNode(tail);
            tail->setNextNode(newNode);
            tail = newNode;
            return;
        }
        Node<T>* temp = head;
        while (temp->getNextNode() != nullptr && temp->getNextNode()->getData() < data){
            temp = temp -> getNextNode();
            
        }
    
        newNode->setNextNode(temp->getNextNode());
        temp->setNextNode(newNode);
        newNode->setPrevNode(temp);
        newNode->getNextNode()->setPrevNode(newNode);
    }

	

	void add(T data) {
		Node<T>* newNode = new Node<T>(data);

		if (head == nullptr) {
			head = newNode;
			tail = newNode;
		} else {
			tail->setNextNode(newNode);
			newNode->setPrevNode(tail);
			tail = newNode;
		}
	}

	void remove(T data) {
		Node<T>* nodeToDelete = head;
		while (nodeToDelete != nullptr) {
			if (nodeToDelete->getData() == data) {
				if (nodeToDelete == head) {
					head = head->getNextNode();
					head->setPrevNodeNull();
				} else if (nodeToDelete == tail) {
					tail = tail->getPrevNode();
					tail->setNextNodeNull();
				} else {
					Node<T>* prevNode = nodeToDelete->getPrevNode();
					Node<T>* nextNode = nodeToDelete->getNextNode();
					prevNode->setNextNode(nextNode);
					nextNode->setPrevNode(prevNode);
				}
				delete nodeToDelete;
			}
			nodeToDelete = nodeToDelete->getNextNode();
		}
	}

	Node<T>* search(T data) {
		Node<T>* temp = head;

		while (temp) {
			if (temp->getData() == data) {
				return temp;
			}

			temp = temp->getNextNode();
		}

		return nullptr;
	}

	void print() {
		Node<T>* temp = head;

		while (temp != nullptr) {
			std::cout << temp->getData() << " ";
			temp = temp->getNextNode();
		}

		std::cout << std::endl;
	}

private:
	Node<T>* head;
	Node<T>* tail;
};

void testSearch() {
	//Testing the search Function
	LinkedList<int>* intListTest = new LinkedList<int>();
	if (intListTest->search(3)) {
		std::cout << "UNEXPECTED OUTPUT" << std::endl;
		std::cout << "Node was found" << std::endl;
	}
	else {
		std::cout << "Expected OUTPUT" << std::endl;
		std::cout << "Node not found" << std::endl;
	}

	intListTest->add(1);
	if (intListTest->search(1)) {
		std::cout << "Expected OUTPUT" << std::endl;
		std::cout << "Node was found" << std::endl;
	}
	else {
		std::cout << "Unexpected OUTPUT" << std::endl;
		std::cout << "Node not found" << std::endl;
	}

	if (intListTest->search(2)) {
		std::cout << "Unexpected OUTPUT" << std::endl;
		std::cout << "Node was found" << std::endl;
	}
	else {
		std::cout << "Expected OUTPUT" << std::endl;
		std::cout << "Node not found" << std::endl;
	}

	intListTest->add(10);
	intListTest->add(25);
	intListTest->add(30);

	if (intListTest->search(30)) {
		std::cout << "Expected OUTPUT" << std::endl;
		std::cout << "Node was found" << std::endl;
	}
	else {
		std::cout << "Unexpected OUTPUT" << std::endl;
		std::cout << "Node not found" << std::endl;
	}

	if (intListTest->search(10000)) {
		std::cout << "Unexpected OUTPUT" << std::endl;
		std::cout << "Node was found" << std::endl;
	}
	else {
		std::cout << "Expected OUTPUT" << std::endl;
		std::cout << "Node not found" << std::endl;
	}
}

int main(int argc, const char* argv[]) {

	LinkedList<int>* list = new LinkedList<int>();
	LinkedList<std::string>* stringList = new LinkedList<std::string>();

	list->add(3);
	list->add(4);
	list->add(5);
	list->add(5);
	list->add(5);
	list->add(5);

	list->print();

	stringList->add("Hello");
	stringList->add("Team");
	stringList->print();

	testSearch();

	return 0;
}