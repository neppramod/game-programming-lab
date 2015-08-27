#include <Windows.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib> // system()
#include <conio.h> // Visual C++ console only!
using namespace std;


struct Wall {
	int startX, startY;
	int direction;
	char character;
	int length;
};

COORD GetConsoleSize()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	COORD size;
	size.X = csbi.srWindow.Right;
	size.Y = csbi.srWindow.Bottom;
	return size;
}

void GotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void DrawWall(const Wall &wall)
{	
	if (wall.direction == 0) {
		for (int i = wall.startX; i < wall.startX + wall.length; i++) {
			GotoXY(i, wall.startY);
			cout << wall.character;
		}
	}
	else if (wall.direction == 1) {
		for (int i = wall.startY; i < wall.startY + wall.length; i++) {
			GotoXY(wall.startX, i);
			cout << wall.character;
		}
	}
}

void ReadDungeon(string filename, vector<Wall>& walls)
{
	ifstream fin;
	fin.open(filename);
	if (fin.fail()) {
		cout << "\nThere was error opening the file." << endl;
		exit(1);
	}

	while (!fin.eof()) {
		Wall wall;
		fin >> wall.startX >> wall.startY >> wall.direction >> wall.character
			>> wall.length;
		if (fin.fail()) {
			break;
		}
		walls.push_back(wall);
	}
}

/*
int main(void)
{
	system("cls");
	COORD size = GetConsoleSize();
	//cout << "Total rows: " << size.Y << " Total columns: " << size.X << endl;

	//GotoXY(size.X / 2, size.Y / 2);
	//cout << "0";
	//GotoXY(0, size.Y);

	Wall wall1 = { 10, 10, 0, '0', 10 };
	DrawWall(wall1);

	wall1 = { 19,11, 1, 'X', 10 };
	DrawWall(wall1);

	GotoXY(0, size.Y);
	cout << "Press any key to exit...";
	_getch();
	return 0;
}
*/

int main(void)
{
	system("cls");

	COORD size = GetConsoleSize();

	vector<Wall> walls;
	ReadDungeon("Dungeon.txt", walls);

	for (int i = 0; i < walls.size(); i++) {
		DrawWall(walls[i]);
	}

	GotoXY(0, size.Y);
	cout << "Press any key to exit...";
	_getch();
	return 0;
}
