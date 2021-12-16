#include "Game.h"

void Game::NewGame()
{
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

void Game::GameEnd()
{
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

void Game::InitGameGrid(Vector2 size)
{
	gridSize = size;
	gameGrid = new char* [gridSize.x];
	for(int i = 0; i<gridSize.x; i++)
		gameGrid[i] = new char [gridSize.y];

	for (int i = 0; i < gridSize.x; i++) {
		for (int j = 0; j < gridSize.y; j++) {
			gameGrid[i][j] = '_';
		}
	}
}

void Game::DefineQueue()
{
	int randVal = 1 + rand() % 10;

	if (randVal <= 5) {
		queue = Queue::player;
	}
	else {
		queue = Queue::AI;
	}
}

void Game::ClearGameGrid()
{
	for (int i = 0; i < gridSize.x; i++)
		delete[] gameGrid[i];
	delete[] gameGrid;
}

bool Game::CkeckList(vector<char> list)
{
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

void Game::CheckingGame()
{
	vector<char> list;

	//1. Проверить все горизонтали (строки)
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

	//2. Проверить все вертикали (столбцы)
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

	//3. Проверяем все левые диагонали
	// Главная диагональ и над ней
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

	// Под главной диагональю
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

	//4. Проверяем все правые диагонали
	// Побочная диагональ и над ней
	for (int j = gridSize.y; j > 0; --j) {
		for (int i = 0; i < gridSize.x; ++i){
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

	// Под побочной диагональю
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

	// Проверка, есть ли ходы
	int countStep = 0;
	for (int i = 0; i < gridSize.x; i++) {
		for (int j = 0; j < gridSize.y; j++) {
			if (gameGrid[i][j] == '_')
				countStep++;
		}
	}

	// Свободные ходы закончились
	if (countStep == 0)
		state == GameState::end;
}

void Game::NextStep()
{
	if (queue == Queue::AI) {
		queue = Queue::player;
	}
	else {
		queue = Queue::AI;
	}
}

bool Game::MakeMove(Vector2 pos, char marker)
{
	// Проверка не занята ли ячейка
	if(!IsCellEmpty(pos))
		return false;

	gameGrid[pos.x][pos.y] = marker;
	return true;
}

bool Game::IsCellEmpty(Vector2 pos)
{
	// Проверка ввода
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

void Game::AI_SelectPosition()
{
	// Выбор позиции хода ИИ
	movePos = ai.GetBestMove(gameGrid, gridSize);
	
	// Проверка позиции
	if (!IsCellEmpty(movePos))
		AI_SelectPosition(); // ячейка занята, выбрать другую
}

Game::Game()
{
	fisrtLounch = true;

	gridSize.x = 3;
	gridSize.y = 3;
	countToWin = 3;

	queue = Queue::player;
	state = GameState::start;

	playerMarker = 'X';
	AIMarker = '0';
}

Game::~Game()
{
	ClearGameGrid();
}

void Game::Logic()
{
	do {
		if (state == GameState::start) {
			NewGame();
		}
		
		if (state == GameState::inGame) {
			if (queue == Queue::player) {
				bool done;
				do {
					view.PrintGame(gameGrid, gridSize.x, gridSize.y);

					input.InputPosition(movePos.x, movePos.y);	// выбрать позицию
					done = IsCellEmpty(movePos);				// проверка выбора

					if (!done) {
						cout << "Неверный ввод!\nПопробуйте иначе!" << endl;
						system("pause");
						system("cls");
					}
				} while (!done);	

				MakeMove(movePos, playerMarker);// сделать ход
			}
			else {
				AI_SelectPosition();			// выбрать позицию
				MakeMove(movePos, AIMarker);	// сделать ход
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


