/*
	This class controlls all input from the player, to be
	sent to the other classes. This way, all input can be processed
	and checked before being sent to the game.
*/
#pragma once
#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>
using namespace std;

class Input
{
public:
	Input(string userin);
	~Input();
	string getVerb();
	string getDirectObject();
	string checkAction();
	string returnActionPhraseFromDirectObject(string verb);

private:
	string verb;
	string directObject;
};

