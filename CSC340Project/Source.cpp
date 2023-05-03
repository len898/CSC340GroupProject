#include <iostream>
#include <string>

class Node {
public:
	Node() {
		this->data = "";
		this->next = nullptr;
		this->prev = nullptr;
	}
	Node(std::string data) {
		this->data = data;
		this->next = nullptr;
		this->prev = nullptr;
	}
	Node(std::string data, Node* prev) {
		this->data = data;
		this->prev = prev;
		this->next = nullptr;
	}
	Node(std::string data, Node* prev, Node* next) {
		this->data = data;
		this->prev = prev;
		this->next = next;
	}
	~Node();

	// getters
	std::string getData() {
		return this->data;
	}

	Node* getNextNode() {
		return this->next;
	}

	Node* getPreviousNode() {
		return this->prev;
	}

	// setters
	void setData(std::string data) {
		this->data = data;
	}

	void setNextNode(Node* next) {
		this->next = next;
	}

	void setPreviousNode(Node* prev) {
		this->prev = prev;
	}

	void setNextNodeNull() {
		this->next = nullptr;
	}
	void setPrevNodeNull() {
		this->prev = nullptr;
	}

private:
	std::string data;
	Node* next;
	Node* prev;
};

Node::~Node() {
	this->next = nullptr;
	this->prev = nullptr;
	//delete this;
}

class LinkedList {
public:
	LinkedList() {
		this->head = nullptr;
		this->tail = nullptr;
	}
	LinkedList(Node* head) {
		this->head = head;
		this->tail = head;
	}
	LinkedList(Node* head, Node* tail) {
		this->head = head;
		this->tail = tail;
	}

	~LinkedList();
	void insertNode(std::string value);
	Node* searchLinkedList(std::string target);
	void printLinkedList();
	void deleteNode(Node* node);

private:
	Node* head;
	Node* tail;
};

LinkedList::~LinkedList() {
	Node* tempNode = this->head;
	while (tempNode && tempNode->getNextNode()) {
		tempNode = tempNode->getNextNode();
		delete tempNode->getPreviousNode();
	}
	this->head = nullptr;
	this->tail = nullptr;
	std::cout << "Linked List Deleted";
}

void LinkedList::insertNode(std::string value) {

	if (!this->head) {
		Node* newNode = new Node(value);
		head = newNode;
		tail = newNode;
	}
	else if (value < this->head->getData()) {
		Node* newNode = new Node(value, nullptr, head);
		head->setPreviousNode(newNode);
		head = newNode;
	}
	else if (value > this->tail->getData()) {
		Node* newNode = new Node(value, this->tail, nullptr);
		tail->setNextNode(newNode);
		tail = newNode;
	}
	else {
		Node* temp = head;
		while (temp && temp->getNextNode()) {
			if (value > temp->getData() && value < temp->getNextNode()->getData()) {
				Node* newNode = new Node(value, temp, temp->getNextNode());
				temp->getNextNode()->setPreviousNode(newNode);
				temp->setNextNode(newNode);
			}
			temp = temp->getNextNode();
		}
	}


}

Node* LinkedList::searchLinkedList(std::string target) {
	Node* temp = this->head;

	if (temp == nullptr) {
		std::cout << "The list is empty. Nothing to search for" << std::endl;
		return nullptr;
	}

	while (temp) {
		if (temp->getData() == target) {
			std::cout << "Node was found!" << std::endl;
			return temp;
		}

		temp = temp->getNextNode();
	}

	std::cout << "Node not found" << std::endl;
	return nullptr;
}

void LinkedList::deleteNode(Node* node) {

	if (head == node) {
		Node* tempHead = head;

		head = head->getNextNode();
		head->setPrevNodeNull();

		delete tempHead;
	}

	else if (tail == node) {
		Node* tempTail = tail;

		tail = tail->getPreviousNode();
		tail->setNextNodeNull();

		delete tempTail;
	}

	else {

		Node* temp = node;
		Node* previousNode = node->getPreviousNode();
		Node* nextNode = node->getNextNode();

		previousNode->setNextNode(nextNode);
		nextNode->setPreviousNode(previousNode);

		delete temp;

	}
}

void LinkedList::printLinkedList() {
	Node* temp = head;

	if (head == nullptr) {
		std::cout << "The linked list is empty." << std::endl;
		return;
	}

	while (temp != nullptr) {
		std::cout << temp->getData() << std::endl;
		temp = temp->getNextNode();
	}

}

int main(int argc, const char* argv[]) {

	LinkedList* list = new LinkedList();

	list->insertNode("Abbacus");
	list->insertNode("Coral");
	list->insertNode("Zoo");
	list->insertNode("Dino");

	list->searchLinkedList("Zoo");

	list->printLinkedList();

	delete list;

	return 0;
}