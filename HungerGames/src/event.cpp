#include "event.h"

Event::Event(int tributes, std::string result, std::string statement, std::string tag, std::vector<std::string> dead)
	: num_involved_tributes(tributes), event_result(result), event_statement(statement), event_tag(tag), dead_tributes(dead) { }

int Event::get_num_tributes() {
	return Event::num_involved_tributes;
}

std::string Event::get_event_result() {
	return Event::event_result;
}

std::string Event::get_event_statement() {
	return Event::event_statement;
}

std::string Event::get_event_tag() {
	return Event::event_tag;
}

std::vector<std::string> Event::get_deaths() {
	return Event::dead_tributes;
}

void Event::change_event(int tributes, std::string result, std::string statement, std::string tag, std::vector<std::string> dead) {
	Event::num_involved_tributes = tributes;
	Event::event_result = result;
	Event::event_statement = statement;
	Event::event_tag = tag;
	Event::dead_tributes = dead;
}
