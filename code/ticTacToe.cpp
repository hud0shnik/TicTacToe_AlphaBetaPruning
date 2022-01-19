#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

class ViewPort {
public:
    void WinnerPrint(int mode);
    void PrintGame(char** grid, int x, int y);
    void MenuEndGamase();
};

struct Vector2 {
    int x,
        y;

    Vector2(int _x, int _y) : x(_x), y(_y) {}
    Vector2() : x(0), y(0) {}
    Vector2(const Vector2& p) : x(p.x), y(p.y) {}
    friend bool operator == (const Vector2& p1,
        const Vector2& p2);
};

class Move {
public:
    Move(Vector2 _p);
    Move();

    Vector2 p;
    float estimation;

    int CompareTo(Move other);
};

class InputSystem {
public:
    void InputPosition(int& x, int& y);
    void Settings(int& x_gridSize, int& y_gridSize, int& countToWin);
    void InputAction(int& act);
};

enum class Queue {
    player,
    AI
};

enum class GameState {
    inGame,
    start,
    end,
    playerWon,
    AIWom,
    exit
};

class AI {
private:
    char** map;
    Vector2 size;

    Vector2 GetMove();
    bool IsEmptyCell(Vector2 p);
    Vector2 GetEmptyCell();
    vector < Vector2 > GetEmptyCells();
    void Init(char** _map, Vector2 size);
    Move SimulationMove(Vector2 p);
    bool CheckWinner();
    bool CkeckList(vector < char > list);

public:
    AI();
    ~AI();

    Vector2 GetBestMove(char** _map, Vector2 _size);
};

Vector2 AI::GetMove() {
    vector < Move > moves;
    vector < Vector2 > points;
    points = GetEmptyCells();

    auto rng = std::default_random_engine{};
    std::shuffle(std::begin(points), std::end(points), rng);
    std::random_shuffle(points.begin(), points.end());

    for (Vector2 p : points) {
        moves.push_back(SimulationMove(p));
    }

    bool found = false;
    Move move;
    for (int i = 0; i < moves.size(); i++) {
        if (moves[i].estimation > 0) {
            move = moves[i];
            found = true;
            break;
        }
    }

    if (found) {
        return move.p;
    }
    else {
        if (points.size() != 0)
            return GetEmptyCell();
        return Vector2(-1, -1);
    }
}

bool AI::IsEmptyCell(Vector2 p) {
    if (map[p.x][p.y] != '_')
        return false;

    return true;
}

Vector2 AI::GetEmptyCell() {
    for (int i = 0; i < size.x; i++)
        for (int j = 0; j < size.y; j++)
            if (map[i][j] == '_')
                return Vector2(i, j);

    return Vector2(-1, -1);
}

vector < Vector2 > AI::GetEmptyCells() {
    vector < Vector2 > points;
    Vector2 point;

    for (int i = 0; i < size.x; i++)
        for (int j = 0; j < size.y; j++)
            if (map[i][j] == '_') {
                point.x = i;
                point.y = j;
                points.push_back(point);
            }

    return points;
}

void AI::Init(char** _map, Vector2 _size) {
    size.x = _size.x;
    size.y = _size.y;

    map = new char* [size.x];
    for (int i = 0; i < size.x; i++)
        map[i] = new char[size.y];

    for (int i = 0; i < size.x; i++)
        for (int j = 0; j < size.y; j++)
            map[i][j] = _map[i][j];
}

Move AI::SimulationMove(Vector2 p) {
    map[p.x][p.y] = '0';
    Move m(p);

    if (CheckWinner())
        m.estimation = 1;
    else
        m.estimation = 0;

    map[p.x][p.y] = '_';

    return m;
}

