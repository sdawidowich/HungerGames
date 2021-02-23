#include <iostream>
#include <random>
#include "hungergames.h"

int randNum(int lower, int upper) {
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(lower, upper); // define the range

	//generates a random number
	return distr(gen);
}

void clear_cin() {
	//Fixes bug that creates a never ending loop when a non-int is entered.
	std::cin.clear();
	std::cin.ignore(100, '\n');
}

Game::Game() 
	: time(0), day(1), option_tribute_list("Realistic Random"), option_sim_type("Realistic")
{	
	//generates generic random tribute list and stores it in the tribute list variable. 
	//The first for loop generates 12 boys, 1 for each district and 12 girls, 1 for each district. The ages, heights, and weights are random. 
	for (int i = 0; i < 12; i++) {
		Tribute tribute("Henry Mitkins", "Male", "Alive", i + 1, i + 1, randNum(12, 18), randNum(60, 77), randNum(100, 250), 0, 100);
		Game::tribute_list.emplace_back(tribute);
	}

	for (int i = 0; i < 12; i++) {
		Tribute tribute("Rose Merryweather", "Female", "Alive", i + 13, i + 1, randNum(12, 18), randNum(56, 72), randNum(80, 200), 0, 100);
		Game::tribute_list.emplace_back(tribute);
	}
	//Creates list of events
	set_events();
	//Calls the start_game function.
	start_game();
}


//Getters and setters for the class variables.
std::vector<Tribute> Game::get_tribute_list()
{
	return Game::tribute_list;
}

std::vector<Tribute> Game::get_alliance_list()
{
	return Game::alliance_list;
}

int Game::get_time()
{
	return Game::time;
}

int Game::get_day()
{
	return Game::day;
}

std::vector<Event> Game::get_event_list()
{
	return Game::event_list;
}

void Game::set_time(int new_time)
{
	Game::time = new_time;
}

void Game::set_day(int new_day)
{
	Game::day = new_day;
}

//Creates a list of events
void Game::set_events() {
	Event event(1, "Alive", "{Tribute1} ran to the cornucopia and grabbed a bow and arrow.", "Cornucopia");
	Game::event_list.emplace_back(event);

	event.change_event(1, "Death", "{Tribute1} stepped off the pedestal too early.", "Cornucopia");
	Game::event_list.emplace_back(event);

	event.change_event(1, "Alive", "{Tribute1} found a spear in the cornucopia.", "Cornucopia");
	Game::event_list.emplace_back(event);

	event.change_event(1, "Alive", "{Tribute1} fled into the woods.", "Cornucopia");
	Game::event_list.emplace_back(event);

	event.change_event(2, "Death", "{Tribute1} got stabbed by {Tribute2} and died.", "Cornucopia");
	Game::event_list.emplace_back(event);

	event.change_event(1, "Alive", "{Tribute1} grabbed a backpack full of supplies.", "Cornucopia");
	Game::event_list.emplace_back(event);

	event.change_event(1, "Alive", "{Tribute1} narrowly avoided a bow shot.", "Cornucopia");
	Game::event_list.emplace_back(event);

	event.change_event(1, "Alive", "{Tribute1} ran away from the cornucopia.", "Cornucopia");
	Game::event_list.emplace_back(event);

	event.change_event(1, "Alive", "{Tribute1} blew up.", "Cornucopia");
	Game::event_list.emplace_back(event);

	event.change_event(2, "Death", "{Tribute1} was beaten to dead by {Tribute2}.", "Cornucopia");
	Game::event_list.emplace_back(event);

	event.change_event(1, "Alive", "{Tribute1} found a sword at the cornucopia.", "Cornucopia");
	Game::event_list.emplace_back(event);

	event.change_event(1, "Alive", "{Tribute1} found a backpack full of food.", "Cornucopia");
	Game::event_list.emplace_back(event);

	event.change_event(2, "Death", "{Tribute1} was shot with arrow by {Tribute2}", "Normal");
	Game::event_list.emplace_back(event);
}

