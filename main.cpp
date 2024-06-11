#include <iostream>
#include <windows.h>
#include <conio.h>
#include "AES.cpp"
#include "DES.cpp"
using namespace std;

void mainpage(); // menu chính
void menu1(); // menu phụ DES
void menu2(); // menu phụ AES

void gotoXY(int column, int line)
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void box(int x, int y, int w, int h, int t_color, int f_color, string content)
{
    for (int iy = y + 1; iy < y + h; iy++)
    {
        for (int ix = x + 1; ix < x + w; ix++)
        {
            gotoXY(ix, iy);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), f_color);
            cout << " ";
        }
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), t_color);
    if (h <= 1 || w <= 1)
        return;
    for (int ix = x; ix <= x + w; ix++)
    {
        gotoXY(ix, y);
        cout << char(196);
        gotoXY(ix, y + h);
        cout << char(196);
    }
    for (int iy = y; iy <= y + h; iy++)
    {
        gotoXY(x, iy);
        cout << char(179);
        gotoXY(x + w, iy);
        cout << char(179); 
    }
    gotoXY(x, y);
    cout << char(218);
    gotoXY(x + w, y);
    cout << char(191); 
    gotoXY(x, y + h);
    cout << char(192); 
    gotoXY(x + w, y + h);
    cout << char(217); 

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), f_color);
    int contentX = x + w / 2 - content.length() / 2;
    int contentY = y + h / 2;
    gotoXY(contentX, contentY);
    cout << content;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Đặt lại màu về mặc định
}


void mainpage()
{
    system("cls");

    const int MENU_SIZE = 4;
    bool selected[MENU_SIZE] = {false};
    int selectedIndex = 0;

    // Tạo mảng chứa thông tin về các lựa chọn trong menu
    string options[MENU_SIZE] = {" 1. DES", 
                                 " 2. AES", 
                                 " 3. Brute-Force", 
                                 " 0. Exit"};
    
    while (true)
    {
        // Vẽ menu với các lựa chọn
        for (int i = 0; i < MENU_SIZE; i++)
        {
            int x = 60;
            int y = 5 + i * 3;

            // Đặt màu cho hình hộp được chọn
            if (i == selectedIndex)
            {
                box(x, y, 40, 2, 10, 12, options[i]);
                selected[i] = true;
            }
            else
            {
                box(x, y, 40, 2, 10, 15, options[i]);
                selected[i] = false;
            }
        }

        char key = _getch();
        if (key == 72) // Phím lên
        {
            selectedIndex--;
            if (selectedIndex < 0)
                selectedIndex = MENU_SIZE - 1;
        }
        else if (key == 80) // Phím xuống
        {
            selectedIndex++;
            if (selectedIndex >= MENU_SIZE)
                selectedIndex = 0;
        }
        else if (key == 13) 
        {
            switch (selectedIndex + 1)
            {
                case 1: 
                    menu1();
                    break;
                case 2:
                    menu2();
                    break;
                case 3:
                    bruteforce();
                    break;
                case 4: 
                    cout << "Day la bai tap cua nhom 5, goodbye nhe!\n";
                    break;
            }
        }
    }
}

void menu1()
{
    char input;
    system("cls");
    const int MENU_SIZE = 3;
    bool selected[MENU_SIZE] = {false};
    int selectedIndex = 0;

    // Tạo mảng chứa thông tin về các lựa chọn trong menu
    string options[MENU_SIZE] = {" 1. Encrypt", 
                                 " 2. Decrypt",
                                 " 3. Exit"};

    while (true)
    {
        // Vẽ menu với các lựa chọn
        for (int i = 0; i < MENU_SIZE; i++)
        {
            int x = 60;
            int y = 5 + i * 3;

            // Đặt màu cho hình hộp được chọn
            if (i == selectedIndex)
            {
                box(x, y, 40, 2, 10, 12, options[i]);
                selected[i] = true;
            }
            else
            {
                box(x, y, 40, 2, 10, 15, options[i]);
                selected[i] = false;
            }
        }

        char key = _getch();
        if (key == 72) // Phím lên
        {
            selectedIndex--;
            if (selectedIndex < 0)
                selectedIndex = MENU_SIZE - 1;
        }
        else if (key == 80) // Phím xuống
        {
            selectedIndex++;
            if (selectedIndex >= MENU_SIZE)
                selectedIndex = 0;
        }
        else if (key == 13) 
        {
            switch(selectedIndex + 1)
            {
                case 1:
                    system("cls");
                    encrypt();
                    cout << "Ban co muon quay tro ve (y/n)?";
                    cin >> input;
                    if (input == 'Y' || input == 'y')
                        menu1();
                    else
                    {
                        mainpage();
                    }
                    cin.ignore();
                    cin.get();
                    break;
                case 2:
                    system("cls");
                    decrypt();
                    cout << "Ban co muon quay tro ve (y/n)?";
                    cin >> input;
                    if (input == 'Y' || input == 'y')
                        menu1();
                    else
                    {
                        mainpage();
                    }
                    cin.ignore();
                    cin.get();
                    break;
                case 3:
                    system("cls");
                    mainpage();
                    break;
            }
        }
    }
}

void menu2()
{
    char input;
    system("cls");
    const int MENU_SIZE = 3;
    bool selected[MENU_SIZE] = {false};
    int selectedIndex = 0;

    // Tạo mảng chứa thông tin về các lựa chọn trong menu
    string options[MENU_SIZE] = {" 1. Encrypt", 
                                 " 2. Decrypt",
                                 " 3. Exit"};

    while (true)
    {
        // Vẽ menu với các lựa chọn
        for (int i = 0; i < MENU_SIZE; i++)
        {
            int x = 60;
            int y = 5 + i * 3;

            // Đặt màu cho hình hộp được chọn
            if (i == selectedIndex)
            {
                box(x, y, 40, 2, 10, 12, options[i]);
                selected[i] = true;
            }
            else
            {
                box(x, y, 40, 2, 10, 15, options[i]);
                selected[i] = false;
            }
        }

        char key = _getch();
        if (key == 72) // Phím lên
        {
            selectedIndex--;
            if (selectedIndex < 0)
                selectedIndex = MENU_SIZE - 1;
        }
        else if (key == 80) // Phím xuống
        {
            selectedIndex++;
            if (selectedIndex >= MENU_SIZE)
                selectedIndex = 0;
        }
        else if (key == 13) 
        {
            switch(selectedIndex + 1)
            {
                case 1:
                    system("cls");
                    AES_Ecrypt();
                    cout << "Ban co muon quay tro ve (y/n)?";
                    cin >> input;
                    if (input == 'Y' || input == 'y')
                        menu2();
                    else
                    {
                        mainpage();
                    }
                    cin.ignore();
                    cin.get();
                    break;

                case 2:
                    system("cls");
                    AES_Decrypt();
                    cout << "Ban co muon quay tro ve (y/n)?";
                    cin >> input;
                    if (input == 'Y' || input == 'y')
                        menu2();
                    else
                    {
                        mainpage();
                    }
                    cin.ignore();
                    cin.get();
                    break;
                case 3:
                    system("cls");
                    mainpage();
                    break;
            }
        }
    }
}

int main(){
	system("cls");
    mainpage();
    return 0;
}
//Ban ro: 49D1CFF4055F1BB9 
//Khoa: 123456789abcdef1
//Ban ma: 725DC10AA5D24A42

//Khoa: 123456789abcdef1123456789abcdef1
//Ban rp: 12345678999a123412345678999a1234
//Ban ma: 3dc4d520805e17a34277cbc411c08e15