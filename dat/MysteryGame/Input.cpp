/*
	This file impliments the methods as initialized in Character.h
*/
#include "Input.h"



Input::Input(string userin)
{
	stringstream instream;
	instream << userin;

	string temp;
	instream >> temp;
	transform(temp.begin(), temp.end(), temp.begin(), tolower);
	verb = temp;

	instream >> temp;
	transform(temp.begin(), temp.end(), temp.begin(), tolower);
	subject = temp;
}


Input::~Input()
{
}

string Input::getVerb()
{
	return verb;
}

string Input::getSubject()
{
	return subject;
}
