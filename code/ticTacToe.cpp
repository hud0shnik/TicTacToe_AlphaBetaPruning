#include <iostream>
#include <string>
#include <limits>
#include <locale.h>
#include <cstdio>

using namespace std;

#define INFPLUS 1000 
#define INFMINUS - 1000 
#define char1 'X'
#define char2 'O'

enum Moves {
    noMove,
    moveUp,
    moveRightUp,
    moveRight,
    moveRightDown,
    moveDown,
    moveLeftDown,
    moveLeft,
    moveLeftUp
};

class Game {
    char* field;
    int cellsToWin;
    int rows;
    int collums;
    char player1;
    char player2;
    char prevMove;

   
    // Функция очистки поля
    void clearField() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < collums; j++) {
                operator[](i)[j] = ' ';
            }
        }
    }
    // Функция для определения победителя
    char fieldState(short int marker = ' ') const {
        char winner; //результат вызова функции для каждой ячейки игрового поля
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < collums; ++j) { //для каждой ячейки игрового поля
                if (operator[](i)[j] != ' ') { //если в ней есть знак
                    winner = fieldState(i, j, 1, noMove, marker); //вызываем от этой ячейки рекурсивную функцию определения победителя
                    if (winner != -1) return winner; //если вызов дал результат - возвращаем
                }
            }
        }
        //иначе не один из вызовов не дал результат - победителя нет, возвращаем -1
        return -1;
    }

    //функция определения заполнено ли поля
    bool areFieldsFull() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < collums; ++j) {
                if (operator[](i)[j] == ' ') {
                    return false;
                }
            }
        }
        return true;
    }

    // Рекурсивная функция определения, победил ли игрок со знаком marker
    char fieldState(const int i, const int j, const int cells, Moves move, char marker) const { 

        if (cells == cellsToWin) { //если мы нашли линию нужного размера
          //если определяется есть ли победитель, возвращаем победителя
            if (marker == ' ') return prevMove;
            //иначе определяется победил ли игрок со знаком marker
            else {
                //если знак marker - значит победил, возвращаем true. Иначе проиграл - возвращаем false
                if (operator[](i)[j] == marker) return true;
                else return false;
            }
        }

        //результат для поочередного рекурсивного вызова функций
        char winner;
        //если можем пойти вверх и текущее действие либо первое, либо шаг вверх
        if ((i != 0) && ((move == noMove) || (move == moveUp))) {
            if (operator[](i - 1)[j] == operator[](i)[j]) { 
                winner = fieldState(i - 1, j, cells + 1, moveUp, marker); 
                if (winner != -1) return winner; 
            }
        }
        if ((j != 0) && ((move == noMove) || (move == moveLeft))) { 
            if (operator[](i)[j - 1] == operator[](i)[j]) { 
                winner = fieldState(i, j - 1, cells + 1, moveLeft, marker);
                if (winner != -1) return winner; 
            }
        }
        if (((i != 0) && (j != 0)) && ((move == noMove) || (move == moveLeftUp))) { 
            if (operator[](i - 1)[j - 1] == operator[](i)[j]) { 
                winner = fieldState(i - 1, j - 1, cells + 1, moveLeftUp, marker); 
                if (winner != -1) return winner; 
            }
        }
        if ((i != rows - 1) && ((move == noMove) || (move == moveDown))) { 
            if (operator[](i + 1)[j] == operator[](i)[j]) { 
                winner = fieldState(i + 1, j, cells + 1, moveDown, marker); 
                if (winner != -1) return winner; 
            }
        }
        if ((j != collums - 1) && ((move == noMove) || (move == moveRight))) { 
            if (operator[](i)[j + 1] == operator[](i)[j]) { 
                winner = fieldState(i, j + 1, cells + 1, moveRight, marker); 
                if (winner != -1) return winner; 
            }
        }
        if (((i != rows - 1) && (j != collums - 1)) && ((move == noMove) || (move == moveRightDown))) { 
            if (operator[](i + 1)[j + 1] == operator[](i)[j]) { 
                winner = fieldState(i + 1, j + 1, cells + 1, moveRightDown, marker);
                if (winner != -1) return winner; 
            }
        }
        if (((i != rows - 1) && (j != 0)) && ((move == noMove) || (move == moveLeftDown))) { 
            if (operator[](i + 1)[j - 1] == operator[](i)[j]) { 
                winner = fieldState(i + 1, j - 1, cells + 1, moveLeftDown, marker); 
                if (winner != -1) return winner; 
            }
        }
        if (((i != 0) && (j != collums - 1)) && ((move == noMove) || (move == moveRightUp))) { 
            if (operator[](i - 1)[j + 1] == operator[](i)[j]) { 
                winner = fieldState(i - 1, j + 1, cells + 1, moveRightUp, marker);
                if (winner != -1) return winner; 
            }
        }
        //если не один из вызовов сверху не дал результат - победителя от текущей ячейки нет, возвращаем -1
        return -1;

    }
   
    // Функция хода пользователя
    void humanMove() {
        int row, col;
        cout << "Ваш ход" << "\n";
        cout << "Ряд (0-" << to_string(rows - 1) << "):";

        // Проверка ввода
        if (!(cin >> row)) {
            cout << "\nОшибка ввода\n";
            cin.clear();
            cin.ignore(numeric_limits < streamsize > ::max(), '\n');
            return humanMove();
        }

        cout << "Колонка (0-" << to_string(collums - 1) << "):";
        // Проверка ввода
        if (!(cin >> col)) {
            cout << "\nОшибка ввода\n";
            cin.clear();
            cin.ignore(numeric_limits < streamsize > ::max(), '\n');
            return humanMove();
        }

        // Проверка ввода
        if ((row >= rows) || (col >= collums) || (operator[](row)[col] != ' ')) {
            cout << "\nНеверные координаты\n";
            cin.clear();
            cin.ignore(numeric_limits < streamsize > ::max(), '\n');
            return humanMove();
        }

        // Записываем шаг в ячейку таблицы (записываемый шаг - противоположный от последнего)
        operator[](row)[col] = (prevMove == char2) ? char1 : char2;
        // Обновляем переменную, хранящую последний шаг
        prevMove = operator[](row)[col];
    }

    // Алгоритм минимакс (альфа-бета отсечение)
    pair < int, pair < int, int >> miniMax(char marker, int depth, int alpha, int beta) const {
        // Лучший ход (представляем из себя пару (r, c), где r - строка игрового поля, а c - столбец)
        pair < int, int > best_move = make_pair(-1, -1);
        // Лучший счет
        int best_score = (marker == player2) ? INFMINUS : INFPLUS;

        // Условия завершения 
        if (areFieldsFull() || fieldState(player2) != -1) {
            char winner = fieldState(player2);
            if (winner != -1) best_score = winner ? INFPLUS : INFMINUS;
            else best_score = -1;

            return make_pair(best_score, best_move);
        }

        Game current(*this);

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < collums; ++j) {
                if (current[i][j] == ' ') {
                    operator[](i)[j] = marker; // Делаем предположительный ход

                    // Максимизируем ход игрока
                    if (marker == player2) {
                        int score = miniMax(player1, depth + 1, alpha, beta).first;

                        // Получаем лучший ход
                        if (best_score < score) {
                            best_score = score - depth * 10;
                            best_move = make_pair(i, j);

                            alpha = max(alpha, best_score);
                            // Отменяем ход
                            operator[](i)[j] = ' ';
                            if (beta <= alpha) {
                                break;
                            }
                        }

                    } // Минимизируем ход оппонента
                    else {
                        int score = miniMax(player2, depth + 1, alpha, beta).first;

                        // Получаем лучший ход
                        if (best_score > score) {
                            best_score = score + depth * 10;
                            best_move = make_pair(i, j);

                            beta = min(beta, best_score);
                            // Отменяем ход
                            operator[](i)[j] = ' ';
                            if (beta <= alpha) {
                                break;
                            }
                        }

                    }
                    // Отменяем ход
                    operator[](i)[j] = ' ';

                }
            }
        }
        return make_pair(best_score, best_move);
    }

    // Функция хода бота
    void aiMove() {
        // Вызываем алгоритм минимакс (альфа-бета отсечение)
        pair < int, pair < int, int > > ai_move = miniMax(player2, 0, INFMINUS, INFPLUS);
        // Записываем шаг в ячейку таблицы (записываемый шаг - противоположный от последнего)
        operator[](ai_move.second.first)[ai_move.second.second] = (prevMove == char2) ? char1 : char2;;
        // Обновляем переменную, хранящую последний шаг
        prevMove = operator[](ai_move.second.first)[ai_move.second.second];
    }

