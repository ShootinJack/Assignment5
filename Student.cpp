#include "Student.h"



Student::Student()
{
}


Student::~Student()
{
}

void Student::printInformation()
{
	cout << "Student name: " << name << endl;
	cout << "Student ID: " << id << endl;
	cout << "Student Standing: " << standing << endl;
	cout << "Student Major: " << major << endl;
	cout << "Student GPA: " << gpa << endl;
	cout << "Student Advisor ID: " << advisorId << endl;
}

void Student::setMajor(string m)
{
	major = m;
}

void Student::setGpa(double g)
{
	gpa = g;
}

void Student::setAdvisorId(int a)
{
	advisorId = a;
}

string Student::getMajor()
{
	return major;
}

double Student::getGpa()
{
	return gpa;
}

int Student::getAdvisorId()
{
	return advisorId;
}

bool Student::operator<(Student* student2) // overloaded comparison operator for tree comparisons
{
	return(id < student2->getId());
}

bool Student::operator>(Student* student2) // overloaded comparison operator for tree comparisons
{
	return(id > student2->getId());
}

ostream& operator<<(ostream& os, Student* s)	// overloaded print operator for printing information
{
	os << "Student Name: " << s->getName() << "\nStudent ID: " << s->getId() << "\nStanding: " << s->getStanding() 
		<< "\nMajor: " << s->getMajor() << "\nGPA: " << s->getGpa() << "\nAdvisor: " << s->getAdvisorId() << endl << endl;
	return os;
}