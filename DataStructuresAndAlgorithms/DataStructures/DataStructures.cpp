

#include <iostream>

#include "chapter-5/arrayList.h"
#include "chapter-5/iterator.h"

int main()
{
    arrayList<int> test(9);
    std::cout << test.capacity() << std::endl;
    if (test.empty()) { std::cout << "is empty" << std::endl; }
    std::cout << "test.size:" << test.size() << std::endl;

    test.insert(0, 0);
    test.insert(1, 3);
    test.insert(2, 5);

    for (iterator<int> it = test.begin(); it != test.end(); ++it) {
        std::cout << *it << "---";
    }
    std::cout << std::endl;


    std::cout << "Hello 1 World!\n";
    exit(0);
    //return 0;
}