public:
    Game(const int cos,
        const int ros,
        const int cells,
        const char first) {
        collums = cos;
        rows = ros;
        cellsToWin = cells;
        player1 = first;
        player2 = (player1 == char2) ? char1 : char2;
        prevMove = player2;
        field = new char[rows * collums];

    }

    Game(const Game& other) : rows(other.rows), collums(other.collums), cellsToWin(other.cellsToWin), player1(other.player1), player2(other.player2), prevMove(other.prevMove) {
        field = new char[rows * collums];
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < collums; ++j) {
                // Инициализируем ячейку матрицы
                operator[](i)[j] = other[i][j];
            }
        }
    }

    ~Game() {
        delete[] field;
    }

    // Прегрузка оператора [] сделана для быстрой работы массива при вводе очень большой размерности поля
    // принцип выделения памяти как при создании обычного двумерного массива только без массы циклов
    char* operator[](const int row) const {
        return field + row * collums;
    }

    // Функция вывода поля
    // Передаем в функцию наше поле обьявленное в main (оно может называться в маине не только field, в данном случае это та переменная которая используется только в этой функции)
    void printField() {
        // Очистка экрана
        system("cls");
        for (int j = 0; j < collums; j++) {
            cout << "----";
        }
        cout << "-\n";
        for (int i = 0; i < rows; i++) {
            // Ряд символов
            for (int j = 0; j < collums; j++) {
                cout << "| " << operator[](i)[j] << " ";
            }
            cout << "|\n";
            for (int j = 0; j < collums; j++) {
                cout << "----";
            }
            cout << "-\n";
        }
    }

    // Функция запуска игры
    void run(const bool aiMode = true) {
        clearField();
        char winner = fieldState(); // Инициализируем начальное значение переменной, хранящее победителя
        while ((winner == -1) && !areFieldsFull()) { // Пока нет победителя и поле не заполнено
            printField(); // Выводим поле
            humanMove(); // Делаем ход игрока
            if (aiMode) { // Если играем против ИИ
                winner = fieldState(); //Смотрим не победил ли игрок
                if ((winner != -1) || areFieldsFull()) break; // Если игрок победит или поле заполнено -  завершаем игру
                aiMove(); // Делаем ход ИИ
            }
            winner = fieldState(); // Обновляем переменную с победителем
        }
        printField(); //Выводим таблицу
        if (winner != -1) { //Если есть победитель
            cout << "\nИгрок " << ((winner == player1) ? "1" : "2") << " выиграл\n"; //Выводим его
        }
        else {
            cout << "\nНичья!\n"; //Иначе результат игры - ничья
        }
    }
};

