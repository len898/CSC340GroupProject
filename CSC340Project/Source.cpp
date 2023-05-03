#include <iostream>
#include <string>

template<typename T>
class Node {
public:
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

	// getters
	T getData() {
		return this->data;
	}

	Node* getNextNode() {
		return this->next;
	}

	Node* getPreviousNode() {
		return this->prev;
	}

	// setters
	void setData(T data) {
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
	T data;
	Node<T>* next;
	Node<T>* prev;
};

template<typename T>
class LinkedList {
public:
	LinkedList() {
		this->head = nullptr;
		this->tail = nullptr;
	}

	void add(T data) {
		Node<T>* newNode = new Node(data);

		if (head == nullptr) {
			head = newNode;
			tail = newNode;
			return;
		}

		Node<T>* temp = head;
		while (temp->getNextNode() != nullptr) {
			temp = temp->getNextNode();
		}
		temp->setNextNode(newNode);
		newNode->setPreviousNode(temp);
		tail = newNode;
	}

	Node<T>* search(T data) {
		Node<T>* temp = head;

		if (head == nullptr) {
			std::cout << "The list is empty. Nothing to search for" << std::endl;
			return nullptr;
		}

		while (temp != nullptr) {
			if (temp->getData() == data) {
				std::cout << "Node was found!" << std::endl;
				return temp;
			}

			temp = temp->getNextNode();
		}

		std::cout << "Node not found" << std::endl;
		return nullptr;
	}

	//    void remove(T data) {
	//
	//        if (head->getData() == data) {
	//            Node<T>* tempHead = head;
	//
	//            head = head->getNextNode();
	//            head->setPrevNodeNull();
	//
	//            delete tempHead;
	//        }
	//
	//       else if (tail->getData() == data) {
	//            Node<T>* tempTail = tail;
	//
	//            tail = tail->getPreviousNode();
	//            tail->setNextNodeNull();
	//
	//            delete tempTail;
	//        }
	//
	//       else {
	//
	//           Node<T>* temp = node;
	//           Node<T>* previousNode = node->getPreviousNode();
	//           Node<T>* nextNode = node->getNextNode();
	//
	//           previousNode->setNextNode(nextNode);
	//           nextNode->setPreviousNode(previousNode);
	//
	//           delete temp;
	//
	//       }
	//    }

	void printLinkedList() {
		Node<T>* temp = head;

		if (head == nullptr) {
			std::cout << "The linked list is empty." << std::endl;
			return;
		}

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



int main(int argc, const char* argv[]) {

	LinkedList<int>* list = new LinkedList<int>();
	LinkedList<std::string>* stringList = new LinkedList<std::string>();

	list->add(3);
	list->add(4);
	list->add(5);
	list->add(5);
	list->add(5);
	list->add(5);

	list->printLinkedList();

	stringList->add("Hello");
	stringList->add("Team");
	stringList->printLinkedList();



	return 0;
}