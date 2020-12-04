#include "Personnel.h"
#include "GenStack.h"
#pragma once

/*
This is the personell class It has its own data.
Its operators are overloaded for comparisons
*/
class Faculty :
	public Personnel
{
private:
	string department;
	int numOfStuds, *students, *tempList;
public:
	Faculty();
	~Faculty();
	void setDepartment(string);
	void setNumOfStuds(int);
	void addStudent(int);
	void removeStudent(int);
	int getNumOfStuds();
	int* getList();
	string getDepartment();
	bool operator<(Faculty*);
	bool operator>(Faculty*);
	friend ostream& operator<<(ostream&, Faculty*);
};

