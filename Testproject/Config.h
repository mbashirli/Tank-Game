#pragma once
#include <string>


class Config
{
public:
	std::string menuColor;
	static Config& getInstance();
private:
	~Config() {};
	Config() {};
	std::string menuColor;
	static Config* instance;

	
};

