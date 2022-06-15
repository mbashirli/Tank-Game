#include "Application.h"

Application* Application::instance;

Application* Application::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Application();
		instance->coutMutex = new std::mutex();
	}
	return instance;
}

void Application::lockCout()
{
	Application::coutMutex->lock();
}

void Application::unlockCout()
{
	Application::coutMutex->unlock();
}