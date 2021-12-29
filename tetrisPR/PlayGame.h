#pragma once
#include "StageData.h"
#include <mmsystem.h>    
#pragma comment(lib,"winmm.lib")
enum
{  //Game.h
	BLACK,      /*  0 : 까망 */
	DARK_BLUE,    /*  1 : 어두운 파랑 */
	DARK_GREEN,    /*  2 : 어두운 초록 */
	DARK_SKY_BLUE,  /*  3 : 어두운 하늘 */
	DARK_RED,    /*  4 : 어두운 빨강 */
	DARK_VOILET,  /*  5 : 어두운 보라 */
	DARK_YELLOW,  /*  6 : 어두운 노랑 */
	GRAY,      /*  7 : 회색 */
	DARK_GRAY,    /*  8 : 어두운 회색 */
	BLUE,      /*  9 : 파랑 */
	GREEN,      /* 10 : 초록 */
	SKY_BLUE,    /* 11 : 하늘 */
	RED,      /* 12 : 빨강 */
	VIOLET,      /* 13 : 보라 */
	YELLOW,      /* 14 : 노랑 */
	WHITE,      /* 15 : 하양 */
};
class PlayGame
{
private:
	int k = -1;
	bool lost_lens = false;
	int high;
	int level;    //레벨
	int ab_x, ab_y;   //화면중 블럭이 나타나는 좌표의 절대위치
	int block_shape, block_angle, block_x, block_y;   //현재 떨어지는 블럭의 정보(종류, 회전상태, 실제 모양??????????)
	int next_block_shape;   //다음블럭모양
	int score;   //점수
	int lines;   //깬 줄
	int game_start;
	int q_ = 3; //아이템 사용가능 개수 
	int w_ = 3;
	int e_ = 3;
	int r_ = 1;
	int check_effect3 = -1;
	bool isTrue = false; //킵여부
	int shape_copy; //킵한 블록 모양 넣을
	char total_block[22][14];      //화면에 표시되는 블럭들
	char block[8][4][4][4] = {
		//막대모양
		1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,   1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,   1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,   1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,

		//네모모양
		1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,   1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,   1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,   1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,

		//'ㅓ' 모양
		0,1,0,0,1,1,0,0,0,1,0,0,0,0,0,0,   1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,   1,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,   0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,

		//'ㄱ'모양
		1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,   1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,   1,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,   0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,

		//'ㄴ' 모양
		1,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,   1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,   0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,0,   1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,

		//'Z' 모양
		1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,   0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,   1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,   0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,

		//'S' 모양
		0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,   1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,   0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,   1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,

		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,

	};
	StageData** stage_data;

public:
	PlayGame();
	~PlayGame();
	void play();
	int check_effect4_int;
	bool check_effect4 = true;
	void gotoxy(int x, int y);   //커서옮기기
	void SetColor(int color);   //색표현
	int init();               //각종변수 초기화 
	int show_cur_block(int shape, int angle, int x, int y);   //진행중인 블럭을 화면에 표시한다
	void show_keep_block(int shape);
	int erase_cur_block(int shape, int angle, int x, int y);   //블럭 진행의 잔상을 지우기 위한 함수
	void show_total_block();   //쌓여져있는 블럭을 화면에 표시한다.
	void show_next_block(int shape);   //다음 블럭 표시
	int make_new_block();   //return값으로 block의 모양번호를 알려줌
	int strike_check(int shape, int angle, int x, int y);   //블럭이 화면 맨 아래에 부닥쳤는지 검사 부닥치면 1을리턴 아니면 0리턴
	void merge_block(int shape, int angle, int x, int y);   //블럭이 바닥에 닿았을때 진행중인 블럭과 쌓아진 블럭을 합침
	int block_start(int& angle, int& x, int& y);   //블럭이 처음 나올때 위치와 모양을 알려줌
	int block_start(int& shape, int& angle, int& x, int& y);
	int block_start2(int& shape, int& angle, int& x, int& y);
	int move_block(int& shape, int& angle, int& x, int& y, int& next_shape);   //게임오버는 1을리턴 바닥에 블럭이 닿으면 2를 리턴
	void rotate_block();
	void show_gameover();
	void show_gamestat(); //스테이지, 점수, 줄 수 출력
	void show_logo();
	void input_data();//게임 레벨 입력받음
	int check_full_line();   //한 줄이 채워졌는지 확인하고 채워졌으면 없앰
	void item_effect1();
	void item_effect2();
	void item_effect3(int i);
	void item_effect4();
	void change_key(int i);
	int keep_block(int shape);
	int getGame_Start() {
		return game_start;
	}
	void setGame_Start() {
		game_start++;
	}
	void map1();
	void map2();
	void map3();
	void map4();
	void map5();
	void map6();
	void attack();
	void crush(int i, int level);
	void crush1();
	void crush2();
	void crush3();
	void crush4();
	void crush5();
	void crush6();
	void crush7();
	void story();
	void talk_m();
	void talk1();
	void talk2();
	void talk3();
	void talk4();
	void talk5();
	void talk6();
	void talk7();
	void talk8();
	void cursor_view(char s);
	void start_logo();
	void over_logo();
	void clear_logo();
	void santa_nice();
	void santa_bad();
	void erase_t();
	void endrudolf();
	void item_message(int i);
	void santa();
	void dolsun();
	void dolf();
	void santa_nohat();
};