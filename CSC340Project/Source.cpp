/********************************************//**
 *  @file Source.cpp
 *  @brief Spring 2023 - CSC340.05 Final Project
 *  
 *  This is the final project to make a custom
 *  LinkedList and Node class project for
 *  Spring 2023 - CSC340.05
 *  
 *  @author Ashley Ching
 *  @author Charlene Breanne Calderon
 *  @author Eduardo Loza
 *  @author Lennart Richter
 ***********************************************/

#include <iostream>
#include <string>
#include <typeinfo>
#include <sstream>

/**
 * A Node class used to in the LinkedList class.
 */
template<typename T>
class Node {
public:
	/**
	 * Node constructor function.
	 * Initializes the next and prev to nullptr.
	 *
	 * @param data The data that the node will hold.
	 */
	Node(T data) {
		this->data = data;
		this->next = nullptr;
		this->prev = nullptr;
	}

	/**
	 * Node deconstructor function.
	 * Resets the next and prev to nullptr.
	 */
	~Node() {
		this->next = nullptr;
		this->prev = nullptr;
	}

	/**
	 * Returns the data.
	 */
	T getData() {
		return this->data;
	}

	/**
	 * Returns the next Node.
	 */
	Node* getNextNode() {
		return this->next;
	}

	/**
	 * Returns the previous Node.
	 */
	Node* getPrevNode() {
		return this->prev;
	}

	/**
	 * Sets the data.
	 */
	void setData(T data) {
		this->data = data;
	}

	/**
	 * Sets the next Node.
	 */
	void setNextNode(Node* next) {
		this->next = next;
	}

	/**
	 * Sets the previous Node.
	 */
	void setPrevNode(Node* prev) {
		this->prev = prev;
	}

	/**
	 * Sets the next Node to nullptr.
	 */
	void setNextNodeNull() {
		this->next = nullptr;
	}

	/**
	 * Sets the previous Node to nullptr.
	 */
	void setPrevNodeNull() {
		this->prev = nullptr;
	}

private:
	T data;
	Node<T>* next;
	Node<T>* prev;
};

/**
 * A LinkedList class used to store multiple elements.
 * Dynamically links elements together so that they
 * do not need to be next to sequential in memory.
 */
template<typename T>
class LinkedList {
public:
	/**
	 * LinkedList constructor function.
	 * Initializes the head and tail to nullptr.
	 */
	LinkedList() {
		this->head = nullptr;
		this->tail = nullptr;
	}

	/**
	 * LinkedList deconstructor function.
	 * Called the clear function to delete each Node.
	 */
	~LinkedList() {
		clear();
	}

	/**
	 * Creates a new Node from the given data and adds
	 * it to the end of the LinkedList.
	 *
	 * @param data The data to be added.
	 */
	void add(T data) {
		Node<T>* newNode = new Node<T>(data);

		if (this->head == nullptr) {
			this->head = newNode;
			this->tail = newNode;
		}
		else {
			this->tail->setNextNode(newNode);
			newNode->setPrevNode(this->tail);
			this->tail = newNode;
		}
	}

