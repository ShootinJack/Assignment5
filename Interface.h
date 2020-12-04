#include <iostream>
#include <fstream>
#include <string>
#include "Tree.h"
#include "TreeF.h"
#include "Faculty.h"
#include "Student.h"
#include "Undo.h"
#include <stdlib.h> 
#include <time.h>
#pragma once
/*
This is the interface class
The interface handles all of the heavy lifting of the database
It has all functions that handle each option
*/
class Interface
{
private:
	StudentBST<Student> studentTree;
	FacultyBST<Faculty> facultyTree;
	GenStack<Undo> rollBackList;
	Student *rollStud;
	Faculty *rollFac;
	ifstream inFile;
	ofstream outFile;
	string firstName, lastName, name, standing, major, department;
	double gpa;
	int advisorId, id, input, numOfStuds, studNum, stdCount, facCount, rollNum;
	bool rollCheck;
public:
	Interface();
	~Interface();
	void openFileS();
	void openFileF();
	void printMenu();
	void setInput();
	void newStudent();
	void newFaculty();
	void printStudents();
	void printFaculty();
	void findStudent();
	void findFaculty();
	void deleteStudent();
	void deleteFaculty();
	void displayAdvisor();
	void displayAdvisees();
	void changeStudentsAdvisor();
	void removeAdvisee();
	void rollBack();
};

