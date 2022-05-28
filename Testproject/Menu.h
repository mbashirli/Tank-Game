#pragma once
#include <iostream>
#include <vector>
#include <algorithm>


class Menu
{
public:
	Menu();
	Menu(std::vector<std::string> ops);
	void set_options(std::vector <std::string> ops);
	std::vector <std::string> get_options();
	void render();
private:
	std::vector <std::string> options;
};

