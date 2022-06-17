#pragma once
#include <mutex>
#include <iostream>

class Application
{
public:
	static Application* getInstance();
	void lockCout();
	void unlockCout();

private:
	Application() {};
	static Application* instance;
	std::mutex* coutMutex;
};
