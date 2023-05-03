#include <iostream>
#include <string>

using namespace std;

class Node {
public:
	Node() {
		this->data = "";
		this->next = nullptr;
		this->prev = nullptr;
	}
	Node(string data) {
		this->data = data;
		this->next = nullptr;
		this->prev = nullptr;
	}
	Node(string data, Node* prev) {
		this->data = data;
		this->prev = prev;
		this->next = nullptr;
	}
	Node(string data, Node* prev, Node* next) {
		this->data = data;
		this->prev = prev;
		this->next = next;
	}
	virtual ~Node();

	// getters
	string getData() {
		return this->data;
	}

	Node* getNextNode() {
		return this->next;
	}

	Node* getPreviousNode() {
		return this->prev;
	}

	// setters
	void setData(string data) {
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
	string data;
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

	virtual ~LinkedList();
	void insertNode(string value);
	Node* searchLinkedList(string target);
	void printLinkedList();
	void deleteNode(string target);

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
	cout << "Linked List Deleted";
}

void LinkedList::insertNode(string value) {

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

Node* LinkedList::searchLinkedList(string target) {
	Node* temp = this->head;

	if (temp == nullptr) {
		cout << "The list is empty. Nothing to search for" << endl;
		return nullptr;
	}

	while (temp) {
		if (temp->getData() == target) {
			cout << "Node was found!" << endl;
			return temp;
		}

		temp = temp->getNextNode();
	}

	cout << "Node not found" << endl;
	return nullptr;
}

void LinkedList::deleteNode(string target) {

	if (this->head->getData() == target) {
		Node* tempHead = this->head;

		if ((this->head = this->head->getNextNode()) != nullptr) {
			this->head->setPrevNodeNull();
		}

		delete tempHead;
	}

	else if (this->tail->getData() == target) {
		Node* tempTail = this->tail;

		if ((this->tail = this->tail->getPreviousNode()) != nullptr) {
			this->tail->setNextNodeNull();
		}

		delete tempTail;
	}

	else {

		Node* temp = head;
		while (temp) {
			if (temp->getData() == target) {
				Node* previousNode = temp->getPreviousNode();
				Node* nextNode = temp->getNextNode();

				previousNode->setNextNode(nextNode);
				nextNode->setPreviousNode(previousNode);

				delete temp;

				return;
			}

			temp = temp->getNextNode();
		}
	}
}

void LinkedList::printLinkedList() {
	Node* temp = this->head;

	if (this->head == nullptr) {
		cout << "The linked list is empty." << endl;
		return;
	}

	while (temp != nullptr) {
		cout << temp->getData() << endl;
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

	list->deleteNode("Zoo");

	list->searchLinkedList("Zoo");

	list->printLinkedList();

	delete list;

	return 0;
}