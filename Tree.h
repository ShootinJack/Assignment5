#include <iostream>
#include <fstream>
#include "Student.h"
#pragma once
using namespace std;

template <class T>
class TreeNode {
public:
	TreeNode();
	TreeNode(T *k);
	~TreeNode();

	T *key;
	TreeNode<Student> *left;
	TreeNode<Student> *right;
};

template <class T>
class StudentBST
{
private:
	TreeNode<Student> *root;
	ofstream outFile;
public:
	StudentBST();
	~StudentBST();

	void insertNode(T *value);
	bool searchNode(int value);
	bool deleteNode(int value);
	bool isStudent();
	T* getStudent(int);

	TreeNode<Student>* getSuccessor(TreeNode<Student> *d);

	bool isEmpty();
	T getMax();
	T getMin();

	void recPrint(TreeNode<Student> *node);
	void recOutputToFile(TreeNode<Student> *node);
	void printTree();
	void outputToFile();
};

template <class T>
TreeNode<T>::TreeNode()
{
	left = NULL;
	right = NULL;
}

template <class T>
TreeNode<T>::TreeNode(T *k)
{
	left = NULL;
	right = NULL;
	key = k;
}

template <class T>
TreeNode<T>::~TreeNode()
{

}

template <class T>
StudentBST<T>::StudentBST()
{
	root = NULL; // Empty Tree
}

template <class T>
StudentBST<T>::~StudentBST()
{
	// iterate and delete, this is O(n)
}

template <class T>
void StudentBST<T>::recOutputToFile(TreeNode<Student> *node) // possible change template type of student
{
	if (node == root && node != NULL) {
		outFile.open("studentTable.txt", ios_base::app);
		outFile << node->key->getName() << "," << node->key->getId() << node->key->getStanding()
			<< "," << node->key->getMajor() << "," << node->key->getGpa() << " " << node->key->getAdvisorId() << endl;
		outFile.close();
		recOutputToFile(node->left);
		recOutputToFile(node->right);
	}
	else if (node != NULL) {
		recOutputToFile(node->left);
		outFile.open("studentTable.txt", ios_base::app);
		outFile << node->key->getName() << "," << node->key->getId() << node->key->getStanding()
			<< "," << node->key->getMajor() << "," << node->key->getGpa() << " " << node->key->getAdvisorId() << endl;
		outFile.close();
		recOutputToFile(node->right);
	}
}

template <class T>
void StudentBST<T>::recPrint(TreeNode<Student> *node) // possible change template type of student
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
void StudentBST<T>::printTree()
{
	if (isStudent()) {
		cout << "\nThere are currently no students.\n\n";
	}
	else {
		recPrint(root);
	}
}

template <class T>
void StudentBST<T>::outputToFile()
{
	outFile.open("studentTable.txt");
	outFile.close();
	recOutputToFile(root);
}

template <class T>
T StudentBST<T>::getMax()
{
	if (isEmpty()) {
		return NULL;
	}
	TreeNode<Student> *current = root; // change template class to student later
	while (current->right != NULL) {
		current = current->right;
	}
	return current->key;
}

template <class T>
T StudentBST<T>::getMin()
{
	if (isEmpty()) {
		return NULL;
	}
	TreeNode<Student> *current = root; // change template class to student later
	while (current->left != NULL) {
		current = current->left;
	}
	return current->key;
}

template <class T>
void StudentBST<T>::insertNode(T *value)
{
	TreeNode<Student> *node = new TreeNode<Student>(value); // change 
	if (isEmpty()) {
		//cout << "Tree is Empty\n" << node->key->getName() << " is the root\n";
		root = node;
	}
	else {
		TreeNode<Student> *current = root; // change template class to student later
		TreeNode<Student> *parent = NULL;

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
bool StudentBST<T>::searchNode(int value)
{
	if (isEmpty()) {
		return false;
	}
	else {
		TreeNode<Student> *current = root; // change
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
T* StudentBST<T>::getStudent(int value)
{
	if (isEmpty()) {
		return NULL;
	}
	else {
		TreeNode<Student> *current = root; // change
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
bool StudentBST<T>::deleteNode(int k)
{
	if (isEmpty()) {
		return false;
	}
	TreeNode<Student> *parent = NULL; //change to student
	TreeNode<Student> *current = root; // change to student
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
		TreeNode<Student> *successor = getSuccessor(current); // change
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
TreeNode<Student>* StudentBST<T>::getSuccessor(TreeNode<Student> *d) { // change to student
	TreeNode<Student> *sp = d;							// change all these, might need to make the student class student* 
	TreeNode<Student> *successor = d;
	TreeNode<Student> *current = d->right;

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
bool StudentBST<T>::isEmpty()
{
	return (root == NULL);
}

template <class T>
bool StudentBST<T>::isStudent()
{
	return (root->left == NULL && root->right == NULL);
}
