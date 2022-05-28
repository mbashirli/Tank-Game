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
	get_screen_buffer_info();
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
		int string_length = m1->get_options()[i].length();
		if (localTempX < struct_coordinates.x || localTempX > struct_coordinates.x)
		{
			go_to_xy(localTempX, localTempY);
			while (string_length != 0)
			{
				std::cout << " ";
				string_length -= 1;
			}
			localTempY += 1;
		}
		else if (localTempY < struct_coordinates.y)
		{
			go_to_xy(localTempX, localTempY);
			while (string_length != 0)
			{
				std::cout << " ";
				string_length -= 1;
			}
			localTempX += 1;
		}
		else if (localTempY > struct_coordinates.y)
		{;
			go_to_xy(localTempX, localTempY);
			while (string_length != 0)
			{
				std::cout << " ";
				string_length -= 1;
			}
			localTempX += 1;
		}
	}
}


