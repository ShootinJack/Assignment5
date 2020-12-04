#include "Faculty.h"



Faculty::Faculty()
{
	numOfStuds = 0;
	students = new int[25];
	tempList = new int[25];
}


Faculty::~Faculty()
{
	delete[] students;
	delete[] tempList;
}

void Faculty::setDepartment(string d)
{
	department = d;
}

void Faculty::addStudent(int n)
{
	students[numOfStuds++] = n;
}

void Faculty::removeStudent(int n)
{
	int count = 0;
	int *tList = new int[numOfStuds];
	for (int i = 0; i < numOfStuds;++i) {
		if (students[i] != n) {
			tList[count] = students[i];
			count++;
		}
	}
	numOfStuds--;
	delete students;
	students = new int[25];
	for (int i = 0; i < numOfStuds; ++i) {
		students[i] = tList[i];
	}
	delete tList;
}

void Faculty::setNumOfStuds(int n)
{
	numOfStuds = n;
}

int Faculty::getNumOfStuds()
{
	return numOfStuds;
}

string Faculty::getDepartment()
{
	return department;
}

int* Faculty::getList()
{
	return students;
}

bool Faculty::operator<(Faculty* faculty2) // overloaded operator for tree comparisons
{
	return(id < faculty2->getId());
}

bool Faculty::operator>(Faculty* faculty2) // overloaded operator for tree comparisons
{
	return(id > faculty2->getId());
}

ostream& operator<<(ostream& os, Faculty* s) // overloaded operator for printing class information
{
	os << "Faculty Name: " << s->getName() << "\nFaculty ID: " << s->getId() << "\nLevel: " << s->getStanding()
		<< "\nDepartment: " << s->getDepartment() << endl << endl;
	return os;
}
