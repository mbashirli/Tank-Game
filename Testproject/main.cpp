#include <iostream>
#include <windows.h>
#include <thread>
#include "Menu.h"
#include "MenuRenderer.h"
#include <vector>


int main() {

	std::vector <std::string> MainMenuItems;
	MainMenuItems.push_back("Menyu 1");
	MainMenuItems.push_back("Menyu 2");
	MainMenuItems.push_back("Menyu 3");

	Menu m1(MainMenuItems);
	MenuRenderer menu;

	while (true)
	{
		menu.render(&m1);
	}

	return 0;
}