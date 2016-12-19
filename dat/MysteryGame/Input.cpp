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
	if (temp == "the" || temp == "a" || temp == "an")
	{
		instream >> temp;
	}
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

string Input::checkAction()
{
	string action;
	// checking if the verb entered by user is a synonym for one of the three available actions
	if (verb == "go" || verb == "travel" || verb == "move" || verb == "proceed" || verb == "advance" || verb == "walk")
	{
		action = returnSubjectFromAction("go");
	}
	else if (verb == "inventory" || verb == "items")
	{
		return "inventory";
	}
	else if (verb == "take" || verb == "grab" || verb == "pick_up") 
	{
		return "takeItem";
	}
	else if (verb == "observe" || verb == "examine" || verb == "look_at" || verb == "inspect" || verb == "view")
	{
		return "observeItem";
	}
	else if (verb == "drop" || verb == "leave" || verb == "throw" || verb == "give" || verb == "discard")
	{
		return "dropItem";
	}
	else if (verb == "quit" || verb == "exit")
	{
		return "quit";
	}
	else if (verb == "help" || verb == "instructions")
	{
		return "help";
	}
	else if (verb == "room" || verb == "describe")
	{
		return "room";
	}
	else if (verb == "unlock")
	{
		return returnSubjectFromAction("unlock");
	}
	else
	{
		return "fail";
	}
	return action;
}

// Calculates the correct action to return based on the verb and subject
string Input::returnSubjectFromAction(string verb)
{
	if (verb == "go")
	{
		if (subject == "north") { return "goNorth"; }
		else if (subject == "south") { return "goSouth"; }
		else if (subject == "east") { return "goEast"; }
		else if (subject == "west") { return "goWest"; }
		else if (subject == "up") { return "goUp"; }
		else if (subject == "down") { return "goDown"; }
		else { return "fail"; }
	}
	else if (verb == "unlock")
	{
		if (subject == "north") { return "unlockNorth"; }
		else if (subject == "south") { return "unlockSouth"; }
		else if (subject == "east") { return "unlockEast"; }
		else if (subject == "west") { return "unlockWest"; }
		else if (subject == "up") { return "unlockUp"; }
		else if (subject == "down") { return "unlockDown"; }
		else { return "fail";  }
	}
	return "";
}
