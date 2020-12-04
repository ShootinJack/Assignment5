#include <iostream>
#pragma once
using namespace std;

template <class T> // This is a template class allowing the stack to take any data type
class GenStack
{
private:
	int top, mSize;
	T *myArray, *tempArray;
public:
	GenStack();
	GenStack(int);
	~GenStack();

	void push(T);
	T pop();
	T peek();
	void resizeStack();
	void removeFront();
	void print();

	bool isFull();
	bool isEmpty();
	int getSize();
};

template <class T>
GenStack<T>::GenStack() // Default constructor with default size
{
	myArray = new T[5];
	tempArray = new T[5];
	mSize = 5;
	top = -1;
}

template <class T>
GenStack<T>::GenStack(int maxSize) // Overloaded constructor for custom size
{
	myArray = new T[maxSize];
	tempArray = new T[maxSize];
	mSize = maxSize;
	top = -1;
}

template <class T>
GenStack<T>::~GenStack() // Destructor deleting Dynamic Arrays
{
	delete[] myArray;
	delete[] tempArray;
}

template <class T>
void GenStack<T>::push(T data) // Pushes data to the top of the stack
{
	if (top == 4) {
		removeFront();
		myArray[++top] = data;
	}
	else {
		top++;
		myArray[top] = data;
	}
}

template <class T>
T GenStack<T>::pop() // This function returns the top item and removes from the stack
{
	return myArray[top--];
}

template <class T>
T GenStack<T>::peek() // This function returns the top item
{
	return myArray[top];
}

template <class T>
bool GenStack<T>::isEmpty() // This functions checks if the stack is empty
{
	return (top == -1);
}

template <class T>
bool GenStack<T>::isFull() // This function checks if the stack is full
{
	return (top == mSize - 1);
}

template <class T>
int GenStack<T>::getSize() // This function tells you how many pieces of data are in the stack
{
	return (top + 1);
}

template <class T>
void GenStack<T>::resizeStack() // This function dynamically increases the size of the stack, doubling it in size if it fills up
{
	int oldSize = mSize;
	delete tempArray;
	tempArray = new T[oldSize];
	mSize = mSize * 2;
	for (int i = 0; i < oldSize; ++i) {
		tempArray[i] = myArray[i];
	}
	delete myArray;
	myArray = new T[mSize];
	for (int i = 0; i < oldSize; ++i) {
		myArray[i] = tempArray[i];
	}
}

template <class T>
void GenStack<T>::removeFront()
{
	delete[] tempArray;
	tempArray = new T[mSize];
	int count = 0;
	for (int i = 0; i < mSize; ++i) {
		if (i != 0) {
			tempArray[count++] = myArray[i];
		}
	}
	delete[] myArray;
	myArray = new T[mSize];
	for (int i = 0; i < (mSize - 1); ++i) {
		myArray[i] = tempArray[i];
	}
	--top;
}

template <class T>
void GenStack<T>::print() {
	cout << "Back: ";
	for (int i = 0; i < mSize; ++i) {
		cout << myArray[i] << " ";
	}
	cout << ": Front\n";
}


