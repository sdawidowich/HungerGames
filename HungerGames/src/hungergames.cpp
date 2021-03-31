#include "menus.h"
#include "hungergames.h"
#include "event.h"
#include <fstream>
#include <random>
#include <string>

HungerGames::HungerGames() : time(0), day(1), option_tribute_list("Realistic Random"), option_sim_type("Realistic") {

}

//Getters and setters for the class variables.

std::vector<Tribute> HungerGames::get_tribute_list() {
	return HungerGames::tribute_list;
}

std::vector<Tribute> HungerGames::get_alliance_list() {
	return HungerGames::alliance_list;
}

int HungerGames::get_time() {
	return HungerGames::time;
}

int HungerGames::get_day() {
	return HungerGames::day;
}

std::string HungerGames::get_option_tribute_list() {
	return HungerGames::option_tribute_list;
}

std::string HungerGames::get_option_sim_type() {
	return HungerGames::option_sim_type;
}

std::vector<Event> HungerGames::get_event_list() {
	return HungerGames::event_list;
}

void HungerGames::set_time(int new_time) {
	HungerGames::time = new_time;
}

void HungerGames::set_day(int new_day) {
	HungerGames::day = new_day;
}

//Creates list of possible events
void HungerGames::set_events() {
	std::vector<std::string> dead_tributes = {};
	Event event(1, "Alive", "{Tribute1} ran to the cornucopia and grabbed a bow and arrow.", "Cornucopia", dead_tributes);
	HungerGames::event_list.emplace_back(event);

	dead_tributes = { "Tribute1" };
	event.change_event(1, "Death", "{Tribute1} stepped off the pedestal too early.", "Cornucopia", dead_tributes);
	HungerGames::event_list.emplace_back(event);

	dead_tributes = {};
	event.change_event(1, "Alive", "{Tribute1} found a spear in the cornucopia.", "Cornucopia", dead_tributes);
	HungerGames::event_list.emplace_back(event);

	event.change_event(1, "Alive", "{Tribute1} fled into the woods.", "Cornucopia", dead_tributes);
	HungerGames::event_list.emplace_back(event);

	event.change_event(1, "Alive", "{Tribute1} ran to the cornucopia and grabbed a sword.", "Cornucopia", dead_tributes);
	HungerGames::event_list.emplace_back(event);

	event.change_event(1, "Alive", "{Tribute1} found a pack full of knives in the cornucopia.", "Cornucopia", dead_tributes);
	HungerGames::event_list.emplace_back(event);

	event.change_event(1, "Alive", "{Tribute1} ran to the cornucopia and found some camping gear.", "Cornucopia", dead_tributes);
	HungerGames::event_list.emplace_back(event);

	dead_tributes = { "Tribute1" };
	event.change_event(2, "Death", "{Tribute1} got stabbed by {Tribute2} and died.", "Cornucopia", dead_tributes);
	HungerGames::event_list.emplace_back(event);

	event.change_event(2, "Death", "{Tribute2} slashed {Tribute1}'s leg and {Tribute1} bled to death.", "Cornucopia", dead_tributes);
	HungerGames::event_list.emplace_back(event);

	event.change_event(2, "Death", "{Tribute2} corned {Tribute1} in the cornucopia and bashed them in the head with a spear, killing them.", "Cornucopia", dead_tributes);
	HungerGames::event_list.emplace_back(event);

	dead_tributes = {};
	event.change_event(1, "Alive", "{Tribute1} grabbed a backpack full of supplies.", "Cornucopia", dead_tributes);
	HungerGames::event_list.emplace_back(event);

	event.change_event(1, "Alive", "{Tribute1} narrowly avoided a bow shot.", "Cornucopia", dead_tributes);
	HungerGames::event_list.emplace_back(event);

	event.change_event(1, "Alive", "{Tribute1} ran away from the cornucopia.", "Cornucopia", dead_tributes);
	HungerGames::event_list.emplace_back(event);

	dead_tributes = { "Tribute1" };
	event.change_event(1, "Death", "{Tribute1} blew up.", "Cornucopia", dead_tributes);
	HungerGames::event_list.emplace_back(event);

	event.change_event(2, "Death", "{Tribute1} was beaten to death by {Tribute2}.", "Cornucopia", dead_tributes);
	HungerGames::event_list.emplace_back(event);

	dead_tributes = {};
	event.change_event(1, "Alive", "{Tribute1} found a sword at the cornucopia.", "Cornucopia", dead_tributes);
	HungerGames::event_list.emplace_back(event);

	event.change_event(1, "Alive", "{Tribute1} found a backpack full of food.", "Cornucopia", dead_tributes);
	HungerGames::event_list.emplace_back(event);

	dead_tributes = { "Tribute1" };
	event.change_event(2, "Death", "{Tribute1} was shot with arrow by {Tribute2}.", "Normal", dead_tributes);
	HungerGames::event_list.emplace_back(event);

	event.change_event(2, "Death", "{Tribute1} and {Tribute2} got into a sword fight, eventually {Tribute2} won and killed {Tribute1}.", "Normal", dead_tributes);
	HungerGames::event_list.emplace_back(event);

	event.change_event(2, "Death", "{Tribute2} snuck up behind {Tribute1} and slit their throat.", "Normal", dead_tributes);
	HungerGames::event_list.emplace_back(event);
	
	event.change_event(2, "Death", "{Tribute2} betrayed {Tribute1} and killed them in their sleep.", "Normal", dead_tributes);
	HungerGames::event_list.emplace_back(event);

	event.change_event(2, "Death", "{Tribute1} was shot with arrow by {Tribute2}", "Normal", dead_tributes);
	HungerGames::event_list.emplace_back(event);

	dead_tributes = {};
	event.change_event(1, "Alive", "{Tribute1} found a pond with clean drinking water.", "Normal", dead_tributes);
	HungerGames::event_list.emplace_back(event);

	event.change_event(2, "Alive", "{Tribute1} climbed a tree to escape {Tribute2}.", "Normal", dead_tributes);
	HungerGames::event_list.emplace_back(event);

	event.change_event(1, "Alive", "{Tribute1} collected raspberries from a bush.", "Normal", dead_tributes);
	HungerGames::event_list.emplace_back(event);

	event.change_event(1, "Alive", "{Tribute1} hunted.", "Normal", dead_tributes);
	HungerGames::event_list.emplace_back(event);

	event.change_event(2, "Alive", "{Tribute1} spied on {Tribute2}.", "Normal", dead_tributes);
	HungerGames::event_list.emplace_back(event);

	event.change_event(1, "Alive", "{Tribute1} fell off a small cliff and injured their ankle.", "Normal", dead_tributes);
	HungerGames::event_list.emplace_back(event);
}

