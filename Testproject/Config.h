#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <map>


class Config
{
public:
	Config();
	~Config();
	static Config& getInstance();
	void loadConfig();
	void saveNewMenuColor(std::string newMenuColor);
	std::string getCurrentMenuColor();

private:
	static Config* instance;
	std::fstream configFile;
	std::map <std::string, std::string> configSettings;
};

