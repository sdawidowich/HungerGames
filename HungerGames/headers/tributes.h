#pragma once
#include <string>

class Tribute {
private:
	std::string name, gender, status;
	int id, district, age, height, weight, kills, health;
public:
	Tribute(std::string c_name, std::string c_gender, std::string c_status, int c_id, int c_district, int c_age, int c_height, int c_weight, int c_kills, int c_health);
	void profile();
	std::string get_name();
	std::string get_gender();
	std::string get_status();
	int get_id();
	int get_district();
	int get_age();
	int get_height();
	int get_weight();
	int get_kills();
	int get_health();
	void set_status(std::string new_status);
	void set_kills(int new_kills);
	void set_health(int new_health);
};