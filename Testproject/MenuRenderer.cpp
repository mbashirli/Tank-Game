#include "MenuRenderer.h"


MenuRenderer::MenuRenderer() {}
MenuRenderer::~MenuRenderer() {}

void MenuRenderer::go_to_xy()
{
	COORD p = { struct_coordinates.x, struct_coordinates.y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void MenuRenderer::go_to_xy(short x, short y)
{
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void MenuRenderer::get_screen_buffer_info()
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
	struct_coordinates.x = csbiInfo.dwSize.X / 2;

	struct_coordinates.y = (csbiInfo.srWindow.Bottom - csbiInfo.srWindow.Top) / 2;
}

void MenuRenderer::out_centered_text(std::vector <std::string> input)
{
	for (int i = 0; i < input.size(); i = i + 1)
	{
		go_to_xy();
		std::cout << input[i] << std::endl;
		struct_coordinates.y = struct_coordinates.y + 1;
	}

}

void MenuRenderer::render(Menu* m1)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
	get_screen_buffer_info();
	ShowConsoleCursor(false);
	if (tempX != struct_coordinates.x || tempY != struct_coordinates.y)
	{
		clear_terminal(m1);
		tempX = struct_coordinates.x; tempY = struct_coordinates.y;
		out_centered_text(m1->get_options());
	}
}

void MenuRenderer::clear_terminal(Menu* m1)
{
	int options_vector_size = m1->get_options().size();
	int localTempX = tempX, localTempY = tempY;

	for (int i = 0; i < options_vector_size; i = i + 1)
	{
		go_to_xy(0, struct_coordinates.y + i);
		for (int j = 0; j < m1->get_options()[i].length(); j = j + 1)
			std::cout << " ";
	}


	for (int i = 0; i < options_vector_size; i = i + 1)
	{
		int string_length = m1->get_options()[i].length();
		if (localTempX < struct_coordinates.x && localTempY == struct_coordinates.y)
		{
			//std::cout << localTempX << "  " << struct_coordinates.x << "1" << std::endl;
			go_to_xy(localTempX, localTempY);
			while (string_length != 0)
			{
				std::cout << " ";
				string_length -= 1;
			}
			localTempY += 1;
			go_to_xy(0, 0);
		
}
		else if (localTempX < struct_coordinates.x && localTempY > struct_coordinates.y) {
			//std::cout << localTempX << "  " << struct_coordinates.x << " 2" << std::endl;
			go_to_xy(localTempX, localTempY);
			while (string_length != 0)
			{
				std::cout << " ";
				string_length -= 1;
			}
			localTempY += 1;
			go_to_xy(0, 0);

		}
		else if (localTempX < struct_coordinates.x && localTempY < struct_coordinates.y)
		{
			//std::cout << localTempX << "  " << struct_coordinates.x << " 3" << std::endl;
			go_to_xy(localTempX, localTempY);
			while (string_length != 0)
			{
				std::cout << " ";
				string_length -= 1;
			}
			localTempY += 1;
			go_to_xy(0, 0);
		}
		else if (localTempX > struct_coordinates.x && localTempY > struct_coordinates.y) {
			//std::cout << localTempX << "  " << struct_coordinates.x << "4";
			go_to_xy(localTempX, localTempY);
			while (string_length != 0)
			{
				std::cout << " ";
				string_length -= 1;
			}
			localTempY += 1;
			go_to_xy(0, 0);
		}
		else if (localTempX > struct_coordinates.x && localTempY == struct_coordinates.y) {
			//std::cout << localTempX << "  " << struct_coordinates.x << "4";
			go_to_xy(localTempX, localTempY);
			while (string_length != 0)
			{
				std::cout << " ";
				string_length -= 1;
			}
			localTempY += 1;
			go_to_xy(0, 0);
		}
		else if (localTempY < struct_coordinates.y )
		{
			//std::cout << localTempX << "  " << struct_coordinates.x << "5";
			go_to_xy(localTempX, localTempY);
			while (string_length != 0)
			{
				std::cout << " ";
				string_length -= 1;
			}
			localTempX += 1;
		}
		else if (localTempY > struct_coordinates.y)
		{
			//std::cout << localTempX << "  " << struct_coordinates.x << "6";
			go_to_xy(localTempX, localTempY);
			while (string_length != 0)
			{
				std::cout << " ";
				string_length -= 1;
			}
			localTempY += 1;
		}
		else {
			std::cout << localTempX << "  " << struct_coordinates.x << "7";
				
		}
	}
	
}

void MenuRenderer::ShowConsoleCursor(bool showFlag)
{

	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);

}

void MenuRenderer::clearterminal(int x, int  y)
{

	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}