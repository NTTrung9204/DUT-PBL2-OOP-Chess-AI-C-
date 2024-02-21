#include"Stack.h"
template<typename T>
Stack<T>::Stack(){
    this->current=0;
}
template<typename T>
Stack<T>::~Stack(){
    
}
template<typename T>
void Stack<T>::push(const T&i){
    if (this->current<this->max){
        this->contents[this->current++]=i;
    }
    else{
        throw logic_error("Stack is full");
    }
}
template<typename T>
void Stack<T>::pop(){
    if (this->current>0){
        this->current--;
    }
    else {
        throw logic_error("Stack is empty");
    }
}
template<typename T>
T Stack<T>::top()const{
    return this->contents[this->current-1];
}
template<typename T>
bool Stack<T>::isEmpty() const{
    return (this->current==0);
}
template<typename T>
bool Stack<T>::isFull() const{
    return (this->current==this->max);
}
template<typename T>
int Stack<T>::getCurrent(){
    return (this->current);
}