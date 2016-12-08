/*
	This class controlls all input from the player, to be
	sent to the other classes. This way, all input can be processed
	and checked before being sent to the game.
*/
#pragma once
#include <string>
#include <sstream>
using namespace std;

class Input
{
public:
	Input(string userin);
	~Input();
	string getVerb();
	string getSubject();


private:
	string verb;
	string subject;
};

