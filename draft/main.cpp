#include <iostream>

using namespace std;

class A {
public:
    int a;
    A(int value): a(value){}
    A(const A& obj){
        cout << "copy-constructor\n";
        this->a = obj.a;
    }
    
    A(A&& obj){
        cout << "move-constructor\n";
        swap(this->a, obj.a);
    }
    
    A& operator=(const A& obj){
        if (this == &obj) return *this;
        cout << "copy-operator\n";
        this->a = obj.a;
        return *this;
    }
    
    A& operator=(A&& obj){
        if (this == &obj) return *this;
        cout << "move-operator\n";
        swap(this->a, obj.a);
        return *this;
    }
};

A foo() {
    A af = A(0);
    return af;
}

int main()
{
    //A a1 = A(5);
    //A a2 = A(10);
    //swap(a1, a2);
    //A a1 = A(1);
    A a1 = foo();
    cout<<a1.a;

    return 0;
}