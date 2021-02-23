#pragma once
#include <string>

class Event {
private:
	int num_involved_tributes;
	std::string event_result, event_statement, event_tag;

public:
	Event(int tributes, std::string result, std::string statement, std::string tag);
	int get_num_tributes();
	std::string get_event_result();
	std::string get_event_statement();
	std::string get_event_tag();
	void change_event(int tributes, std::string result, std::string statement, std::string tag);
};