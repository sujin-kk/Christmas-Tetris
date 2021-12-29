#include "PlayGame.h"
#include <iostream>

using namespace std;


PlayGame::PlayGame()
	:stage_data(new StageData* [6])
{
	score = 0;
	stage_data[0] = new StageData(35, 20, 3);
	stage_data[1] = new StageData(30, 20, 3);
	stage_data[2] = new StageData(20, 20, 3);
	stage_data[3] = new StageData(15, 20, 3);
	stage_data[4] = new StageData(10, 20, 3);
	stage_data[5] = new StageData(8, 20, 3);

}

PlayGame::~PlayGame()
{
	for (int i = 0; i < 6; i++)
		delete stage_data[i];
	delete[] stage_data;
	stage_data = nullptr;
}
void PlayGame::cursor_view(char s)      // 0넣으면숨기기, 1넣으면보이기
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = s;
	ConsoleCursor.dwSize = 2;
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void PlayGame::play()
{


	cursor_view(0); //커서 안보이게 
	int is_gameover = 0;
	char keytemp;
	init();


	show_logo();
	PlaySound(TEXT("bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
	story();
	start_logo();
	talk1();
	cursor_view(0);
	while (1)
	{
		//start_logo();
		show_total_block();
		block_shape = make_new_block();
		next_block_shape = make_new_block();
		show_next_block(next_block_shape);
		block_start(block_angle, block_x, block_y);
		show_gamestat();
		if (level == 0)
			map1();
		else if (level == 1)
			map2();
		else if (level == 2)
			map3();
		else if (level == 3)
			map4();
		else if (level == 4)
			map5();
		else if (level == 5)
			map6();
		for (this->getGame_Start(); 1; this->setGame_Start())
		{
			if (k == this->getGame_Start())
			{
				talk6();
				Sleep(1000);
				system("cls");
				change_key(this->getGame_Start());
				show_total_block();
				show_gamestat();
				show_next_block(next_block_shape);
				if (level == 0)
					map1();
				else if (level == 1)
					map2();
				else if (level == 2)
					map3();
				else if (level == 3)
					map4();
				else if (level == 4)
					map5();
				else if (level == 5)
					map6();
			}

			if (this->check_effect3 - this->getGame_Start() == 0 && this->check_effect3 > 0) {
				stage_data[level]->setspeed(stage_data[level]->getspeed() - 50);
				this->check_effect3 = -1;
			}
			if (this->check_effect4_int - this->getGame_Start() == 0 && this->check_effect4_int > 0) {
				this->check_effect4 = true;
				this->check_effect4_int = -1;
			}
			if (_kbhit())
			{
				keytemp = _getch();
				if (keytemp == EXT_KEY && check_effect4)
				{
					keytemp = _getch();
					switch (keytemp)
					{
					case KEY_UP:      //회전하기
						rotate_block();
						break;
					case KEY_LEFT:      //왼쪽으로 이동
						if (block_x > 1)
						{
							erase_cur_block(block_shape, block_angle, block_x, block_y);
							block_x--;
							if (strike_check(block_shape, block_angle, block_x, block_y) == 1)
								block_x++;

							show_cur_block(block_shape, block_angle, block_x, block_y);
						}
						break;
					case KEY_RIGHT:      //오른쪽으로 이동
						if (block_x < 14)
						{
							erase_cur_block(block_shape, block_angle, block_x, block_y);
							block_x++;
							if (strike_check(block_shape, block_angle, block_x, block_y) == 1)
								block_x--;
							show_cur_block(block_shape, block_angle, block_x, block_y);
						}
						break;
					case KEY_DOWN:      //아래로 이동
						is_gameover = move_block(block_shape, block_angle, block_x, block_y, next_block_shape);
						show_cur_block(block_shape, block_angle, block_x, block_y);
						break;
					}
				}

				else if (keytemp == EXT_KEY && !check_effect4)
				{
					keytemp = _getche();
					switch (keytemp)
					{
					case KEY_UP:      //회전하기
						rotate_block();
						break;
					case KEY_RIGHT:      //왼쪽으로 이동
						if (block_x > 1)
						{
							erase_cur_block(block_shape, block_angle, block_x, block_y);
							block_x--;
							if (strike_check(block_shape, block_angle, block_x, block_y) == 1)
								block_x++;

							show_cur_block(block_shape, block_angle, block_x, block_y);
						}
						break;
					case KEY_LEFT:      //오른쪽으로 이동
						if (block_x < 14)
						{
							erase_cur_block(block_shape, block_angle, block_x, block_y);
							block_x++;
							if (strike_check(block_shape, block_angle, block_x, block_y) == 1)
								block_x--;
							show_cur_block(block_shape, block_angle, block_x, block_y);
						}
						break;
					case KEY_DOWN:      //아래로 이동
						is_gameover = move_block(block_shape, block_angle, block_x, block_y, next_block_shape);
						show_cur_block(block_shape, block_angle, block_x, block_y);
						break;
					}
				}
				else if (keytemp == 32)   //스페이스바를 눌렀을때
				{
					while (is_gameover == 0)
					{
						is_gameover = move_block(block_shape, block_angle, block_x, block_y, next_block_shape);
					}
					show_cur_block(block_shape, block_angle, block_x, block_y);
				}
				else if (keytemp == 27) {
					score = 0;
					Sleep(50);
					system("cls");
					break;
				}
				else if (keytemp == 113) { //q
					if (q_ > 0) {
						item_message(1);
						item_effect1(); //임의의 줄 파괴
						q_--;
						show_total_block();
						show_gamestat();
					}
				}
				else if (keytemp == 119) { //w
					if (w_ > 0) {
						item_message(2);
						item_effect3(this->getGame_Start()); // 블록 떨어지는 속도 감소
						w_--;
						show_gamestat();
					}
				}
				else if (keytemp == 101) { //e
					if (e_ > 0) {

						if (keep_block(block_shape)) {
							item_message(3);
							int a = make_new_block();
							block_start(block_shape, block_angle, block_x, block_y);
							show_next_block(a);
							next_block_shape = a;
							show_total_block();

						}
						else {
							item_message(5);
							block_start2(block_shape, block_angle, block_x, block_y);
							show_keep_block(8);
							e_--;
						}
						show_gamestat();
					}
				}

				else if (keytemp == 114) {
					if (r_ > 0) {
						item_message(4);
						item_effect4();
						r_--;
						show_gamestat();
					}
				}
			}
			if (this->getGame_Start() % stage_data[level]->getspeed() == 0)
			{
				is_gameover = move_block(block_shape, block_angle, block_x, block_y, next_block_shape);
				show_cur_block(block_shape, block_angle, block_x, block_y);
			}

			if (is_gameover == 1)
			{

				system("cls");
				santa_bad();
				SetColor(GRAY);
				is_gameover = 0;
				score = 0;

				break;
			}

			if (stage_data[level]->getclearline() <= lines) //레벨 클리어
			{
				level++;
				cursor_view(0);
				if (level == 1) {
					talk2();
					Sleep(1000);
					system("cls");
				}
				if (level == 2) {
					talk3();
					Sleep(1000);
					system("cls");
				}
				if (level == 3) {
					talk4();
					Sleep(1000);
					system("cls");


				}
				if (level == 4) {
					talk5();
					Sleep(1000);
					system("cls");
					int a = this->game_start;
					int ran;
					ran = rand() % 500 + 60;
					k = a + ran;
				}
				if (level == 5) {
					talk7();
					Sleep(1000);
					system("cls");
					int i, j;
					for (i = 0; i < 20; i++)
					{
						for (j = 0; j < 14; j++)
						{
							if ((j == 0) || (j == 13))
							{
								total_block[i][j] = 1;
							}
							else {
								if (total_block[i][j] == 1)
									total_block[i][j] = 2;
								else
									total_block[i][j] = 0;
							}
						}
					}
				}
				if (level == 6) {
					talk8();
					system("cls");
					santa_nice();
				}

				lines = 0;
				show_total_block();
				show_gamestat();
				show_next_block(next_block_shape);
				if (level == 0)
					map1();
				else if (level == 1)
					map2();
				else if (level == 2)
					map3();
				else if (level == 3)
					map4();
				else if (level == 4)
					map5();
				else if (level == 5)
					map6();




			}
			gotoxy(108, 26);
			Sleep(15);
			gotoxy(108, 26);
		}
		init();
		is_gameover = 0;
	}

}



void PlayGame::gotoxy(int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.Y = y;
	pos.X = x;
	SetConsoleCursorPosition(hConsole, pos);

}

void PlayGame::SetColor(int color)
{
	HANDLE std_output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(std_output_handle, color);

}

int PlayGame::init()
{
	int i, j;


	srand((unsigned)time(NULL));


	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 14; j++)
		{
			if ((j == 0) || (j == 13))
			{
				total_block[i][j] = 1;
			}
			else {
				total_block[i][j] = 0;
			}
		}
	}

	for (j = 0; j < 14; j++)         //화면의 제일 밑의 줄은 1로 채운다.
		total_block[20][j] = 1;

	//전역변수 초기화
	level = 0;
	lines = 0;
	ab_x = 5;
	ab_y = 1;
	q_ = 3;
	w_ = 3;
	e_ = 3;
	r_ = 1;


	return 0;
}

int PlayGame::show_cur_block(int shape, int angle, int x, int y)
{
	int i, j;

	switch (shape)
	{
	case 0:
		SetColor(RED);
		break;
	case 1:
		SetColor(BLUE);
		break;
	case 2:
		SetColor(SKY_BLUE);
		break;
	case 3:
		SetColor(WHITE);
		break;
	case 4:
		SetColor(YELLOW);
		break;
	case 5:
		SetColor(VIOLET);
		break;
	case 6:
		SetColor(GREEN);
		break;
	}
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if ((j + y) < 0)
				continue;

			if (block[shape][angle][j][i] == 1)
			{
				gotoxy((i + x) * 2 + ab_x, j + y + ab_y);
				cout << "■";
			}
		}
	}

	SetColor(BLACK);
	gotoxy(108, 26);
	return 0;

}

void PlayGame::show_keep_block(int shape) {
	int i, j;
	SetColor(WHITE);
	for (i = 1; i < 7; i++)
	{
		gotoxy(48, i);
		for (j = 0; j < 6; j++)
		{
			if (i == 1 || i == 6 || j == 0 || j == 5)
			{
				cout << "■";
			}
			else {
				cout << "  ";
			}

		}
	}
	show_cur_block(shape, 0, 23, 1);
}


int PlayGame::erase_cur_block(int shape, int angle, int x, int y)
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (block[shape][angle][j][i] == 1)
			{
				gotoxy((i + x) * 2 + ab_x, j + y + ab_y);
				cout << "  ";
				//break;

			}
		}
	}
	return 0;
}

