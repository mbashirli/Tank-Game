#include "Config.h"


Config& Config::getInstance()
{
    static Config instance;
    return instance;
}

Config::Config()
{
    configFile.open("config.txt");
	if (configFile.is_open())
	{
		while (configFile)
		{
			std::getline(configFile, menuColor);
		}
	}
}

Config::~Config()
{
    configFile.close();
}

void Config::loadConfig()
{

}

void Config::updateConfigFile()
{
	configFile << menuColor;
}

void Config::saveNewMenuColor(std::string newMenuColor)
{
	menuColor = newMenuColor;
	updateConfigFile();
}

std::string Config::getCurrentMenuColor()
{
	return menuColor;
}