bool AI::CheckWinner() {
    vector < char > list;
    int stateIA = 0;
    int statePL = 0;

    for (int i = 0; i < size.x; i++) {
        for (int j = 0; j < size.y; j++) {
            list.push_back(map[i][j]);
        }

        if (CkeckList(list)) {
            stateIA++;
        }
        else {
            statePL++;
        }

        list.clear();
    }

    for (int i = 0; i < size.x; i++) {
        for (int j = 0; j < size.y; j++) {
            list.push_back(map[j][i]);
        }

        if (CkeckList(list)) {
            stateIA++;
        }
        else {
            statePL++;
        }

        list.clear();
    }

    for (int i = 0; i < size.x; ++i) {
        for (int j = 0; i + j < size.y; ++j) {
            list.push_back(map[i + j][j]);
        }

        if (CkeckList(list)) {
            stateIA++;
        }
        else {
            statePL++;
        }

        list.clear();
    }

    for (int i = 1; i < size.x; ++i) {
        for (int j = 0; i + j < size.y; ++j) {
            list.push_back(map[i + j][j]);
        }

        if (CkeckList(list)) {
            stateIA++;
        }
        else {
            statePL++;
        }

        list.clear();
    }

    for (int j = size.y; j > 0; --j) {
        for (int i = 0; i < size.x; ++i) {
            if (size.x - j - i >= 0) {
                list.push_back(map[i][size.x - j - i]);
            }
        }

        if (CkeckList(list)) {
            stateIA++;
        }
        else {
            statePL++;
        }

        list.clear();
    }

    for (int j = 0; j < size.y; ++j) {
        for (int i = 0; i < size.x; ++i) {
            if (size.x + j - i < size.x) {
                if (size.x - j - i >= 0) {
                    list.push_back(map[i][size.x + j - i]);
                }
            }
        }

        if (CkeckList(list)) {
            stateIA++;
        }
        else {
            statePL++;
        }

        list.clear();
    }

    if (stateIA > statePL)
        return true;
    else
        return false;
}

bool AI::CkeckList(vector < char > list) {

    int countPl = 0;
    int countAI = 0;

    if (list.size() == 0)
        return false;

    for (int i = 0; i < list.size(); i++) {
        if (list[i] == 'X') {
            countPl++;

            if (i < list.size() - 1) {
                if (list[i + 1] != 'X') {
                    countPl = 0;
                }
                else {
                    if (i == list.size() - 1) {
                        countPl++;
                    }
                }
            }
        }

        if (list[i] == '0') {
            countAI++;

            if (i < list.size() - 1) {
                if (list[i + 1] != '0') {
                    countAI = 0;
                }
                else {
                    if (i == list.size() - 1) {
                        countAI++;
                    }
                }
            }
        }
    }

    return countAI >= countPl;
}

AI::AI() {
    map = new char* [0];
    size.x = 0;
    size.y = 0;
}

AI::~AI() {
    for (int i = 0; i < size.x; i++)
        delete[] map[i];

    delete[] map;
}

Vector2 AI::GetBestMove(char** _map, Vector2 _size) {
    Init(_map, _size);

    if (GetEmptyCells().size() == 0) {
        return Vector2(-1, -1);
    }

    return GetMove();
}

class Game {
private:
    Vector2 gridSize;
    char** gameGrid;
    int countToWin;
    Queue queue;
    GameState state;

    char AIMarker;
    AI ai;

    char playerMarker;
    Vector2 movePos;

    InputSystem input;
    ViewPort view;

    bool fisrtLounch;

    void NewGame();
    void GameEnd();
    void InitGameGrid(Vector2 size);
    void DefineQueue();
    void ClearGameGrid();
    bool CkeckList(vector < char > list);
    void CheckingGame();
    void NextStep();
    bool MakeMove(Vector2 pos, char marker);
    bool IsCellEmpty(Vector2 pos);
    void AI_SelectPosition();

public:
    Game();
    ~Game();

    void Logic();
};

void Game::NewGame() {
    if (!fisrtLounch) {
        ClearGameGrid();
    }
    fisrtLounch = false;

    DefineQueue();
    input.Settings(gridSize.x, gridSize.y, countToWin);
    InitGameGrid(gridSize);
    state = GameState::inGame;

    Logic();
}

void Game::GameEnd() {
    if (state == GameState::playerWon) {
        view.WinnerPrint(1);
    }
    else if (state == GameState::AIWom) {
        view.WinnerPrint(2);
    }
    else {
        view.WinnerPrint(3);
    }

    int act;
    cout << endl;
    view.MenuEndGamase();
    input.InputAction(act);

    if (act == 1) {
        state = GameState::start;
        Logic();
    }
    else {
        state = GameState::exit;
        return;
    }
}

