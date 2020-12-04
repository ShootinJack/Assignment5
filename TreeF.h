#include <iostream>
#include <fstream>
#include "Faculty.h"
#pragma once
using namespace std;

template <class T>
class TreeNodeF {
public:
	TreeNodeF();
	TreeNodeF(T *k);
	~TreeNodeF();

	T *key;
	TreeNodeF<Faculty> *left;
	TreeNodeF<Faculty> *right;
};

template <class T>
class FacultyBST
{
private:
	TreeNodeF<Faculty> *root;
	ofstream outFile;
public:
	FacultyBST();
	~FacultyBST();

	void insertNode(T *value);
	bool searchNode(int value);
	bool deleteNode(int value);
	bool isFaculty();
	T* getFaculty(int);

	TreeNodeF<Faculty>* getSuccessor(TreeNodeF<Faculty> *d);

	bool isEmpty();
	T getMax();
	T getMin();

	void recPrint(TreeNodeF<Faculty> *node);
	void recOutputToFile(TreeNodeF<Faculty> *node);
	void printTree();
	void printAdvisors();
	void recPrintAdvisors(TreeNodeF<Faculty> *node);
	void outputToFile();
};

template <class T>
TreeNodeF<T>::TreeNodeF()
{
	left = NULL;
	right = NULL;
}

template <class T>
TreeNodeF<T>::TreeNodeF(T *k)
{
	left = NULL;
	right = NULL;
	key = k;
}

template <class T>
TreeNodeF<T>::~TreeNodeF()
{

}

template <class T>
FacultyBST<T>::FacultyBST()
{
	root = NULL; // Empty Tree
}

template <class T>
FacultyBST<T>::~FacultyBST()
{
	// iterate and delete, this is O(n)
}

template <class T>
void FacultyBST<T>::recOutputToFile(TreeNodeF<Faculty> *node) // possible change template type of student
{
	if (node == root && node != NULL) {
		outFile.open("facultyTable.txt", ios_base::app);
		outFile << node->key->getName() << "," << node->key->getId() << node->key->getStanding() << "," // removed space after id
			<< node->key->getDepartment() << ", " << node->key->getNumOfStuds() << endl;
		outFile.close();
		recOutputToFile(node->left);
		recOutputToFile(node->right);
	}
	else if (node != NULL) {
		recOutputToFile(node->left);
		outFile.open("facultyTable.txt", ios_base::app);
		outFile << node->key->getName() << "," << node->key->getId() << node->key->getStanding() << "," // removed space after id
			<< node->key->getDepartment() << ", " << node->key->getNumOfStuds() << endl;
		if (node->key->getNumOfStuds() != 0) {
			for (int i = 0; i < node->key->getNumOfStuds(); ++i) {
				outFile << node->key->getList()[i] << endl;
			}
		}
		outFile.close();
		recOutputToFile(node->right);
	}
}

template <class T>
void FacultyBST<T>::recPrint(TreeNodeF<Faculty> *node) // possible change template type of student
{
	if (node != NULL) {
		recPrint(node->left);
		if (node->key->getId() != root->key->getId()) {
			cout << node->key << endl;
		}
		recPrint(node->right);
	}
}

template <class T>
void FacultyBST<T>::recPrintAdvisors(TreeNodeF<Faculty> *node) // possible change template type of student
{
	if (node != NULL) {
		recPrintAdvisors(node->left);
		if (node->key->getId() != root->key->getId()) {
			cout << node->key->getName() << ": " << node->key->getId() << endl;
		}
		recPrintAdvisors(node->right);
	}
}

template <class T>
void FacultyBST<T>::printTree()
{
	if (isFaculty()) {
		cout << "There are currently no faculty.\n";
	}
	else {
		recPrint(root);
	}
}

template <class T>
void FacultyBST<T>::printAdvisors()
{
	recPrintAdvisors(root);
}

template <class T>
void FacultyBST<T>::outputToFile()
{
	outFile.open("facultyTable.txt");
	outFile.close();
	recOutputToFile(root);
}

template <class T>
T FacultyBST<T>::getMax()
{
	if (isEmpty()) {
		return NULL;
	}
	TreeNodeF<Faculty> *current = root; // change template class to student later
	while (current->right != NULL) {
		current = current->right;
	}
	return current->key;
}

