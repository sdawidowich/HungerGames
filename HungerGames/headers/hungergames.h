#pragma once
#include <string>
#include <vector>
#include "tributes.h"
#include "event.h"

class Game {
private:
	int time, day;
	std::string option_tribute_list, option_sim_type;
	std::vector<Tribute> tribute_list, alliance_list;
	std::vector<Event> event_list;
public:
	Game();
	std::vector<Tribute> get_tribute_list();
	std::vector<Tribute> get_alliance_list();
	int get_time();
	int get_day();
	std::vector<Event> get_event_list();
	void set_time(int new_time);
	void set_day(int new_day);
	void set_events();
	void start_game();
	void custom_tribute_list();
	void create_tribute_list();
	void view_tribute_list();
	void CreateGame();
	void SimTypeOption();
	void TributeCreationOption();
	void sim_day();
};