void Game::InitGameGrid(Vector2 size) {
    gridSize = size;
    gameGrid = new char* [gridSize.x];
    for (int i = 0; i < gridSize.x; i++)
        gameGrid[i] = new char[gridSize.y];

    for (int i = 0; i < gridSize.x; i++) {
        for (int j = 0; j < gridSize.y; j++) {
            gameGrid[i][j] = '_';
        }
    }
}

void Game::DefineQueue() {
    int randVal = 1 + rand() % 10;

    if (randVal <= 5) {
        queue = Queue::player;
    }
    else {
        queue = Queue::AI;
    }
}

void Game::ClearGameGrid() {
    for (int i = 0; i < gridSize.x; i++)
        delete[] gameGrid[i];
    delete[] gameGrid;
}

bool Game::CkeckList(vector < char > list) {
    int countPl = 0;
    int countAI = 0;

    if (list.size() == 0)
        return false;

    for (int i = 0; i < list.size(); i++) {
        if (list[i] == playerMarker) {
            countPl++;

            if (countPl >= countToWin) {
                state = GameState::playerWon;
                return true;
            }

            if (i < list.size() - 1) {
                if (list[i + 1] != playerMarker) {
                    countPl = 0;
                }
                else {
                    if (i == list.size() - 1) {
                        countPl++;
                    }
                }
            }
        }

        if (list[i] == AIMarker) {
            countAI++;

            if (countAI >= countToWin) {
                state = GameState::AIWom;
                return true;
            }

            if (i < list.size() - 1) {
                if (list[i + 1] != AIMarker) {
                    countAI = 0;
                }
                else {
                    if (i == list.size() - 1) {
                        countAI++;
                    }
                }
            }
        }
    }

    return false;
}

void Game::CheckingGame() {
    vector < char > list;

    for (int i = 0; i < gridSize.x; i++) {
        for (int j = 0; j < gridSize.y; j++) {
            list.push_back(gameGrid[i][j]);
        }

        if (CkeckList(list)) {
            return;
        }
        else {
            list.clear();
        }
    }

    for (int i = 0; i < gridSize.x; i++) {
        for (int j = 0; j < gridSize.y; j++) {
            list.push_back(gameGrid[j][i]);
        }

        if (CkeckList(list)) {
            return;
        }
        else {
            list.clear();
        }
    }

    for (int i = 0; i < gridSize.x; ++i) {
        for (int j = 0; i + j < gridSize.y; ++j) {
            list.push_back(gameGrid[i + j][j]);
        }

        if (CkeckList(list)) {
            return;
        }
        else {
            list.clear();
        }
    }

    for (int i = 1; i < gridSize.x; ++i) {
        for (int j = 0; i + j < gridSize.y; ++j) {
            list.push_back(gameGrid[i + j][j]);
        }

        if (CkeckList(list)) {
            return;
        }
        else {
            list.clear();
        }
    }

    for (int j = gridSize.y; j > 0; --j) {
        for (int i = 0; i < gridSize.x; ++i) {
            if (gridSize.x - j - i >= 0) {
                list.push_back(gameGrid[i][gridSize.x - j - i]);
            }
        }

        if (CkeckList(list)) {
            return;
        }
        else {
            list.clear();
        }
    }

    for (int j = 0; j < gridSize.y; ++j) {
        for (int i = 0; i < gridSize.x; ++i) {
            if (gridSize.x + j - i < gridSize.x) {
                if (gridSize.x - j - i >= 0) {
                    list.push_back(gameGrid[i][gridSize.x + j - i]);
                }
            }
        }

        if (CkeckList(list)) {
            return;
        }
        else {
            list.clear();
        }
    }

    int countStep = 0;
    for (int i = 0; i < gridSize.x; i++) {
        for (int j = 0; j < gridSize.y; j++) {
            if (gameGrid[i][j] == '_')
                countStep++;
        }
    }

    if (countStep == 0)
        state == GameState::end;
}

