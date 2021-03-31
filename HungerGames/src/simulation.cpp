#include "hungergames.h"
#include <iostream>

void HungerGames::realistic_sim() {

}

void HungerGames::AmendEventStatement(std::string& event_statement, Tribute& tribute1, std::string key)
{
	size_t start_pos = 0;
	while ((start_pos = event_statement.find(key, start_pos)) != std::string::npos) {
		event_statement.replace(start_pos, key.length(), tribute1.get_name());
		start_pos += tribute1.get_name().length(); // Handles case where 'to' is a substring of 'from'
	}
}

void HungerGames::ProcessEvent(int event_index, std::vector<Tribute>& unused_tributes, std::vector<Tribute>& alive_tributes)
{
	Event chosen_event = HungerGames::event_list[event_index];
	if (chosen_event.get_num_tributes() == 1) {
		int tribute1_index = randNum(0, unused_tributes.size() - 1);
		Tribute tribute1 = unused_tributes[tribute1_index];
		unused_tributes.erase(unused_tributes.begin() + tribute1_index);

		std::string event_statement = chosen_event.get_event_statement();

		AmendEventStatement(event_statement, tribute1, "{Tribute1}");

		std::cout << event_statement << std::endl;

		for (std::string death : chosen_event.get_deaths()) {
			int tribute_alive_index = 0;
			if (death == "Tribute1") {
				for (int i = 0; i < alive_tributes.size(); i++) {
					if (alive_tributes[i].get_id() == tribute1.get_id()) {
						tribute_alive_index = i;
					}
				}
				alive_tributes.erase(alive_tributes.begin() + tribute_alive_index);
			}
		}
	}
	else if (chosen_event.get_num_tributes() == 2) {
		int tribute1_index = randNum(0, unused_tributes.size() - 1);
		Tribute tribute1 = unused_tributes[tribute1_index];
		unused_tributes.erase(unused_tributes.begin() + tribute1_index);

		int tribute2_index = randNum(0, unused_tributes.size() - 1);
		Tribute tribute2 = unused_tributes[tribute2_index];
		unused_tributes.erase(unused_tributes.begin() + tribute2_index);

		std::string event_statement = chosen_event.get_event_statement();

		AmendEventStatement(event_statement, tribute1, "{Tribute1}");
		AmendEventStatement(event_statement, tribute2, "{Tribute2}");

		std::cout << event_statement << std::endl;

		for (std::string death : chosen_event.get_deaths()) {
			int tribute_alive_index = 0;
			if (death == "Tribute1") {
				for (int i = 0; i < alive_tributes.size(); i++) {
					if (alive_tributes[i].get_id() == tribute1.get_id()) {
						tribute_alive_index = i;
					}
				}
				alive_tributes.erase(alive_tributes.begin() + tribute_alive_index);
			}
			else if (death == "Tribute2") {
				for (int i = 0; i < alive_tributes.size(); i++) {
					if (alive_tributes[i].get_id() == tribute2.get_id()) {
						tribute_alive_index = i;
					}
				}
				alive_tributes.erase(alive_tributes.begin() + tribute_alive_index);
			}
		}
	}
	else if (chosen_event.get_num_tributes() == 3) {
		int tribute1_index = randNum(0, unused_tributes.size() - 1);
		Tribute tribute1 = unused_tributes[tribute1_index];
		unused_tributes.erase(unused_tributes.begin() + tribute1_index);

		int tribute2_index = randNum(0, unused_tributes.size() - 1);
		Tribute tribute2 = unused_tributes[tribute2_index];
		unused_tributes.erase(unused_tributes.begin() + tribute2_index);

		int tribute3_index = randNum(0, unused_tributes.size() - 1);
		Tribute tribute3 = unused_tributes[tribute3_index];
		unused_tributes.erase(unused_tributes.begin() + tribute3_index);

		std::string event_statement = chosen_event.get_event_statement();

		AmendEventStatement(event_statement, tribute1, "{Tribute1}");
		AmendEventStatement(event_statement, tribute2, "{Tribute2}");
		AmendEventStatement(event_statement, tribute3, "{Tribute3}");

		std::cout << event_statement << std::endl;

		for (std::string death : chosen_event.get_deaths()) {
			int tribute_alive_index = 0;
			if (death == "Tribute1") {
				for (int i = 0; i < alive_tributes.size(); i++) {
					if (alive_tributes[i].get_id() == tribute1.get_id()) {
						tribute_alive_index = i;
					}
				}
				alive_tributes.erase(alive_tributes.begin() + tribute_alive_index);
			}
			else if (death == "Tribute2") {
				for (int i = 0; i < alive_tributes.size(); i++) {
					if (alive_tributes[i].get_id() == tribute2.get_id()) {
						tribute_alive_index = i;
					}
				}
				alive_tributes.erase(alive_tributes.begin() + tribute_alive_index);
			}
			else if (death == "Tribute3") {
				for (int i = 0; i < alive_tributes.size(); i++) {
					if (alive_tributes[i].get_id() == tribute3.get_id()) {
						tribute_alive_index = i;
					}
				}
				alive_tributes.erase(alive_tributes.begin() + tribute_alive_index);
			}
		}
	}
}

void HungerGames::random_sim() {
	int num_alive_tributes = 24;
	std::vector<Tribute> alive_tributes = HungerGames::tribute_list;
	while (num_alive_tributes > 1) {
		std::vector<Tribute> unused_tributes = alive_tributes;
		if (HungerGames::day == 1) {
			std::cout << "<<====== Day 1 ======>>\n" << std::endl;
			while (unused_tributes.size() > 0) {
				int event_index = randNum(0, HungerGames::event_list.size() - 1);
				while (true) {
					if (HungerGames::event_list[event_index].get_event_tag() != "Cornucopia" || HungerGames::event_list[event_index].get_num_tributes() > unused_tributes.size()) {
						event_index = randNum(0, HungerGames::event_list.size() - 1);
					}
					else {
						break;
					}
				}
				ProcessEvent(event_index, unused_tributes, alive_tributes);
			}
		}
		else {
			std::cout << "<<====== Day " << HungerGames::day << " ======>>\n" << std::endl;
			while (unused_tributes.size() > 0) {
				int event_index = randNum(0, HungerGames::event_list.size() - 1);
				while (true) {
					if (HungerGames::event_list[event_index].get_event_tag() == "Cornucopia" || HungerGames::event_list[event_index].get_num_tributes() > unused_tributes.size()) {
						event_index = randNum(0, HungerGames::event_list.size() - 1);
					}
					else {
						break;
					}
				}
				ProcessEvent(event_index, unused_tributes, alive_tributes);
			}
		}
		num_alive_tributes = get_alive_tributes(alive_tributes);
		std::cout << "Alive tributes: " << num_alive_tributes << std::endl;
		HungerGames::day++;
	}
}

void HungerGames::chaotic_random_sim() {

}