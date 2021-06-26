#include "hungergames.h"
#include <iostream>


void invalidCommand() {
	std::cout << "\n<<====== Invalid Command ======>>" << std::endl;

	//Fixes bug that creates a never ending loop when a non-int is entered.
	std::cin.clear();
	std::cin.ignore(100, '\n');
}

void sim_menu(std::vector<Tribute>& tribute_list, std::vector<Tribute>& alive_tributes) {
	while (true) {
		std::cout << "1. View full roster\n2. View alive tributes\n3. View dead tributes\n4. Continue" << std::endl;
		std::cout << "What would you like to do?" << std::endl;
		std::cout << "\n>> ";
		int option;
		std::cin >> option;
		if (option == 1) {
			for (int i = 0; i < 12; i++) {
				std::cout << "District " << i + 1 << std::endl;
				int tributeFound = 1;
				for (Tribute tribute : tribute_list) {
					if (tribute.get_district() == (i + 1)) {
						std::cout << tributeFound << ". " << tribute.get_name() << " - " << tribute.get_gender() << " - " << tribute.get_age() << " years old" << " - " << inch_to_feet(tribute.get_height()) << " - " << tribute.get_weight() << " lbs." << std::endl;
						tributeFound++;
					}
				}
				std::cout << std::endl;
			}
		}
		else if (option == 2) {
			for (int i = 0; i < 12; i++) {
				std::cout << "District " << i + 1 << std::endl;
				int tributeFound = 1;
				for (Tribute tribute : alive_tributes) {
					if (tribute.get_district() == (i + 1)) {
						std::cout << tributeFound << ". " << tribute.get_name() << " - " << tribute.get_gender() << " - " << tribute.get_age() << " years old" << " - " << inch_to_feet(tribute.get_height()) << " - " << tribute.get_weight() << " lbs." << std::endl;
						tributeFound++;
					}
				}
				if (tributeFound == 1) {
					std::cout << "No alive tributes" << std::endl;
				}
				std::cout << std::endl;
			}
		}
		else if (option == 3) {
			for (int i = 0; i < 12; i++) {
				std::cout << "District " << i + 1 << std::endl;
				int tributeFound = 1;
				for (Tribute tribute : tribute_list) {
					if (tribute.get_district() == (i + 1) && tribute.get_status() == "Dead") {
						std::cout << tributeFound << ". " << tribute.get_name() << " - " << tribute.get_gender() << " - " << tribute.get_age() << " years old" << " - " << inch_to_feet(tribute.get_height()) << " - " << tribute.get_weight() << " lbs." << std::endl;
						tributeFound++;
					}
				}
				if (tributeFound == 1) {
					std::cout << "No dead tributes" << std::endl;
				}
				std::cout << std::endl;
			}
		}
		else if (option == 4) {
			break;
		}
		else {
			invalidCommand();
		}
	}
}

void HungerGames::AmendEventStatement(std::string& event_statement, Tribute& tribute1, std::string key) {
	size_t start_pos = 0;
	while ((start_pos = event_statement.find(key, start_pos)) != std::string::npos) {
		event_statement.replace(start_pos, key.length(), tribute1.get_name());
		start_pos += tribute1.get_name().length(); // Handles case where 'to' is a substring of 'from'
	}
}

