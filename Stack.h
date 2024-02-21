
#include<iostream>
using namespace std;

template<class T>
class Stack{
    static const int max=1000;
    T contents[max];
    int current;
    public:
        Stack();
        ~Stack();
        void push(const T &i) noexcept(false) ;
        void pop()noexcept(false);
        T top() const;
        bool isEmpty() const;
        bool isFull() const;
        int getCurrent();

};

