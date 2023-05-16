#include <iostream>
#include <string>
#include <typeinfo>
#include <sstream>

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
		next = nullptr;
		prev = nullptr;
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

	/**
	 * Finds the midpoint between two node.
	 * Used to assist the binary search
	 * Can also be used to just find the middle
	 */
	Node<T>* findMid(Node<T>* end) {
		Node* slow = this;
		Node* fast = this;
		while (fast != end && fast->getNextNode() != end) {
			slow = slow->getNextNode();
			fast = fast->getNextNode()->getNextNode();
		}
		fast = nullptr;
		return slow;
	}

private:
	T data;
	Node<T>* next;
	Node<T>* prev;
};

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

	/**
	 * Returns the first Node to match the given data,
	 * otherwise returns nullptr if no Node match the
	 * given data.
	 * 
	 * @param data The data to be searched.
	 */
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
		if (head == nullptr || head->getNextNode() == nullptr)
			return;
		// do not sort if empty or one 

		bool swap;
		Node <T>* current = head;
		Node <T>* end = nullptr;

		while (current != end) {
			swap = false;
			Node <T>* current2 = head;

			while (current2->getNextNode() != end) {
				if (current2->getData() > current2->getNextNode()->getData()) {
					T temp = current2->getData();
					current2->setData(current2->getNextNode()->getData());
					current2->getNextNode()->setData(temp);
					swap = true;
				}
				current2 = current2->getNextNode();

			}
			end = current2; // update end to last swap
			if (!swap)
				break; // if no swap the list is already sorted
		}
	}

	/**
	 * Sorts the LinkedList using the merge sort algorithm.
	 */
	void mergeSort() {
		// base case: 1 or 0 Nodes
		if (head == nullptr || head->getNextNode() == nullptr) {
			return;
		}

		// split the LinkedList in half
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

		// detach the two halves
		subHead2->getPrevNode()->setNextNodeNull();
		subHead2->setPrevNodeNull();

		// recurse first half
		head = subHead1;
		mergeSort();
		subHead1 = head;

		// recurse second half
		head = subHead2;
		mergeSort();
		subHead2 = head;

		// merge both halves
		head = nullptr;
		Node<T>* nodeptr = nullptr;

		// compare head of both halves
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

		// add the rest of first half to the main LinkedList
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

		// add the rest of second half to the main LinkedList
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

	/**
	 * Searches for a value using binary search.
	 * Requires the list to be sorted to work
	 */
	Node<T>* binarySearch(T target) {
		Node<T>* searchHead = this->head;
		Node<T>* searchTail = this->tail;
		Node<T>* searchMid = this->head->findMid(searchTail);

		if (searchHead) {
			while (searchHead->getData() < searchTail->getData() && searchHead->getNextNode() != searchTail->getPrevNode()) {
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
					searchMid = searchHead->findMid(searchTail);
				}
				else if (target < searchMid->getData()) {
					searchHead = searchMid->getNextNode();
					searchTail = searchTail->getPrevNode();
					searchMid = searchHead->findMid(searchTail);
				}
			}
		}
		return nullptr;
	}

	/**
	 * Clears the LinkedList and deletes each Node.
	 */
	void clear() {
		Node<T>* nodeToDelete = head;
		while (head != nullptr) {
			head = head->getNextNode();
			delete nodeToDelete;
			nodeToDelete = head;
		}
	}

	/**
	 * Returns the string representation of the LinkedList
	 * in the form of an array.
	 */
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
	 */
	std::string to_string(const T& obj) {
		std::ostringstream oss{};
		oss << obj;
		return oss.str();
	}
};

/**
 * A function that tests adding and removing items from LinkedLists.
 */
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

/**
 * A function that tests inserting items into LinkedLists.
 */
void testInsert() {
	LinkedList<int> intList;
	LinkedList <std::string> stringList;

	//pi
	intList.insert(3);
	intList.insert(1);
	intList.insert(4);
	intList.insert(2);
	intList.insert(9);
	intList.insert(5);

	std::cout << "Inserted: " << intList.toString() << std::endl;

	stringList.insert("one");
	stringList.insert("two");
	stringList.insert("three");

	std::cout << "inserted: " << stringList.toString() << std::endl;
}

/**
 * A function that tests searching for items in a LinkedLists.
 */
