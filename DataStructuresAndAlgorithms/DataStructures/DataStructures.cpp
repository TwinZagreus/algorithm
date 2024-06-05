

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




/*****************************************************************
#include <iostream>
#include <string>
#include "chapter-7/sparseMatrix.h"

using namespace std;

int main()
{
    
    sparseMatrix<int> a, b, c;

    // test input and output
    cin >> a;
    cout << "Matrix a is" << endl << a;
    cin >> b;
    cout << "Matrix b is" << endl << b;

    // test transpose
    a.transpose(c);
    cout << "The transpose of a is" << endl << c;

    // test add
    a.add(b, c);
    cout << "The sum of a and b is" << endl << c;

    return 0;
    exit(0);
}
/*****************************************************************/





/*****************************************************************
#include <iostream>
#include <string>
#include "chapter-8/arrayStack.h"
#include "chapter-8/linkedStack.h"

using namespace std;

int main()
{
    arrayStack<int> s;

    // add a few elements
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);

    cout << "Stack should be 1234, bottom to top" << endl;

    // test empty and size
    if (s.empty())
        cout << "The stack is empty" << endl;
    else
        cout << "The stack is not empty" << endl;

    cout << "The stack size is " << s.size() << endl;

    while (!s.empty())
    {
        cout << "Stack top is " << s.top() << endl;
        s.pop();
        cout << "Popped top element" << endl;
    }

    try { s.pop(); }
    catch (stackEmpty message)
    {
        cout << "Last pop failed " << endl;
        message.outputMessage();
    }


    linkedStack<int> s;

    // add a few elements
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);

    cout << "Stack should be 1234, bottom to top" << endl;

    // test empty and size
    if (s.empty())
        cout << "The stack is empty" << endl;
    else
        cout << "The stack is not empty" << endl;

    cout << "The stack size is " << s.size() << endl;

    while (!s.empty())
    {
        cout << "Stack top is " << s.top() << endl;
        s.pop();
        cout << "Popped top element" << endl;
    }

    try { s.pop(); }
    catch (stackEmpty message)
    {
        cout << "Last pop failed " << endl;
        message.outputMessage();
    }

   
    exit(0);
}
/*****************************************************************/

/*****************************************************************
#include <iostream>
#include <string>
#include "chapter-8/arrayStack.h"

using namespace std;

void towersOfHanoi(int n, int x, int y, int z)
{// Move the top n disks from tower x to tower y.
 // Use tower z for intermediate storage.
    if (n > 0)
    {
        towersOfHanoi(n - 1, x, z, y);
        cout << "Move top disk from tower " << x
            << " to top of tower " << y << endl;
        towersOfHanoi(n - 1, z, y, x);
    }
}


arrayStack<int> tower[4];


void moveAndShow(int, int, int, int);

void towersOfHanoiStack(int n)
{// Preprocessor for moveAndShow.
    for (int d = n; d > 0; d--) // initialize
        tower[1].push(d); // add disk d to tower 1

     // move n disks from tower 1 to 3 using 2 as
     // intermediate tower
    moveAndShow(n, 1, 2, 3);
}

void moveAndShow(int n, int x, int y, int z)
{// Move the top n disks from tower x to tower y showing states.
 // Use tower z for intermediate storage.
    if (n > 0)
    {
        moveAndShow(n - 1, x, z, y);
        int d = tower[x].top();   // move a disk from top of
        tower[x].pop();           // tower x to top of
        tower[y].push(d);         // tower y
     // showState();              // show state of 3 towers
     // substitute showState code for test run
        cout << "Move disk " << d << " from tower "
            << x << " to top of tower " << y << endl;
        moveAndShow(n - 1, z, y, x);
    }
}

int main() {

    towersOfHanoi(2, 1, 2, 3);
    towersOfHanoiStack(2);

    exit(0);
}
/*****************************************************************/


/*****************************************************************
#include <iostream>
#include <string>
#include "myExceptions.h"
#include "chapter-9/arrayQueue.h"
#include "chapter-9/linkedQueue.h"

int main() {
    arrayQueue<int> q(4);

    // add a few elements
    q.push(1);
    cout << "Queue rear is " << q.back() << endl;
    q.push(2);
    cout << "Queue rear is " << q.back() << endl;
    q.push(3);
    cout << "Queue rear is " << q.back() << endl;
    q.push(4);
    cout << "Queue rear is " << q.back() << endl;

    cout << "Queue should be 1234, front to rear" << endl << endl;


    // test empty and size
    if (q.empty())
        cout << "The queue is empty" << endl;
    else
        cout << "The queue is not empty" << endl;

    cout << "The queue size is " << q.size() << endl;

    while (!q.empty())
    {
        cout << "Queue front is " << q.front() << endl;
        q.pop();
        cout << "Popped front element" << endl;
    }

    try { q.pop(); }
    catch (queueEmpty message)
    {
        cout << "Last pop failed " << endl;
        message.outputMessage();
    }



    linkedQueue<int> q;

    // add a few elements
    q.push(1);
    cout << "Queue back is " << q.back() << endl;
    q.push(2);
    cout << "Queue back is " << q.back() << endl;
    q.push(3);
    cout << "Queue back is " << q.back() << endl;
    q.push(5);
    cout << "Queue back is " << q.back() << endl;

    cout << "Queue should be 1234, front to back" << endl;

    // test empty and size
    if (q.empty())
        cout << "The queue is empty" << endl;
    else
        cout << "The queue is not empty" << endl;

    cout << "The queue size is " << q.size() << endl;

    while (!q.empty())
    {
        cout << "Queue front is " << q.front() << endl;
        q.pop();
        cout << "Popped front element" << endl;
    }

    try { q.pop(); }
    catch (queueEmpty message)
    {
        cout << "Last pop failed " << endl;
        message.outputMessage();
    }


    exit(0);
}
/*****************************************************************/

#include <iostream>
#include <string>
#include "myExceptions.h"
#include "chapter-10/sortedChain.h"

int main() {
    sortedChain<int, int> z;
    pair<int, int> p;

    p.first = 2; p.second = 10;
    z.insert(p);
    p.first = 10; p.second = 50;
    z.insert(p);
    p.first = 6; p.second = 30;
    z.insert(p);
    p.first = 8; p.second = 40;
    z.insert(p);
    p.first = 1; p.second = 5;
    z.insert(p);
    p.first = 12; p.second = 60;
    z.insert(p);

    cout << "The chain is " << z << endl;
    cout << "Its size is " << z.size() << endl;

    // test find
    cout << "Element associated with 1 is " << z.find(1)->second << endl;
    cout << "Element associated with 6 is " << z.find(6)->second << endl;
    cout << "Element associated with 12 is " << z.find(12)->second << endl;

    // test erase
    z.erase(1);
    z.erase(2);
    z.erase(6);
    z.erase(12);
    cout << "Deleted 1, 2, 6, 12" << endl;
    cout << "The chain is " << z << endl;
    cout << "Its size is " << z.size() << endl;

    exit(0);
}