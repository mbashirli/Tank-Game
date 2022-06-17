#pragma once
#include <iostream>
#include <vector>

class Menu
{
public:
	Menu(std::vector<std::string> ops);
	void setOptions(std::vector <std::string> ops);
	std::vector <std::string> getOptions();
private:
	std::vector <std::string> options;
};

