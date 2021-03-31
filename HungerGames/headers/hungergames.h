#pragma once
#include <string>
#include <vector>
#include "tributes.h"
#include "event.h"

class HungerGames {
private:
	int time, day;
	std::string option_tribute_list, option_sim_type;
	std::vector<Tribute> tribute_list, alliance_list;
	std::vector<Event> event_list;
public:
	HungerGames();
	void realistic_sim();
	void random_sim();
	void chaotic_random_sim();
	std::vector<Tribute> get_tribute_list();
	std::vector<Tribute> get_alliance_list();
	int get_time();
	int get_day();
	std::string get_option_tribute_list();
	std::string get_option_sim_type();
	std::vector<Event> get_event_list();
	void set_time(int new_time);
	void set_day(int new_day);
	void set_events();
	void set_option_tribute_list(std::string tribute_list_type);
	void set_option_sim_type(std::string sim_type);
	void set_tribute_list(std::vector<Tribute>& new_tribute_list);
	void add_tribute(Tribute& tribute);
	void add_alliance(std::vector<Tribute>& alliance);
	int countLines(std::ifstream& filename);
	int randNum(int lower, int upper);
	void randomNames(std::vector<std::string>& boysNamesVector, std::vector<std::string>& girlsNamesVector);
	void create_tribute_list();
	void reset_tribute_list();
};