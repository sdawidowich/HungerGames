#include <iostream>
#include <random>
#include <fstream>
#include <filesystem>
#include "hungergames.h"

namespace fs = std::filesystem;

int randNum(int lower, int upper) {
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(lower, upper); // define the range

	//generates a random number
	return distr(gen);
}

void invalid_command() {
	system("cls");
	std::cout << "<<====== Invalid Command ======>>" << std::endl;

	//Fixes bug that creates a never ending loop when a non-int is entered.
	std::cin.clear();
	std::cin.ignore(100, '\n');
}

Game::Game() 
	: time(0), day(1), option_tribute_list("Realistic Random"), option_sim_type("Realistic") {	
	//Create generic random tribute list and stores it in the tribute list variable. 
	create_tribute_list();
	//Creates list of events
	set_events();
	//Calls the start_game function.
	start_game();
}


//Getters and setters for the class variables.
std::vector<Tribute> Game::get_tribute_list() {
	return Game::tribute_list;
}

std::vector<Tribute> Game::get_alliance_list() {
	return Game::alliance_list;
}

int Game::get_time() {
	return Game::time;
}

int Game::get_day() {
	return Game::day;
}

std::vector<Event> Game::get_event_list() {
	return Game::event_list;
}

void Game::set_time(int new_time) {
	Game::time = new_time;
}

