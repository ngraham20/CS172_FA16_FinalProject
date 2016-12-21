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

	//Lowercase directObject from string stream
	instream >> temp;
	if (temp == "the" || temp == "a" || temp == "an")
	{
		instream >> temp;
	}
	transform(temp.begin(), temp.end(), temp.begin(), tolower);
	directObject = temp;

	//Above code sets verb and directObject to the same input if the user only enters one word. This sets directObject to a blank string to counteract
	if (directObject == verb)
	{
		directObject = "";
	}
}


Input::~Input()
{
}

string Input::getVerb()
{
	return verb;
}

string Input::getDirectObject()
{
	return directObject;
}

string Input::checkAction()
{
	string action;
	// checking if the verb entered by user is a synonym for one of the three available actions
	if (verb == "go" || verb == "travel" || verb == "move" || verb == "proceed" || verb == "advance" || verb == "walk")
	{
		action = returnActionPhraseFromDirectObject("go");
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
		return returnActionPhraseFromDirectObject("unlock");
	}
	else if (verb == "light")
	{
		// Game class must handle the lighting of the item
		return "light";
	}
	else if (verb == "equip")
	{
		return "equip";
	}
	else
	{
		return "fail";
	}
	return action;
}

// Calculates the correct action to return based on the verb and directObject
string Input::returnActionPhraseFromDirectObject(string verb)
{
	if (verb == "go")
	{
		if (directObject == "north") { return "goNorth"; }
		else if (directObject == "south") { return "goSouth"; }
		else if (directObject == "east") { return "goEast"; }
		else if (directObject == "west") { return "goWest"; }
		else if (directObject == "up") { return "goUp"; }
		else if (directObject == "down") { return "goDown"; }
		else { return "fail"; }
	}
	else if (verb == "unlock")
	{
		if (directObject == "north") { return "unlockNorth"; }
		else if (directObject == "south") { return "unlockSouth"; }
		else if (directObject == "east") { return "unlockEast"; }
		else if (directObject == "west") { return "unlockWest"; }
		else if (directObject == "up") { return "unlockUp"; }
		else if (directObject == "down") { return "unlockDown"; }
		else { return "fail";  }
	}
	return "";
}
