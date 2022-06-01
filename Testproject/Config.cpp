#include "Config.h"

Config::Config() {}

Config& Config::getInstance()
{
	if (!instance)
		instance = new Config;
	return *instance;
}