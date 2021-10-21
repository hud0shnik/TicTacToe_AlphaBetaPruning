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
		cout << "Your choice: ";
		cin >> turn;
		cout << endl;
		if ((turn == "1") || (turn == "2") || (turn == "3") || (turn == "4") || (turn == "5") || (turn == "6") || (turn == "7") || (turn == "8") || (turn == "9")) {
			if (m[stoi(turn) - 1] == ' ') {
				m[stoi(turn) - 1] = 'O';
				printMap(m);
				return true;
			}
		}
		cout << "Wrong input, try again" << endl;
	}
	return false;
}

bool botTurn(char m[9]) {
	if (m[0] == ' ') {
		m[0] = 'X';
		return true;
	}
	if (m[4] == ' ') {
		m[4] = 'X';
		return true;
	}
	if (m[7] == ' ') {
		m[7] = 'X';
		return true;
	}
	if (m[5] == ' ') {
		m[5] = 'X';
		return true;
	}
}

bool checkWin(char m[], char c) {
	if ((m[0] == m[1]) && (c == m[0]) && (m[2] == c)) {
		return true;
	}
	if ((m[3] == m[4]) && (c == m[3]) && (m[5] == c)) {
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
	if ((m[0] == m[4]) && (c == m[0]) && (m[8] == c)) {
		return true;
	}
	if ((m[6] == m[4]) && (c == m[6]) && (m[2] == c)) {
		return true;
	}
	return false;
}

void Clear() {
	//функция для очистки терминала
#if defined _WIN32
	system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
	system("clear");
#elif defined (__APPLE__)
	system("clear");
#endif
}

int main()
{

	while (true)
	{
		cout << "\nTicTacToe\n";
		cout << "USER (O)      BOT (X)" << endl;
		char map[9] = { ' ',' ',' ',' ',' ',' ',' ',' ',' ' };
		bool userWin = false;
		bool botWin = false;

		printMap(map);
		while (!isFull(map)) {
			userTurn(map);
			if (checkWin(map, 'O')) {
				cout << "You Won!" << endl;
				break;
			}
			botTurn(map);
			printMap(map);
			if (checkWin(map, 'X')) {
				printMap(map);
				cout << "Bot Won!" << endl;
				break;
			}
			if (isFull(map)) {
				cout << "Draw!" << endl;
				break;
			}
		}


		cout << "\nOne more time? (y/n)" << endl;
		string answ;
		cin >> answ;
		if (answ == "y" || answ == "yes") {
			Clear();
			continue;
		}

		return 0;
	}
}