void PlayGame::show_total_block()
{
	int i, j;
	SetColor(DARK_GRAY);
	for (i = 0; i < 21; i++)
	{
		for (j = 0; j < 14; j++)
		{
			if (j == 0 || j == 13 || i == 20)      //레벨에 따라 외벽 색이 변함
			{
				SetColor((level % 6) + 1);
			}
			else {
				SetColor(DARK_GRAY);
			}
			gotoxy((j * 2) + ab_x, i + ab_y);
			if (total_block[i][j] == 1)
			{
				cout << "■";
			}
			else if (total_block[i][j] == 2) {
				cout << "  ";
			}
			else {
				cout << "  ";
			}

		}
	}
	SetColor(BLACK);
	gotoxy(108, 26);
}

void PlayGame::show_next_block(int shape)
{
	int i, j;
	SetColor((level + 1) % 6 + 1);
	for (i = 1; i < 7; i++)
	{
		gotoxy(33, i);
		for (j = 0; j < 6; j++)
		{
			if (i == 1 || i == 6 || j == 0 || j == 5)
			{
				cout << "■";
			}
			else {
				cout << "  ";
			}

		}
	}
	show_cur_block(shape, 0, 15, 1);
}

int PlayGame::make_new_block()
{
	srand(time(NULL));
	int shape;
	int i;
	i = rand() % 100;
	if (i <= stage_data[level]->getstickrate())      //막대기 나올확률 계산
		return 0;                     //막대기 모양으로 리턴

	shape = (rand() % 6) + 1;      //shape에는 1~6의 값이 들어감
	//show_next_block(shape);

	return shape;
}

int PlayGame::strike_check(int shape, int angle, int x, int y)
{
	int i, j;
	int block_dat;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (((x + j) == 0) || ((x + j) == 13))
				block_dat = 1;
			else
			{
				if (y + i >= 0)
					block_dat = total_block[y + i][x + j];
				else
					block_dat = 0;
			}

			if ((block_dat == 1 || block_dat == 2) && (block[shape][angle][i][j] == 1))      //좌측벽의 좌표를 빼기위함
			{
				return 1;
			}
		}
	}
	return 0;
}
void PlayGame::merge_block(int shape, int angle, int x, int y)
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (block[shape][angle][i][j] > 0) {
				total_block[y + i][x + j] = 1;
			}
		}
	}
	check_full_line();
	show_total_block();
	return;

}

int PlayGame::block_start(int& angle, int& x, int& y)
{
	x = 5;
	y = -2;
	angle = 0;
	return 0;
}

int PlayGame::block_start(int& shape, int& angle, int& x, int& y)
{
	shape = next_block_shape;
	x = 5;
	y = -2;
	angle = 0;
	return 0;
}

int PlayGame::block_start2(int& shape, int& angle, int& x, int& y)
{
	shape = shape_copy;
	x = 5;
	y = -2;
	angle = 0;
	return 0;
}

int PlayGame::move_block(int& shape, int& angle, int& x, int& y, int& next_shape)
{
	erase_cur_block(shape, angle, x, y);

	y++;   //블럭을 한칸 아래로 내림
	if (strike_check(shape, angle, x, y) == 1)
	{
		if (y < 1)   //게임오버
		{
			return 1;
		}
		y--;
		merge_block(shape, angle, x, y);
		shape = next_shape;
		next_shape = make_new_block();

		block_start(angle, x, y);
		show_next_block(next_shape);
		return 2;
	}
	return 0;
}

void PlayGame::rotate_block()
{

	erase_cur_block(block_shape, block_angle, block_x, block_y);
	//   block_angle = (block_angle + 1) % 4;
	int check = 0;

	while (strike_check(block_shape, (block_angle + 1) % 4, block_x, block_y) == 1)
	{
		block_x--;
		check++;
	}

	if (check > 3)
		block_x += check;
	else
		block_angle = (block_angle + 1) % 4;

	show_cur_block(block_shape, block_angle, block_x, block_y);



}

void PlayGame::show_gameover()
{
	SetColor(RED);
	gotoxy(15, 8);
	cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓";
	gotoxy(15, 9);
	cout << "┃**************************┃";
	gotoxy(15, 10);
	cout << "┃*        GAME OVER       *┃";
	gotoxy(15, 11);
	cout << "┃**************************┃";
	gotoxy(15, 12);
	cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛";
	fflush(stdin); //버퍼비우기
	Sleep(1000);

	_getch();
	system("cls");

}

void PlayGame::show_gamestat()
{
	static int printed_text = 0;
	SetColor(GRAY);
	if (printed_text == 0)
	{
		gotoxy(35, 7);
		cout << "STAGE";

		gotoxy(35, 9);
		cout << "SCORE";

		gotoxy(35, 12);
		cout << "LINES";
		gotoxy(35, 16);
		cout << "ITEM";
	}
	gotoxy(41, 7);
	cout << level + 1;
	gotoxy(35, 10);
	cout << score;
	gotoxy(35, 13);
	cout << setw(2) << stage_data[level]->getclearline() - lines;
	gotoxy(35, 17);
	cout << "q :" << q_;
	gotoxy(35, 19);
	cout << "w :" << w_;
	gotoxy(35, 21);
	cout << "e :" << e_;
	gotoxy(35, 23);
	cout << "r :" << r_;



}
void PlayGame::show_logo()
{
	int i, j;
	gotoxy(42, 10);
	cout << "      ■         ■                     ■         ■■■      ■";
	gotoxy(42, 11);
	cout << "    ■■■       ■        ■■■■     ■       ■      ■    ■";
	gotoxy(42, 12);
	cout << "  ■■  ■■     ■■      ■           ■       ■      ■    ■";
	gotoxy(42, 13);
	cout << " ■■    ■■    ■        ■■■■     ■■■    ■■■■     ■";
	gotoxy(42, 14);
	cout << "                 ■        ■           ■                     ■";
	gotoxy(42, 15);
	cout << "       ■                  ■■■■     ■       ■■■■■■■■";
	gotoxy(42, 16);
	cout << "       ■                               ■                     ■";
	gotoxy(42, 17);
	cout << "       ■■■■■■                                            ■";

	Sleep(700);

	SetColor(12);
	gotoxy(57, 21);
	cout << "■■■■■■■■ ";
	gotoxy(57, 22);
	cout << "■            ■ ";
	gotoxy(57, 23);
	cout << "■            ■ ";
	gotoxy(57, 24);
	cout << "■■■■■■■■ ";
	gotoxy(57, 25);
	cout << "       ■        ";
	gotoxy(57, 26);
	cout << "■■■■■■■■ ";

	Sleep(700);

	SetColor(12);
	gotoxy(57, 20);
	cout << "              ■ ";
	gotoxy(57, 21);
	cout << "■      ■    ■ ";
	gotoxy(57, 22);
	cout << "■      ■    ■ ";
	gotoxy(57, 23);
	cout << "■■■■■    ■ ";
	gotoxy(57, 24);
	cout << "■      ■    ■ ";
	gotoxy(57, 25);
	cout << "■■■■■    ■ ";
	gotoxy(57, 26);
	cout << "              ■ ";
	gotoxy(57, 27);
	cout << "              ■ ";

	Sleep(700);

	gotoxy(77, 20);
	cout << "   ■■■■■ ";
	gotoxy(77, 21);
	cout << "           ■";
	gotoxy(77, 22);
	cout << "          ■";
	gotoxy(77, 23);
	cout << "         ■";
	gotoxy(77, 24);
	cout << " ";
	gotoxy(77, 25);
	cout << "  ■■■■■■";
	gotoxy(77, 26);
	cout << "";
	gotoxy(77, 27);
	cout << "   ■■■■■ ";
	gotoxy(77, 28);
	cout << "           ■";
	gotoxy(77, 29);
	cout << "           ■";

	Sleep(300);
	gotoxy(120, 39);
	cout << "아무 키나 누르세요";



	_getch();
	system("cls");

}


void PlayGame::start_logo()
{

	SetColor(2);
	gotoxy(30, 8);
	cout << "■■■■■■";
	gotoxy(30, 9);
	cout << "■ ";
	gotoxy(30, 10);
	cout << "■ ";
	gotoxy(30, 11);
	cout << "■ ";
	gotoxy(30, 12);
	cout << "■■■■■■";
	gotoxy(30, 13);
	cout << "          ■ ";
	gotoxy(30, 14);
	cout << "          ■";
	gotoxy(30, 15);
	cout << "          ■";
	gotoxy(30, 16);
	cout << "■■■■■■ ";

	SetColor(12);
	gotoxy(45, 8);
	cout << "■■■■■■■";
	gotoxy(45, 9);
	cout << "      ■";
	gotoxy(45, 10);
	cout << "      ■";
	gotoxy(45, 11);
	cout << "      ■";
	gotoxy(45, 12);
	cout << "      ■";
	gotoxy(45, 13);
	cout << "      ■";
	gotoxy(45, 14);
	cout << "      ■";
	gotoxy(45, 15);
	cout << "      ■";
	gotoxy(45, 16);
	cout << "      ■";

	SetColor(2);
	gotoxy(60, 8);
	cout << "  ■■■■■";
	gotoxy(60, 9);
	cout << " ■        ■";
	gotoxy(60, 10);
	cout << " ■        ■";
	gotoxy(60, 11);
	cout << " ■        ■";
	gotoxy(60, 12);
	cout << " ■■■■■■";
	gotoxy(60, 13);
	cout << " ■        ■";
	gotoxy(60, 14);
	cout << " ■        ■";
	gotoxy(60, 15);
	cout << " ■        ■ ";
	gotoxy(60, 16);
	cout << " ■        ■";

	SetColor(12);
	gotoxy(77, 8);
	cout << " ■■■■ ";
	gotoxy(77, 9);
	cout << "■       ■ ";
	gotoxy(77, 10);
	cout << "■       ■";
	gotoxy(77, 11);
	cout << "■■■■■";
	gotoxy(77, 12);
	cout << "■ ■";
	gotoxy(77, 13);
	cout << "■   ■";
	gotoxy(77, 14);
	cout << "■    ■ ";
	gotoxy(77, 15);
	cout << "■     ■";
	gotoxy(77, 16);
	cout << "■      ■";

	SetColor(2);
	gotoxy(90, 8);
	cout << "■■■■■■■";
	gotoxy(90, 9);
	cout << "      ■";
	gotoxy(90, 10);
	cout << "      ■";
	gotoxy(90, 11);
	cout << "      ■";
	gotoxy(90, 12);
	cout << "      ■";
	gotoxy(90, 13);
	cout << "      ■";
	gotoxy(90, 14);
	cout << "      ■";
	gotoxy(90, 15);
	cout << "      ■";
	gotoxy(90, 16);
	cout << "      ■";

	SetColor(14);
	gotoxy(110, 8);
	cout << "■       ■ ";
	gotoxy(110, 9);
	cout << "■       ■";
	gotoxy(110, 10);
	cout << "■       ■";
	gotoxy(110, 11);
	cout << "■       ■";
	gotoxy(110, 12);
	cout << "■       ■";
	gotoxy(110, 13);
	cout << "■       ■";
	gotoxy(110, 14);
	cout << "■       ■";
	gotoxy(110, 15);
	cout << "";
	gotoxy(110, 16);
	cout << "■       ■";

	SetColor(7);





	level = 0;
	Sleep(1000);
	system("cls");

}

