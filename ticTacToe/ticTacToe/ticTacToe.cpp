#include<iostream>
#include <string>
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

bool userTurn(char m[9]) {
    //функция возвращает true если ход сделан
    string turn;
    while (true)
    {
        cin >> turn;
        if ((turn == "1") || (turn == "2") || (turn == "3") || (turn == "4") || (turn == "5") || (turn == "6") || (turn == "7") || (turn == "8") || (turn == "9")) {
            if (m[stoi(turn)-1] == ' ') {
                m[stoi(turn)-1] = 'O';
                return true;
            }
        }
        cout << "Wrong input, try again" << endl;
    }
    return false;
}

int main()
{
    char map[9] = { ' ',' ',' ',' ',' ',' ',' ',' ',' ' };

    cout << "\nTicTacToe\n";
    cout << endl << "USER (O)      BOT (X)";

    printMap(map);
    while (!isFull(map)) {
        userTurn(map);
        printMap(map);
    }



    cout << "\nThat's all!\n";
}
