#pragma once
#include <string>
#include <vector>
#include "tributes.h"

class Event {
private:
	int num_involved_tributes;
	std::string event_result, event_statement, event_tag;
	std::vector<std::string> dead_tributes;

public:
	Event(int tributes, std::string result, std::string statement, std::string tag, std::vector<std::string> dead);
	int get_num_tributes();
	std::string get_event_result();
	std::string get_event_statement();
	std::string get_event_tag();
	std::vector<std::string> get_deaths();
	void change_event(int tributes, std::string result, std::string statement, std::string tag, std::vector<std::string> dead);
};