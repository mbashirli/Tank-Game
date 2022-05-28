#include "Menu.h"

Menu::Menu()
{
}

Menu::Menu(std::vector <std::string> ops)
{
	set_options(ops);
}	 
  

void Menu::set_options(std::vector <std::string> ops)
{

	for (int i = 0; i < ops.size(); i++)
		options.push_back(ops[i]);
	
}

std::vector <std::string> Menu::get_options()
{
	return options;
}