//Displays a text menu and gets user command input
void Game::start_game()
{
	while (true)
	{
		int command;
		std::cout << "<<========== Menu ==========>>" << std::endl;
		std::cout << "1. Create Game\n2. Load Game\n3. Quit\n" << std::endl;
		std::cout << ">> ";
		std::cin >> command;
		system("cls");
		if (command == 1) {
			CreateGame();
		}
		else if (command == 2) {
			std::cout << "<<======= Load Game =======>>" << std::endl;
		}
		else if (command == 3) {
			std::cout << "<<======= Quitting Game... =======>>\n" << std::endl;
			break;
		}
		else {
			system("cls");
			std::cout << "<<====== Invalid Command ======>>" << std::endl;
			clear_cin();
		}
	}
}

//Called when the user selects "create game" in the above start_game function. Allows the user to change game options.
void Game::CreateGame()
{
	while (true)
	{
		std::cout << "<<======= Create Game =======>>\n" << std::endl;
		std::cout << "<<== Game Options ==>>" << std::endl;
		std::cout << "1. Tribute List Creation = " << Game::option_tribute_list << "\n2. Simulation Type = " << Game::option_sim_type << "\n3. Continue\n4. Cancel" << std::endl;
		std::cout << "Type the option number you would like to edit or enter 3 to continue." << std::endl;
		std::cout << ">> ";
		int option;
		std::cin >> option;
		if (option == 1) {
			system("cls");
			TributeCreationOption();
		}
		else if (option == 2) {
			system("cls");
			SimTypeOption();
		}
		else if (option == 3) {
			sim_day();
			break;
		}
		else if (option == 4) {
			system("cls");
			break;
		}
		else {
			system("cls");
			std::cout << "<<====== Invalid Command ======>>" << std::endl;
			clear_cin();
		}
	}
}

//Called when the user selects to edit the sim type option
void Game::SimTypeOption()
{
	std::cout << "<<== Simulation Type ==>>\n1. Realistic | 2. Random | 3. Chaotic Random\n" << std::endl;
	std::cout << ">> ";
	int option_edit;
	std::cin >> option_edit;
	if (option_edit == 1) {
		system("cls");
		Game::option_sim_type = "Realistic";
		std::cout << "<<== Set Simulation Type to Realistic ==>>\n" << std::endl;
	}
	else if (option_edit == 2) {
		system("cls");
		Game::option_sim_type = "Random";
		std::cout << "<<== Set Simulation Type to Random ==>>\n" << std::endl;
	}
	else if (option_edit == 3) {
		system("cls");
		Game::option_sim_type = "Chaotic Random";
		std::cout << "<<== Set Simulation Type to Chaotic Random ==>>\n" << std::endl;
	}
	else {
		system("cls");
		std::cout << "<<====== Invalid Command ======>>" << std::endl;
		clear_cin();
	}
}

//Called when the user selects to edit the tribute list creation. 
void Game::TributeCreationOption()
{
	std::cout << "<<== Tribute List Creation ==>>\n1. Realistic Random | 2. Chaotic Random | 3. Custom\n" << std::endl;
	std::cout << ">> ";
	int option_edit;
	std::cin >> option_edit;
	if (option_edit == 1) {
		system("cls");
		Game::option_tribute_list = "Realistic Random";
		std::cout << "<<== Set Tribute List Creation to Realistic Random ==>>\n" << std::endl;
	}
	else if (option_edit == 2) {
		system("cls");
		Game::option_tribute_list = "Chaotic Random";
		std::cout << "<<== Set Tribute List Creation to Chaotic Random ==>>\n" << std::endl;
	}
	else if (option_edit == 3) {
		std::cout << "Select the Tribute Roster you would like to use." << std::endl;
		int roster_selection;
		std::cin >> roster_selection;
		system("cls");
		Game::option_tribute_list = "Custom";
		std::cout << "<<== Set Tribute List Creation to Custom ==>>\n" << std::endl;
	}
	else {
		system("cls");
		std::cout << "<<====== Invalid Command ======>>" << std::endl;
		clear_cin();
	}
}

//Called to simulate the hunger games
void Game::sim_day()
{
	std::cout << "Welcome to the Hunger Games! May the odds be ever in your favor." << std::endl;
}