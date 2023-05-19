

#ifndef FunctionTests_hpp
#define FunctionTests_hpp

#include "Vault.hpp"

void testAddRemove();
void testSearch();
void emptyMerge();
void callingListEmptyMerge();
void paramterListEmptyMerge();
void twoNonEmptyMerge();
void testMerge();
void testMergeSort();
void testAddFromFile();
void testBubbleSort();
void testInsert();
void testBinarySearch();
void testLinkedList();
void demo();
template<class T>
bool assertion(T actual, T expected);
template<class T>
bool assertion(T actual, T expected, bool message);

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


void testAddFromFile() {
    std::string fileName = "file333.txt";
    LinkedList<std::string>* list = new LinkedList<std::string>;
    Node<std::string>* node = new Node<std::string>;
    
    list->add("The");
    list->add("best");
    list->add("team");
    list->add("in");
    list->add("CSC340");
    
    std::cout << "Before adding data from file: " << list->toString() << std::endl;
    
    list->addFromFile(fileName);
    
    std::cout << "After adding data from file: " << list->toString() << std::endl;
    
    node = list->search("Dummy");
    
    if (node->getNextNode()->getData() == "Text") {
        std::cout << "Test passed" << std::endl;
    }
    else {
        std::cerr << "Test failed" << std::endl;
    }
}

std::string read_file() {
    std::string data = "";
    std::ifstream file;
    std::string line = "";
    file.open("file333.txt");
    
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
    }
    
    while (file >> line) {
        data += line;
    }
    
    file.close();
    
    return data;
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
 * An assertion test function.
 *
 * @param actual The result generated from the test.
 * @param expected The result you expected to get.
 */

template<class T>
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

template<class T>
bool assertion(T actual, T expected, bool message) {
    if (message) {
        return assertion(actual, expected);
    }
    else {
        return actual == expected;
    }
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
        std::cin >> choice;
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
                std::cout << "Enter the value of the target vault ";
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
                std::cout << "Enter the value of the target vault ";
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
            default:
                std::cout << "Enter a value between 1 and 6 or -1";
        }
        
        
    }
}

#endif /* FunctionTests_hpp */
