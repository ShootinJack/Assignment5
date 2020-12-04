#include "Personnel.h"



Personnel::Personnel()
{
}

Personnel::~Personnel()
{

}

void Personnel::setId(int in)
{
	id = in;
}

void Personnel::setName(string n)
{
	name = n;
}

void Personnel::setStanding(string s)
{
	standing = s;
}

int Personnel::getId()
{
	return id;
}

string Personnel::getName()
{
	return name;
}

string Personnel::getStanding()
{
	return standing;
}