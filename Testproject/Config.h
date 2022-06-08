#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>

class Config
{
public:
	Config();
	~Config();
	static Config& getInstance();
	void loadConfig();
	void saveNewMenuColor(int newcolor);
	void createConfigFile();
	void changeConfigName(std::string newConfigName);
	int getCurrentMenuColor();

private:
	enum ConfigKeys { MENU_COLOR };
	static Config* instance;
	int menuColor;
	std::ifstream configFile;
	std::vector<int> configKeys;
	std::string configFileName;
	std::map <std::string, std::string> configSettings;
};

