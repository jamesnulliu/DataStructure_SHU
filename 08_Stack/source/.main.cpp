#include "../class/linkedStack.h"
#include "../class/arrayStack.h"
#include <windows.h>

using namespace std;

class Base
{
public:
    // Constructor.
    Base() { printf("Base.\n"); }
    int a = 1;
private:
    int m_a;
protected:
    int p_a = 2;
};

class Child :
    public Base
{
public:
    // Constructor.
    Child()
    {
        printf("Child.\n");
        cout << p_a << endl;
    }
    int aC;
private:
    int m_aC;
};

int main()
{
    Child c;
    cout << sizeof(Base) << ' ' << sizeof(Child);
    cin.get();
}