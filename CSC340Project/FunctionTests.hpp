//
//  FunctionTests.hpp
//  CSC340GP
//
//  Created by e on 5/13/23.
//

#ifndef FunctionTests_hpp
#define FunctionTests_hpp

void testAddRemove();
void testSearch();
bool emptyMerge();
bool callingListEmptyMerge();
bool paramterListEmptyMerge();
bool twoNonEmptyMerge();
void testMerge();
void testMergeSort();
void testAddFromFile();

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
    
    list->addFromFile(fileName, list);
    
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

#endif /* FunctionTests_hpp */