template <class T>
T FacultyBST<T>::getMin()
{
	if (isEmpty()) {
		return NULL;
	}
	TreeNodeF<Faculty> *current = root; // change template class to student later
	while (current->left != NULL) {
		current = current->left;
	}
	return current->key;
}

template <class T>
void FacultyBST<T>::insertNode(T *value)
{
	TreeNodeF<Faculty> *node = new TreeNodeF<Faculty>(value); // change 
	if (isEmpty()) {
		root = node;
	}
	else {
		TreeNodeF<Faculty> *current = root; // change template class to student later
		TreeNodeF<Faculty> *parent = NULL;

		while (true) {
			parent = current;

			if (node->key->getId() < current->key->getId()) {
				current = current->left;
				if (current == NULL) {
					parent->left = node;
					break;
				}
			}
			else {
				current = current->right;
				if (current == NULL) {
					parent->right = node;
					break;
				}
			}
		}
	}
}

template <class T>
bool FacultyBST<T>::searchNode(int value)
{
	if (isEmpty()) {
		return false;
	}
	else {
		TreeNodeF<Faculty> *current = root; // change
		while (current->key->getId() != value) {
			if (value < current->key->getId()) {
				current = current->left;
			}
			else {
				current = current->right;
			}
			if (current == NULL) {
				return false;
			}
		}
	}
	return true;
}

template <class T>
T* FacultyBST<T>::getFaculty(int value)
{
	if (isEmpty()) {
		return NULL;
	}
	else {
		TreeNodeF<Faculty> *current = root; // change
		while (current->key->getId() != value) {
			if (value < current->key->getId()) {
				current = current->left;
			}
			else {
				current = current->right;
			}
			if (current == NULL) {
				return NULL;
			}
		}
		return current->key;
	}
}

template <class T>
bool FacultyBST<T>::deleteNode(int k)
{
	if (isEmpty()) {
		return false;
	}
	TreeNodeF<Faculty> *parent = NULL; //change to student
	TreeNodeF<Faculty> *current = root; // change to student
	bool isLeftNode = true;

	while (current->key->getId() != k) {
		parent = current;

		if (k < current->key->getId()) {
			isLeftNode = true;
			current = current->left;
		}
		else {
			isLeftNode = false;
			current = current->right;
		}

		if (current == NULL) {
			return false;
		}
	}
	// We have found which node to delete^^

	if (current->left == NULL && current->right == NULL) {
		if (current == root) {
			root = NULL;
		}
		else if (isLeftNode) {
			parent->left = NULL;
		}
		else {
			parent->right = NULL;
		}
	}
	else if (current->right == NULL) {
		if (current == root) {
			root = current->left;
		}
		else if (isLeftNode) {
			parent->left = current->left;
		}
		else {
			parent->right = current->right;
		}
	}
	else if (current->left == NULL) {
		if (current == root) {
			root = current->right;
		}
		else if (isLeftNode) {
			parent->left = current->right;
		}
		else {
			parent->right = current->right;
		}
	}
	else {
		TreeNodeF<Faculty> *successor = getSuccessor(current); // change
		if (current == root) {
			root = successor;
		}
		else if (isLeftNode) {
			parent->left = successor;
		}
		else {
			parent->right = successor;
		}
		successor->left = current->left;
	}
	return true;
}

template <class T>
TreeNodeF<Faculty>* FacultyBST<T>::getSuccessor(TreeNodeF<Faculty> *d) { // change to student
	TreeNodeF<Faculty> *sp = d;							// change all these, might need to make the student class student* 
	TreeNodeF<Faculty> *successor = d;
	TreeNodeF<Faculty> *current = d->right;

	while (current != NULL) {
		sp = successor;
		successor = current;
		current = current->left;
	}

	if (successor != d->right) {
		sp->left = successor->right;
		successor->right = d->right;
	}
	return successor;
}

template <class T>
bool FacultyBST<T>::isEmpty()
{
	return (root == NULL);
}

template <class T>
bool FacultyBST<T>::isFaculty()
{
	return (root->left == NULL && root->right == NULL);
}