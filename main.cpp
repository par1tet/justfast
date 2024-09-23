#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "not found a path" << endl;
        return 0;
    }
    std::string line;

    string temp = "./";

    if(argv[1][0] == '/'){
        temp = "";
    }

    string pathToFile = temp + argv[1];

    ifstream in(pathToFile); // окрываем файл для чтения

    if (in.is_open())
    {
        while (getline(in, line))
        {
            cout << line << endl;
        }
    }
    else
    {
        cout << "not found a file" << endl;
    }

    in.close(); // закрываем файл

    return 0;
}