void testSearch() {
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

/**
 * A function that tests merging two empty LinkedLists.
 */
bool emptyMerge() {
	LinkedList<int> list1 = LinkedList<int>();
	LinkedList<int> list2 = LinkedList<int>();
	list1.mergeLists(&list2);
	bool returnVal = list1.toString() == "{}";
	return returnVal;
}

/**
 * A function that tests merging an empty and a non-empty LinkedList.
 */
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

/**
 * A function that tests merging a non-empty and an empty LinkedList.
 */
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

/**
 * A function that tests merging two non-empty LinkedLists.
 */
bool twoNonEmptyMerge() {
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
	std::cout << "Output: " << output << std::endl;
	bool returnVal = output == expect_output;
	return returnVal;
}

/**
 * A function that calls all the merge test functions.
 */
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
	LinkedList<std::string>* stringList = new LinkedList<std::string>();

	for (unsigned int i = 0; i < 26; ++i) {
		stringList->add(stringItems[i]);
	}

	int intItems[26] = {23, 1, 21, 5, 4, 17, 15, 13, 3, 2, 12, 19, 6, 10, 20, 26, 18, 9, 25, 24, 16, 14, 11, 22, 8, 7};
	LinkedList<int>* intList = new LinkedList<int>();

	for (unsigned int i = 0; i < 26; ++i) {
		intList->add(intItems[i]);
	}

	std::cout << "Before Merge Sort: ";
	stringList->print();

	stringList->mergeSort();

	std::cout << "After Merge Sort: ";
	stringList->print();

	std::cout << std::endl;

	std::cout << "Before Merge Sort: ";
	intList->print();

	intList->mergeSort();

	std::cout << "After Merge Sort: ";
	intList->print();
}

/**
 * A function that tests the bubble sort algorithm.
 */
void testBubbleSort() {
	LinkedList<int> intList;
	LinkedList< std::string> stringList;

	intList.insert(3);
	intList.insert(1);
	intList.insert(4);
	intList.insert(1);
	intList.insert(5);
	intList.insert(9);
	intList.insert(2);

	std::cout << "before sorting: " << intList.toString() << std::endl;
	intList.bubbleSort();
	std::cout << "after sorting: " << intList.toString() << std::endl;

	stringList.add("zzz");
	stringList.add("bbb");
	stringList.add("eee");
	stringList.add("ddd");

	std::cout << "before sorting: " << stringList.toString() << std::endl;
	stringList.bubbleSort();
	std::cout << "after sorting: " << stringList.toString() << std::endl;

}


/**
 * A function that tests the binary search algorithm.
 */
void testBinarySearch() {
	LinkedList<int>* listForSearch = new LinkedList<int>();

	Node<int>* result = listForSearch->binarySearch(2);
	if (result) {
		std::cout << "Unexpected Ouput, Empty List Binary Search int" << std::endl;
	}
	else {
		std::cout << "Expected Output, Empty Binary Search int" << std::endl;
	}

	listForSearch->add(2);
	result = listForSearch->binarySearch(2);
	if (result) {
		std::cout << "Expected Ouput, One Item List Binary Search int" << std::endl;
	}
	else {
		std::cout << "Expected Output, One Item Binary Search int" << std::endl;
	}

	listForSearch->insert(1);
	result = listForSearch->binarySearch(1);
	if (result) {
		std::cout << "Expected Ouput, Two Item List Binary Search int, First Val" << std::endl;
	}
	else {
		std::cout << "Expected Output, Two Item Binary Search int, First Val" << std::endl;
	}

	listForSearch->insert(10);
	result = listForSearch->binarySearch(10);
	if (result) {
		std::cout << "Expected Ouput, Three Item List Binary Search int, Last Val" << std::endl;
	}
	else {
		std::cout << "Expected Output, Three Item Binary Search int, Last Val" << std::endl;
	}
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

	std::cout << " -- Merge LinkedLists Test -- " << std::endl;
	testMerge();
	std::cout << std::endl;

	std::cout << " -- Bubble Sort Test -- " << std::endl;
	testBubbleSort();
	std::cout << std::endl;

	std::cout << " -- Merge Sort Test -- " << std::endl;
	testMergeSort();
	std::cout << std::endl;

	std::cout << "-- Binary Search Test --" << std::endl;
	testBinarySearch();
	std::cout << std::endl;
}


int main(int argc, const char* argv[]) {
	
	testLinkedList();
	return 0;
}