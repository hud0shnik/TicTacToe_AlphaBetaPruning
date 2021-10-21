#include<iostream>
using namespace std;

void printMap(char m[9])
{
    //вывод игрового поля в консоль
    cout << endl;
    cout << m[0] << "|" << m[1] << "|" << m[2] << endl;
    cout << "-+-+-" << endl;
    cout << m[3] << "|" << m[4] << "|" << m[5] << endl;
    cout << "-+-+-" << endl;
    cout << m[6] << "|" << m[7] << "|" << m[8] << endl;
}

bool isFull(char m[9])
{
    for (int i = 0; i < 9; i++)
    {
        if (m[i] == ' ')
        {
            return false;
        }
    }
    return true;
}

int main()
{
    cout << "\nTicTacToe\n";
    char map[9] = { ' ',' ',' ',' ',' ',' ',' ',' ',' ' };
    printMap(map);
    cout << "\nThat's all!\n";
}
