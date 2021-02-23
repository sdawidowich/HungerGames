#pragma once
#include <string>
#include <vector>
#include "tributes.h"

class Game {
private:
	int time, day;
	std::string option_tribute_list, option_sim_type;
	std::vector<Tribute> tribute_list, alliance_list;
public:
	Game();
	std::vector<Tribute> get_tribute_list();
	std::vector<Tribute> get_alliance_list();
	int get_time();
	int get_day();
	void set_time(int new_time);
	void set_day(int new_day);
	void start_game();
	void CreateGame();
	void SimTypeOption();
	void TributeCreationOption();
	void sim_day();
};