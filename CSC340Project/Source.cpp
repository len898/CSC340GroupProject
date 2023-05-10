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

	//insert
    void insert (T data){
        Node<T>* newNode = new Node <T>(data);
        if(head == nullptr){
            head = newNode;
            tail = newNode;
            return;
        }
        if (data <= head -> getData()) {
            newNode -> setNextNode(head);
            head -> setPreviousNode(newNode);
            head = newNode;
            return;
        }
        if(data >= tail -> getData ()){
            newNode->setPreviousNode(tail);
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
        newNode->setPreviousNode(temp);
        newNode->getNextNode()->setPreviousNode(newNode);
    }

	void testInsert(){
		LinkedList <int>* list = new LinkedList <int>();

			list -> insert(2);
			list -> insert(8);
			list -> insert(6);
			list -> insert(8);
			list -> insert(1);
			list -> insert(0);

			std:: cout << "After insert: ";
			list -> printLinkedList();

		
	}

	void bubbleSort(){
		if (head == nullptr || head -> getNextNode() == nullptr)
		return; 
		//if empty dont sort 

		bool swap;
		Node <T>* current1 = head;
		Node <T>* current2;
		
		while (current1 -> getNextNode() != nullptr){
			current2 = head;

			while (current2 -> getNextNode() != nullptr){
				if (current2 -> getData() > current2 -> getNextNode() -> getData()){
					//swap nodes
					T temp = current2 -> getData();
					current2 -> setData((current2 -> getNextNode()) -> getData());
					current2 -> getNextNode() -> setData(temp);
					swap = true;

			}
			current2 = current2 -> getNextNode();
		}
		current1 = current1 -> getNextNode();
		
		}
	}

	void testBubbleSort() {
		LinkedList <int>* list = new LinkedList <int>();

		//pi 
		list -> add (3);
		list -> add (1);
		list -> add (4);
		list -> add (1);
		list -> add (5);
		list -> add (9);
		list -> add (2);
		list -> add (6);
		list -> add (5);
		list -> add (3);

		std:: cout << "Before sorting: ";
		list -> printLinkedList();

		//bubble sort applied
		list -> bubbleSort();

		std:: cout << "After sorting: ";
		list -> printLinkedList();
	}
	

	void add(T data) {
		Node<T>* newNode = new Node<T>(data);

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
		Node<T>* temp = this->head;

		if (this->head == nullptr) {
			//std::cout << "The list is empty. Nothing to search for" << std::endl;
			return nullptr;
		}

		while (temp) {
			if (temp->getData() == data) {
				//std::cout << "Node was found!" << std::endl;
				return temp;
			}

			temp = temp->getNextNode();
		}

		//std::cout << "Node not found" << std::endl;
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

	list->printLinkedList();

	stringList->add("Hello");
	stringList->add("Team");
	stringList->printLinkedList();

	testSearch();

	// test case for bubble sort
	std:: cout << "\n";
	list -> testBubbleSort();

	// test case for insert 
	std:: cout << "\n";
	list -> testInsert();
	std:: cout << "\n";


	return 0;
}