void Game::set_day(int new_day) {
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
void Game::start_game() {
	while (true) {
		int command;
		std::cout << "<<========== Menu ==========>>" << std::endl;
		std::cout << "1. Create Game\n2. Create/Edit Tribute Roster\n3. Quit\n" << std::endl;
		std::cout << ">> ";
		std::cin >> command;
		system("cls");
		if (command == 1) {
			CreateGame();
		}
		else if (command == 2) {
			custom_tribute_list();
		}
		else if (command == 3) {
			std::cout << "<<======= Quitting Game... =======>>\n" << std::endl;
			break;
		}
		else {
			invalid_command();
		}
	}
}

void Game::custom_tribute_list() {
	std::cout << "<<======= Create/Edit Tribute Roster =======>>" << std::endl;
	std::cout << "<<== Options ==>>" << std::endl;
	std::cout << "1. Create New Custom Tribute Roster\n2. Edit Existing Custom Tribute Roster\n3. Cancel" << std::endl;
	std::cout << "Type the option number you would like to choose or enter 3 to cancel." << std::endl;
	std::cout << ">> ";
	int option;
	
	std::cin >> option;
	if (option == 1) {
		system("cls");

		std::string roster_name;
		int attempt = 0;
		while (true) {
			//First checks to see if the roster name exists, then if it doesn't, it makes a new file with that name.
			std::cout << "<<======= Create/Edit Tribute Roster =======>>" << std::endl;
			std::cout << "What would you like to name this new tribute roster?" << std::endl;
			std::cout << ">> ";

			//After the first attempt, it starts ignoring the first letter, however this is needed the first time because otherwise the getline gets skipped.
			if (attempt == 0) {
				std::cin.ignore();
			}
			getline(std::cin, roster_name);

			bool existing_roster = false;
			//Checks if file already exists
			std::string path = "rosters";
			for (const auto& entry : fs::directory_iterator(path)) {
				std::string existing_roster_name = entry.path().u8string();
				//erases first 8 letters, which is the 'rosters/' part of the directory
				existing_roster_name.erase(0, 8);
				//erases the final 5 letters, which is the '.json' part of the directory
				existing_roster_name.erase(existing_roster_name.length() - 5, existing_roster_name.length());
				if (roster_name == existing_roster_name) {
					system("cls");
					std::cout << "A roster already exists with that name!\n" << std::endl;
					existing_roster = true;
				}
			}
			if (!existing_roster) {
				std::ofstream outfile("rosters/" + roster_name + ".json");
				outfile.close();
				std::cout << "<<==== New Roster ====>>\n" << std::endl;
				std::cout << "Name: " << roster_name << "\n" << std::endl;
				for (int i = 0; i < 24; i++) {
					std::string tributeName;
					int tributeAge;
					std::string tributeGender;
					int tributeHeight;
					int tributeWeight;
					if ((i % 2) == 0) {
						std::cout << "<<= District " << (i / 2) + 1 << " =>>" << std::endl;
						std::cout << "Tribute 1: " << std::endl;
						std::cout << "Name: ";
						getline(std::cin, tributeName);
						std::cout << "Age: ";
						std::cin >> tributeAge;
						std::cin.ignore();
						std::cout << "Gender: ";
						getline(std::cin, tributeGender);
						std::cout << "Height (inches): ";
						std::cin >> tributeHeight;
						std::cout << "Weight (pounds): ";
						std::cin >> tributeWeight;
						std::cout << std::endl;
						std::cin.ignore();
					}
					else {
						std::cout << "Tribute 2: " << std::endl;
						std::cout << "Name: ";
						getline(std::cin, tributeName);
						std::cout << "Age: ";
						std::cin >> tributeAge;
						std::cin.ignore();
						std::cout << "Gender: ";
						getline(std::cin, tributeGender);
						std::cout << "Height (inches): ";
						std::cin >> tributeHeight;
						std::cout << "Weight (pounds): ";
						std::cin >> tributeWeight;
						std::cout << std::endl;
						std::cin.ignore();
					}
				}
				break;
			}
			attempt++;
		}
	}
	else if (option == 2) {
		system("cls");
		while (true)
		{
			std::cout << "<<=== Rosters ===>>\n" << std::endl;

			//Find the existing roster files in the rosters/ directory
			std::string path = "rosters";
			std::vector<std::string> roster_list;
			int roster_num = 1;
			for (const auto& entry : fs::directory_iterator(path)) {
				std::string roster_name = entry.path().u8string();
				//erases first 8 letters, which is the 'rosters/' part of the directory
				roster_name.erase(0, 8);
				//erases the final 5 letters, which is the '.json' part of the directory
				roster_name.erase(roster_name.length()-5, roster_name.length());
				std::cout << roster_num << ". " << roster_name << std::endl;
				roster_list.push_back(roster_name);
				roster_num++;
			}
			std::cout << "\nWhich roster would you like to edit?" << std::endl;
			std::cout << ">> ";
			int roster_choice;
			std::cin >> roster_choice;
			std::cout << roster_choice << std::endl;
			if (roster_choice <= 0 || roster_choice > roster_list.size()) {
				system("cls");
				std::cout << "<<=== Roster not found ===>\n" << std::endl;
			}
			else {
				std::cout << roster_list[roster_choice - 1] << std::endl;
				break;
			}
			std::cin.clear();
			std::cin.ignore(100, '\n');
		}
		
	}
	else if (option == 3) {
		invalid_command();
	}
	else {

	}
}


void Game::create_tribute_list() {
	//generates generic random tribute list and stores it in the tribute list variable. 
	//The first for loop generates 12 boys, 1 for each district and 12 girls, 1 for each district. The ages, heights, and weights are random. 
	if (Game::option_tribute_list == "Realistic Random") {
		
		int ages[28] = {
				12,
				13, 13,
				14, 14, 14,
				15, 15, 15, 15,
				16, 16, 16, 16, 16,
				17, 17, 17, 17, 17, 17,
				18, 18, 18, 18, 18, 18, 18 
		};

		for (int i = 0; i < 12; i++) {
			//12 yr olds get name put in 1 time, 13 yr olds 2 times, 14 yr olds 3 times, etc. The older you are, the more likely to be picked. 
			//So this selects the age with the proper odds associated with that age.
			int num_for_age = randNum(1, 28);
			int age = ages[num_for_age - 1];

			int height;
			int weight;
			//Determines if the height will be around average for that height, or a little more abnormal. Then picks a height range to pick a random height from.
			//12 year olds are most likely to be short because they didn't hit puberty yet/are just hitting puberty.
			int age_outlier = randNum(0, 100);
			if (age == 12) {
				if (age_outlier <= 50) {
					height = randNum(57, 63);
				}
				else if (age_outlier <= 75) {
					height = randNum(64, 65);
				}
				else if (age_outlier <= 90) {
					height = randNum(66, 69);
				}
				else {
					height = randNum(70, 72);
				}
			}
			else if (age == 13) {
				if (age_outlier <= 50) {
					height = randNum(59, 64);
				}
				else if (age_outlier <= 75) {
					height = randNum(65, 67);
				}
				else if (age_outlier <= 90) {
					height = randNum(68, 70);
				}
				else {
					height = randNum(71, 72);
				}
			}
			else if (age == 14) {
				if (age_outlier <= 50) {
					height = randNum(61, 67);
				}
				else if (age_outlier <= 75) {
					height = randNum(68, 70);
				}
				else if (age_outlier <= 90) {
					height = randNum(71, 73);
				}
				else {
					height = 74;
				}
			}
			else if (age == 15) {
				if (age_outlier <= 50) {
					height = randNum(62, 70);
				}
				else if (age_outlier <= 85) {
					height = randNum(71, 73);
				}
				else {
					height = 74;
				}
			}
			else if (age == 16) {
				if (age_outlier <= 50) {
					height = randNum(63, 72);
				}
				else if (age_outlier <= 80) {
					height = randNum(73, 74);
				}
				else if (age_outlier <= 95) {
					height = randNum(75, 76);
				}
				else {
					height = 77;
				}
			}
			else {
				if (age_outlier <= 50) {
					height = randNum(63, 72);
				}
				else if (age_outlier <= 75) {
					height = randNum(73, 75);
				}
				else if (age_outlier <= 95) {
					height = randNum(76, 77);
				}
				else {
					height = 78;
				}
			}

			//Determines weight.
			//Tall people will weight more.
			if (height <= 60) {
				weight = randNum(75, 110);
			}
			else if (height <= 64) {
				weight = randNum(100, 140);
			}
			else if (height <= 68) {
				weight = randNum(120, 170);
			}
			else if (height <= 71) {
				weight = randNum(135, 200);
			}
			else if (height <= 74) {
				weight = randNum(150, 230);
			}
			else {
				weight = randNum(160, 250);
			}

			Tribute tribute("Henry Mitkins", "Male", "Alive", i + 1, i + 1, age, height, weight, 0, 100);
			Game::tribute_list.emplace_back(tribute);
		}
		for (int i = 0; i < 12; i++) {
			//12 yr olds get name put in 1 time, 13 yr olds 2 times, 14 yr olds 3 times, etc. The older you are, the more likely to be picked. 
			//So this selects the age with the proper odds associated with that age.
			int num_for_age = randNum(1, 28);
			int age = ages[num_for_age - 1];

			int height;
			int weight;
			//Determines if the height will be around average for that height, or a little more abnormal. Then picks a height range to pick a random height from.
			//12 year olds are most likely to be short because they didn't hit puberty yet/are just hitting puberty.
			int age_outlier = randNum(0, 100);
			if (age == 12) {
				if (age_outlier <= 50) {
					height = randNum(56, 62);
				}
				else if (age_outlier <= 80) {
					height = randNum(63, 64);
				}
				else if (age_outlier <= 95) {
					height = randNum(65, 69);
				}
				else {
					height = randNum(70, 71);
				}
			}
			else if (age == 13) {
				if (age_outlier <= 50) {
					height = randNum(58, 63);
				}
				else if (age_outlier <= 80) {
					height = randNum(64, 66);
				}
				else if (age_outlier <= 92) {
					height = randNum(67, 69);
				}
				else {
					height = randNum(70, 71);
				}
			}
			else if (age == 14) {
				if (age_outlier <= 50) {
					height = randNum(60, 65);
				}
				else if (age_outlier <= 85) {
					height = randNum(66, 70);
				}
				else if (age_outlier <= 95) {
					height = randNum(71, 72);
				}
				else {
					height = 73;
				}
			}
			else if (age == 15) {
				if (age_outlier <= 50) {
					height = randNum(61, 67);
				}
				else if (age_outlier <= 85) {
					height = randNum(68, 71);
				}
				else if (age_outlier <= 95) {
					height = randNum(72, 73);
				}
				else {
					height = 74;
				}
			}
			else {
				if (age_outlier <= 50) {
					height = randNum(61, 68);
				}
				else if (age_outlier <= 85) {
					height = randNum(69, 71);
				}
				else if (age_outlier <= 95) {
					height = randNum(72, 74);
				}
				else {
					height = 75;
				}
			}

			//Determines weight.
			//Tall people will weight more.
			if (height <= 60) {
				weight = randNum(75, 110);
			}
			else if (height <= 64) {
				weight = randNum(100, 140);
			}
			else if (height <= 68) {
				weight = randNum(120, 170);
			}
			else if (height <= 71) {
				weight = randNum(135, 200);
			}
			else if (height <= 74) {
				weight = randNum(150, 215);
			}
			else {
				weight = randNum(160, 225);
			}
			Tribute tribute("Rose Merryweather", "Female", "Alive", i + 13, i + 1, age, height, weight, 0, 100);
			Game::tribute_list.emplace_back(tribute);
		}
	}
	else if (Game::option_tribute_list == "Chaotic Random") {
		//Completely random ages, height, weight. Not realistic at all.
		for (int i = 0; i < 12; i++) {
			Tribute tribute("Henry Mitkins", "Male", "Alive", i + 1, i + 1, randNum(12, 18), randNum(60, 77), randNum(100, 250), 0, 100);
			Game::tribute_list.emplace_back(tribute);
		}
		for (int i = 0; i < 12; i++) {
			Tribute tribute("Rose Merryweather", "Female", "Alive", i + 13, i + 1, randNum(12, 18), randNum(56, 72), randNum(80, 200), 0, 100);
			Game::tribute_list.emplace_back(tribute);
		}
	}
	else {
		for (int i = 0; i < 12; i++) {
			Tribute tribute("Henry Mitkins", "Male", "Alive", i + 1, i + 1, randNum(12, 18), randNum(60, 77), randNum(100, 250), 0, 100);
			Game::tribute_list.emplace_back(tribute);
		}
		for (int i = 0; i < 12; i++) {
			Tribute tribute("Rose Merryweather", "Female", "Alive", i + 13, i + 1, randNum(12, 18), randNum(56, 72), randNum(80, 200), 0, 100);
			Game::tribute_list.emplace_back(tribute);
		}
	}
	
}

void Game::view_tribute_list() {
	std::vector<Tribute> tributeList = get_tribute_list();
	for (int i = 0; i < 12; i++) {
		std::cout << "District " << tributeList[i].get_district() << std::endl;
		std::cout << "1. " << tributeList[i].get_name() << " - " << tributeList[i].get_gender() << " - " << tributeList[i].get_age() << " years old" << " - " << inch_to_feet(tributeList[i].get_height()) << " - " << tributeList[i].get_weight() << " lbs." << std::endl;
		std::cout << "2. " << tributeList[i+12].get_name() << " - " << tributeList[i+12].get_gender() << " - " << tributeList[i].get_age() << " years old" << " - " << inch_to_feet(tributeList[i+12].get_height()) << " - " << tributeList[i].get_weight() << " lbs." << std::endl;
		std::cout << std::endl;
	}
}

//Called when the user selects "create game" in the above start_game function. Allows the user to change game options.
void Game::CreateGame() {
	while (true) {
		std::cout << "<<======= Create Game =======>>\n" << std::endl;
		std::cout << "<<== Game Options ==>>" << std::endl;
		std::cout << "1. Tribute List Creation = " << Game::option_tribute_list << "\n2. Simulation Type = " << Game::option_sim_type << "\n3. View Tribute List\n4. Continue\n5. Cancel" << std::endl;
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
			system("cls");
			view_tribute_list();
		}
		else if (option == 4) {
			sim_day();
			break;
		}
		else if (option == 5) {
			system("cls");
			break;
		}
		else {
			invalid_command();
		}
	}
}

