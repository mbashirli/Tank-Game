#include <iostream>
#include <windows.h>
#include <thread>


void MainMenu();
void Menu1();
void Menu2();

struct terminalBufferSize {
    short x;
    short y;
};

// set cursor position
void go_to_xy(short x, short y)
{
    COORD p = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

// get terminal size info
void get_screen_buffer_info(terminalBufferSize* ts)
{
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
    ts->x = csbiInfo.dwSize.X;
    ts->y = csbiInfo.srWindow.Bottom - csbiInfo.srWindow.Top;
}

static int temp1, temp2;
terminalBufferSize* ts = new terminalBufferSize;

void set_centered_text()
{
    while (true)
    {
        get_screen_buffer_info(ts);
        std::cout << "prt" << std::endl;
        if (ts->x != temp1 || ts->y != temp2)
        {

            go_to_xy(temp1 / 2, temp2 / 2);
            temp1 = ts->x; temp2 = ts->y;
        }
    }
}


void MainMenu()
{

    bool leaveApp = false;

    while (leaveApp!=true)
    {
        std::cout<<std::endl;

        std::cout<<"Menyuya xoş gəlmişsiniz."<<std::endl;
        std::cout<<"Menyu - 1"<<std::endl;
        std::cout<<"Menyu - 2"<<std::endl;
        std::cout<<"Proqramı sonlandır - 0"<<std::endl;

        int input;
        std::cout<<"Seçiminiz: ";
        std::cin>>input;

        switch(input)
        {
            case 0:
                leaveApp = true;
                break;
            case 1:
                leaveApp = true;
                Menu1();
                break;
            case 2:
                leaveApp = true;
                Menu2();
                break;
            default:
                break;
        }
    }

}

void Menu1()
{

    bool leaveMenu1 = false;
    while (leaveMenu1!= true)
    {
        std::cout<<std::endl;
        std::cout<<"Menyu 1 Seçim - 1"<<std::endl;
        std::cout<<"Seçim - 2"<<std::endl;
        std::cout<<"Əvvəlki menyu - 0"<<std::endl;
        std::cout<<"Proqramı sonlandır - 9"<<std::endl;

        int input;
        std::cout<<"Seçiminiz: ";
        std::cin>>input;

        switch (input)
        {
            case 0:
                leaveMenu1 = true;
                MainMenu();
                break;
            case 1:
                break;
            case 2:
                break;
            case 9:
                leaveMenu1 = true;
                break;
            default:
                break;
        }

    }
}

void Menu2()
{

    bool leaveMenu2 = false;
    while (leaveMenu2!=true)
    {
        std::cout<<std::endl;
        std::cout<<"Menyu 2 Seçim - 1"<<std::endl;
        std::cout<<"Seçim - 2"<<std::endl;
        std::cout<<"Əvvəlki menyu - 0"<<std::endl;
        std::cout<<"Proqramı sonlandır - 9"<<std::endl;

        int input;
        std::cout<<"Seçiminiz: ";
        std::cin>>input;

        switch (input)
        {
            case 0:
                MainMenu();
                break;
            case 1:
                break;
            case 2:
                break;
            case 9:
                leaveMenu2 = true;
                break;
            default:
                break;
        }
    }
}

int main() {

    get_screen_buffer_info(ts);
    temp1 = ts->x; temp2 = ts->y;
    go_to_xy(temp1 / 2, temp2 / 2);
    std::thread recenter_loop(set_centered_text);

    MainMenu();


    recenter_loop.join();
    return 0;

}