#pragma once
#include <string>
#include <vector>
#include "tributes.h"
#include "event.h"
#include "hungergames.h"

class Menus {
public:
	Menus();
	void start_game(HungerGames& simulation);
	void SaveRoster(std::string& roster_name, std::vector<Tribute>& custom_tribute_list);
	void CustomRosterList(std::string& path, std::vector<std::string>& roster_list);
	void LoadCustomRoster(std::string& roster_name, std::vector<Tribute>& tribute_roster);
	void custom_tribute_list();
	void view_tribute_list(std::vector<Tribute> tributeList);
	void CreateGame(HungerGames& simulation);
	void SimTypeOption(HungerGames& simulation);
	void TributeCreationOption(HungerGames& simulation);
};
