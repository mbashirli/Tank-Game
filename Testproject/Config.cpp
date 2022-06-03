#include "Config.h"


Config& Config::getInstance()
{
    static Config instance;
    return instance;
}

Config::Config(){
	
	configSettings.insert(std::map <std::string, std::string>:: value_type("Menu Color", "Default"));

}
Config::~Config()
{
    configFile.close();
}

void Config::loadConfig()
{
	configFile.open(configFileName);
	std::map<std::string, std::string>::iterator itr;
	itr = configSettings.begin();
	std::string line;
	if (configFile.is_open())
	{
		while (std::getline(configFile, line))
		{
			configSettings[itr->first] = line;
			itr++;
		}
	}
	else
	{
		std::ofstream newConfigFile;
		newConfigFile.open("config.txt");
		loadConfig();
		configFile.close();
	}

	configFile.close();
}

void Config::saveNewMenuColor(std::string newMenuColor)
{
	configSettings["Menu Color"] = newMenuColor;
	std::ofstream configFile("config.txt");
	configFile << configSettings["Menu Color"];
}

std::string Config::getCurrentMenuColor()
{
	return configSettings["Menu Color"];
}
