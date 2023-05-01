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

	void insertNode(Node* node);
	Node* searchLinkedList(Node* node);
	void printLinkedList();
	void deleteNode(Node* node);

private:
	Node* head;
	Node* tail;
};

void LinkedList::insertNode(Node* node) {

	if (head == nullptr) {
		head = node;
		tail = node;
		return;
	}

	Node* temp = head;
	while (temp->getNextNode() != nullptr) {
		temp = temp->getNextNode();
	}
	temp->setNextNode(node);
	node->setPreviousNode(temp);
	tail = node;
}

Node* LinkedList::searchLinkedList(Node* node) {
	Node* temp = head;

	if (head == nullptr) {
		std::cout << "The list is empty. Nothing to search for" << std::endl;
		return nullptr;
	}

	while (temp != nullptr) {
		if (temp->getData() == node->getData()) {
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

	LinkedList list;

	Node* node1 = new Node("Welcome");
	Node* node2 = new Node("To");
	Node* node3 = new Node("CSC340");

	list.insertNode(node1);
	list.insertNode(node2);
	list.insertNode(node3);

	list.printLinkedList();

	list.searchLinkedList(node2);

	list.deleteNode(node1);

	list.printLinkedList();

	return 0;
}