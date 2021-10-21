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
                printMap(m);
                return true;
            }
        }
        cout << "Wrong input, try again" << endl;
    }
    printMap(m);
    return false;
}


bool botTurn(char m[9]) {
    if (m[1] == ' ') {
        m[1] = 'X';
        return true;
    }
    if (m[0] == ' ') {
        m[0] = 'X';
        return true;
    }
    if (m[2] == ' ') {
        m[2] = 'X';
        return true;
    }
    printMap(m);
}

bool checkWin(char m[], char c) {
    if ((m[0] == m[1])&& (c==m[0])&&(m[2] == c)) {
        return true;
    }
    if ((m[3] == m[4]) &&(c==m[3])&& (m[5] == c)) {
        return true;
    }
    if ((m[6] == m[7]) && (c == m[6]) && (m[8] == c)) {
        return true;
    }
    if ((m[0] == m[3]) && (c == m[3]) && (m[6] == c)) {
        return true;
    }
    if ((m[1] == m[4]) && (c == m[1]) && (m[7] == c)) {
        return true;
    }
    if ((m[2] == m[5]) && (c == m[2]) && (m[8] == c)) {
        return true;
    }
    if ((m[0] == m[4]) && (c == m[0]) && (m[8] == c) ){
        return true;
    }
    if ((m[6] == m[4]) && (c == m[6]) && (m[2] == c)) {
        return true;
    }
    return false;
}

int main()
{
    char map[9] = { ' ',' ',' ',' ',' ',' ',' ',' ',' ' };
    bool userWin = false;
    bool botWin = false;
    cout << "\nTicTacToe\n";
    cout <<  "USER (O)      BOT (X)"<< endl;

    printMap(map);
    while (!isFull(map)) {
        userTurn(map);
        if (checkWin(map,'O')){
            cout  << "You Won!" << endl;
            return 0;
        }
        botTurn(map);
        if (checkWin(map, 'X')) {
            printMap(map);
            cout << "Bot Won!" << endl;
            return 0;
        }
    }
    cout << "Draw!" << endl;
}