void HungerGames::ProcessEvent(int event_index, std::vector<Tribute>& unused_tributes, std::vector<Tribute>& alive_tributes, const char* sim_type) {
	if (sim_type == "Random") {
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
					for (int i = 0; i < tribute_list.size(); i++) {
						if (tribute_list[i].get_id() == tribute1.get_id()) {
							tribute_list[i].set_status("Dead");
						}
					}
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
					for (int i = 0; i < tribute_list.size(); i++) {
						if (tribute_list[i].get_id() == tribute1.get_id()) {
							tribute_list[i].set_status("Dead");
						}
					}
				}
				else if (death == "Tribute2") {
					for (int i = 0; i < alive_tributes.size(); i++) {
						if (alive_tributes[i].get_id() == tribute2.get_id()) {
							tribute_alive_index = i;
						}
					}
					alive_tributes.erase(alive_tributes.begin() + tribute_alive_index);
					for (int i = 0; i < tribute_list.size(); i++) {
						if (tribute_list[i].get_id() == tribute2.get_id()) {
							tribute_list[i].set_status("Dead");
						}
					}
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
					for (int i = 0; i < tribute_list.size(); i++) {
						if (tribute_list[i].get_id() == tribute1.get_id()) {
							tribute_list[i].set_status("Dead");
						}
					}
				}
				else if (death == "Tribute2") {
					for (int i = 0; i < alive_tributes.size(); i++) {
						if (alive_tributes[i].get_id() == tribute2.get_id()) {
							tribute_alive_index = i;
						}
					}
					alive_tributes.erase(alive_tributes.begin() + tribute_alive_index);
					for (int i = 0; i < tribute_list.size(); i++) {
						if (tribute_list[i].get_id() == tribute2.get_id()) {
							tribute_list[i].set_status("Dead");
						}
					}
				}
				else if (death == "Tribute3") {
					for (int i = 0; i < alive_tributes.size(); i++) {
						if (alive_tributes[i].get_id() == tribute3.get_id()) {
							tribute_alive_index = i;
						}
					}
					alive_tributes.erase(alive_tributes.begin() + tribute_alive_index);
					for (int i = 0; i < tribute_list.size(); i++) {
						if (tribute_list[i].get_id() == tribute3.get_id()) {
							tribute_list[i].set_status("Dead");
						}
					}
				}
			}
		}
	}
	else if (sim_type == "Realistic") {
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
					for (int i = 0; i < tribute_list.size(); i++) {
						if (tribute_list[i].get_id() == tribute1.get_id()) {
							tribute_list[i].set_status("Dead");
						}
					}
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

			if (chosen_event.get_deaths().size() > 0) {
				int prob_trib1_death = 50;
				int height_dif = tribute1.get_height() - tribute2.get_height();
				int weight_dif = tribute1.get_weight() - tribute2.get_weight();

				if (height_dif > -2 && height_dif < 2) {
					prob_trib1_death += 0;
				}
				else if (height_dif > -4 && height_dif < 4) {
					if (height_dif > 0) {
						prob_trib1_death -= 5;
					}
					else {
						prob_trib1_death += 5;
					}
				}
				else if (height_dif > -8 && height_dif < 8) {
					if (height_dif > 0) {
						prob_trib1_death -= 15;
					}
					else {
						prob_trib1_death += 15;
					}
				}
				else if (height_dif > -11 && height_dif < 11) {
					if (height_dif > 0) {
						prob_trib1_death -= 25;
					}
					else {
						prob_trib1_death += 25;
					}
				}
				else {
					if (height_dif > 0) {
						prob_trib1_death -= 30;
					}
					else {
						prob_trib1_death += 30;
					}
				}


				if (weight_dif > -10 && weight_dif < 10) {
					prob_trib1_death += 0;
				}
				else if (weight_dif > -25 && weight_dif < 25) {
					if (weight_dif > 0) {
						prob_trib1_death -= 5;
					}
					else {
						prob_trib1_death += 5;
					}
				}
				else if (weight_dif > -45 && weight_dif < 45) {
					if (weight_dif > 0) {
						prob_trib1_death -= 15;
					}
					else {
						prob_trib1_death += 15;
					}
				}
				else if (weight_dif > -70 && weight_dif < 70) {
					if (weight_dif > 0) {
						prob_trib1_death -= 25;
					}
					else {
						prob_trib1_death += 25;
					}
				}
				else {
					if (weight_dif > 0) {
						prob_trib1_death -= 30;
					}
					else {
						prob_trib1_death += 30;
					}
				}

				if (prob_trib1_death > 100) {
					prob_trib1_death = 100;
				}
				if (prob_trib1_death < 0) {
					prob_trib1_death = 0;
				}

				int decision = randNum(0, 100);
				Tribute dead_tribute = tribute2;
				Tribute alive_tribute = tribute1;

				if (decision <= prob_trib1_death) {
					dead_tribute = tribute1;
					alive_tribute = tribute2;
					for (int i = 0; i < tribute_list.size(); i++) {
						if (tribute_list[i].get_id() == tribute1.get_id()) {
							tribute_list[i].set_status("Dead");
						}
					}
				}
				else {
					for (int i = 0; i < tribute_list.size(); i++) {
						if (tribute_list[i].get_id() == tribute2.get_id()) {
							tribute_list[i].set_status("Dead");
						}
					}
				}
				std::string event_statement = chosen_event.get_event_statement();

				AmendEventStatement(event_statement, dead_tribute, "{Tribute1}");
				AmendEventStatement(event_statement, alive_tribute, "{Tribute2}");

				std::cout << event_statement << std::endl;

				for (std::string death : chosen_event.get_deaths()) {
					int tribute_alive_index = 0;
					if (death == "Tribute1") {
						for (int i = 0; i < alive_tributes.size(); i++) {
							if (alive_tributes[i].get_id() == dead_tribute.get_id()) {
								tribute_alive_index = i;
							}
						}
						alive_tributes.erase(alive_tributes.begin() + tribute_alive_index);
					}
					else if (death == "Tribute2") {
						for (int i = 0; i < alive_tributes.size(); i++) {
							if (alive_tributes[i].get_id() == dead_tribute.get_id()) {
								tribute_alive_index = i;
							}
						}
						alive_tributes.erase(alive_tributes.begin() + tribute_alive_index);
					}
				}
			}
			else {
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
					for (int i = 0; i < tribute_list.size(); i++) {
						if (tribute_list[i].get_id() == tribute1.get_id()) {
							tribute_list[i].set_status("Dead");
						}
					}
				}
				else if (death == "Tribute2") {
					for (int i = 0; i < alive_tributes.size(); i++) {
						if (alive_tributes[i].get_id() == tribute2.get_id()) {
							tribute_alive_index = i;
						}
					}
					alive_tributes.erase(alive_tributes.begin() + tribute_alive_index);
					for (int i = 0; i < tribute_list.size(); i++) {
						if (tribute_list[i].get_id() == tribute2.get_id()) {
							tribute_list[i].set_status("Dead");
						}
					}
				}
				else if (death == "Tribute3") {
					for (int i = 0; i < alive_tributes.size(); i++) {
						if (alive_tributes[i].get_id() == tribute3.get_id()) {
							tribute_alive_index = i;
						}
					}
					alive_tributes.erase(alive_tributes.begin() + tribute_alive_index);
					for (int i = 0; i < tribute_list.size(); i++) {
						if (tribute_list[i].get_id() == tribute3.get_id()) {
							tribute_list[i].set_status("Dead");
						}
					}
				}
			}
		}
	}
}

void HungerGames::realistic_sim() {
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
				ProcessEvent(event_index, unused_tributes, alive_tributes, "Realistic");
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
				ProcessEvent(event_index, unused_tributes, alive_tributes, "Realistic");
			}
		}
		num_alive_tributes = get_alive_tributes(alive_tributes);
		std::cout << "Alive tributes: " << num_alive_tributes << "\n" << std::endl;
		HungerGames::day++;
		sim_menu(HungerGames::tribute_list, alive_tributes);
	}
	std::cout << "\nThe winner of the Hunger Games is " << alive_tributes[0].get_name() << "!\n" << std::endl;
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
				ProcessEvent(event_index, unused_tributes, alive_tributes, "Random");
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
				ProcessEvent(event_index, unused_tributes, alive_tributes, "Random");
			}
		}
		num_alive_tributes = get_alive_tributes(alive_tributes);
		std::cout << "Alive tributes: " << num_alive_tributes << "\n" << std::endl;
		HungerGames::day++;
		sim_menu(HungerGames::tribute_list, alive_tributes);
	}
	std::cout << "\nThe winner of the Hunger Games is " << alive_tributes[0].get_name() << "!\n" << std::endl;
}