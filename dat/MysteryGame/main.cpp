/*
	This file runs the menu before the game, and
	begins the game upon request from the player.
	After the game begins, however, little is done
	in this file.
*/
#include <iostream>
#include "Coordinates.h"
#include "Game.h"
#include "Input.h"
#include "Room.h"
using namespace std;

int main()
{
	string input;
	do
	{
		// basic game menu to play game
		cout << "------------------------------------------------" << endl;
		cout << "        WELCOME TO THE JACKSONBURG MANSION      " << endl;
		cout << "------------------------------------------------" << endl;
		cout << "|play|" << endl;
		cout << "|load|" << endl;
		cout << "|quit|" << endl;
		cout << ">>";

		cin >> input;
		bool quit = false;

		if (input == "play")
		{
			// begins a new game
			Game game;

			// exits the game
			return 0;
		}
		else if (input == "load")
		{
			cout << "Which game do you want to load?" << endl;
			cout << "--------" << endl;
			cout << "|slot 1|" << endl;
			cout << "--------" << endl;
			cout << "|slot 2|" << endl;
			cout << "--------" << endl;
			cout << "|slot 3|" << endl;
			cout << "--------" << endl;
			cout << ">>";
			cin >> input;
			if (input == "slot 1" || input == "1")
			{
				Game game("slot 1");

				// exits the game
				return 0;
			}
			else if (input == "slot 2" || input == "2")
			{
				Game game("slot 2");

				// exits the game
				return 0;
			}
			else if (input == "slot 3" || input == "3")
			{
				Game game("slot 3");

				// exits the game
				return 0;
			}
			else if (input == "back")
			{

			}
			else
				cout << "Invalid Input. Please try again." << endl;
		}
		else if (input == "clear")
			Game::fullTempClear();
	} while (input != "quit");

	return 0;
}