//Called when the user selects to edit the sim type option
void Game::SimTypeOption() {
	std::cout << "<<== Simulation Type ==>>\n1. Realistic | 2. Random | 3. Chaotic Random\n" << std::endl;
	std::cout << ">> ";
	int option_edit;
	std::cin >> option_edit;
	switch (option_edit) {
	case 1:
		system("cls");
		Game::option_sim_type = "Realistic";
		std::cout << "<<== Set Simulation Type to Realistic ==>>\n" << std::endl;
		break;
	case 2:
		system("cls");
		Game::option_sim_type = "Random";
		std::cout << "<<== Set Simulation Type to Random ==>>\n" << std::endl;
		break;
	case 3:
		system("cls");
		Game::option_sim_type = "Chaotic Random";
		std::cout << "<<== Set Simulation Type to Chaotic Random ==>>\n" << std::endl;
		break;
	default:
		invalid_command();
		break;
	}
}

//Called when the user selects to edit the tribute list creation. 
void Game::TributeCreationOption() {
	std::cout << "<<== Tribute List Creation ==>>\n1. Realistic Random | 2. Chaotic Random | 3. Custom\n" << std::endl;
	std::cout << ">> ";
	int option_edit;
	std::cin >> option_edit;
	switch (option_edit) {
	case 1:
		system("cls");
		Game::option_tribute_list = "Realistic Random";
		std::cout << "<<== Set Tribute List Creation to Realistic Random ==>>\n" << std::endl;
		break;
	case 2:
		system("cls");
		Game::option_tribute_list = "Chaotic Random";
		std::cout << "<<== Set Tribute List Creation to Chaotic Random ==>>\n" << std::endl;
		break;
	case 3:
		std::cout << "Select the Tribute Roster you would like to use." << std::endl;
		int roster_selection;
		std::cin >> roster_selection;
		system("cls");
		Game::option_tribute_list = "Custom";
		std::cout << "<<== Set Tribute List Creation to Custom ==>>\n" << std::endl;
		break;
	default:
		invalid_command();
		break;
	}
}

//Called to simulate the hunger games
void Game::sim_day() {
	std::cout << "Welcome to the Hunger Games! May the odds be ever in your favor." << std::endl;
}