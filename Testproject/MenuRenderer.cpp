#include "MenuRenderer.h"


MenuRenderer::MenuRenderer(Menu* _menu)
{
	this->menu = _menu;
	activeTitleID = 1;
	setMenuActiveColor("default");
}

void MenuRenderer::go_to_xy(short x, short y)
{
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}


MenuStartPosition MenuRenderer::getScreenBufferInfo()
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
	MenuStartPosition coordinates;
	coordinates.x = csbiInfo.dwSize.X / 2;
	coordinates.y = (csbiInfo.srWindow.Bottom - csbiInfo.srWindow.Top) / 2;
	return coordinates;
}

void MenuRenderer::outCenteredText()
{
	std::vector <std::string> input = this->menu->getOptions();
	for (int i = 0; i < input.size(); i = i + 1)
	{
		setTitleInactiveColor();
		if (i + 1 == activeTitleID)
			setTitleActiveColor();
		go_to_xy(menuPosition.x, menuPosition.y + i);
		std::cout << input[i] << std::endl;
	}

}

void MenuRenderer::setMenuActiveColor(std::string menuColor)
{
	if (menuColor == "Green")
		this->menuColor = 2;
	else if (menuColor == "Red")
		this->menuColor = 4;
	else if (menuColor == "Purple")
		this->menuColor = 5;
	else if (menuColor == "Yellow")
		this->menuColor = 6;
	else
		this->menuColor = 7; // default: white
}

void MenuRenderer::setTitleActiveColor()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
}

void MenuRenderer::setTitleInactiveColor()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, this->menuColor);
}



void MenuRenderer::updateActiveTitleID()
{
	int lastOptionId = menu->getOptions().size();
	if (_kbhit())
	{
		int pressedKey = _getch();
		if (pressedKey == UP)
		{
			if (activeTitleID == 1)
				activeTitleID = lastOptionId;
			else activeTitleID -= 1;
		}
		else if (pressedKey == DOWN)
		{
			if (activeTitleID == lastOptionId)
				activeTitleID = 1;
			else activeTitleID += 1;
		}
		else
		{
			return;
		}
	}
}

bool MenuRenderer::consoleWindowSizeChanged() {
	MenuStartPosition currentCoord = getScreenBufferInfo();
	if (menuPosition.x != currentCoord.x || menuPosition.y != currentCoord.y)
	{
		return true;
	}
	return false;
}

void MenuRenderer::updateMenuPosition() {
	MenuStartPosition currentCoord = getScreenBufferInfo();
	menuPosition = currentCoord;
}

void MenuRenderer::render()
{
	outCenteredText();
	showConsoleCursor(false);
}

void MenuRenderer::clearTerminal()
{
	std::vector<std::string> vector = this->menu->getOptions();
	int vector_size = vector.size();

	for (int i = 0; i < vector_size; i = i + 1)
	{
		go_to_xy(menuPosition.x, menuPosition.y + i);
		for (int j = 0; j < vector[i].size(); j = j + 1)
			std::cout << " ";
	}

	for (int j = 0; j < vector_size; j = j + 1)
	{
		go_to_xy(0, menuPosition.y + j);
		for (int i = 0; i < vector[j].size(); i = i + 1)
			std::cout << " ";
	}
	go_to_xy(0, 0);
}

void MenuRenderer::showConsoleCursor(bool showFlag)
{

	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);

}

int MenuRenderer::getActiveTitleID()
{
	return activeTitleID;
}