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
		ClearScreen();
		ShowConsoleCursor(false);
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


void MenuRenderer::ShowConsoleCursor(bool showFlag)
{
	{
		HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

		CONSOLE_CURSOR_INFO     cursorInfo;

		GetConsoleCursorInfo(out, &cursorInfo);
		cursorInfo.bVisible = showFlag; // set the cursor visibility
		SetConsoleCursorInfo(out, &cursorInfo);
	}
}

void MenuRenderer::ClearScreen()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR)' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}