void HungerGames::set_option_tribute_list(std::string tribute_list_type) {
	HungerGames::option_tribute_list = tribute_list_type;
}

void HungerGames::set_option_sim_type(std::string sim_type) {
	HungerGames::option_sim_type = sim_type;
}

void HungerGames::set_tribute_list(std::vector<Tribute>& new_tribute_list) {
	HungerGames::tribute_list = new_tribute_list;
}

void HungerGames::add_tribute(Tribute& tribute) {

}

void HungerGames::add_alliance(std::vector<Tribute>& alliance) {

}

//Gets the number of lines in a txt file
int HungerGames::countLines(std::ifstream& filename)
{
	std::string line;
	int numLines = 0;
	while (getline(filename, line))
	{
		numLines++;
	}
	filename.clear();
	filename.seekg(0);
	return numLines;
}

//Generates a random number when given a range
int HungerGames::randNum(int lower, int upper) {
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(lower, upper); // define the range

	//generates a random number
	return distr(gen);
}

//Generates a random list of 12 boy names and 12 girl names.
void HungerGames::randomNames(std::vector<std::string>& boysNamesVector, std::vector<std::string>& girlsNamesVector) {
	std::ifstream boynames("name_lists/boynames.txt");
	int boyNamesSize = countLines(boynames);
	std::ifstream girlnames("name_lists/girlnames.txt");
	int girlNamesSize = countLines(girlnames);

	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> boys(1, boyNamesSize); // define the range
	std::uniform_int_distribution<> girls(1, girlNamesSize); // define the range

	std::vector<int> boysNamesLines;
	std::vector<int> girlsNamesLines;

	//These generate a list of 12 random numbers for both the boys and girls names withtin the range of the number of lines for each file.
	for (int i = 0; i < 12; i++)
	{
		int boyNameLine = boys(gen);
		bool differentLine = false;
		while (!differentLine)
		{
			if (std::find(boysNamesLines.begin(), boysNamesLines.end(), boyNameLine) != boysNamesLines.end())
			{
				boyNameLine = boys(gen);
			}
			else
			{
				differentLine = true;
			}
		}
		boysNamesLines.emplace_back(boyNameLine);
	}
	for (int i = 0; i < 12; i++)
	{
		int girlNameLine = girls(gen);
		bool differentLine = false;
		while (!differentLine)
		{
			if (std::find(girlsNamesLines.begin(), girlsNamesLines.end(), girlNameLine) != girlsNamesLines.end())
			{
				girlNameLine = girls(gen);
			}
			else
			{
				differentLine = true;
			}
		}
		girlsNamesLines.emplace_back(girlNameLine);
	}

	//These 2 loops then convert those line numbers into the corresponding line in the 2 names list files.
	std::string name;
	int i = 0;
	while (getline(boynames, name))
	{
		i++;
		if (std::find(boysNamesLines.begin(), boysNamesLines.end(), i) != boysNamesLines.end())
		{
			boysNamesVector.emplace_back(name);
		}
	}

	i = 0;
	while (getline(girlnames, name))
	{
		i++;
		if (std::find(girlsNamesLines.begin(), girlsNamesLines.end(), i) != girlsNamesLines.end())
		{
			girlsNamesVector.emplace_back(name);
		}
	}
}

