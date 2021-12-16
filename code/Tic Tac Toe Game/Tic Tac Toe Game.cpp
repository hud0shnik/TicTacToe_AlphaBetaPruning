#include "Game.h"

int main()
{
	// Локализация консоли
	setlocale(LC_ALL, "rus");

	// Ядро рандома
	srand(time(NULL));

	// Инициализация данных
	Game game;
	game.Logic();
}