void Game::NextStep() {
    if (queue == Queue::AI) {
        queue = Queue::player;
    }
    else {
        queue = Queue::AI;
    }
}

bool Game::MakeMove(Vector2 pos, char marker) {
    if (!IsCellEmpty(pos))
        return false;

    gameGrid[pos.x][pos.y] = marker;
    return true;
}

bool Game::IsCellEmpty(Vector2 pos) {
    if (pos.x < 0 || pos.x >= gridSize.x) {
        return false;
    }

    if (pos.y < 0 || pos.y >= gridSize.y) {
        return false;
    }

    if (gameGrid[pos.x][pos.y] != '_')
        return false;

    return true;
}

void Game::AI_SelectPosition() {
    movePos = ai.GetBestMove(gameGrid, gridSize);

    if (!IsCellEmpty(movePos))
        AI_SelectPosition();
}

Game::Game() {
    fisrtLounch = true;

    gridSize.x = 3;
    gridSize.y = 3;
    countToWin = 3;

    queue = Queue::player;
    state = GameState::start;

    playerMarker = 'X';
    AIMarker = '0';
}

Game::~Game() {
    ClearGameGrid();
}

void Game::Logic() {
    do {
        if (state == GameState::start) {
            NewGame();
        }

        if (state == GameState::inGame) {
            if (queue == Queue::player) {
                bool done;
                do {
                    view.PrintGame(gameGrid, gridSize.x, gridSize.y);

                    input.InputPosition(movePos.x, movePos.y);
                    done = IsCellEmpty(movePos);

                    if (!done) {
                        cout << "Wrong input..." << endl;
                        system("pause");
                        system("cls");
                    }
                } while (!done);

                MakeMove(movePos, playerMarker);
            }
            else {
                AI_SelectPosition();
                MakeMove(movePos, AIMarker);
            }

            CheckingGame();
            NextStep();
        }

        if (state == GameState::end || state == GameState::AIWom || state == GameState::playerWon) {
            GameEnd();
        }

        system("cls");
    } while (state != GameState::exit);
}

void InputSystem::InputPosition(int& x, int& y) {
    cout << "Your turn (x, y): ";
    cin >> x >> y;

    x--;
    y--;

    system("cls");
}

void InputSystem::Settings(int& x_gridSize, int& y_gridSize, int& countToWin) {
    cout << "Game size (x, y): ";
    cin >> x_gridSize >> y_gridSize;
    cout << "Win size: ";
    cin >> countToWin;

    system("cls");
}

void InputSystem::InputAction(int& act) {
    cout << "Your choise: ";
    cin >> act;
    system("cls");
}

Move::Move(Vector2 _p) {
    p.x = _p.x;
    p.y = _p.y;

    estimation = 0;
}

Move::Move() {
    p.x = -1;
    p.y = -1;

    estimation = 0;
}

int Move::CompareTo(Move other) {
    auto res = CompareTo(other);
    if (res == 0 && p.x == 1 && p.y == 1) return 1;
    return res;
}

bool operator == (const Vector2& p1,
    const Vector2& p2) {
    if (p1.x != p2.x || p1.y != p2.y)
        return false;
    return true;
}

void ViewPort::WinnerPrint(int mode) {
    cout << "Game over" << endl;
    if (mode == 1) {
        cout << "You win!!!" << endl;
    }
    else if (mode == 2) {
        cout << "You lose..." << endl;
    }
}

void ViewPort::PrintGame(char** grid, int x, int y) {
    cout << "    === TicTacToe === " << endl;

    cout << " ";
    for (int i = 0; i < x; i++) {
        cout << " " << i + 1;
    }
    cout << endl;

    for (int i = 0; i < x; i++) {
        cout << i + 1 << " ";
        for (int j = 0; j < y; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }

    cout << "===================================" << endl;
    cout << "_ - empty cell, X - Player, 0 - Bot" << endl;
    cout << "===================================" << endl;
}

void ViewPort::MenuEndGamase() {
    cout << "Chose: " << endl <<
        "(0) Exit" << endl <<
        "(1) One more time" << endl;
}

int main() {
    //setlocale(LC_ALL, "rus");

    srand(time(NULL));

    Game game;
    game.Logic();
}