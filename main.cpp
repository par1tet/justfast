#include <iostream>
#include <fstream>
#include <string>
#include <ncurses.h>
#include <vector>

using namespace std;

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
    vector<string> lines;

    string temp = "./";

    if (argv[1][0] == '/')
    {
        temp = "";
    }

    string pathToFile = temp + argv[1];

    int x = 0;
    int y = 0;
    int inputSym = 0;

    ifstream in(pathToFile); // окрываем файл для чтения

    if (in.is_open())
    {
        clear();

        while (getline(in, line))
        {
            lines.push_back(line);
        }

        for (int i = 0; i != lines.size(); i++)
        {
            printw("%s\n", lines[i].c_str());
        }

        move(0, 0);

        while (true)
        {
            inputSym = getch();
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
                lines[y][x] = inputSym;

                ofstream out;
                out.open(pathToFile);
                if (out.is_open())
                {
                    for (int i = 0; i != lines.size(); i++)
                    {
                        out << lines[i] << endl;
                    }
                }
                out.close();
            }
            clear();
            for (int i = 0; i != lines.size(); i++)
            {
                printw("%s\n", lines[i].c_str());
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