int main() {
    setlocale(LC_ALL, "Rus");

    int aiMode = true;
    int modePlayer = char1;
    int choice;
    cout << "\n";
    cout << "\t\t*-------------------Меню-------------------*" << endl;
    cout << "\t\t|1) Игра против другого человека           |" << endl;
    cout << "\t\t|2) Игра против робота                     |" << endl;
    cout << "\t\t|3) Выйти                                  |" << endl;
    cout << "\t\t*------------------------------------------*" << endl;
TryAgain:
    cout << "\n\nВведите число: ";
    cin >> choice;

    switch (choice) {
    case 1:
        aiMode = false;
        choice = 0;
        system("cls");
        cout << "Вы выбрали режим *Один на один*" << endl;
        break;
    case 2:
        aiMode = true;
        choice = 0;
        system("cls");
        cout << "Вы выбрали режим *Игра с роботом*" << endl;
        break;
    case 3:
        return 0;
    default:
        cout << "Некорректное значение" << endl;
        goto TryAgain;
        break;
    }

    cout << "Выберите за кого будете играть" << endl;
    cout << "1) X" << endl;
    cout << "2) O" << endl;
TryAgain2:
    cout << "Введите число: ";
    cin >> choice;

    switch (choice) {
    case 1:
        cout << "Вы выбрали игру за X" << endl;
        modePlayer = char1;
        break;
    case 2:
        cout << "Вы выбрали игру за O" << endl;
        modePlayer = char2;
        break;
    default:
        cout << "Некорректное значение" << endl;
        goto TryAgain2;
        break;
    }

    int rows, collums, cellsToWin;

    cout << "1) 3x3" << endl;
    cout << "2) 3x4" << endl;
    cout << "3) 4x3" << endl;
TryAgain3:
    cout << "Выберите размер игрового поля: ";
    cin >> choice;

    switch (choice) {
    case 1:
        cout << "Вы выбрали размер игрового поля 3x3" << endl;
        rows = 3;
        collums = 3;
        break;
    case 2:
        cout << "Вы выбрали размер игрового поля 3x4" << endl;
        rows = 4;
        collums = 3;
        break;
    case 3:
        cout << "Вы выбрали размер игрового поля 4x3" << endl;
        rows = 4;
        collums = 4;
        break;

    default:
        cout << "Некорректное значение" << endl;
        choice = 0;
        goto TryAgain3;
        break;
    }

    cout << "Введите количество клеток для победы: ";
    cin >> cellsToWin;

    Game field(rows, collums, cellsToWin, modePlayer);
    field.run(aiMode);

    return 0;
}