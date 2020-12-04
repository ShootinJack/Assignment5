#include "Personnel.h"
#pragma once

/*
The student class has its own data and has its operators overloaded for printing and comparing.

*/
class Student :
	public Personnel
{
private:
	string major;
	double gpa;
	int advisorId;
public:
	Student();
	~Student();
	void printInformation();
	void setMajor(string);
	void setGpa(double);
	void setAdvisorId(int);
	string getMajor();
	double getGpa();
	int getAdvisorId();
	bool operator<(Student*);
	bool operator>(Student*);
	friend ostream& operator<<(ostream&, Student*);
};