void PlayGame::over_logo()
{
	int i, g;

	while (1) {
		i = (rand() % 15) + 1;
		g = (rand() % 15) + 1;
		SetColor(i);
		gotoxy(72, 4);
		cout << "     ■■■■■        ■■■■        ■■    ■■       ■■■■■";
		gotoxy(72, 5);
		cout << "   ■                 ■      ■      ■   ■■   ■      ■";
		gotoxy(72, 6);
		cout << "   ■     ■■■      ■■■■■      ■    ■    ■      ■■■■■";
		gotoxy(72, 7);
		cout << "   ■         ■      ■      ■      ■          ■      ■";
		gotoxy(72, 8);
		cout << "    ■■■■■        ■      ■      ■          ■      ■■■■■";
		gotoxy(75, 9);
		Sleep(200);
		SetColor(g);
		gotoxy(80, 12);
		cout << "  ■■■■      ■        ■    ■■■■■     ■■■■";
		gotoxy(80, 13);
		cout << "■       ■      ■      ■     ■             ■     ■";
		gotoxy(80, 14);
		cout << "■       ■       ■    ■      ■■■■■     ■■■■";
		gotoxy(80, 15);
		cout << "■       ■        ■  ■       ■             ■   ■";
		gotoxy(80, 16);
		cout << " ■■■■            ■         ■■■■■     ■    ■";
	}
}

void PlayGame::clear_logo()
{
	int i, g;

	while (1) {
		i = (rand() % 15) + 1;
		g = (rand() % 15) + 1;
		SetColor(i);
		gotoxy(72, 4);
		cout << "     ■■■■■        ■■■■        ■■    ■■       ■■■■■";
		gotoxy(72, 5);
		cout << "   ■                 ■      ■      ■   ■■   ■      ■";
		gotoxy(72, 6);
		cout << "   ■     ■■■      ■■■■■      ■    ■    ■      ■■■■■";
		gotoxy(72, 7);
		cout << "   ■         ■      ■      ■      ■          ■      ■";
		gotoxy(72, 8);
		cout << "    ■■■■■        ■      ■      ■          ■      ■■■■■";
		gotoxy(72, 9);
		Sleep(200);

		SetColor(g);
		gotoxy(73, 12);
		cout << " ■■■■■      ■            ■■■■■      ■■■■      ■■■■";
		gotoxy(73, 13);
		cout << "■               ■            ■             ■      ■     ■     ■";
		gotoxy(73, 14);
		cout << "■               ■            ■■■■■     ■■■■■     ■■■■";
		gotoxy(73, 15);
		cout << "■               ■            ■             ■      ■     ■   ■";
		gotoxy(73, 16);
		cout << " ■■■■■      ■■■■■    ■■■■■     ■      ■     ■    ■";

	}
}

void PlayGame::santa_nice()
{
	
	gotoxy(30, 1);
	SetColor(12);
	cout << "■■■■■■";
	gotoxy(28, 2);
	cout << "■■■■■■■■";
	gotoxy(26, 3);
	cout << "■■■■■■■■■■";
	gotoxy(24, 4);
	SetColor(7);
	cout << "■■■";
	SetColor(12);
	cout << "■■■■■■■■■";
	gotoxy(20, 5);
	SetColor(7);
	cout << "■■■■■■■";
	SetColor(12);
	cout << "■■■■■■■";
	gotoxy(20, 6);
	SetColor(7);
	cout << "■";
	SetColor(8);
	cout << "■■■■■■";
	SetColor(7);
	cout << "■■■■";
	SetColor(12);
	cout << "■■■";
	gotoxy(18, 7);
	SetColor(7);
	cout << "■";
	SetColor(6);
	cout << "■■■■■";
	SetColor(8);
	cout << "■■";
	SetColor(7);
	cout << "■■■■";
	SetColor(12);
	cout << "■■■";
	gotoxy(16, 8);
	SetColor(7);
	cout << "■■";
	SetColor(6);
	cout << "■■";
	SetColor(0);
	cout << "■";
	SetColor(6);
	cout << "■■■■";
	SetColor(8);
	cout << "■";
	SetColor(7);
	cout << "■■■■";
	SetColor(12);
	cout << "■■";
	gotoxy(12, 9);
	SetColor(13);
	cout << "■■";
	SetColor(7);
	cout << "■■";
	SetColor(6);
	cout << "■■■■■■■■";
	SetColor(8);
	cout << "■■";
	SetColor(7);
	cout << "■■";
	SetColor(12);
	cout << "■";
	gotoxy(10, 10);
	SetColor(13);
	cout << "■■■";
	SetColor(7);
	cout << "■■■■";
	SetColor(6);
	cout << "■■■";
	SetColor(0);
	cout << "■";
	SetColor(6);
	cout << "■■";
	SetColor(8);
	cout << "■■■■■";
	gotoxy(8, 11);
	SetColor(12);
	cout << "■■■";
	SetColor(7);
	cout << "■■■■■■";
	SetColor(6);
	cout << "■■■■■■■";
	SetColor(7);
	cout << "■■■";
	gotoxy(6, 12);
	SetColor(12);
	cout << "■■■";
	SetColor(7);
	cout << "■■";
	SetColor(8);
	cout << "■■";
	SetColor(7);
	cout << "■■■■■■";
	SetColor(6);
	cout << "■■■■";
	SetColor(7);
	cout << "■■■";
	gotoxy(6, 13);
	SetColor(12);
	cout << "■■■";
	SetColor(7);
	cout << "■■■";
	SetColor(8);
	cout << "■■■";
	SetColor(4);
	cout << "■";
	SetColor(7);
	cout << "■■■■";
	SetColor(6);
	cout << "■■";
	SetColor(7);
	cout << "■■■■";
	gotoxy(4, 14);
	SetColor(12);
	cout << "■■";
	SetColor(13);
	cout << "■■";
	SetColor(7);
	cout << "■■■■■";
	SetColor(8);
	cout << "■";
	SetColor(7);
	cout << "■";
	SetColor(8);
	cout << "■■■■";
	SetColor(7);
	cout << "■■■■■■";
	gotoxy(4, 15);
	SetColor(12);
	cout << "■■";
	SetColor(13);
	cout << "■■";
	SetColor(7);
	cout << "■■■■■■■■■■";
	SetColor(8);
	cout << "■■■";
	SetColor(7);
	cout << "■■■";
	gotoxy(4, 16);
	SetColor(12);
	cout << "■■";
	SetColor(13);
	cout << "■■";
	SetColor(7);
	cout << "■■■■■■■■■■■■■■■■";
	SetColor(12);
	cout << "    ■";
	gotoxy(4, 17);
	SetColor(12);
	cout << "■■";
	SetColor(13);
	cout << "■■";
	SetColor(7);
	cout << "■■■■■■■■■■■■■■■";
	SetColor(12);
	cout << "■■";
	SetColor(7);
	cout << "■";
	SetColor(12);
	cout << "■■■";
	gotoxy(4, 18);
	cout << "■■■";
	SetColor(13);
	cout << "■";
	SetColor(7);
	cout << "■■■■■■■■■■■■■■";
	SetColor(12);
	cout << "■■■";
	SetColor(7);
	cout << "■";
	SetColor(12);
	cout << "■■■";
	gotoxy(4, 19);
	SetColor(13);
	cout << "■■■■";
	SetColor(12);
	cout << "■";
	SetColor(7);
	cout << "■■■■■■■■■■■■■";
	SetColor(12);
	cout << "■■■";
	SetColor(7);
	cout << "■";
	SetColor(12);
	cout << "■■■";
	gotoxy(2, 20);
	SetColor(13);
	cout << "■■■■■";
	SetColor(12);
	cout << "■";
	SetColor(7);
	cout << "■■■■■■■■■■■■";
	SetColor(12);
	cout << "■■";
	gotoxy(0, 21);
	SetColor(13);
	cout << "■■■■■";
	SetColor(12);
	cout << "■■";
	SetColor(7);
	cout << "■■■■■■■■■■■";
	SetColor(12);
	cout << "■■■";
	gotoxy(0, 22);
	SetColor(13);
	cout << "■■■■■■";
	SetColor(12);
	cout << "■■";
	SetColor(7);
	cout << "■■■■■■■■";
	SetColor(12);
	cout << "■■■■■";
	gotoxy(0, 23);
	SetColor(13);
	cout << "■■■■■■";
	SetColor(0);
	cout << "■";
	SetColor(12);
	cout << "■■";
	SetColor(7);
	cout << "■■■■■■";
	SetColor(12);
	cout << "■■■■";
	SetColor(0);
	cout << "■■";
	SetColor(12);
	cout << "■";
	gotoxy(0, 24);
	SetColor(13);
	cout << "■■■■";
	SetColor(7);
	cout << "■";
	SetColor(12);
	cout << "■";
	SetColor(0);
	cout << "■■■";
	SetColor(7);
	cout << "■■■";
	SetColor(0);
	cout << "■■■■■■■■";
	SetColor(12);
	cout << "■";

	gotoxy(0, 25);
	SetColor(13);
	cout << "■■■■";
	SetColor(7);
	cout << "■■";
	SetColor(12);
	cout << "■■■■■■■■■■■■■■";
	SetColor(7);
	cout << "■■";
	gotoxy(2, 26);
	SetColor(13);
	cout << "■■■";
	SetColor(7);
	cout << "■■■■";
	SetColor(12);
	cout << "■■■■■■■■■";
	SetColor(7);
	cout << "■■■■■";
	gotoxy(2, 27);
	SetColor(13);
	cout << "■■■■■";
	SetColor(7);
	cout << "■■■■■■■■■■■■■■■";
	gotoxy(4, 28);
	SetColor(13);
	cout << "■■■■";
	SetColor(4);
	cout << "■■■■■■■■■■■■■■■";
	gotoxy(6, 29);
	SetColor(13);
	cout << "■■■";
	SetColor(12);
	cout << "■■■                  ■■■";
	gotoxy(10, 30);
	SetColor(13);
	cout << "■";
	SetColor(8);
	cout << "■■■                  ■■■";
	gotoxy(12, 31);
	cout << "■■■                  ■■■";
	gotoxy(10, 32);
	cout << "■■■■                ■■■■";
	gotoxy(10, 33);
	cout << "■■■■                ■■■■";
	clear_logo();
}

