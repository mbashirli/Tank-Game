#include <iostream>

void MainMenu();
void Menu1();
void Menu2();

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
                Menu1();
                break;
            case 2:
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
        std::cout<<"Seçim - 1"<<std::endl;
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
        std::cout<<"Seçim - 1"<<std::endl;
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

    MainMenu();
    return 0;

}
