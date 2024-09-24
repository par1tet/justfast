#include <iostream>
#include <fstream>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <ncurses.h>

using namespace std;

// void moveCursor(int x, int y)
// {
//     std::cout << "\033[" << y << ";" << x << "H";
// }

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "not found a path" << endl;
        return 0;
    }
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    cbreak();

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
            printw("%s\n", line.c_str());
        }

        move(y, x);

        while (true)
        {
            int inputSym = getch();
            if (inputSym == KEY_RIGHT)
            {
                x++;
            }
            else if (inputSym == KEY_LEFT)
            {
                x--;
            }
            else if (inputSym == KEY_UP)
            {
                y--;
            }
            else if (inputSym == KEY_DOWN)
            {
                y++;
            }
            else
            {
                printw("%c", inputSym);
            }
            move(y, x);
        }
    }
    else
    {
        printw("not found a file");
    }

    in.close(); // закрываем файл
    endwin();

    return 0;
}