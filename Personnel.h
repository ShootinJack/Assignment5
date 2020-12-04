#include <iostream>
#include <string>
#pragma once
using namespace std;

/*
This is the parent class for students and faculty
*/
class Personnel {
protected:
	int id;
	string name, standing;
public:
	Personnel();
	~Personnel();
	void setId(int);
	void setName(string);
	void setStanding(string);
	int getId();
	string getName();
	string getStanding();
};