void PlayGame::santa_bad()
{
	system("mode con:cols=150 lines=42");
	gotoxy(30, 1);
	SetColor(11);
	cout << "■■■■■■";
	gotoxy(28, 2);
	cout << "■■■■■■■■";
	gotoxy(26, 3);
	cout << "■■■■■■■■■■";
	gotoxy(24, 4);
	SetColor(7);
	cout << "■■■";
	SetColor(11);
	cout << "■■■■■■■■■";
	gotoxy(20, 5);
	SetColor(7);
	cout << "■■■■■■■";
	SetColor(11);
	cout << "■■■■■■■";
	gotoxy(20, 6);
	SetColor(7);
	cout << "■";
	SetColor(8);
	cout << "■■■■■■";
	SetColor(7);
	cout << "■■■■";
	SetColor(11);
	cout << "■■■";
	gotoxy(18, 7);
	SetColor(7);
	cout << "■";
	SetColor(9);
	cout << "■■■■■";
	SetColor(8);
	cout << "■■";
	SetColor(7);
	cout << "■■■■";
	SetColor(11);
	cout << "■■■";
	gotoxy(16, 8);
	SetColor(7);
	cout << "■■";
	SetColor(9);
	cout << "■■";
	SetColor(0);
	cout << "■";
	SetColor(9);
	cout << "■■■■";
	SetColor(8);
	cout << "■";
	SetColor(7);
	cout << "■■■■";
	SetColor(11);
	cout << "■■";
	gotoxy(12, 9);
	SetColor(11);
	cout << "■■";
	SetColor(7);
	cout << "■■";
	SetColor(9);
	cout << "■■■■■■■■";
	SetColor(8);
	cout << "■■";
	SetColor(7);
	cout << "■■";
	SetColor(11);
	cout << "■";
	gotoxy(10, 10);
	SetColor(1);
	cout << "■■■";
	SetColor(7);
	cout << "■■■■";
	SetColor(9);
	cout << "■■■";
	SetColor(0);
	cout << "■";
	SetColor(9);
	cout << "■■";
	SetColor(8);
	cout << "■■■■■";
	gotoxy(8, 11);
	SetColor(1);
	cout << "■■■";
	SetColor(7);
	cout << "■■■■■■";
	SetColor(9);
	cout << "■■■■■■■";
	SetColor(7);
	cout << "■■■";
	gotoxy(6, 12);
	SetColor(1);
	cout << "■■■";
	SetColor(7);
	cout << "■■";
	SetColor(8);
	cout << "■■";
	SetColor(7);
	cout << "■■■■■■";
	SetColor(9);
	cout << "■■■■";
	SetColor(7);
	cout << "■■■";
	gotoxy(6, 13);
	SetColor(1);
	cout << "■■■";
	SetColor(7);
	cout << "■■■";
	SetColor(8);
	cout << "■■■";
	SetColor(4);
	cout << "■";
	SetColor(7);
	cout << "■■■■";
	SetColor(9);
	cout << "■■";
	SetColor(7);
	cout << "■■■■";
	gotoxy(4, 14);
	SetColor(1);
	cout << "■■";
	SetColor(11);
	cout << "■■";
	SetColor(7);
	cout << "■■■■■";
	SetColor(8);
	cout << "■";
	SetColor(7);
	cout << "■";
	SetColor(8);
	cout << "■■■■";
	SetColor(7);
	cout << "■■■■■■";
	gotoxy(4, 15);
	SetColor(1);
	cout << "■■";
	SetColor(11);
	cout << "■■";
	SetColor(7);
	cout << "■■■■■■■■■■";
	SetColor(8);
	cout << "■■■";
	SetColor(7);
	cout << "■■■";
	gotoxy(4, 16);
	SetColor(1);
	cout << "■■";
	SetColor(11);
	cout << "■■";
	SetColor(7);
	cout << "■■■■■■■■■■■■■■■■";
	gotoxy(4, 17);
	SetColor(1);
	cout << "■■";
	SetColor(11);
	cout << "■■";
	SetColor(7);
	cout << "■■■■■■■■■■■■■■■";
	SetColor(11);
	cout << "■■";
	SetColor(7);
	cout << "■";
	SetColor(11);
	cout << "■■■";
	gotoxy(4, 18);
	cout << "■■■";
	SetColor(1);
	cout << "■";
	SetColor(7);
	cout << "■■■■■■■■■■■■■■";
	SetColor(11);
	cout << "■■■";
	SetColor(7);
	cout << "■";
	SetColor(11);
	cout << "■■■";
	gotoxy(4, 19);
	SetColor(1);
	cout << "■■■■";
	SetColor(11);
	cout << "■";
	SetColor(7);
	cout << "■■■■■■■■■■■■■";
	SetColor(11);
	cout << "■■■";
	SetColor(7);
	cout << "■";
	SetColor(11);
	cout << "■■■";
	gotoxy(2, 20);
	SetColor(1);
	cout << "■■■■■";
	SetColor(11);
	cout << "■";
	SetColor(7);
	cout << "■■■■■■■■■■■■";
	SetColor(11);
	cout << "■■";
	SetColor(11);
	cout << "        ■";
	gotoxy(0, 21);
	SetColor(1);
	cout << "■■■■■";
	SetColor(11);
	cout << "■■";
	SetColor(7);
	cout << "■■■■■■■■■■■";
	SetColor(11);
	cout << "■■■";
	gotoxy(0, 22);
	SetColor(1);
	cout << "■■■■■■";
	SetColor(11);
	cout << "■■";
	SetColor(7);
	cout << "■■■■■■■■";
	SetColor(11);
	cout << "■■■■■";
	gotoxy(0, 23);
	SetColor(1);
	cout << "■■■■■■";
	SetColor(0);
	cout << "■";
	SetColor(11);
	cout << "■■";
	SetColor(7);
	cout << "■■■■■■";
	SetColor(11);
	cout << "■■■■";
	SetColor(0);
	cout << "■■";
	SetColor(11);
	cout << "■";
	gotoxy(0, 24);
	SetColor(1);
	cout << "■■■■";
	SetColor(7);
	cout << "■";
	SetColor(11);
	cout << "■";
	SetColor(0);
	cout << "■■■";
	SetColor(7);
	cout << "■■■";
	SetColor(0);
	cout << "■■■■■■■■";
	SetColor(11);
	cout << "■";

	gotoxy(0, 25);
	SetColor(1);
	cout << "■■■■";
	SetColor(7);
	cout << "■■";
	SetColor(11);
	cout << "■■■■■■■■■■■■■■";
	SetColor(7);
	cout << "■■";
	gotoxy(2, 26);
	SetColor(1);
	cout << "■■■";
	SetColor(7);
	cout << "■■■■";
	SetColor(11);
	cout << "■■■■■■■■■";
	SetColor(7);
	cout << "■■■■■";
	gotoxy(2, 27);
	SetColor(1);
	cout << "■■■■■";
	SetColor(7);
	cout << "■■■■■■■■■■■■■■■";
	gotoxy(4, 28);
	SetColor(1);
	cout << "■■■■";
	SetColor(4);
	cout << "■■■■■■■■■■■■■■■";
	gotoxy(6, 29);
	SetColor(1);
	cout << "■■■";
	SetColor(11);
	cout << "■■■                  ■■■";
	gotoxy(10, 30);
	SetColor(11);
	cout << "■";
	SetColor(8);
	cout << "■■■                  ■■■";
	gotoxy(12, 31);
	cout << "■■■                  ■■■";
	gotoxy(10, 32);
	cout << "■■■■                ■■■■";
	gotoxy(10, 33);
	cout << "■■■■                ■■■■";
	over_logo();
}

int PlayGame::check_full_line()
{
	int i, j, k, h;
	int m = 0;
	int check1 = 0, check2 = 0;
	int tmp = lines;
	for (i = 0; i < 20; i++)
	{
		for (j = 1, h = 0; j < 13; j++)
		{
			if (total_block[i][j] == 0)
				break;

		}
		if (j == 13)   //한줄이 다 채워졌음
		{
			check1++;
			tmp++;
			if (lines < stage_data[level]->getclearline()) //LINES 출력에서 -안뜨기위함 
				lines++;
			show_total_block();
			SetColor(BLUE);
			gotoxy(1 * 2 + ab_x, i + ab_y);
			for (j = 1; j < 13; j++)
			{
				cout << "□";
				Sleep(10);
			}
			gotoxy(1 * 2 + ab_x, i + ab_y);
			for (j = 1; j < 13; j++)
			{
				cout << "  ";
				Sleep(10);
			}

			for (k = i; k > 0; k--)
			{
				for (j = 1; j < 13; j++)
					total_block[k][j] = total_block[k - 1][j];
			}
			for (j = 1; j < 13; j++)
				total_block[0][j] = 0;
			score += 100 + (level * 10) + (rand() % 10);
			show_gamestat();
			if (tmp <= stage_data[level]->getclearline()) {
				attack();
				crush(level, lines);
			}
		}
	}

	return 0;

}

void PlayGame::item_effect1()
{
	int  i, j, k;
	int a, b;
	while (1) {
		a = rand() % 12 + 1;
		b = rand() % 19 + 1;
		if (total_block[b][a] == 1 || total_block[b][a] == 2) {
			break;
		}
	}
	SetColor(BLUE);
	gotoxy(2 + ab_x, b + ab_y);
	for (j = 1; j < 13; j++)
	{
		cout << "□";
		Sleep(10);
	}
	gotoxy(2 + ab_x, b + ab_y);
	for (j = 1; j < 13; j++)
	{
		cout << "  ";
		Sleep(10);
	}

	for (k = b; k > 0; k--)
	{
		for (j = 1; j < 13; j++)
			total_block[k][j] = total_block[k - 1][j];
	}
	for (j = 1; j < 13; j++)
		total_block[0][j] = 0;


	return;
}

void PlayGame::item_effect2()
{

}

void PlayGame::item_effect3(int i)
{
	int start, end;

	stage_data[level]->setspeed(stage_data[level]->getspeed() + 50);
	this->check_effect3 = 300 + i;


}

void PlayGame::item_effect4()
{

	int i, j;
	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 14; j++)
		{
			if ((j == 0) || (j == 13))
			{
				total_block[i][j] = 1;
			}
			else {
				total_block[i][j] = 0;
			}
		}
	}
	show_total_block();
}

void PlayGame::change_key(int i)
{
	this->check_effect4 = false;
	this->check_effect4_int = 300 + i;

}