	/**
	 * Removes the first Node that matches the given data.
	 *
	 * Uses the search function to find the Node.
	 *
	 * @param data The data to be removed.
	 */
	void remove(T data) {
		Node<T>* nodeToDelete = search(data);
		if (nodeToDelete != nullptr) {
			if (nodeToDelete == this->head) {
				this->head = this->head->getNextNode();
				this->head->setPrevNodeNull();
			}
			else if (nodeToDelete == this->tail) {
				this->tail = this->tail->getPrevNode();
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

	/**
	 * Creates a new Node from the given data and inserts
	 * it into the LinkedList in sorted order.
	 *
	 * Assumes the LinkedList is sorted, otherwise will
	 * insert it into the first place that it thinks it
	 * will go in.
	 *
	 * @param data The data to be inserted.
	 */
	void insert(T data) {
		Node<T>* newNode = new Node<T>(data);
		if (this->head == nullptr) {
			this->head = newNode;
			this->tail = newNode;
			return;
		}
		if (data <= this->head->getData()) {
			newNode->setNextNode(this->head);
			this->head->setPrevNode(newNode);
			this->head = newNode;
			return;
		}
		if (data >= this->tail->getData()) {
			newNode->setPrevNode(this->tail);
			this->tail->setNextNode(newNode);
			this->tail = newNode;
			return;
		}
		Node<T>* temp = this->head;
		while (temp->getNextNode() != nullptr && temp->getNextNode()->getData() < data) {
			temp = temp->getNextNode();

		}

        newNode -> setPrevNode(temp);
        newNode->setNextNode(temp->getNextNode());
        temp->getNextNode()->setPrevNode(newNode);
        temp->setNextNode(newNode);
        if(newNode->getNextNode() == nullptr){
            this->tail = newNode;
        }
            
    }

	/**
	 * Returns the first Node to match the given data,
	 * otherwise returns nullptr if no Node match the
	 * given data.
	 *
	 * @param data The data to be searched.
	 */
	Node<T>* search(T data) {
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
	 * Searches for a value using binary search.
	 * Requires the list to be sorted to work.
	 * 
	 * @param target The value to look for.
	 */
	Node<T>* binarySearch(T target) {
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

	/**
	 * Modified the LinkedList from which it was called.
	 * Calling LinkedList will be modified and sorted.
	 *
	 * @param listTwo Does not need to be sorted and remains unchanged.
	 */
	void mergeLists(const LinkedList<T>* listTwo) {
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

	/**
	 * Sorts the LinkedList using the bubble sort algorithm.
	 */
	void bubbleSort() {
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

	/**
	 * Sorts the LinkedList using the merge sort algorithm.
	 */
	void mergeSort() {
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
					subHead2->setPrevNode(nodeptr);
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
	 * Clears the LinkedList and deletes each Node.
	 */
	void clear() {
		Node<T>* nodeToDelete = this->head;
		while (this->head != nullptr) {
			this->head = this->head->getNextNode();
			delete nodeToDelete;
			nodeToDelete = this->head;
		}
	}

	/**
	 * Returns the string representation of the LinkedList
	 * in the form of an array.
	 */
	std::string toString() {
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
	 * Prints the string representation of the LinkedList.
	 */
	void print() {
		std::cout << toString() << std::endl;
	}

private:
	Node<T>* head;
	Node<T>* tail;

	/**
	 * Custom to_string that allows a string to string convertion.
	 * Used to fix compatibility with LinkedList<std::string> type.
	 * 
	 * @ param obj The data that is to be turned into a string.
	 */
	static std::string to_string(const T& obj) {
		std::ostringstream oss;
		oss << obj;
		return oss.str();
	}

	/**
	 * A function that finds the middle Node between two given Nodes.
	 * This is a private function so we will assume that Nodes are within
	 * the LinkedList and do not have to worry about Nodes that do not belong.
	 * 
	 * @param start The Node where we start our search from.
	 * @param end The Node where we end our search from.
	 */
	static Node<T>* findMid(Node<T>* start, Node<T>* end) {
		bool flip = true;
		while (start != end) {
			if (flip) {
				start = start->getNextNode();
			}
			else {
				end = end->getPrevNode();
			}
			flip = flip ? false : true;
		}

		return start;
	}
};

/**
 * An assertion test function.
 * 
 * @param actual The result generated from the test.
 * @param expected The result you expected to get.
 */

template<typename T>
bool assertion(T actual, T expected) {
	if (actual == expected) {
		std::cout << "[\033[0;32mPass\033[0m] ";
		return true;
	}
	else {
		std::cout << "[\033[0;31mFail\033[0m] ";
		std::cout << "Expected: " << expected << std::endl;
		std::cout << "[\033[0;31m--->\033[0m] ";
		std::cout << "  Actual: " << actual << std::endl;
		std::cout << "[\033[0;36m----\033[0m] ";
		return false;
	}
}

template<typename T>
bool assertion(T actual, T expected, bool message) {
	if (message) {
		return assertion(actual, expected);
	}
	else {
		return actual == expected;
	}
}

/**
 * A function that tests adding and removing items from LinkedLists.
 */
void testAddRemove() {
	unsigned int i;
	LinkedList<int> intList = LinkedList<int>();
	LinkedList<std::string> stringList = LinkedList<std::string>();

	for (i = 1; i <= 20; i++) {
		intList.add(i);
		stringList.add("Number " + std::to_string(i));
	}

	assertion(intList.toString(), std::string("{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}"));
	std::cout << "Added: ";
	std::cout << intList.toString() << std::endl;

	assertion(stringList.toString(), std::string("{\"Number 1\", \"Number 2\", \"Number 3\", \"Number 4\", \"Number 5\", "
		"\"Number 6\", \"Number 7\", \"Number 8\", \"Number 9\", \"Number 10\", \"Number 11\", \"Number 12\", \"Number 13\", "
		"\"Number 14\", \"Number 15\", \"Number 16\", \"Number 17\", \"Number 18\", \"Number 19\", \"Number 20\"}"));
	std::cout << "Added: ";
	std::cout << stringList.toString() << std::endl;

	for (i = 1; i <= 20; i += 2) {
		intList.remove(i);
		stringList.remove("Number " + std::to_string(i));
	}

	assertion(intList.toString(), std::string("{2, 4, 6, 8, 10, 12, 14, 16, 18, 20}"));
	std::cout << "Removed: ";
	std::cout << intList.toString() << std::endl;

	assertion(stringList.toString(), std::string("{\"Number 2\", \"Number 4\", \"Number 6\", \"Number 8\", \"Number 10\", "
		"\"Number 12\", \"Number 14\", \"Number 16\", \"Number 18\", \"Number 20\"}"));
	std::cout << "Removed: ";
	std::cout << stringList.toString() << std::endl;
}

/**
 * A function that tests inserting items into LinkedLists.
 */
void testInsert() {
	LinkedList<int> intList;
	LinkedList <std::string> stringList;

	// pi
	int intItems[9] = {3, 1, 4, 1, 5, 9, 2, 6, 5};
	for (unsigned int i = 0 ; i < 9; ++i) {
		intList.insert(intItems[i]);
		std::cout << "[\033[0;36m----\033[0m] ";
		intList.print();
	}

	intList.insert(3);
	assertion(intList.toString(), std::string("{1, 1, 2, 3, 3, 4, 5, 5, 6, 9}"));
	intList.print();

	std::string stringItems[2] = {"pug", "bear"};
	for (unsigned int i = 0; i < 2; ++i) {
		stringList.insert(stringItems[i]);
		std::cout << "[\033[0;36m----\033[0m] ";
		stringList.print();
	}

	stringList.insert("zebra");
	assertion(stringList.toString(), std::string("{\"bear\", \"pug\", \"zebra\"}"));
	stringList.print();
}

/**
 * A function that tests searching for items in a LinkedLists.
 */
void testSearch() {
	LinkedList<int> intListTest = LinkedList<int>();
	Node<int>* result;

	std::cout << "[\033[0;36m----\033[0m] ";
	intListTest.print();
	result = intListTest.search(3);
	assertion(result, static_cast<Node<int>*>(nullptr));
	std::cout << "Empty Search -> ";
	std::cout << "Searching for 3: ";
	if (result) {
		std::cout << "Node was found" << std::endl;
	}
	else {
		std::cout << "Node not found" << std::endl;
	}

	intListTest.add(1);
	std::cout << "[\033[0;36m----\033[0m] ";
	intListTest.print();
	result = intListTest.search(1);
	assertion(result->getData(), 1);
	std::cout << "One Item Search -> ";
	std::cout << "Searching for 1: ";
	if (result) {
		std::cout << "Node was found" << std::endl;
	}
	else {
		std::cout << "Node not found" << std::endl;
	}

	std::cout << "[\033[0;36m----\033[0m] ";
	intListTest.print();
	result = intListTest.search(2);
	assertion(result, static_cast<Node<int>*>(nullptr));
	std::cout << "One Item Search -> ";
	std::cout << "Searching for 2: ";
	if (result) {
		std::cout << "Node was found" << std::endl;
	}
	else {
		std::cout << "Node not found" << std::endl;
	}

	intListTest.add(10);
	intListTest.add(25);
	intListTest.add(30);

	std::cout << "[\033[0;36m----\033[0m] ";
	intListTest.print();
	result = intListTest.search(30);
	assertion(result->getData(), 30);
	std::cout << "Multiple Item Search -> ";
	std::cout << "Searching for 30: ";
	if (result) {
		std::cout << "Node was found" << std::endl;
	}
	else {
		std::cout << "Node not found" << std::endl;
	}

	std::cout << "[\033[0;36m----\033[0m] ";
	intListTest.print();
	result = intListTest.search(10000);
	assertion(result, static_cast<Node<int>*>(nullptr));
	std::cout << "Multiple Item Search -> ";
	std::cout << "Searching for 10000: ";
	if (result) {
		std::cout << "Node was found" << std::endl;
	}
	else {
		std::cout << "Node not found" << std::endl;
	}
}

/**
 * A function that tests the binary search algorithm.
 */
void testBinarySearch() {
	LinkedList<int> listForSearch = LinkedList<int>();
	Node<int>* result;

	std::cout << "[\033[0;36m----\033[0m] ";
	listForSearch.print();
	result = listForSearch.binarySearch(2);
	assertion(result, static_cast<Node<int>*>(nullptr));
	std::cout << "Empty Binary Search -> ";
	std::cout << "Searching for 2: ";
	if (result) {
		std::cout << "Node was found" << std::endl;
	}
	else {
		std::cout << "Node not found" << std::endl;
	}

	listForSearch.add(2);
	std::cout << "[\033[0;36m----\033[0m] ";
	listForSearch.print();
	result = listForSearch.binarySearch(2);
	assertion(result->getData(), 2);
	std::cout << "One Item Binary Search -> ";
	std::cout << "Searching for 2: ";
	if (result) {
		std::cout << "Node was found" << std::endl;
	}
	else {
		std::cout << "Node not found" << std::endl;
	}

	listForSearch.insert(1);
	std::cout << "[\033[0;36m----\033[0m] ";
	listForSearch.print();
	result = listForSearch.binarySearch(1);
	assertion(result->getData(), 1);
	std::cout << "Two Item List Binary Search - First Node -> ";
	std::cout << "Searching for 1: ";
	if (result) {
		std::cout << "Node was found" << std::endl;
	}
	else {
		std::cout << "Node not found" << std::endl;
	}

	listForSearch.insert(10);
	std::cout << "[\033[0;36m----\033[0m] ";
	listForSearch.print();
	result = listForSearch.binarySearch(10);
	assertion(result->getData(), 10);
	std::cout << "Tree Item List Binary Search - Last Node -> ";
	std::cout << "Searching for 10: ";
	if (result) {
		std::cout << "Node was found with a " << result->getData() << std::endl;
	}
	else {
		std::cout << "Node not found" << std::endl;
	}
}

/**
 * A function that tests merging two empty LinkedLists.
 */
void emptyMerge() {
	LinkedList<int> list1 = LinkedList<int>();
	LinkedList<int> list2 = LinkedList<int>();
	list1.mergeLists(&list2);
	std::string expect_output = "{}";
	std::string output = list1.toString();
	assertion(output, expect_output);
	std::cout << "Empty Merge Output: " << output << std::endl;
}

/**
 * A function that tests merging an empty and a non-empty LinkedList.
 */
void callingListEmptyMerge() {
	LinkedList<int> list1 = LinkedList<int>();
	LinkedList<int> list2 = LinkedList<int>();
	list2.add(25);
	list1.mergeLists(&list2);
	std::string expect_output = "{25}";
	std::string output = list1.toString();
	assertion(output, expect_output);
	std::cout << "Calling List Empty Output: " << output << std::endl;
}

/**
 * A function that tests merging a non-empty and an empty LinkedList.
 */
void paramterListEmptyMerge() {
	LinkedList<int> list1 = LinkedList<int>();
	LinkedList<int> list2 = LinkedList<int>();
	list1.add(25);
	list1.mergeLists(&list2);
	std::string expect_output = "{25}";
	std::string output = list1.toString();
	assertion(output, expect_output);
	std::cout << "Parameter List Empty Output: " << output << std::endl;
}

/**
 * A function that tests merging two non-empty LinkedLists.
 */
void twoNonEmptyMerge() {
	LinkedList<int> list1 = LinkedList<int>();
	LinkedList<int> list2 = LinkedList<int>();
	list1.add(65);
	list1.add(25);
	list1.add(35);
	list2.add(45);
	list2.add(90);
	list2.add(10);
	list1.mergeLists(&list2);
	std::string expect_output = "{10, 25, 35, 45, 65, 90}";
	std::string output = list1.toString();
	assertion(output, expect_output);
	std::cout << "Two Non Empty List Output: " << output << std::endl;
}

/**
 * A function that calls all the merge test functions.
 */
void testMerge() {
	emptyMerge();
	callingListEmptyMerge();
	paramterListEmptyMerge();
	twoNonEmptyMerge();
}

/**
 * A function that tests the bubble sort algorithm.
 */
void testBubbleSort() {
	LinkedList<int> intList;
	LinkedList<std::string> stringList;

	int intItems[10] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
	for (unsigned int i = 0; i < 10; ++i) {
		intList.add(intItems[i]);
	}

	std::cout << "[\033[0;36m----\033[0m] ";
	std::cout << "Before Sorting: " << intList.toString() << std::endl;
	intList.bubbleSort();
	assertion(intList.toString(), std::string("{1, 1, 2, 3, 3, 4, 5, 5, 6, 9}"));
	std::cout << "After Sorting: " << intList.toString() << std::endl;

	std::string stringItems[4] = {"zzz", "bbb", "eee", "ddd"};
	for (unsigned int i = 0; i < 4; ++i) {
		stringList.add(stringItems[i]);
	}

	std::cout << "[\033[0;36m----\033[0m] ";
	std::cout << "Before Sorting: " << stringList.toString() << std::endl;
	stringList.bubbleSort();
	assertion(stringList.toString(), std::string("{\"bbb\", \"ddd\", \"eee\", \"zzz\"}"));
	std::cout << "After Sorting: " << stringList.toString() << std::endl;
}

/**
 * A function that tests the merge sort algorithm.
 */
void testMergeSort() {
	std::string stringItems[26] = {
		"Quebec", "Victor", "November", "Mike", "Charlie", "X-Ray",
		"Zulu", "Yankee", "Juliett", "Uniform", "Oscar", "Lima", "Romeo",
		"Bravo", "Tango", "Kilo", "Foxtrot", "India", "Delta", "Sierra",
		"Golf", "Alpha", "Papa", "Echo", "Hotel", "Whiskey"
	};
	LinkedList<std::string> stringList = LinkedList<std::string>();

	for (unsigned int i = 0; i < 26; ++i) {
		stringList.add(stringItems[i]);
	}

	int intItems[26] = {23, 1, 21, 5, 4, 17, 15, 13, 3, 2, 12, 19, 6, 10, 20, 26, 18, 9, 25, 24, 16, 14, 11, 22, 8, 7};
	LinkedList<int> intList = LinkedList<int>();

	for (unsigned int i = 0; i < 26; ++i) {
		intList.add(intItems[i]);
	}

	std::cout << "[\033[0;36m----\033[0m] ";
	std::cout << "Before Sort: ";
	stringList.print();

	stringList.mergeSort();

	assertion(stringList.toString(), std::string("{\"Alpha\", \"Bravo\", \"Charlie\", \"Delta\", \"Echo\", \"Foxtrot\", \"Golf\", "
		"\"Hotel\", \"India\", \"Juliett\", \"Kilo\", \"Lima\", \"Mike\", \"November\", \"Oscar\", \"Papa\", \"Quebec\", \"Romeo\", "
		"\"Sierra\", \"Tango\", \"Uniform\", \"Victor\", \"Whiskey\", \"X-Ray\", \"Yankee\", \"Zulu\"}"));
	std::cout << "After Sort: ";
	stringList.print();

	std::cout << std::endl;

	std::cout << "[\033[0;36m----\033[0m] ";
	std::cout << "Before Sort: ";
	intList.print();

	intList.mergeSort();

	assertion(intList.toString(), std::string("{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26}"));
	std::cout << "After Sort: ";
	intList.print();
}

/**
 * A function that runs all the tests.
 */
void testLinkedList() {
	std::cout << " -- Add and Remove Node Test -- " << std::endl;
	testAddRemove();
	std::cout << std::endl;

	std::cout << " -- Insert Node Test -- " << std::endl;
	testInsert();
	std::cout << std::endl;

	std::cout << " -- Search For Node Test -- " << std::endl;
	testSearch();
	std::cout << std::endl;

	std::cout << " -- Binary Search Test -- " << std::endl;
	testBinarySearch();
	std::cout << std::endl;

	std::cout << " -- Merge LinkedLists Test -- " << std::endl;
	testMerge();
	std::cout << std::endl;

	std::cout << " -- Bubble Sort Test -- " << std::endl;
	testBubbleSort();
	std:: cout << std::endl;

	std::cout << " -- Merge Sort Test -- " << std::endl;
	testMergeSort();
	std:: cout << std::endl;
}

class Vault
{
public:
	Vault() {
		this->balance = 0;
	}
	Vault(int startBal) {
		this->balance = startBal;
	}
	~Vault() {}
	bool operator==(const Vault& r) {
		return this->balance == r.balance;
	}

	bool operator!=(const Vault& r) {
		return this->balance != r.balance;
	}

	bool operator<(const Vault& r) {
		return this->balance < r.balance;
	}

	bool operator>(const Vault& r) {
		return this->balance > r.balance;
	}

	bool operator<=(const Vault& r) {
		return this->balance <= r.balance;
	}

	bool operator>=(const Vault& r) {
		return this->balance >= r.balance;
	}

private:
	int balance;

	friend std::ostream& operator<<(std::ostream& os, const Vault& v) {
		os << "Vault with balance: " << v.balance;
		return os;
	}
};


void demo() {
	LinkedList<Vault> BankSystem = LinkedList<Vault>();
	LinkedList<Vault> BankSystem2 = LinkedList<Vault>();
	BankSystem2.add(Vault(100));
	BankSystem2.add(Vault(100000));
	BankSystem2.add(Vault(13));
	int choice = 0;
	while (choice != -1) {
		std::cout << "Banking System Main Menu: " << std::endl;
		std::cout << "Enter '1' to print the current Bank System" << std::endl;
		std::cout << "Enter '2' to add a vault to the current system" << std::endl;
		std::cout << "Enter '3' to search for a vault" << std::endl;
		std::cout << "Enter '4' to do a binary search must be sorted" << std::endl;
		std::cout << "Enter '5' to bubble sort the Bank System" << std::endl;
		std::cout << "Enter '6' to merge sort the Bank System" << std::endl;
		std::cout << "Enter '7' to merge another Bank System into this one" << std::endl;
		std::cout << "Enter '-1' to exit the management system" << std::endl;
		std::cout << "Console: ";
		std::cin >> choice;
		if (system("cls")) system("clear");
		switch (choice) {
			case 1:
				std::cout << "Current Bank System: ";
				BankSystem.print();
				std::cout << std::endl;
				break;
			case 2:
				int toAdd;
				std::cout << "Enter the value of the new vault to add to the system: ";
				std::cin >> toAdd;
				BankSystem.add(Vault(toAdd));
				std::cout << "Added" << std::endl;
				break;
			case 3:
				int searchTarget;
				std::cout << "Enter the value of the target vault: ";
				std::cin >> searchTarget;
				if (BankSystem.search(searchTarget)) {
					std::cout << "Vault located" << std::endl;
				}
				else {
					std::cout << "Vault not located" << std::endl;
				}
				break;
			case 4:
				int binaryTarget;
				std::cout << "Enter the value of the target vault: ";
				std::cin >> binaryTarget;
				if (BankSystem.binarySearch(binaryTarget)) {
					std::cout << "Vault located" << std::endl;
				}
				else {
					std::cout << "Vault not located" << std::endl;
				}
				break;
			case 5:
				std::cout << "Bubble Sorting" << std::endl;
				BankSystem.bubbleSort();
				std::cout << "Sorted!" << std::endl;
				break;
			case 6:
				std::cout << "Merge Sorting" << std::endl;
				BankSystem.mergeSort();
				std::cout << "Sorted!" << std::endl;
				break;
			case 7:
				std::cout << "Merging other Bank System" << std::endl;
				std::cout << "Other system: ";
				BankSystem2.print();
				BankSystem.mergeLists(&BankSystem2);
				std::cout << "New Merge System: ";
				BankSystem.print();
				break;
			case -1:
				std::cout << "Thank you for using the Banking System" << std::endl;
				break;
			default:
				std::cout << "Enter a value between 1 and 6 or -1";
		}
	}
}


int main(int argc, const char* argv[]) {
	if (argc == 2 && (std::string(argv[1]) == "-t" || std::string(argv[1]) == "--test")) {
		testLinkedList();
	} else {
		demo();
	}
	
	return 0;
}