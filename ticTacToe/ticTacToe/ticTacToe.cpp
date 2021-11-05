#include<iostream>
#include <string>
using namespace std;

#define SIZE  4


int botChoice;
char m[SIZE * SIZE] = {};

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
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			cout << m[j + SIZE * i] << "|";

		}
		cout << endl;
		for (int k = 0; k < SIZE; k++) {
			cout << "-+";
		}
		cout << endl;
	}
}

bool checkWin(char c) {
	int points = 0;

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (m[j + SIZE * i] == c) {
				points++;
				if (points == SIZE) {
					return true;
				}
			}
		}
		points = 0;
	}
	points = 0;

	for (int j = 0; j < SIZE; j++) {
		for (int i = 0; i < SIZE; i++) {
			if (m[j + SIZE * i] == c) {
				points++;
				if (points == SIZE) {
					return true;
				}
			}
		}
		points = 0;
	}
	points = 0;

	for (int i = 0; i <= SIZE; i++) {
		if (m[i * (SIZE + 1)] == c) {
			points++;
			if (points == SIZE) {
				return true;
			}
		}
	}
	points = 0;

	for (int i = 0; i <= SIZE; i++) {
		if (m[i * (SIZE - 1)] == c) {
			points++;
			if (points == SIZE) {
				return true;
			}
		}
	}
	


	return false;
}

bool isFull() {
	for (int i = 0; i < SIZE * SIZE; i++) {
		if (m[i] == ' ') {
			return false;
		}
	}
	return true;
}

void userTurn() {
	string s;
	int turn;
	while (true) {
		cout << "Your choice: ";
		cin >> s;
		turn = std::stoi(s);
		cout << endl;
		if ((turn < SIZE * SIZE) /* & (turn > -1)*/) {
			if (m[turn] == ' ') {
				m[turn] = 'O';
				printMap();
				break;
			}
		}
		cout << "Wrong input, try again" << endl;
	}
}

int ab(bool flag) {// Логика бота
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
	// массив со всеми возможными ходами, чем выше значение - тем лучше ход
	int score[SIZE * SIZE] = {};	

	for (int k = 0; k < SIZE * SIZE; k++) {
		score[k] = 1;
	}

	for (i = 0; i < SIZE * SIZE; i++) {
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
		for (j = 0; j < SIZE * SIZE; j++) {
			if (score[j] > max && score[j] != 1) {
				max = score[j];
				botChoice = j;
			}
		}
		return max;
	}
	if (!flag) {
		min = 20;
		for (j = 0; j < SIZE * SIZE; j++) {
			if (score[j] < min && score[j] != 1) {
				min = score[j];
				botChoice = j;
			}
		}
		return min;
	}
}

bool yesOrNo() {
	string answ;
	cin >> answ;

	if (answ == "y" || answ == "yes") {
		return 1;
	}
	return 0;

}

int main() {
	cout << "\nTicTacToe\n";
	cout << "USER (O)      BOT (X)\n" << endl;
	cout << "Start? (y/n)" << endl;

	if (!yesOrNo()) {
		return 0;
	}

	for (int i = 0; i < SIZE * SIZE; i++) {
		m[i] = ' ';
	}
	m[0] = 'O';
	m[1] = 'X';
	m[4] = 'X';
	m[5] = 'X';
	m[2] = 'O';
	m[8] = 'O';

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

		if (yesOrNo()) {
			Clear();
			for (int i = 0; i < SIZE * SIZE; i++)
				m[i] = ' ';
			continue;
		}

		return 0;
	}
}