#include<iostream>
#include<fstream>
#include<string>
#include <time.h>
#include <Windows.h>

using namespace std;

static int gotoxy(int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.Y = y;
	pos.X = x;
	SetConsoleCursorPosition(hConsole, pos);
	return 0;
}
int main() {
	string filename;
	string i = "prol";
	filename = i + ".txt";
	int col = 0;
	ifstream file1(filename);
	while (!file1.eof()) {
		string str;
		gotoxy(0, col++);
		getline(file1, str);
		cout << str;
		Sleep(500);
	}
}