
#include "LinkedList.hpp"
#include "FunctionTests.hpp"

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
    std::cout << std::endl;
    
    std::cout << " -- Add From File Test -- " << std::endl;
    testAddFromFile();
    std::cout << std::endl;
    
    std::cout << " -- Bubble Sort Test -- " << std::endl;
    testBubbleSort();
    std::cout << std::endl;
    
    LinkedList<int>* list = new LinkedList<int>;
    list->add(3);
    list->add(2);
    list->add(35);
    list->add(52);
    list->add(5);
    list->print();
    
    list->addFromFile("dict.txt", list);
    list->print();
    
    list->bubbleSort();
    list->print();
    

    return 0;
}
