#include <iostream>
#include <string>
#include <typeinfo>
#include <sstream>

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

	//Update with binary search
	void insert(T data) {
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



	void add(T data) {
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

	void remove(T data) {
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

	std::string toString() {
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

	void mergeSort() {
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

	//Modified the list from which it was called
	//List 2 does not need to be sorted
	//Calling list will be modified and sorted
	//Second list remains unchanged
	void mergeLists(const LinkedList<T>* listTwo) {
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

	//Append function possible

private:
	Node<T>* head;
	Node<T>* tail;

	std::string to_string(const T& obj) {
		std::ostringstream oss{};
		oss << obj;
		return oss.str();
	}
};

void testAddRemove() {
	unsigned int i;
	LinkedList<int>* intList = new LinkedList<int>();
	LinkedList<std::string>* stringList = new LinkedList<std::string>();

	for (i = 1; i <= 20; i++) {
		intList->add(i);
		stringList->add("Number " + std::to_string(i));
	}

	std::cout << "Added: ";
	std::cout << intList->toString() << std::endl;

	std::cout << "Added: ";
	std::cout << stringList->toString() << std::endl;

	for (i = 1; i <= 20; i += 2) {
		intList->remove(i);
		stringList->remove("Number " + std::to_string(i));
	}

	std::cout << "Removed: ";
	std::cout << intList->toString() << std::endl;

	std::cout << "Removed: ";
	std::cout << stringList->toString() << std::endl;
}

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

bool emptyMerge() {
	LinkedList<int> list1 = LinkedList<int>();
	LinkedList<int> list2 = LinkedList<int>();
	list1.mergeLists(&list2);
	bool returnVal = list1.toString() == "{}";
	return returnVal;
}

bool callingListEmptyMerge() {
	LinkedList<int> list1 = LinkedList<int>();
	LinkedList<int> list2 = LinkedList<int>();
	list2.add(25);
	list1.mergeLists(&list2);
	std::string expect_output = "{25}";
	std::string output = list1.toString();
	std::cout << "Output: " << output << std::endl;
	bool returnVal = output == expect_output;
	return returnVal;
}

bool paramterListEmptyMerge() {
	LinkedList<int> list1 = LinkedList<int>();
	LinkedList<int> list2 = LinkedList<int>();
	list1.add(25);
	list1.mergeLists(&list2);
	std::string expect_output = "{25}";
	std::string output = list1.toString();
	std::cout << "Output: " << output << std::endl;
	bool returnVal = output == expect_output;
	return returnVal;
}

bool twoNonEmptyMerge() {
	LinkedList<int> list1 = LinkedList<int>();
	LinkedList<int> list2 = LinkedList<int>();
	list1.add(25);
	list1.add(35);
	list1.add(45);
	list2.add(10);
	list2.add(65);
	list2.add(90);
	list1.mergeLists(&list2);
	std::string expect_output = "{10, 25, 35, 45, 65, 90}";
	std::string output = list1.toString();
	std::cout << "Output: " << output << std::endl;
	bool returnVal = output == expect_output;
	return returnVal;
}

void testMerge() {
	if (emptyMerge()) {
		std::cout << "Expected Output" << std::endl;
		std::cout << "Empty Merge Functional" << std::endl;
	}
	else {
		std::cout << "Unexpected Output" << std::endl;
		std::cout << "Empty Merge Not Functional" << std::endl;
	}

	if (callingListEmptyMerge()) {
		std::cout << "Expected Output" << std::endl;
		std::cout << "Calling List Empty Merge Functional" << std::endl;
	}
	else {
		std::cout << "Unexpected Output" << std::endl;
		std::cout << "Calling List Empty Merge Not Functional" << std::endl;
	}

	if (paramterListEmptyMerge()) {
		std::cout << "Expected Output" << std::endl;
		std::cout << "Parameter List Empty Merge Functional" << std::endl;
	}
	else {
		std::cout << "Unexpected Output" << std::endl;
		std::cout << "Parameter List Empty Merge Not Functional" << std::endl;
	}

	if (twoNonEmptyMerge()) {
		std::cout << "Expected Output" << std::endl;
		std::cout << "Two Non Empty List Empty Merge Functional" << std::endl;
	}
	else {
		std::cout << "Unexpected Output" << std::endl;
		std::cout << "Two Non Empty List Empty Merge Not Functional" << std::endl;
	}
}

void testMergeSort() {
	auto arrayToLinkedListInt = [](int items[], LinkedList<int>* list) {
		for (unsigned int i = 0; i < 26; ++i) {
			list->add(items[i]);
		}
	};

	auto arrayToLinkedListString = [](std::string items[], LinkedList<std::string>* list) {
		for (unsigned int i = 0; i < 26; ++i) {
			list->add(items[i]);
		}
	};

	auto mergeSortInt = [](LinkedList<int>* list) {
		std::cout << "Before Merge Sort: ";
		std::cout << list->toString() << std::endl;

		list->mergeSort();

		std::cout << "After Merge Sort: ";
		std::cout << list->toString() << std::endl;
	};

	auto mergeSortString = [](LinkedList<std::string>* list) {
		std::cout << "Before Merge Sort: ";
		std::cout << list->toString() << std::endl;

		list->mergeSort();

		std::cout << "After Merge Sort: ";
		std::cout << list->toString() << std::endl;
	};

	std::string stringItems[26] = {
		"Quebec", "Victor", "November", "Mike", "Charlie", "X-Ray",
		"Zulu", "Yankee", "Juliett", "Uniform", "Oscar", "Lima", "Romeo",
		"Bravo", "Tango", "Kilo", "Foxtrot", "India", "Delta", "Sierra",
		"Golf", "Alpha", "Papa", "Echo", "Hotel", "Whiskey"
	};
	LinkedList<std::string>* stringList = new LinkedList<std::string>();

	int intItems[26] = { 23, 1, 21, 5, 4, 17, 15, 13, 3, 2, 12, 19, 6, 10, 20, 26, 18, 9, 25, 24, 16, 14, 11, 22, 8, 7 };
	LinkedList<int>* intList = new LinkedList<int>();

	arrayToLinkedListString(stringItems, stringList);
	arrayToLinkedListInt(intItems, intList);

	mergeSortString(stringList);
	std::cout << std::endl;
	mergeSortInt(intList);
}

int main(int argc, const char* argv[]) {
	std::cout << " -- Add and Remove Node Test" << std::endl;
	testAddRemove();
	std::cout << std::endl;

	std::cout << " -- Search For Node Test -- " << std::endl;
	testSearch();
	std::cout << std::endl;

	std::cout << " -- Merge LinkedLists Test -- " << std::endl;
	testMerge();
	std::cout << std::endl;

	std::cout << " -- Merge Sort Test -- " << std::endl;
	testMergeSort();

	return 0;
}