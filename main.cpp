#include <iostream>
#include <fstream>
#include <string>
#include <termios.h>
#include <unistd.h>

using namespace std;

char getch()
{
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);          // Получаем текущие настройки терминала
    newt = oldt;                             // Копируем настройки
    newt.c_lflag &= ~(ICANON | ECHO);        // Отключаем echo и canonical mode
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Применяем новые настройки
    ch = getchar();                          // Считываем символ
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Восстанавливаем старые настройки
    return ch;
}

void moveCursor(int x, int y)
{
    std::cout << "\033[" << y << ";" << x << "H";
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "not found a path" << endl;
        return 0;
    }
    std::string line;

    string temp = "./";

    if (argv[1][0] == '/')
    {
        temp = "";
    }

    string pathToFile = temp + argv[1];

    int x = 0;
    int y = 0;

    ifstream in(pathToFile); // окрываем файл для чтения

    if (in.is_open())
    {
        system("clear");

        while (getline(in, line))
        {
            cout << line << endl;
        }

        while (true)
        {
            char inputSym = getch();
            switch (inputSym)
            {
            case 65:
                if (y != 0)
                {
                    y--;
                }
                moveCursor(x, y);
                break;
            case 66:
                y++;
                moveCursor(x, y);
                break;
            case 67:
                x++;
                moveCursor(x, y);
                break;
            case 68:
                if (x != 0)
                {
                    x--;
                }
                moveCursor(x, y);
                break;
            default:
                if (inputSym != 65 && inputSym != 66 && inputSym != 67 && inputSym != 68)
                {
                    cout << inputSym;
                }
                break;
            }
        }
    }
    else
    {
        cout << "not found a file" << endl;
    }

    in.close(); // закрываем файл

    return 0;
}