//k누르면 킵, 킵중인 블록 옆에 띄우기, 다시 k 누르면 비워지고 nextblcok이 바뀌기로?
// if key==K
int PlayGame::keep_block(int shape) {
	//bool isTrue = false; //키핑돼있는지
	//넥스트 블럭을갖고와

	if (!isTrue) { //false 비어있음
		gotoxy(48, 5);
		shape_copy = shape; //킵해논 카피 모양채우기
		show_keep_block(shape_copy);
		isTrue = true;
		return 1;
	}
	else {
		show_total_block();

		isTrue = false;
		return 0;
	}

}

void PlayGame::map1() { //매개변수수정..?
	srand(time(NULL));

	int map_x = 45; //맵시작좌표
	int map_y = 11;
	int wid = 36; //맵크기
	int hei = 12;

	//맵틀
	gotoxy(map_x, map_y);
	SetColor(WHITE);
	for (int i = 0; i < wid; i++) {
		cout << "■";
	}
	for (int i = 0; i < hei; i++) {
		gotoxy(map_x, map_y + 1 + i);
		cout << "■" << endl;
	}
	gotoxy(map_x, map_y + hei);
	for (int i = 0; i < wid; i++) {
		cout << "■";
	}
	for (int i = 0; i < hei; i++) {
		gotoxy(map_x + 2 * (wid - 1), hei + i);
		cout << "■" << endl;
	}

	//트리(도착지)7*5
	gotoxy(map_x + 61, map_y + 5);
	SetColor(YELLOW);
	cout << "★" << endl;
	SetColor(DARK_GREEN);
	gotoxy(map_x + 61, map_y + 6);
	cout << "▲" << endl;
	gotoxy(map_x + 60, map_y + 7);
	cout << "▲▲" << endl;
	gotoxy(map_x + 59, map_y + 8);
	cout << "▲▲▲" << endl;
	gotoxy(map_x + 58, map_y + 9);
	cout << "▲▲▲▲" << endl;
	gotoxy(map_x + 57, map_y + 10);
	cout << "▲▲▲▲▲" << endl;
	gotoxy(map_x + 61, map_y + 11);
	SetColor(DARK_YELLOW);
	cout << "■" << endl;

	//선물,움직여야하는객체 3*3
	SetColor(WHITE);
	gotoxy(map_x + 6, map_y + 9);
	cout << "■■" << endl;
	SetColor(RED);
	gotoxy(map_x + 6, map_y + 10);
	cout << "■■" << endl;
	gotoxy(map_x + 6, map_y + 11);
	cout << "■■■" << endl;

	//부셔야하는 탑 7*5
	SetColor(WHITE);
	gotoxy(map_x + 42, map_y + 5);
	cout << "■■" << endl;
	gotoxy(map_x + 39, map_y + 6);
	cout << "■■■■■" << endl;
	gotoxy(map_x + 41, map_y + 7);
	cout << "■⊙■" << endl;
	gotoxy(map_x + 41, map_y + 8);
	cout << "■■■" << endl;
	gotoxy(map_x + 41, map_y + 9);
	cout << "■■■" << endl;
	gotoxy(map_x + 41, map_y + 10);
	cout << "■■■" << endl;
	gotoxy(map_x + 41, map_y + 11);
	cout << "■■■" << endl;



}

void PlayGame::map2()
{
	srand(time(NULL));

	int map_x = 45; //맵시작좌표
	int map_y = 11;
	int wid = 36; //맵크기
	int hei = 12;

	//맵틀
	gotoxy(map_x, map_y);
	SetColor(WHITE);
	for (int i = 0; i < wid; i++) {
		cout << "■";
	}
	for (int i = 0; i < hei; i++) {
		gotoxy(map_x, map_y + 1 + i);
		cout << "■" << endl;
	}
	gotoxy(map_x, map_y + hei);
	for (int i = 0; i < wid; i++) {
		cout << "■";
	}
	for (int i = 0; i < hei; i++) {
		gotoxy(map_x + 2 * (wid - 1), hei + i);
		cout << "■" << endl;
	}

	//트리(도착지)7*5
	SetColor(15);
	gotoxy(map_x + 61, map_y + 6);
	cout << " ●" << endl;
	gotoxy(map_x + 60, map_y + 7);
	SetColor(12);
	cout << " ■■" << endl;
	gotoxy(map_x + 59, map_y + 8);
	cout << " ■■■" << endl;
	gotoxy(map_x + 58, map_y + 9);
	cout << " ■■■■" << endl;
	gotoxy(map_x + 57, map_y + 10);
	cout << " ■■■■■" << endl;
	gotoxy(map_x + 57, map_y + 11);
	SetColor(15);
	cout << "■■■■■■" << endl;

	//선물,움직여야하는객체 3*3
	SetColor(WHITE);
	gotoxy(map_x + 6, map_y + 9);
	cout << "■■" << endl;
	SetColor(RED);
	gotoxy(map_x + 6, map_y + 10);
	cout << "■■" << endl;
	gotoxy(map_x + 6, map_y + 11);
	cout << "■■■" << endl;

	//부셔야하는 탑 7*5
	SetColor(WHITE);
	gotoxy(map_x + 42, map_y + 5);
	cout << "■■" << endl;
	gotoxy(map_x + 39, map_y + 6);
	cout << "■■■■■" << endl;
	gotoxy(map_x + 41, map_y + 7);
	cout << "■⊙■" << endl;
	gotoxy(map_x + 41, map_y + 8);
	cout << "■■■" << endl;
	gotoxy(map_x + 41, map_y + 9);
	cout << "■■■" << endl;
	gotoxy(map_x + 41, map_y + 10);
	cout << "■■■" << endl;
	gotoxy(map_x + 41, map_y + 11);
	cout << "■■■" << endl;



}

void PlayGame::map3()
{
	int map_x = 45; //맵시작좌표
	int map_y = 11;
	int wid = 36; //맵크기
	int hei = 12;

	//맵틀
	gotoxy(map_x, map_y);
	SetColor(WHITE);
	for (int i = 0; i < wid; i++) {
		cout << "■";
	}
	for (int i = 0; i < hei; i++) {
		gotoxy(map_x, map_y + 1 + i);
		cout << "■" << endl;
	}
	gotoxy(map_x, map_y + hei);
	for (int i = 0; i < wid; i++) {
		cout << "■";
	}
	for (int i = 0; i < hei; i++) {
		gotoxy(map_x + 2 * (wid - 1), hei + i);
		cout << "■" << endl;
	}

	//렌즈_ 도착지
	int rudolf[9][9] = {
	{ 8, 0, 0, 0, 8, 0, 0, 0, 0},
	{ 0, 8, 0, 8, 0, 0, 0, 0, 0 },
	{ 0, 6, 6, 6, 0, 0, 0, 0, 0 },
	{ 6, 0, 6, 0, 6, 0, 0, 0, 0 },
	{ 0, 6, 4, 6, 0, 0, 0, 0, 6 },
	{ 0, 6, 6, 6, 6, 6, 6, 6, 0 },
	{ 0, 6, 6, 6, 6, 6, 6, 0, 0 },
	{ 0, 6, 0, 0, 0, 6, 0, 0, 0 },
	{ 0, 6, 6, 0, 0, 6, 6, 0, 0 }
	};

	int current_y = 14;
	int current_x = 95;
	for (int i = 0; i < 9; i++) {
		gotoxy(95, 14 + i);
		for (int j = 0; j < 9; j++) {
			if (i + 5 == current_y && j * 2 + 50 == current_x) {
				SetColor(15);
				cout << "□";
			}
			else {
				SetColor(rudolf[i][j]);
				cout << "■";
			}
		}
		cout << endl;
	}

	//선물,움직여야하는객체 3*3
	SetColor(WHITE);
	gotoxy(map_x + 6, map_y + 9);
	cout << "■■" << endl;
	SetColor(RED);
	gotoxy(map_x + 6, map_y + 10);
	cout << "■■" << endl;
	gotoxy(map_x + 6, map_y + 11);
	cout << "■■■" << endl;

	//부셔야하는 탑 7*5
	SetColor(WHITE);
	gotoxy(map_x + 42, map_y + 5);
	cout << "■■" << endl;
	gotoxy(map_x + 39, map_y + 6);
	cout << "■■■■■" << endl;
	gotoxy(map_x + 41, map_y + 7);
	cout << "■⊙■" << endl;
	gotoxy(map_x + 41, map_y + 8);
	cout << "■■■" << endl;
	gotoxy(map_x + 41, map_y + 9);
	cout << "■■■" << endl;
	gotoxy(map_x + 41, map_y + 10);
	cout << "■■■" << endl;
	gotoxy(map_x + 41, map_y + 11);
	cout << "■■■" << endl;

}

void PlayGame::map4()
{
	srand(time(NULL));

	int map_x = 45; //맵시작좌표
	int map_y = 11;
	int wid = 36; //맵크기
	int hei = 12;

	//맵틀
	gotoxy(map_x, map_y);
	SetColor(WHITE);
	for (int i = 0; i < wid; i++) {
		cout << "■";
	}
	for (int i = 0; i < hei; i++) {
		gotoxy(map_x, map_y + 1 + i);
		cout << "■" << endl;
	}
	gotoxy(map_x, map_y + hei);
	for (int i = 0; i < wid; i++) {
		cout << "■";
	}
	for (int i = 0; i < hei; i++) {
		gotoxy(map_x + 2 * (wid - 1), hei + i);
		cout << "■" << endl;
	}

	//물_ 도착지
	int water[7][4] = {
	{ 0, 8, 8, 0},
	{ 0, 6, 6, 0},
	{ 6, 6, 6, 6},
	{ 6, 11, 11, 6},
	{ 6, 11, 11, 6},
	{ 6, 11, 11, 6},
	{ 6, 6, 6, 6}
	};

	int current_y = 16;
	int current_x = 100;
	for (int i = 0; i < 7; i++) {
		gotoxy(100, 16 + i);
		for (int j = 0; j < 4; j++) {
			if (i + 5 == current_y && j * 2 + 50 == current_x) {
				SetColor(15);
				cout << "□";
			}
			else {
				SetColor(water[i][j]);
				cout << "■";
			}
		}
		cout << endl;
	}

	//선물,움직여야하는객체 3*3
	SetColor(WHITE);
	gotoxy(map_x + 6, map_y + 9);
	cout << "■■" << endl;
	SetColor(RED);
	gotoxy(map_x + 6, map_y + 10);
	cout << "■■" << endl;
	gotoxy(map_x + 6, map_y + 11);
	cout << "■■■" << endl;

	//부셔야하는 탑 7*5
	SetColor(WHITE);
	gotoxy(map_x + 42, map_y + 5);
	cout << "■■" << endl;
	gotoxy(map_x + 39, map_y + 6);
	cout << "■■■■■" << endl;
	gotoxy(map_x + 41, map_y + 7);
	cout << "■⊙■" << endl;
	gotoxy(map_x + 41, map_y + 8);
	cout << "■■■" << endl;
	gotoxy(map_x + 41, map_y + 9);
	cout << "■■■" << endl;
	gotoxy(map_x + 41, map_y + 10);
	cout << "■■■" << endl;
	gotoxy(map_x + 41, map_y + 11);
	cout << "■■■" << endl;
}

