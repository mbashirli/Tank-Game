#include "Config.h"

Config& Config::getInstance()
{
	static Config instance;
	return instance;
}

Config::Config() {
	configFileName = "config.txt";
	menuColor = 7;
}
Config::~Config()
{
	configFile.close();
}

void Config::loadConfig()
{
	std::ifstream configFile(configFileName);
	int key;
	if (configFile.is_open())
	{
		while (configFile >> key)
		{
			configKeys.push_back(key);
		}
	}
	else
	{
		createConfigFile();
	}
	this->menuColor = configKeys[0];
	configFile.close();
}

void Config::saveNewMenuColor(int newMenuColor)
{

	this->menuColor = newMenuColor;
	std::ofstream configFile(configFileName);
	configFile << this->menuColor;
}

void Config::createConfigFile()
{
	std::ofstream configFile(configFileName);
	configFile << this->menuColor;
	configFile.close();
	loadConfig();
}

int Config::getCurrentMenuColor()
{
	return this->menuColor;
}

void Config::changeConfigName(std::string newConfigName)
{
	configFileName = newConfigName;
}
