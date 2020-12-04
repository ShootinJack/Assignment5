#include "Undo.h"

/*
It only has standard sets and gets.
*/

Undo::Undo()
{
}


Undo::~Undo()
{
}

void Undo::setId(int in)
{
	id = in;
}

void Undo::setAdvisorId(int in)
{
	advisorId = in;
}

void Undo::setType(int in)
{
	type = in;
}

void Undo::setList(int *in)
{
	list = in;
}

void Undo::setSize(int in)
{
	size = in;
}

void Undo::setGpa(double in)
{
	gpa = in;
}

void Undo::setName(string in)
{
	name = in;
}

void Undo::setStanding(string in)
{
	standing = in;
}

void Undo::setStr2(string in)
{
	str2 = in;
}

int Undo::getId()
{
	return id;
}

int Undo::getAdvisorId()
{
	return advisorId;
}

int Undo::getType()
{
	return type;
}

int* Undo::getList()
{
	return list;
}

int Undo::getSize()
{
	return size;
}

double Undo::getGpa()
{
	return gpa;
}

string Undo::getName()
{
	return name;
}

string Undo::getStanding()
{
	return standing;
}
string Undo::getStr2()
{
	return str2;
}