void PlayGame::map5()
{
	int map_x = 45; //맵시작좌표
	int map_y = 11;
	int wid = 36; //맵크기
	int hei = 12;

	//맵틀
	gotoxy(map_x, map_y);
	SetColor(WHITE);
	for (int i = 0; i < wid; i++) {
		cout << "■";
	}
	for (int i = 0; i < hei; i++) {
		gotoxy(map_x, map_y + 1 + i);
		cout << "■" << endl;
	}
	gotoxy(map_x, map_y + hei);
	for (int i = 0; i < wid; i++) {
		cout << "■";
	}
	for (int i = 0; i < hei; i++) {
		gotoxy(map_x + 2 * (wid - 1), hei + i);
		cout << "■" << endl;
	}

	gotoxy(map_x + 53, map_y + 8);
	SetColor(RED);
	cout << "■■";
	gotoxy(map_x + 53, map_y + 9);
	cout << "■■■";

	SetColor(YELLOW);
	gotoxy(map_x + 64, map_y + 9);
	cout << "◆" << endl;
	gotoxy(map_x + 53, map_y + 10);
	cout << "■■■■■■" << endl;
	gotoxy(map_x + 53, map_y + 11);
	cout << "〓〓〓〓〓〓〓" << endl;

	//선물,움직여야하는객체 3*3
	SetColor(WHITE);
	gotoxy(map_x + 6, map_y + 9);
	cout << "■■" << endl;
	SetColor(RED);
	gotoxy(map_x + 6, map_y + 10);
	cout << "■■" << endl;
	gotoxy(map_x + 6, map_y + 11);
	cout << "■■■" << endl;

	//부셔야하는 탑 7*5
	SetColor(WHITE);
	gotoxy(map_x + 42, map_y + 5);
	cout << "■■" << endl;
	gotoxy(map_x + 39, map_y + 6);
	cout << "■■■■■" << endl;
	gotoxy(map_x + 41, map_y + 7);
	cout << "■⊙■" << endl;
	gotoxy(map_x + 41, map_y + 8);
	cout << "■■■" << endl;
	gotoxy(map_x + 41, map_y + 9);
	cout << "■■■" << endl;
	gotoxy(map_x + 41, map_y + 10);
	cout << "■■■" << endl;
	gotoxy(map_x + 41, map_y + 11);
	cout << "■■■" << endl;
}

void PlayGame::map6()
{
	srand(time(NULL));

	int map_x = 45; //맵시작좌표
	int map_y = 11;
	int wid = 36; //맵크기
	int hei = 12;

	//맵틀
	gotoxy(map_x, map_y);
	SetColor(WHITE);
	for (int i = 0; i < wid; i++) {
		cout << "■";
	}
	for (int i = 0; i < hei; i++) {
		gotoxy(map_x, map_y + 1 + i);
		cout << "■" << endl;
	}
	gotoxy(map_x, map_y + hei);
	for (int i = 0; i < wid; i++) {
		cout << "■";
	}
	for (int i = 0; i < hei; i++) {
		gotoxy(map_x + 2 * (wid - 1), hei + i);
		cout << "■" << endl;
	}

	//렌즈_ 도착지
	int lens[7][7] = {
	{ 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 11, 11, 11, 0, 0},
	{ 0, 11, 11, 15, 15, 11, 0},
	{ 0, 11, 11, 15, 15, 11, 0},
	{ 0, 11, 11, 11, 11, 11, 0},
	{ 0, 0, 11, 11, 11, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0},
	};

	int current_y = 16;
	int current_x = 100;
	for (int i = 0; i < 7; i++) {
		gotoxy(100, 16 + i);
		for (int j = 0; j < 7; j++) {
			if (i + 5 == current_y && j * 2 + 50 == current_x) {
				SetColor(15);
				cout << "□";
			}
			else {
				SetColor(lens[i][j]);
				cout << "■";
			}
		}
		cout << endl;
	}

	//선물,움직여야하는객체 3*3
	SetColor(WHITE);
	gotoxy(map_x + 6, map_y + 9);
	cout << "■■" << endl;
	SetColor(RED);
	gotoxy(map_x + 6, map_y + 10);
	cout << "■■" << endl;
	gotoxy(map_x + 6, map_y + 11);
	cout << "■■■" << endl;

	//부셔야하는 탑 7*5
	SetColor(WHITE);
	gotoxy(map_x + 42, map_y + 5);
	cout << "■■" << endl;
	gotoxy(map_x + 39, map_y + 6);
	cout << "■■■■■" << endl;
	gotoxy(map_x + 41, map_y + 7);
	cout << "■⊙■" << endl;
	gotoxy(map_x + 41, map_y + 8);
	cout << "■■■" << endl;
	gotoxy(map_x + 41, map_y + 9);
	cout << "■■■" << endl;
	gotoxy(map_x + 41, map_y + 10);
	cout << "■■■" << endl;
	gotoxy(map_x + 41, map_y + 11);
	cout << "■■■" << endl;

}

void PlayGame::attack()
{
	int map_x = 45; //맵시작좌표
	int map_y = 11;


	for (int i = 0; i < 33; i++) {
		gotoxy(map_x + 6 + i, map_y + 9);
		cout << "    " << endl;
		gotoxy(map_x + 6 + i, map_y + 10);
		cout << "    " << endl;
		gotoxy(map_x + 6 + i, map_y + 11);
		cout << "       " << endl;

		SetColor(WHITE);
		gotoxy(map_x + 8 + i, map_y + 9);
		cout << "■■" << endl;
		SetColor(RED);
		gotoxy(map_x + 8 + i, map_y + 10);
		cout << "■■" << endl;
		gotoxy(map_x + 8 + i, map_y + 11);
		cout << "■■■" << endl;
		Sleep(10);
	}

	SetColor(WHITE);
	gotoxy(map_x + 6, map_y + 9);
	cout << "■■" << endl;
	SetColor(RED);
	gotoxy(map_x + 6, map_y + 10);
	cout << "■■" << endl;
	gotoxy(map_x + 6, map_y + 11);
	cout << "■■■" << endl;

	gotoxy(map_x + 39, map_y + 9);
	cout << "    " << endl;
	gotoxy(map_x + 39, map_y + 10);
	cout << "    " << endl;
	gotoxy(map_x + 39, map_y + 11);
	cout << "      " << endl;


}


void PlayGame::crush(int i, int lines) {
	switch (i)
	{
	case 0: {
		switch (lines) {
		case 1:
			crush1();
			crush2();
			break;
		case 2:
			crush3();
			crush4();
			break;
		case 3:
			crush5();
			crush6();
			crush7();
			map1();
			erase_t();
			break;
		}
		break; }
	case 1: {
		switch (lines) {
		case 1:
			crush1();
			crush2();
			break;
		case 2:
			crush3();
			crush4();
			break;
		case 3:
			crush5();
			crush6();
			crush7();
			map2();
			erase_t();
			break;
		}
		break; }
	case 2: {
		switch (lines) {
		case 1:
			crush1();
			crush2();
			break;
		case 2:
			crush3();
			crush4();
			break;
		case 3:
			crush5();
			crush6();
			crush7();
			map3();
			erase_t();
			break;
		}
		break; }
	case 3: {
		switch (lines) {
		case 1:
			crush1();
			crush2();
			break;
		case 2:
			crush3();
			crush4();
			break;
		case 3:
			crush5();
			crush6();
			crush7();
			map4();
			erase_t();
			break;
		}
		break; }
	case 4: {
		switch (lines) {
		case 1:
			crush1();
			crush2();
			break;
		case 2:
			crush3();
			crush4();
			break;
		case 3:
			crush5();
			crush6();
			crush7();
			map5();
			erase_t();
			break;
		}
		break; }
	case 5: {
		switch (lines) {
		case 1:
			crush1();
			crush2();
			break;
		case 2:
			crush3();
			crush4();
			break;
		case 3:
			crush5();
			crush6();
			crush7();
			map6();
			erase_t();
			break;
		}
		break; }
		  break;
	}
}
void PlayGame::crush1()
{
	int map_x = 45; //맵시작좌표
	int map_y = 11;


	gotoxy(map_x + 39, map_y + 5);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 6);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 7);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 8);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 9);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 10);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 11);
	cout << "          " << endl;

	SetColor(WHITE);
	gotoxy(map_x + 42, map_y + 6);
	cout << "■■" << endl;
	gotoxy(map_x + 39, map_y + 7);
	cout << "■■■■■" << endl;
	gotoxy(map_x + 41, map_y + 8);
	cout << "■⊙■" << endl;
	gotoxy(map_x + 41, map_y + 9);
	cout << "■■■" << endl;
	gotoxy(map_x + 41, map_y + 10);
	cout << "■■■" << endl;
	gotoxy(map_x + 41, map_y + 11);
	cout << "■■■" << endl;
}

void PlayGame::crush2()
{
	int map_x = 45; //맵시작좌표
	int map_y = 11;

	gotoxy(map_x + 39, map_y + 5);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 6);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 7);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 8);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 9);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 10);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 11);
	cout << "          " << endl;

	SetColor(WHITE);
	gotoxy(map_x + 42, map_y + 7);
	cout << "■■" << endl;
	gotoxy(map_x + 39, map_y + 8);
	cout << "■■■■■" << endl;
	gotoxy(map_x + 41, map_y + 9);
	cout << "■⊙■" << endl;
	gotoxy(map_x + 41, map_y + 10);
	cout << "■■■" << endl;
	gotoxy(map_x + 41, map_y + 11);
	cout << "■■■" << endl;
}

void PlayGame::crush3()
{
	int map_x = 45; //맵시작좌표
	int map_y = 11;

	gotoxy(map_x + 39, map_y + 5);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 6);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 7);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 8);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 9);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 10);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 11);
	cout << "          " << endl;

	SetColor(WHITE);
	gotoxy(map_x + 42, map_y + 8);
	cout << "■■" << endl;
	gotoxy(map_x + 39, map_y + 9);
	cout << "■■■■■" << endl;
	gotoxy(map_x + 41, map_y + 10);
	cout << "■⊙■" << endl;
	gotoxy(map_x + 41, map_y + 11);
	cout << "■■■" << endl;
}

void PlayGame::crush4()
{
	int map_x = 45; //맵시작좌표
	int map_y = 11;

	gotoxy(map_x + 39, map_y + 5);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 6);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 7);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 8);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 9);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 10);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 11);
	cout << "          " << endl;

	SetColor(WHITE);
	gotoxy(map_x + 42, map_y + 9);
	cout << "■■" << endl;
	gotoxy(map_x + 39, map_y + 10);
	cout << "■■■■■" << endl;
	gotoxy(map_x + 41, map_y + 11);
	cout << "■⊙■" << endl;
}

