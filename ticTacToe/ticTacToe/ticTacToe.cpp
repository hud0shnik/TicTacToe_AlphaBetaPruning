#include<iostream>
#include <string>

using namespace std;

int botChoice;
char m[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

void Clear() {
	//функция для очистки терминала
#if defined _WIN32
	system("cls");
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
	system("clear");
#elif defined(__APPLE__)
	system("clear");
#endif
}

void printMap() {
	Clear();
	//вывод игрового поля в консоль
	cout << endl;
	cout << m[0] << "|" << m[1] << "|" << m[2] << endl;
	cout << "-+-+-" << endl;
	cout << m[3] << "|" << m[4] << "|" << m[5] << endl;
	cout << "-+-+-" << endl;
	cout << m[6] << "|" << m[7] << "|" << m[8] << endl;
}

bool checkWin(char c) {
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

bool isFull() {
	for (int i = 0; i < 9; i++) {
		if (m[i] == ' ') {
			return false;
		}
	}
	return true;
}

bool userTurn() {
	//функция возвращает true если ход сделан
	string turn;
	while (true) {
		cout << "Your choice: ";
		cin >> turn;
		cout << endl;
		if ((turn == "1") || (turn == "2") || (turn == "3") || (turn == "4") || (turn == "5") || (turn == "6") || (turn == "7") || (turn == "8") || (turn == "9")) {
			if (m[stoi(turn) - 1] == ' ') {
				m[stoi(turn) - 1] = 'O';
				printMap();
				return true;
			}
		}
		cout << "Wrong input, try again" << endl;
	}
	return false;
}

int ab(bool flag) // The ab function
{
	int max = -20, min = 20;
	int i, j, value = 1;
	if (checkWin('X')) {
		return 10;
	}
	if (checkWin('O')) {
		return -10;
	}
	if (isFull()) {
		return 0;
	}

	int score[9] = { 1, 1, 1, 1, 1, 1, 1, 1, 1};

	for (i = 0; i < 9; i++) {
		if (m[i] == ' ') {
			if (min > max) {
				if (flag == true) {
					m[i] = 'X';
					value = ab(false);
				}
				else {
					m[i] = 'O';
					value = ab(true);
				}
				m[i] = ' ';
				score[i] = value;
			}
		}
	}

	if (flag) {
		max = -20;
		for (j = 0; j < 9; j++) {
			if (score[j] > max && score[j] != 1) {
				max = score[j];
				botChoice = j;
			}
		}
		return max;
	}
	if (!flag) {
		min = 20;
		for (j = 0; j < 9; j++) {
			if (score[j] < min && score[j] != 1) {
				min = score[j];
				botChoice = j;
			}
		}
		return min;
	}
}

int main() {
	cout << "\nTicTacToe\n";
	cout << "USER (O)      BOT (X)\n" << endl;
	cout << "Start? (y/n)" << endl;
	string answ;
	cin >> answ;

	if (answ == "y" || answ == "yes") {

	}
	else {
		return 0;
	}

	while (true) {
		printMap();
		while (!isFull()) {
			userTurn();
			if (checkWin('O')) {
				cout << "You Won!!! Impossible!!!" << endl;
				break;
			}
			ab(true);
			m[botChoice] = 'X';
			printMap();
			if (checkWin('X')) {
				printMap();
				cout << "Bot Won" << endl;
				break;
			}
			if (isFull()) {
				cout << "Draw!" << endl;
				break;
			}
		}

		cout << "\nOne more time? (y/n)" << endl;
		cin >> answ;
		if (answ == "y" || answ == "yes") {
			Clear();
			for (int i = 0; i < 9; i++)
				m[i] = ' ';

			continue;
		}

		return 0;
	}
}