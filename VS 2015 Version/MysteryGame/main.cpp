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
	string language;
	cout << "english/spanish\n>>";
	// cin >> language;
	cout << "Default language selected: English." << endl;
	language = "english";

	bool displayMenu = true;

	if (language == "english")
	{
		string input;
		do
		{
			if (displayMenu)
			{
				// basic game menu to play game
				cout << "------------------------------------------------" << endl;
				cout << "|     --------------------------------------   |" << endl;
				cout << "|     | WELCOME TO THE JACKSONBURG MANSION |   |" << endl;
				cout << "|     --------------------------------------   |" << endl;
				cout << "|           | Type commands to play |          |" << endl;
				cout << "|              | instructions |                |" << endl;
				cout << "|                  | play |                    |" << endl;
				cout << "|                  | load |                    |" << endl;
				cout << "|                  | quit |                    |" << endl;
				cout << "--                                            --" << endl;
				
				displayMenu = false;
			}

			cout << ">>";
			cin >> input;

			bool quit = false;

			if (input == "play")
			{
				Game game(language);
				displayMenu = true;
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
					Game game(language, 1);
					displayMenu = true;
				}
				else if (input == "slot 2" || input == "2")
				{
					Game game(language, 2);
					displayMenu = true;
				}
				else if (input == "slot 3" || input == "3")
				{
					Game game(language, 3);
					displayMenu = true;
				}
				else if (input == "back")
				{
					displayMenu = true;
				}
				else
					cout << "Invalid Input. Please try again." << endl;
			}
			else if (input == "clear")
			{
				Game::fullTempClear();
				displayMenu = true;
			}
			else if (input == "instructions")
			{
				cout << "------------------------------------------------------------------------" << endl;
				cout << "  -> All commands should be phrased with verbs and direct objects only. " << endl;
				cout << "  -> For verbs that require more than one word, such as 'pick up,'      " << endl;
				cout << "     combine the two words together: 'pick_up.'                          " << endl;
				cout << "  -> To move, type a command, then a cardinal direction or up or down.  " << endl;
				cout << "  -> This game is designed to be interactive and exploratory. Thus,     " << endl;
				cout << "     try different verb/direct object combinations to create commands!  " << endl;
				cout << "                                                                        " << endl;
				cout << "  -> Example commands: walk north, pick_up torch                        " << endl;
				cout << "  -> If at any time, you would like to quit, type \"quit\"              " << endl;
				cout << "  -> You may save your progress by typing \"save,\" then following the  " << endl;
				cout << "     prompted instructions.                                             " << endl;
				cout << "------------------------------------------------------------------------" << endl;
			}

		} while (input != "quit");
	}
	else if (language == "spanish")
	{
		string input;
		do
		{
			// basic game menu to play game
			cout << "------------------------------------------------" << endl;
			cout << "|     --------------------------------------   |" << endl;
			cout << "|    | Bienvenido al Mansion de Jacksonburg!|  |" << endl;
			cout << "|     --------------------------------------   |" << endl;
			cout << "|        | Escribir a machina para jugar |     |" << endl;
			cout << "|                 | jugar  |                   |" << endl;
			cout << "|                 | cargar |                   |" << endl;
			cout << "|                 | dejar  |                   |" << endl;
			cout << "--                                            --" << endl;
			cout << ">>";

			cin >> input;

			bool quit = false;

			if (input == "jugar")
			{
				Game game(language);
			}
			else if (input == "cargar")
			{
				cout << "Cual juguete quiere cargar?" << endl;
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
					Game game(language, 1);
				}
				else if (input == "slot 2" || input == "2")
				{
					Game game(language, 2);
				}
				else if (input == "slot 3" || input == "3")
				{
					Game game(language, 3);
				}
				else if (input == "back")
				{

				}
				else
					cout << "Incorrecto. Trate otra vez por favor." << endl;
			}
			else if (input == "clear")
			{
				Game::fullTempClear();
			}

		} while (input != "dejar");
	}

	return 0;
}