#include "Menu.h"

Menu::Menu()
{
}

Menu::Menu(std::vector <std::string> ops)
{
	setOptions(ops);
}	 
  

void Menu::setOptions(std::vector <std::string> ops)
{

	for (int i = 0; i < ops.size(); i++)
		options.push_back(ops[i]);
}

std::vector <std::string> Menu::getOptions()
{
	return options;
}