void PlayGame::crush5()
{
	int map_x = 45; //맵시작좌표
	int map_y = 11;

	gotoxy(map_x + 39, map_y + 5);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 6);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 7);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 8);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 9);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 10);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 11);
	cout << "          " << endl;

	SetColor(WHITE);
	gotoxy(map_x + 42, map_y + 10);
	cout << "■■" << endl;
	gotoxy(map_x + 39, map_y + 11);
	cout << "■■■■■" << endl;
}

void PlayGame::crush6()
{
	int map_x = 45; //맵시작좌표
	int map_y = 11;

	gotoxy(map_x + 39, map_y + 5);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 6);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 7);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 8);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 9);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 10);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 11);
	cout << "          " << endl;


	SetColor(WHITE);
	gotoxy(map_x + 42, map_y + 11);
	cout << "■■" << endl;
}

void PlayGame::crush7()
{

	int map_x = 45; //맵시작좌표
	int map_y = 11;
	gotoxy(map_x + 39, map_y + 5);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 6);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 7);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 8);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 9);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 10);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 11);
	cout << "          " << endl;

}
void PlayGame::talk_m() {
	SetColor(7);
	gotoxy(5, 29);
	cout << "┌";
	for (int i = 0; i < 135; i++)
		cout << "─";
	cout << "┐";
	for (int i = 0; i < 10; i++) {
		gotoxy(5, 30 + i);
		cout << "│                                                                                                                                       │";
	}
	gotoxy(5, 39);
	cout << "└";
	for (int i = 0; i < 135; i++)
		cout << "─";
	cout << "┘";
	gotoxy(80, 25);



}
void PlayGame::story() {
	SetColor(7);
	talk_m();

	gotoxy(7, 34);
	cout << "매년 크리스마스,";
	Sleep(300);
	_getch();
	gotoxy(8, 36);
	cout << "24시간 내에 세계 영공을 침투해 1억 3천여 명이 넘는 어린이 가정에 방범창을 뚫고 선물을 나눠줘야하는 산타.";
	Sleep(1000);
	system("cls");
	talk_m();
	gotoxy(7, 34);
	cout << "전무후무한 시련이 그의 앞을 가로막는데...";
	Sleep(1000);

	_getch();
	system("cls");
	talk_m();
	santa_nohat();
	SetColor(7);
	gotoxy(7, 34);
	cout << "산타 : \"잠시만..오늘 크리스마스 이브잖아?!";
	Sleep(1000);
	_getch();
	gotoxy(9, 36);
	cout << "내 커리어에 똥칠을 할 순 없지...!!!\"";
	Sleep(1000);

	_getch();
	system("cls");
	talk_m();
	santa_nohat();
	SetColor(7);
	gotoxy(7, 34);
	cout << "산타 : \"돌프야 이번 일 잘못되면...알지?\"";
	Sleep(1000);

	_getch();
	system("cls");
	talk_m();
	dolf();
	gotoxy(7, 34);
	SetColor(7);
	cout << "루돌프:\"..?! 흐에!\"";
	Sleep(1000);

	_getch();
	system("cls");
	talk_m();
	gotoxy(7, 34);
	cout << "과연 산타는 시련을 이겨내고 아이들에게 선물을 배달할 수 있을 것인가!? ";
	Sleep(1000);

	_getch();
	system("cls");
	talk_m();
	gotoxy(60, 34);
	cout << "지금 바로 시작하시죠";
	Sleep(300);

	_getch();
	system("cls");

	gotoxy(1, 1);
	cout << "┌";
	for (int i = 0; i < 65; i++)
		cout << "─";
	cout << "P R O L O G U E";
	for (int i = 0; i < 65; i++)
		cout << "─";
	cout << "┐";
	for (int i = 0; i < 37; i++) {
		gotoxy(1, 2 + i);
		cout << "│                                                                                                                                                 │";
	}
	gotoxy(1, 39);
	cout << "└";
	for (int i = 0; i < 145; i++)
		cout << "─";
	cout << "┘";


	SetColor(WHITE);
	gotoxy(57, 9);
	Sleep(500);
	cout << "크리스마스 이브, 산타에게 닥친 비극 . . ." << endl;

	Sleep(500);
	gotoxy(60, 11);
	cout << "그에게는 시간이 얼마 없어요 . . !" << endl;

	Sleep(500);
	gotoxy(46, 13);
	cout << "산타가 아이들에게 선물을 하기 위해서는 6가지 물건들을 찾아야 해요." << endl;

	Sleep(500);
	gotoxy(53, 16);
	cout << "1.트리 2. 산타모자 3. 루돌순 4. 썰매 5. 물 6. 렌즈" << endl;

	Sleep(500);
	gotoxy(56, 19);
	cout << "아이들에게 크리스마스의 ";
	SetColor(YELLOW);
	cout << "행복";
	SetColor(WHITE);
	cout << " 을 가져다 주세요 !" << endl;


	//SetColor(DARK_RED);
	//gotoxy(52, 19);
	//Sleep(500);
	//cout << "♨ 주의 ♨ 산타에게는 무시무시한 비극이 도사리고있어요..!" << endl;
	//gotoxy(0, 27);

	_getch();
	gotoxy(90, 30);
	system("pause");
	system("cls");
	Sleep(500);




}
void PlayGame::talk1() {
	SetColor(7);
	talk_m();
	santa_nohat();
	SetColor(7);
	gotoxy(7, 34);
	cout << "산타:\"우선 트리먼저 찾고 시작하자!\"";
	Sleep(1000);
	_getch();
	gotoxy(95, 38);
	system("pause");
	system("cls");
}
void PlayGame::talk2() {
	SetColor(7);
	system("cls");
	talk_m();
	santa_nohat();
	SetColor(7);
	gotoxy(7, 34);
	cout << "산타:\"내 모자는 어딨어!!\"";
	Sleep(1000);
	_getch();
	gotoxy(95, 38);
	system("pause");
	system("cls");
}

void PlayGame::talk3()
{
	SetColor(7);
	system("cls");
	talk_m();
	santa();
	SetColor(7);
	gotoxy(7, 34);
	cout << "산타:\"휴~ 모자는 찾았고";
	Sleep(300);
	_getch();
	gotoxy(10, 35);
	cout << " 돌프야 돌순이는 어디갔어?!";
	_getch();
	gotoxy(7, 36);
	cout << "루돌프:\"흐에!";
	gotoxy(95, 38);
	system("pause");
	system("cls");
}

void PlayGame::talk4()
{
	SetColor(7);
	system("cls");
	talk_m();
	dolf();
	dolsun();
	SetColor(7);
	gotoxy(7, 34);
	cout << "산타:\"이제 츨발?!";
	Sleep(300);
	_getch();
	gotoxy(7, 35);
	cout << "루돌순:\" 흐에!";
	_getch();
	gotoxy(7, 36);
	cout << "산타:\" 잠깐만 물이 어디있지?";
	gotoxy(95, 38);
	system("pause");
	system("cls");
}

void PlayGame::talk5()
{
	SetColor(7);
	system("cls");
	talk_m();
	santa();
	SetColor(7);
	gotoxy(7, 34);
	cout << "산타:\"물도 찾았으니깐 준비는 다 된건가?";
	Sleep(300);
	_getch();
	gotoxy(7, 35);
	cout << "산타:\"잠깐만!";
	_getch();
	gotoxy(7, 36);
	cout << "산타:\"썰매는 어디갔어!!?";
	gotoxy(95, 38);
	system("pause");
	system("cls");
}

void PlayGame::talk6()
{
	SetColor(7);
	system("cls");
	talk_m();
	gotoxy(7, 34);
	cout << "산타:\"푸흡,,! 이거 물이아니라 술이잖아!";
	Sleep(300);
	_getch();
	gotoxy(7, 35);
	cout << "산타:\"취한다 ♨!!";
	_getch();
	SetColor(15);
	gotoxy(95, 38);
	system("pause");
	system("cls");
	talk_m();
	gotoxy(7, 34);

	cout << "방향키가 잠시 이상해질수도 있습니다 흐흐,,";
	gotoxy(95, 38);
	system("pause");
	system("cls");
}

void PlayGame::talk7()
{
	SetColor(7);
	system("cls");
	talk_m();
	santa();
	SetColor(7);
	gotoxy(7, 34);
	cout << "산타:\"으억,,! 렌즈가 빠져서 앞이 안보여!!";
	Sleep(300);
	_getch();
	gotoxy(95, 38);
	system("pause");
	system("cls");
}

void PlayGame::talk8()
{
	SetColor(7);
	system("cls");
	talk_m();
	dolf();
	dolsun();
	SetColor(7);
	gotoxy(7, 34);
	cout << "당신 덕분에 산타가 무사히 준비를 마치고";
	Sleep(300);
	_getch();
	gotoxy(7, 35);
	cout << "아이들에게 선물을 줄 수 있게 되었습니다..!";
	gotoxy(95, 38);
	system("pause");
	system("cls");
}
void PlayGame::erase_t()
{
	int map_x = 45; //맵시작좌표
	int map_y = 11;


	gotoxy(map_x + 39, map_y + 5);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 6);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 7);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 8);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 9);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 10);
	cout << "          " << endl;
	gotoxy(map_x + 39, map_y + 11);
	cout << "          " << endl;
}

