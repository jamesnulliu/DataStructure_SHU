// test the iterator for arrayList
#include<iostream>
#include<algorithm>   // has reverse
#include<numeric>     // has accumulate
#include "../header/linearList.h"
#include "../header/arrayListWithIterator.h"

using namespace std;

int main()
{
    //// create a linear list
    //arrayList<int> y(2);
    //y.insert(0, 2);
    //y.insert(1, 6);
    //y.insert(0, 1);
    //y.insert(2, 4);
    //y.insert(3, 5);
    //y.insert(2, 3);
    //cout << "Inserted 6 integers, list y should be 1 2 3 4 5 6" << endl;
    //cout << "Size of y = " << y.size() << endl;
    //cout << "Capacity of y = " << y.capacity() << endl;

    //// test iterator
    //cout << "Ouput using forward iterators pre and post ++" << endl;
    //for (arrayList<int>::iterator i = y.begin();
    //     i != y.end(); i++)
    //   cout << *i << "  ";
    //cout << endl;
    //for (arrayList<int>::iterator i = y.begin();
    //     i != y.end(); ++i)
    //   cout << *i << "  ";
    //cout << endl;

    //cout << "Ouput using backward iterators pre and post --" << endl;
    //for (arrayList<int>::iterator i = y.end();
    //     i != y.begin(); cout << *(--i) << "  ");
    //cout << endl;
    //for (arrayList<int>::iterator i = y.end();
    //     i != y.begin();)
    //   {i--; cout << *i << "  "; *i += 1;}
    //cout << endl;
    //cout << "Incremented by 1 list is " << y << endl;
    //
    //// try out some STL algorithms
    //reverse(y.begin(), y.end());
    //cout << "The reversed list is " << y << endl;
    //int sum = accumulate(y.begin(), y.end(), 0);
    //cout << "The sum of the elements is " << sum << endl;

    // Test 1:
    arrayList<int> x;
    x.push_back(1); x.push_back(2); x.push_back(3);
    x.push_back(3); x.push_back(1); x.push_back(2);
    x.push_back(2); x.push_back(3); x.push_back(1);
    arrayList<int>y(x);
    cout << "Test 1:" << endl << "Source: " << x << endl;
    x.shrink_to_unique_On2();
    cout << "Result O(n2): " << x << endl;
    y.shrink_to_unique_On();
    cout << "Result O(n): " << y << endl;

    //Test 2:
    arrayList<int> a;
    a.push_back(3); a.push_back(2); a.push_back(1);
    cout << "Test 2:" << endl << "Source1(odd elements): " << a << endl;
    a.reverse();
    cout << "Resul1t: " << a << endl;
    a.push_back(4);
    cout << "Source2(even elements):" << a << endl;
    a.reverse();
    cout << "Result2: " << a << endl;

    return 0;
}