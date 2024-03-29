﻿#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <map>
#include <thread>
#include <mutex>
#include <vector>
#include <windows.h>
#include "Config.h"
#include "TankRenderer.h"
#include "BulletRenderer.h"
#include "Menu.h"
#include "Positions.h"
#include "MenuRenderer.h"
#include "GameMap.h"
#include "Server.h"
#include "Client.h"
#pragma comment (lib, "ws2_32.lib")

#define KEY_ENTER 13
#define KEY_ESCAPE 27
#define KEY_SPACE 32



void mainMenu();
void newGameMenu();;
void settingsMenu();
void settingsColorMenu();
void setConfigName(char** argv, char** envp);
void tankGame();
void joinServer();


int main(int argc, char** argv, char** envp)
{
	setConfigName(argv, envp);
	mainMenu();

	return 0;
}



void clientTankGame()
{

}


void joinServer()
{
	system("CLS");
	std::string name, newPort;
	std::vector <std::string> menuItems;

	menuItems.push_back("Name: ");

	Menu newMenu(menuItems);
	MenuRenderer newMenuRenderer(&newMenu);
	newMenuRenderer.setMenuActiveColor(Config::getInstance().getCurrentMenuColor());
	newMenuRenderer.updateMenuPosition();
	newMenuRenderer.render();

	std::getline(std::cin, name);
	newMenuRenderer.clearTerminal();

	system("CLS");
	
	Client newClient(name);
	newClient.initializeClientServer();

	return;
}

void tankGame()
{

	enum players { PRIMARY, SECONDARY, NPC };
	struct positionInformation {
		int x, y;
	};
	int inactiveTank;
	std::vector <positionInformation> tanksInformation;
	std::vector <positionInformation> bulletInformation;


	TankRenderer Tanks[] = { TankRenderer( 0), TankRenderer( 1), TankRenderer( 2) };

	BulletRenderer newBullet(&Tanks[0]);
	Tanks[0].renderTank();
	Tanks[1].renderTank();
	Tanks[2].renderTank();

	std::thread animateDeath(&TankRenderer::deathAnimation, &Tanks[1]);
	std::thread animateBullets(&BulletRenderer::renderBullets, &newBullet);
	animateBullets.detach();
	animateDeath.detach();

	GameMap::getInstance()->renderMap();
	while (true)
	{
		bool isKeyPressed = _kbhit();
		if (isKeyPressed)
		{

			int keyPressed = _getch();
			if (keyPressed == KEY_SPACE)
			{
				newBullet.addBullet();
			}
			else if (keyPressed == KEY_ESCAPE)
			{
				break;
			}
			else
			{
				Tanks[0].moveTank();
			}
		}
		if (newBullet.isTankActive() != -1)
		{
			inactiveTank = newBullet.isTankActive();
			if (Tanks[inactiveTank].isTankDisabled())
				Tanks[inactiveTank].disableTank();
		}
	}

	return;
}


struct Bullet {
	int x, y;
};

void mainMenu()
{

	Config::getInstance().loadConfig();

	std::vector <std::string> MainMenuItems;
	MainMenuItems.push_back("New Game");
	MainMenuItems.push_back("Settings");
	MainMenuItems.push_back("Exit");

	Menu menu(MainMenuItems);
	MenuRenderer renderer(&menu);

	renderer.render();

	while (true)
	{
		bool isKeyPressed = _kbhit();
		if (renderer.consoleWindowSizeChanged() || isKeyPressed)
		{
			if (isKeyPressed)
			{
				int keyPressed = _getch();
				if (keyPressed == KEY_ENTER)
				{
					renderer.clearTerminal();
					if (renderer.getActiveTitleID() == 1)
						newGameMenu();
					else if (renderer.getActiveTitleID() == 2)
						settingsMenu();
					else if (renderer.getActiveTitleID() == 3)
						return;
				}
				else
					renderer.updateActiveTitleID();
			}

			renderer.setMenuActiveColor(Config::getInstance().getCurrentMenuColor());
			renderer.clearTerminal();

			renderer.updateMenuPosition();

			renderer.render();

		}
	}

}

void newGameMenu()
{
	std::vector <std::string> newGameMenuItems;

	newGameMenuItems.push_back("Create Server");
	newGameMenuItems.push_back("Join Server");
	newGameMenuItems.push_back("Previous Menu");

	Menu menu(newGameMenuItems);
	MenuRenderer renderer(&menu);

	renderer.render();

	while (true)
	{
		bool isKeyPressed = _kbhit();

		if (renderer.consoleWindowSizeChanged() || isKeyPressed || renderer.menuColorChanged())
		{
			if (isKeyPressed)
			{
				int keyPressed = _getch();
				if (keyPressed == KEY_ENTER)
				{
					renderer.clearTerminal();
					if (renderer.getActiveTitleID() == 1)
					{
						system("CLS");
						Server newServer;
						newServer.generateServer();
						return;

					}
					if (renderer.getActiveTitleID() == 2)
					{
						joinServer();
					}
					if (renderer.getActiveTitleID() == 3)
						return;
				}
				else
					renderer.updateActiveTitleID();
			}
			if (renderer.menuColorChanged())
				renderer.setMenuActiveColor(Config::getInstance().getCurrentMenuColor());
			renderer.clearTerminal();

			renderer.updateMenuPosition();

			renderer.render();

		}
	}

}

