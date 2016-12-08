/*
	This file impliments the methods as initialized in Character.h
*/
#include "Input.h"



Input::Input(string userin)
{
	stringstream instream;
	instream << userin;

	instream >> verb;
	instream >> subject;
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
