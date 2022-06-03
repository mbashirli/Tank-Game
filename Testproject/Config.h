#pragma once
#include <string>
#include <iostream>
#include <fstream>


class Config
{
public:
	Config();
	~Config();
	static Config& getInstance();
	void loadConfig();
	void saveNewMenuColor(std::string newMenuColor);
	void updateConfigFile();
	std::string getCurrentMenuColor();

private:
	static Config* instance;
	std::string menuColor;
	std::fstream configFile;
};