void PlayGame::dolf()
{
	int current_y = 2;
	int current_x = 20;
	int dolf[25][25] = {
   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
   { 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0},
   { 0, 0, 0, 0, 0, 0, 0, 8, 8, 0, 0, 0, 0, 0, 0, 0, 8, 8, 0, 0, 0, 0, 0, 0, 0},
   { 0, 0, 0, 0, 0, 0, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 0, 0, 0, 0, 0, 0},
   { 0, 0, 0, 0, 0, 0, 0, 8, 8, 0, 0, 0, 0, 0, 0, 0, 8, 8, 0, 0, 0, 0, 0, 0, 0},
   { 0, 0, 0, 0, 0, 8, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 8, 0, 0, 0, 0, 0},
   { 0, 0, 0, 0, 0, 0, 8, 8, 8, 8, 0, 0, 0, 0, 0, 8, 8, 8, 8, 0, 0, 0, 0, 0, 0},
   { 0, 6, 6, 0, 0, 0, 0, 0, 8, 8, 6, 6, 6, 6, 6, 8, 8, 0, 0, 0, 0, 0, 6, 6, 0},
   { 0, 14, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 14, 0},
   { 0, 14, 14, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 14, 14, 0},
   { 0, 0, 14, 14, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 14, 14, 0, 0},
   { 0, 0, 0, 0, 14, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 14, 0, 0, 0, 0},
   { 0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 0, 0, 0, 0},
   { 0, 0, 0, 0, 6, 6, 6, 6, 6, 6, 6, 4, 4, 4, 6, 6, 6, 6, 6, 6, 6, 0, 0, 0, 0},
   { 0, 0, 0, 0, 6, 6, 0, 15, 6, 6, 4, 4, 15, 15, 4, 6, 6, 0, 15, 6, 6, 0, 0, 0, 0},
   { 0, 0, 0, 0, 6, 6, 0, 0, 6, 6, 4, 4, 4, 4, 4, 6, 6, 0, 0, 6, 6, 0, 0, 0, 0},
   { 0, 0, 0, 0, 6, 6, 6, 6, 6, 6, 6, 4, 4, 4, 6, 6, 6, 6, 6, 6, 6, 0, 0, 0, 0},
   { 0, 0, 0, 6, 6, 6, 6, 6, 6, 14, 14, 14, 0, 14, 14, 14, 6, 6, 6, 6, 6, 6, 0, 0, 0},
   { 0, 0, 0, 6, 6, 6, 6, 6, 14, 14, 14, 14, 0, 14, 14, 14, 14, 6, 6, 6, 6, 6, 0, 0, 0},
   { 0, 0, 0, 6, 6, 6, 6, 6, 14, 14, 0, 0, 0, 0, 0, 14, 14, 6, 6, 6, 6, 6, 0, 0, 0},
   { 0, 0, 0, 6, 6, 6, 6, 6, 14, 14, 0, 12, 12, 12, 0, 14, 14, 6, 6, 6, 6, 6, 0, 0, 0},
   { 0, 0, 0, 0, 0, 6, 6, 6, 14, 14, 14, 0, 0, 0, 14, 14, 14, 6, 6, 6, 0, 0, 0, 0, 0},
   { 0, 0, 0, 0, 0, 0, 0, 6, 6, 14, 14, 14, 14, 14, 14, 14, 6, 6, 0, 0, 0, 0, 0, 0, 0},
   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}

	};


	for (int i = 0; i < 25; i++) {
		gotoxy(20, 2 + i);
		for (int j = 0; j < 25; j++) {
			if (i + 5 == current_y && j * 2 + 50 == current_x) {
				SetColor(15);
				cout << "□";
			}
			else {
				SetColor(dolf[i][j]);
				cout << "■";
			}
		}
		cout << endl;
	}
	SetColor(7);



}
void PlayGame::dolsun() {
	int current_x2 = 75;
	int current_y2 = 2;
	int dolsoon[25][25] = {
	   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 8, 8, 0, 0, 0, 0, 0, 0, 0, 8, 8, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 8, 8, 0, 0, 0, 0, 0, 0, 0, 8, 8, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 8, 8, 8, 8, 13, 0, 0, 0, 0, 0, 13, 8, 8, 8, 8, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 8, 8, 8, 13, 13, 0, 0, 0, 13, 13, 8, 8, 8, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 8, 13, 13, 13, 13, 13, 13, 13, 8, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 6, 6, 0, 0, 0, 0, 0, 6, 6, 13, 13, 13, 13, 13, 13, 13, 6, 6, 0, 0, 0, 0, 0, 6, 6 },
	{ 14, 6, 6, 6, 6, 0, 6, 6, 6, 13, 13, 6, 6, 6, 13, 13, 6, 6, 6, 0, 6, 6, 6, 6, 14 },
	{ 14, 14, 6, 6, 6, 6, 6, 6, 6, 13, 6, 6, 6, 6, 6, 13, 6, 6, 6, 6, 6, 6, 6, 14, 14 },
	{ 0, 14, 14, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 14, 14, 0 },
	{ 0, 0, 0, 14, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 14, 0, 0, 0 },
	{ 0, 0, 0, 0, 6, 6, 6, 6, 6, 6, 6, 4, 4, 4, 6, 6, 6, 6, 6, 6, 6, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 6, 6, 0, 15, 6, 6, 4, 4, 15, 15, 4, 6, 6, 0, 15, 6, 6, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 6, 6, 0, 0, 6, 6, 4, 4, 4, 4, 4, 6, 6, 0, 0, 6, 6, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 6, 6, 6, 6, 6, 6, 6, 4, 4, 4, 6, 6, 6, 6, 6, 6, 6, 0, 0, 0, 0 },
	{ 0, 0, 0, 6, 6, 6, 6, 6, 14, 14, 14, 14, 0, 14, 14, 14, 14, 6, 6, 6, 6, 6, 0, 0, 0 },
	{ 0, 0, 0, 6, 6, 6, 6, 14, 14, 14, 14, 14, 0, 14, 14, 14, 14, 14, 6, 6, 6, 6, 0, 0, 0 },
	{ 0, 0, 0, 6, 6, 6, 6, 14, 14, 14, 0, 0, 0, 0, 0, 14, 14, 14, 6, 6, 6, 6, 0, 0, 0 },
	{ 0, 0, 0, 6, 6, 6, 6, 14, 14, 14, 0, 12, 12, 12, 0, 14, 14, 14, 6, 6, 6, 6, 0, 0, 0 },
	{ 0, 0, 0, 0, 6, 6, 6, 6, 14, 14, 14, 0, 0, 0, 14, 14, 14, 6, 6, 6, 6, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 6, 6, 6, 14, 14, 14, 14, 14, 14, 14, 6, 6, 6, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};

	for (int i = 0; i < 25; i++) {
		gotoxy(75, 2 + i);
		for (int j = 0; j < 25; j++) {
			if (i + 5 == current_y2 && j * 2 + 50 == current_x2) {
				SetColor(15);
				cout << "□";
			}
			else {
				SetColor(dolsoon[i][j]);
				cout << "■";
			}
		}
		cout << endl;
	}

}
void PlayGame::item_message(int i)
{
	SetColor(WHITE);
	switch (i) {
	case 1://q
		gotoxy(51, 8);
		cout << "                                                                            ";
		gotoxy(51, 8);
		cout << "루돌프가 폭탄을 가져왔어요! 블록 한 줄이 파괴됩니다!";
		break;
	case 2://w
		gotoxy(51, 8);
		cout << "                                                                            ";
		gotoxy(51, 8);
		cout << "산타의 마음이 우주에 전해졌어요! 시간이 느리게 흐르는 마법이 발동됩니다!";
		break;
	case 3://e
		gotoxy(51, 8);
		cout << "                                                                            ";
		gotoxy(51, 8);
		cout << "블록이 산타의 선물 보따리에 저장되었어요!";
		break;
	case 4://r
		gotoxy(51, 8);
		cout << "                                                                            ";
		gotoxy(51, 8);
		cout << "루돌프가 핵폭탄을 가져왔어요! 모든 블록이 파괴됩니다!";
		break;
	case 5://킵사용
		gotoxy(51, 8);
		cout << "                                                                            ";
		gotoxy(51, 8);
		cout << "저장해놓은 블록을 가져왔어요!";
		break;
	}
}
void PlayGame::santa() {
	int current_x = 50;
	int current_y = 5;

	int santa[23][23] = {
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{ 0, 0, 0, 0, 0, 0, 0, 12, 12, 12, 12, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0},
{ 0, 0, 0, 0, 0, 0, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0},
{ 0, 0, 0, 0, 0, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0},
{ 0, 0, 0, 0, 12, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 12, 12, 0, 0, 0, 0, 0},
{ 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 12, 0, 0, 0, 0, 0},
{ 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 12, 12, 0, 0, 0, 0},
{ 0, 0, 0, 15, 15, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 15, 15, 12, 12, 0, 0, 0, 0},
{ 0, 0, 0, 15, 15, 6, 6, 0, 6, 6, 6, 6, 0, 6, 6, 15, 15, 12, 12, 0, 0, 0, 0},
{ 0, 0, 0, 15, 15, 6, 6, 6, 6, 12, 12, 6, 6, 6, 6, 15, 15, 12, 12, 0, 0, 0, 0},
{ 0, 0, 0, 0, 15, 6, 6, 15, 15, 12, 12, 15, 15, 6, 6, 15, 15, 12, 12, 12, 15, 15, 0},
{ 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0, 15, 15, 0},
{ 0, 0, 0, 15, 15, 15, 15, 6, 6, 6, 6, 6, 6, 15, 15, 15, 15, 0, 0, 0, 0, 0, 0},
{ 0, 0, 15, 15, 15, 15, 15, 15, 15, 12, 12, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0, 0, 0},
{ 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0, 0},
{ 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0},
{ 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0},
{ 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0},
{ 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0},
{ 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0},
{ 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0},
{ 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0, 0, 0},
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}

	};
	for (int i = 0; i < 23; i++) {
		gotoxy(50, 5 + i);
		for (int j = 0; j < 23; j++) {
			if (i + 8 == current_y && j * 2 + 50 == current_x) {
				SetColor(15);
				cout << "□";
			}
			else {
				SetColor(santa[i][j]);
				cout << "■";
			}
		}
		cout << endl;
	}

}
void PlayGame::santa_nohat() {
	int current_x = 50;
	int current_y = 5;
	int santa_nohat[23][23] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 15, 15, 15, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{ 0, 0, 0, 0, 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0, 0, 0, 0},
{ 0, 0, 0, 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0, 0, 0},
{ 0, 0, 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0, 0},
{ 0, 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0, 0},
{ 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0, 0},
{ 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0, 0},
{ 0, 0, 0, 15, 15, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 15, 15, 15, 0, 0, 0, 0, 0},
{ 0, 0, 0, 15, 15, 6, 6, 0, 6, 6, 6, 6, 0, 6, 6, 15, 15, 15, 0, 0, 0, 0, 0},
{ 0, 0, 0, 15, 15, 6, 6, 6, 6, 12, 12, 6, 6, 6, 6, 15, 15, 15, 0, 0, 0, 0, 0},
{ 0, 0, 0, 0, 15, 6, 6, 15, 15, 12, 12, 15, 15, 6, 6, 15, 15, 15, 0, 0, 0, 0, 0},
{ 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0, 0, 0, 0},
{ 0, 0, 0, 15, 15, 15, 15, 6, 6, 6, 6, 6, 6, 15, 15, 15, 15, 0, 0, 0, 0, 0, 0},
{ 0, 0, 15, 15, 15, 15, 15, 15, 15, 12, 12, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0, 0, 0},
{ 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0, 0},
{ 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0},
{ 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0},
{ 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0},
{ 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0},
{ 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0},
{ 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0},
{ 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0, 0, 0},
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

	};
	for (int i = 0; i < 23; i++) {
		gotoxy(50, 5 + i);
		for (int j = 0; j < 23; j++) {
			if (i + 8 == current_y && j * 2 + 50 == current_x) {
				SetColor(15);
				cout << "□";
			}
			else {
				SetColor(santa_nohat[i][j]);
				cout << "■";
			}
		}
		cout << endl;
	}
}