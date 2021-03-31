#include <iostream>
#include <random>
#include <fstream>
#include <filesystem>
#include "menus.h"
#include <string>
#include "json.hpp"
#include "hungergames.h"

using json = nlohmann::json;

namespace fs = std::filesystem;

//Printed when the user enters an invalid input/command.
void invalid_command() {
	system("cls");
	std::cout << "<<====== Invalid Command ======>>" << std::endl;

	//Fixes bug that creates a never ending loop when a non-int is entered.
	std::cin.clear();
	std::cin.ignore(100, '\n');
}

//Menu constructer, basically starts the program.
Menus::Menus() {
	HungerGames game;
	//Create generic random tribute list and stores it in the tribute list variable. 
	game.create_tribute_list();
	//Creates list of events
	game.set_events();
	//Calls the start_game function.
	start_game(game);
}


//Displays a text menu and gets user command input
void Menus::start_game(HungerGames& game) {
	while (true) {
		int command;
		std::cout << "<<========== Menu ==========>>\n" << std::endl;
		std::cout << "1. Create Game\n2. Create/Edit Tribute Roster\n3. Quit\n" << std::endl;
		std::cout << ">> ";
		std::cin >> command;
		system("cls");
		if (command == 1) {
			CreateGame(game);
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

//Turns a Tribute vector into a json object and saves that json object into the specified json file.
void Menus::SaveRoster(std::string& roster_name, std::vector<Tribute>& custom_tribute_list) {
	std::ofstream saveroster("rosters/" + roster_name + ".json");
	json roster_json;
	roster_json["Roster Name"] = roster_name;
	for (int i = 0; i < 12; i++) {
		std::string district_key = "District " + std::to_string(i + 1);
		roster_json["Tribute List"][district_key] = {
			{ "Tribute 1",
			{
				{ "Name", custom_tribute_list[2 * i].get_name() },
				{ "Gender", custom_tribute_list[2 * i].get_gender() },
				{ "Age", custom_tribute_list[2 * i].get_age() },
				{ "Height", custom_tribute_list[2 * i].get_height() },
				{ "Weight", custom_tribute_list[2 * i].get_weight() }
			}
			},
			{ "Tribute 2",
			{
				{ "Name", custom_tribute_list[2 * i + 1].get_name() },
				{ "Gender", custom_tribute_list[2 * i + 1].get_gender() },
				{ "Age", custom_tribute_list[2 * i + 1].get_age() },
				{ "Height", custom_tribute_list[2 * i + 1].get_height() },
				{ "Weight", custom_tribute_list[2 * i + 1].get_weight() }
			}
			}
		};
	}
	saveroster << std::setw(4) << roster_json << std::endl;
	saveroster.close();
}

//Prints a list of saved roster files (All the json files it finds in the roster folder)
void Menus::CustomRosterList(std::string& path, std::vector<std::string>& roster_list) {
	int roster_num = 1;
	for (const auto& entry : fs::directory_iterator(path)) {
		std::string roster_name = entry.path().u8string();
		//erases first 8 letters, which is the 'rosters/' part of the directory
		roster_name.erase(0, 8);
		//erases the final 5 letters, which is the '.json' part of the directory
		roster_name.erase(roster_name.length() - 5, roster_name.length());
		std::cout << roster_num << ". " << roster_name << std::endl;
		roster_list.push_back(roster_name);
		roster_num++;
	}
}

//Turns a json file of the tributes and turns it into a Tribute vector that the program can use.
void Menus::LoadCustomRoster(std::string& roster_name, std::vector<Tribute>& tribute_roster) {
	std::ifstream load_roster("rosters/" + roster_name + ".json");
	json roster_json;
	load_roster >> roster_json;
	for (int i = 0; i < 12; i++) {
		std::string district_key = "District " + std::to_string(i + 1);
		json district_tributes = roster_json["Tribute List"][district_key];
		Tribute tribute1(district_tributes["Tribute 1"]["Name"], district_tributes["Tribute 1"]["Gender"], "Alive", (2 * i) + 1, i + 1, district_tributes["Tribute 1"]["Age"], district_tributes["Tribute 1"]["Height"], district_tributes["Tribute 1"]["Weight"], 0, 100);
		Tribute tribute2(district_tributes["Tribute 2"]["Name"], district_tributes["Tribute 2"]["Gender"], "Alive", (2 * i) + 2, i + 1, district_tributes["Tribute 2"]["Age"], district_tributes["Tribute 2"]["Height"], district_tributes["Tribute 2"]["Weight"], 0, 100);
		tribute_roster.emplace_back(tribute1);
		tribute_roster.emplace_back(tribute2);
	}
	load_roster.close();
}

//The custom tribute roster menu where you can create or edit a tribute roster.
void Menus::custom_tribute_list() {
	while (true)
	{
		std::cout << "<<======= Create/Edit Tribute Roster =======>>\n" << std::endl;
		std::cout << "<<== Options ==>>" << std::endl;
		std::cout << "1. Create New Custom Tribute Roster\n2. Edit Existing Custom Tribute Roster\n3. Cancel" << std::endl;
		std::cout << "Type the option number you would like to choose or enter 3 to cancel." << std::endl;
		std::cout << "\n>> ";
		int option;
		std::cin >> option;
		if (option == 1) {
			system("cls");

			std::string roster_name;
			int attempt = 0;
			while (true) {
				//First checks to see if the roster name exists, then if it doesn't, it makes a new file with that name.
				std::cout << "<<======= Create/Edit Tribute Roster =======>>\n" << std::endl;
				std::cout << "What would you like to name this new tribute roster?\n" << std::endl;
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
					std::vector<Tribute> custom_tribute_list;
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
						Tribute new_tribute(tributeName, tributeGender, "Alive", i + 1, (i / 2) + 1, tributeAge, tributeHeight,tributeWeight, 0, 100);
						custom_tribute_list.emplace_back(new_tribute);
					}
					SaveRoster(roster_name, custom_tribute_list);
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
				CustomRosterList(path, roster_list);
				std::cout << "\nWhich roster would you like to edit? Or type 0 to cancel.\n" << std::endl;
				std::cout << ">> ";
				int roster_choice;
				std::cin >> roster_choice;
			
				if (roster_choice < 0 || roster_choice > roster_list.size()) {
					system("cls");
					std::cout << "<<=== Roster not found ===>\n" << std::endl;
				}
				else if (roster_choice == 0) {
					system("cls");
					break;
				}
				else {
					while (true) {
						system("cls");
						std::cout << "<<=== Edit Roster ===>>\n" << std::endl;
						std::string roster_name = roster_list[roster_choice - 1];
						std::cout << "Roster Name: " << roster_name << "\n" << std::endl;
						std::vector<Tribute> tribute_roster;
						LoadCustomRoster(roster_name, tribute_roster);
						view_tribute_list(tribute_roster);
						std::cout << "Which district would you like to edit? Or type 0 to go back.\n" << std::endl;
						std::cout << ">> ";
						int district_choice;
						std::cin >> district_choice;
						if (district_choice == 0) {
							system("cls");
							break;
						}
						std::cout << "\nWhich tribute would you like to edit?\n" << std::endl;
						std::cout << ">> ";
						int tribute_choice;
						std::cin >> tribute_choice;
						int tributeFound = 1;
						int index = 0;
						for (Tribute tribute : tribute_roster) {
							if (tribute.get_district() == district_choice) {
								if (tributeFound == tribute_choice) {
									system("cls");
									while (true) {
										std::cout << "<<=== Edit Tribute ===>>\n" << std::endl;
										std::cout << "1. Name: " << tribute_roster[index].get_name() << "\n2. Gender: " << tribute_roster[index].get_gender() << "\n3. Age: " << tribute_roster[index].get_age() << " yrs\n4. Height: " << inch_to_feet(tribute_roster[index].get_height()) << "\n5. Weight: " << tribute_roster[index].get_weight() << " lbs.\n6. Back" << std::endl;
										std::cout << "What attribute would you like to edit?\n" << std::endl;
										std::cout << ">> ";
										int attribute_choice;
										std::cin >> attribute_choice;
										if (attribute_choice == 6) {
											break;
										}
										else if (attribute_choice == 1) {
											std::cin.clear();
											std::cin.ignore(100, '\n');
											std::cout << "\nWhat do you want to change their name to?\n" << std::endl;
											std::cout << ">> ";
											std::string new_name;
											getline(std::cin, new_name);
											tribute_roster[index].set_name(new_name);
										}
										else if (attribute_choice == 2) {
											std::cin.clear();
											std::cin.ignore(100, '\n');
											std::cout << "\nWhat do you want to change their gender to?\n" << std::endl;
											std::cout << ">> ";
											std::string new_gender;
											getline(std::cin, new_gender);
											tribute_roster[index].set_gender(new_gender);
										}
										else if (attribute_choice == 3) {
											std::cout << "\nWhat do you want to change their age to?\n" << std::endl;
											std::cout << ">> ";
											int new_age;
											std::cin >> new_age;
											tribute_roster[index].set_age(new_age);
										}
										else if (attribute_choice == 4) {
											std::cout << "\nWhat do you want to change their height to (in inches)?\n" << std::endl;
											std::cout << ">> ";
											int new_height;
											std::cin >> new_height;
											tribute_roster[index].set_height(new_height);
										}
										else if (attribute_choice == 5) {
											std::cout << "\nWhat do you want to change their weight to (in lbs)?\n" << std::endl;
											std::cout << ">> ";
											int new_weight;
											std::cin >> new_weight;
											tribute_roster[index].set_weight(new_weight);
										}
										SaveRoster(roster_list[roster_choice - 1], tribute_roster);
										
										system("cls");
										std::cout << "<<=== Saved Tribute Data Successfully ===>>\n" << std::endl;
									}
									break;
								}
								else {
									tributeFound++;
								}
							}
							index++;
						}
					}
				}
				std::cin.clear();
				std::cin.ignore(100, '\n');
			}
		}
		else if (option == 3) {
			system("cls");
			break;
		}
		else {
			invalid_command();
		}
	}
}

//Prints out the tribute roster when given a Tribute vector.
void Menus::view_tribute_list(std::vector<Tribute> tributeList) {
	for (int i = 0; i < 12; i++) {
		std::cout << "District " << i + 1 << std::endl;
		int tributeFound = 1;
		for (Tribute tribute : tributeList) {
			if (tribute.get_district() == (i + 1)) {
				std::cout << tributeFound << ". " << tribute.get_name() << " - " << tribute.get_gender() << " - " << tribute.get_age() << " years old" << " - " << inch_to_feet(tribute.get_height()) << " - " << tribute.get_weight() << " lbs." << std::endl;
				tributeFound++;
			}
		}
		std::cout << std::endl;
	}
}

//Create game menu, called when the user selects "create game" in the above start_game function. Allows the user to change game options.
void Menus::CreateGame(HungerGames& game) {
	while (true) {
		std::cout << "<<======= Create Game =======>>\n" << std::endl;
		std::cout << "<<== Game Options ==>>" << std::endl;
		std::cout << "1. Tribute List Creation = " << game.get_option_tribute_list() << "\n2. Simulation Type = " << game.get_option_sim_type() << "\n3. View Tribute List\n4. Continue\n5. Cancel" << std::endl;
		std::cout << "Type the option number you would like to edit or enter 4 to continue." << std::endl;
		std::cout << "\n>> ";
		int option;
		std::cin >> option;
		if (option == 1) {
			system("cls");
			TributeCreationOption(game);
		}
		else if (option == 2) {
			system("cls");
			SimTypeOption(game);
		}
		else if (option == 3) {
			system("cls");
			std::cout << "<<=== Current Roster ===>>\n" << std::endl;
			view_tribute_list(game.get_tribute_list());
		}
		else if (option == 4) {
			system("cls");
			std::cout << "Welcome to the Hunger Games! May the odds be ever in your favor." << std::endl;
			if (game.get_option_sim_type() == "Realistic") {
				game.realistic_sim();
			}
			else if (game.get_option_sim_type() == "Random") {
				game.random_sim();
			}
			else if (game.get_option_sim_type() == "Chaotic Random") {
				game.chaotic_random_sim();
			}
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
void Menus::SimTypeOption(HungerGames& game) {
	std::cout << "<<== Simulation Type ==>>\n1. Realistic | 2. Random | 3. Chaotic Random\n" << std::endl;
	std::cout << ">> ";
	int option_edit;
	std::cin >> option_edit;
	switch (option_edit) {
	case 1:
		system("cls");
		game.set_option_sim_type("Realistic");
		std::cout << "<<== Set Simulation Type to Realistic ==>>\n" << std::endl;
		break;
	case 2:
		system("cls");
		game.set_option_sim_type("Random");
		std::cout << "<<== Set Simulation Type to Random ==>>\n" << std::endl;
		break;
	case 3:
		system("cls");
		game.set_option_sim_type("Chaotic Random");
		std::cout << "<<== Set Simulation Type to Chaotic Random ==>>\n" << std::endl;
		break;
	default:
		invalid_command();
		break;
	}
}

//Called when the user selects to edit the tribute list creation. 
void Menus::TributeCreationOption(HungerGames& game) {
	std::cout << "<<== Tribute List Creation ==>>\n1. Realistic Random | 2. Chaotic Random | 3. Custom\n" << std::endl;
	std::cout << ">> ";
	int option_edit;
	std::vector<std::string> roster_list;
	std::vector<Tribute> tribute_roster;
	std::string path = "rosters";
	std::cin >> option_edit;
	switch (option_edit) {
	case 1:
		game.set_option_tribute_list("Realistic Random");
		game.reset_tribute_list();
		game.create_tribute_list();
		system("cls");
		std::cout << "<<== Set Tribute List Creation to Realistic Random ==>>\n" << std::endl;
		break;
	case 2:
		game.set_option_tribute_list("Chaotic Random");
		game.reset_tribute_list();
		game.create_tribute_list();
		system("cls");
		std::cout << "<<== Set Tribute List Creation to Chaotic Random ==>>\n" << std::endl;
		break;
	case 3:
		game.set_option_tribute_list("Custom");
		std::cout << "\nWhich Tribute Roster you would like to use?\n" << std::endl;
		CustomRosterList(path, roster_list);
		std::cout << "\n>> ";
		int roster_selection;
		std::cin >> roster_selection; 
		LoadCustomRoster(roster_list[roster_selection-1], tribute_roster);
		game.reset_tribute_list();
		game.set_tribute_list(tribute_roster);
		system("cls");
		std::cout << "<<== Set Tribute List Creation to Custom ==>>\n" << std::endl;
		break;
	default:
		invalid_command();
		break;
	}
}