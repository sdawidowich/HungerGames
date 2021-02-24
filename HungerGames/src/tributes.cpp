#include <iostream>
#include <string>
#include "tributes.h"

Tribute::Tribute(std::string c_name, std::string c_gender, std::string c_status, int c_id, int c_district, int c_age, int c_height, int c_weight, int c_kills, int c_health)
	: name(c_name), gender(c_gender), status(c_status), id(c_id), district(c_district), age(c_age), height(c_height), weight(c_weight), kills(c_kills), health(c_health) { }

std::string inch_to_feet(int inches) {
	int feet = inches / 12;
	int new_inches = inches % 12;
	std::string height = std::to_string(feet) + "'" + std::to_string(new_inches) + '"';
	return height;
}

void Tribute::profile() {
	std::cout << "Name: " << Tribute::name << "\nDistrict: " << Tribute::district << "\nAge: " << Tribute::age << "\nGender: " << Tribute::gender << "\nHeight: " << inch_to_feet(Tribute::height);
	std::cout << "\nWeight: " << Tribute::weight << " lbs.\nStatus: " << Tribute::status << "\nHealth: " << Tribute::health << "/100\nKills: " << Tribute::kills << "\n" << std::endl;
}

std::string Tribute::get_name() {
	return Tribute::name;
}

std::string Tribute::get_gender() {
	return Tribute::gender;
}

std::string Tribute::get_status() {
	return Tribute::status;
}

int Tribute::get_id() {
	return Tribute::id;
}

int Tribute::get_district() {
	return Tribute::district;
}

int Tribute::get_age() {
	return Tribute::age;
}

int Tribute::get_height() {
	return Tribute::height;
}

int Tribute::get_weight() {
	return Tribute::weight;
}

int Tribute::get_kills() {
	return Tribute::kills;
}

int Tribute::get_health() {
	return Tribute::health;
}

void Tribute::set_status(std::string new_status) {
	Tribute::status = new_status;
}

void Tribute::set_kills(int new_kills) {
	Tribute::kills = new_kills;
}

void Tribute::set_health(int new_health) {
	Tribute::health = new_health;
}