void settingsMenu()
{
	std::vector <std::string> newGameMenuItems;

	newGameMenuItems.push_back("Menu Color");
	newGameMenuItems.push_back("Resolution");
	newGameMenuItems.push_back("Sound");
	newGameMenuItems.push_back("Multi-player settings");
	newGameMenuItems.push_back("Previous Menu");

	Menu menu(newGameMenuItems);
	MenuRenderer renderer(&menu);

	renderer.render();

	while (true)
	{
		bool isKeyPressed = _kbhit();

		if (renderer.consoleWindowSizeChanged() || isKeyPressed)
		{
			renderer.setMenuActiveColor(Config::getInstance().getCurrentMenuColor());
			if (isKeyPressed)
			{
				int keyPressed = _getch();
				if (keyPressed == KEY_ENTER)
				{
					renderer.clearTerminal();
					if (renderer.getActiveTitleID() == 1)
						settingsColorMenu();
					if (renderer.getActiveTitleID() == 5)
						return;
				}
				else
					renderer.updateActiveTitleID();
			}
			if (renderer.menuColorChanged())
				renderer.setMenuActiveColor(Config::getInstance().getCurrentMenuColor());

			renderer.clearTerminal();

			renderer.updateMenuPosition();

			renderer.render();

		}
	}

}

void settingsColorMenu() {

	std::vector <std::string> colorSettingsMenuItems;

	colorSettingsMenuItems.push_back("Green");
	colorSettingsMenuItems.push_back("Red");
	colorSettingsMenuItems.push_back("Purple");
	colorSettingsMenuItems.push_back("Yellow");
	colorSettingsMenuItems.push_back("Default");


	Menu menu(colorSettingsMenuItems);
	MenuRenderer renderer(&menu);

	renderer.render();

	while (true)
	{
		bool isKeyPressed = _kbhit();

		if (renderer.consoleWindowSizeChanged() || isKeyPressed)
		{
			if (isKeyPressed)
			{
				int keyPressed = _getch();
				if (keyPressed == KEY_ENTER)
				{

					renderer.clearTerminal();
					enum consoleColor {
						RED = 4, GREEN = 2, PURPLE = 5, YELLOW = 6, DEFAULT = 7
					};
					if (renderer.getActiveTitleID() == 1)
					{
						Config::getInstance().saveNewMenuColor(consoleColor::GREEN);
						renderer.setMenuActiveColor(Config::getInstance().getCurrentMenuColor());
						return;
					}
					if (renderer.getActiveTitleID() == 2)
					{
						Config::getInstance().saveNewMenuColor(consoleColor::RED);
						renderer.setMenuActiveColor(Config::getInstance().getCurrentMenuColor());
						return;
					}
					if (renderer.getActiveTitleID() == 3)
					{
						Config::getInstance().saveNewMenuColor(consoleColor::PURPLE);
						renderer.setMenuActiveColor(Config::getInstance().getCurrentMenuColor());
						return;
					}
					if (renderer.getActiveTitleID() == 4)
					{
						Config::getInstance().saveNewMenuColor(consoleColor::YELLOW);
						renderer.setMenuActiveColor(Config::getInstance().getCurrentMenuColor());
						return;
					}
					if (renderer.getActiveTitleID() == 5)
					{
						Config::getInstance().saveNewMenuColor(consoleColor::DEFAULT);
						renderer.setMenuActiveColor(Config::getInstance().getCurrentMenuColor());
						return;
					}
					if (renderer.getActiveTitleID() == 6)
					{
						return;
					}
				}
				else
					renderer.updateActiveTitleID();
			}
			renderer.clearTerminal();

			renderer.updateMenuPosition();

			renderer.render();

		}
	}
}

std::string environmentalValuesScanner(char** envp)
{
	std::map <std::string, std::string> envVariables;
	for (char** env = envp; *env != 0; *(env++))
	{
		std::string firstValue, secondValue, variable = *env;
		int i = variable.find_first_of('=');
		firstValue.append(variable, 0, i);
		secondValue.append(variable, i + 1, variable.length());
		envVariables.insert(std::make_pair(firstValue, secondValue));
	}

	if (!envVariables["CONFIG"].empty())
		return envVariables["CONFIG"];
	return "NULL";
}

void setConfigName(char** argv, char** envp)
{
	std::string envConfigValue = environmentalValuesScanner(envp);
	if (argv[1] != NULL)
	{
		Config::getInstance().changeConfigName(argv[1]);
	}
	else if (envConfigValue != "NULL")
	{
		Config::getInstance().changeConfigName(envConfigValue);
	}
	else
	{
		Config::getInstance().changeConfigName("config.txt");
	}

	system("cls");
}