void HungerGames::create_tribute_list() {
	//generates generic random tribute list and stores it in the tribute list variable. 
	//The first for loop generates 12 boys, 1 for each district and 12 girls, 1 for each district. The ages, heights, and weights are random. 
	if (HungerGames::option_tribute_list == "Realistic Random") {
		std::vector<std::string> boysNamesVector;
		std::vector<std::string> girlsNamesVector;
		randomNames(boysNamesVector, girlsNamesVector);

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
					height = randNum(64, 72);
				}
				else if (age_outlier <= 75) {
					height = randNum(73, 75);
				}
				else if (age_outlier <= 95) {
					height = randNum(76, 78);
				}
				else {
					height = 79;
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
				weight = randNum(125, 170);
			}
			else if (height <= 71) {
				weight = randNum(135, 200);
			}
			else if (height <= 74) {
				weight = randNum(150, 230);
			}
			else {
				weight = randNum(170, 250);
			}

			//Creates the final tribute object and puts it in the vector
			Tribute tribute(boysNamesVector[i], "Male", "Alive", i + 1, i + 1, age, height, weight, 0, 100);
			HungerGames::tribute_list.emplace_back(tribute);
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

			//Creates the final tribute object and puts it in the vector
			Tribute tribute(girlsNamesVector[i], "Female", "Alive", i + 13, i + 1, age, height, weight, 0, 100);
			HungerGames::tribute_list.emplace_back(tribute);
		}
	}
	else if (HungerGames::option_tribute_list == "Chaotic Random") {
		std::vector<std::string> boysNamesVector;
		std::vector<std::string> girlsNamesVector;
		randomNames(boysNamesVector, girlsNamesVector);
		//Completely random ages, height, weight. Not realistic at all.
		for (int i = 0; i < 12; i++) {
			Tribute tribute(boysNamesVector[i], "Male", "Alive", i + 1, i + 1, randNum(12, 18), randNum(60, 77), randNum(100, 250), 0, 100);
			HungerGames::tribute_list.emplace_back(tribute);
		}
		for (int i = 0; i < 12; i++) {
			Tribute tribute(girlsNamesVector[i], "Female", "Alive", i + 13, i + 1, randNum(12, 18), randNum(56, 72), randNum(80, 200), 0, 100);
			HungerGames::tribute_list.emplace_back(tribute);
		}
	}
	else {
		//Same as the Chaotic Random. Just in case something goes wrong and the tribute list option doesn't match the other settings.
		std::vector<std::string> boysNamesVector;
		std::vector<std::string> girlsNamesVector;
		randomNames(boysNamesVector, girlsNamesVector);
		for (int i = 0; i < 12; i++) {
			Tribute tribute(boysNamesVector[i], "Male", "Alive", i + 1, i + 1, randNum(12, 18), randNum(60, 77), randNum(100, 250), 0, 100);
			HungerGames::tribute_list.emplace_back(tribute);
		}
		for (int i = 0; i < 12; i++) {
			Tribute tribute(girlsNamesVector[i], "Female", "Alive", i + 13, i + 1, randNum(12, 18), randNum(56, 72), randNum(80, 200), 0, 100);
			HungerGames::tribute_list.emplace_back(tribute);
		}
	}

}

//Clears out the tribute list so a new tribute roster can be generated.
void HungerGames::reset_tribute_list() {
	HungerGames::tribute_list.clear();
}

int HungerGames::get_alive_tributes(std::vector<Tribute>& tribute_list) {
	int num_alive_tributes = 0;
	for (Tribute tribute : tribute_list) {
		if (tribute.get_status() == "Alive") {
			num_alive_tributes++;
		}
	}
	return num_alive_tributes;
}
