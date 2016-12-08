/*
	This file impliments the methods as initialized in Character.h
*/
#include "Input.h"



Input::Input(string userin)
{
	//Takes user input and creates a string stream to separate the words
	stringstream instream;
	instream << userin;

	//Lowercase verb from string stream
	string temp;
	instream >> temp;
	transform(temp.begin(), temp.end(), temp.begin(), tolower);
	verb = temp;

	//Lowercase subject from string stream
	instream >> temp;
	transform(temp.begin(), temp.end(), temp.begin(), tolower);
	subject = temp;

	//Above code sets verb and subject to the same input if the user only enters one word. This sets subject to a blank string to counteract
	if (subject == verb)
	{
		subject = "";
	}
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

void Input::checkAction()
{
	// checking if the verb entered by user is a synonym for one of the three available actions
	if (verb == "go" || verb == "travel" || verb == "move")
	{
		returnSubjectFromAction("go");
	}
	else if (verb == "take" || verb == "grab" || verb == "pick_up") 
	{
		returnSubjectFromAction("take");
	}
	else if (verb == "observe" || verb == "examine" || verb == "look_at" || verb == "inspect" || verb == "view")
	{
		returnSubjectFromAction("observe");
	}
	else
	{
		returnSubjectFromAction("fail");
	}
}

string Input::returnSubjectFromAction(string verb)
{
	if (verb == "go") 
	{

	}
	else if (verb == "take") 
	{

	}
	else if (verb == "observe") 
	{

	}
	else if (verb == "fail")
	{

	}
}
