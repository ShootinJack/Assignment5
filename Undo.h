#include <iostream>
#include <string>
using namespace std;
#pragma once
/*
This class is the undo class, it stores all the information about the students or faculty members being created or deleted.
*/
class Undo
{
private:
	int id, advisorId, type, *list, size;
	double gpa;
	string name, standing, str2;
public:
	Undo();
	~Undo();
	void setId(int);
	void setAdvisorId(int);
	void setType(int);
	void setList(int*);
	void setSize(int);
	void setGpa(double);
	void setName(string);
	void setStanding(string);
	void setStr2(string);
	int getId();
	int getAdvisorId();
	int getType();
	int* getList();
	int getSize();
	double getGpa();
	string getName();
	string getStanding();
	string getStr2();
};

