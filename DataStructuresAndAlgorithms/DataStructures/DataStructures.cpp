

/*****************************************************************
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
/*****************************************************************/







/*****************************************************************
#include <iostream>
#include "chapter-6/chain.h"
#include "chapter-6/extendedChain.h"

int main()
{
    //chain<double> app(6);
    //app.insert(0, 2);
    //std::cout <<"is empty"<< app.empty() << std::endl;

    //app.insert(1, 3);
    //std::cout << "is size" << app.size() << std::endl;

    //for (chain<double>::iterator it = app.begin(); it != app.end(); ++it) {
    //    std::cout << *it << "---";
    //}


    extendedChain<int> appp(10);
    appp.push_back(111);
    appp.push_back(333);

    for (chain<int>::iterator it = appp.begin(); it != appp.end(); ++it) {
        std::cout << *it << "---";
    }

    std::cout << "Hello 1 World!\n";
    exit(0);
}
/*****************************************************************/



#include <iostream>
#include <string>
using namespace std;

int main()
{
    struct worldnew
    {
        string a = "wor11ld";
    };

    //string* a_p = &a;
    //string** a_pp = &a_p;

    worldnew* wn_p = new worldnew();
    worldnew** wn_pp = &wn_p;

    std::cout << "Hello 1 World!"<< (*wn_p).a <<std::endl;
    std::cout << "Hello 1 World!\n";
    exit(0);
}