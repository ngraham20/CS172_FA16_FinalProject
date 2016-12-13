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
		cout << "|     --------------------------------------   |" << endl;
		cout << "|     | WELCOME TO THE JACKSONBURG MANSION |   |" << endl;
		cout << "|     --------------------------------------   |" << endl;
		cout << "|           | Type commands to play |          |" << endl;
		cout << "|                  | play |                    |" << endl;
		cout << "|                  | load |                    |" << endl;
		cout << "|                  | quit |                    |" << endl;
		cout << "--                                            --" << endl;
 		cout << ">>";

		cin >> input;
		
		bool quit = false;

		if (input == "play")
		{
			// begins a new game
			Game game;
		}
		else if (input == "load")
		{
			cout << "Which game do you want to load?" << endl;
			cout << "--------" << endl;
			cout << "|  G1  |" << endl;
			cout << "--------" << endl;
			cout << "|  G2  |" << endl;
			cout << "--------" << endl;
			cout << "|  G3  |" << endl;
			cout << "--------" << endl;
			cout << ">>";
			cin >> input;
			if (input == "slot 1" || input == "1")
			{
				Game game(1);
			}
			else if (input == "slot 2" || input == "2")
			{
				Game game(2);
			}
			else if (input == "slot 3" || input == "3")
			{
				Game game(3);
			}
			else if (input == "back")
			{

			}
			else
				cout << "Invalid Input. Please try again." << endl;
		}
		else if (input == "clear")
		{
			Game::fullTempClear();
		}

	} while (input != "quit");

	return 0;
}