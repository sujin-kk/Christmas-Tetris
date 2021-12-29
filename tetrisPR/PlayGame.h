#pragma once
#include "StageData.h"
#include <mmsystem.h>    
#pragma comment(lib,"winmm.lib")
enum
{  //Game.h
	BLACK,      /*  0 : ��� */
	DARK_BLUE,    /*  1 : ��ο� �Ķ� */
	DARK_GREEN,    /*  2 : ��ο� �ʷ� */
	DARK_SKY_BLUE,  /*  3 : ��ο� �ϴ� */
	DARK_RED,    /*  4 : ��ο� ���� */
	DARK_VOILET,  /*  5 : ��ο� ���� */
	DARK_YELLOW,  /*  6 : ��ο� ��� */
	GRAY,      /*  7 : ȸ�� */
	DARK_GRAY,    /*  8 : ��ο� ȸ�� */
	BLUE,      /*  9 : �Ķ� */
	GREEN,      /* 10 : �ʷ� */
	SKY_BLUE,    /* 11 : �ϴ� */
	RED,      /* 12 : ���� */
	VIOLET,      /* 13 : ���� */
	YELLOW,      /* 14 : ��� */
	WHITE,      /* 15 : �Ͼ� */
};
class PlayGame
{
private:
	int k = -1;
	bool lost_lens = false;
	int high;
	int level;    //����
	int ab_x, ab_y;   //ȭ���� ���� ��Ÿ���� ��ǥ�� ������ġ
	int block_shape, block_angle, block_x, block_y;   //���� �������� ���� ����(����, ȸ������, ���� ���??????????)
	int next_block_shape;   //���������
	int score;   //����
	int lines;   //�� ��
	int game_start;
	int q_ = 3; //������ ��밡�� ���� 
	int w_ = 3;
	int e_ = 3;
	int r_ = 1;
	int check_effect3 = -1;
	bool isTrue = false; //ŵ����
	int shape_copy; //ŵ�� ��� ��� ����
	char total_block[22][14];      //ȭ�鿡 ǥ�õǴ� ����
	char block[8][4][4][4] = {
		//������
		1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,   1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,   1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,   1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,

		//�׸���
		1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,   1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,   1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,   1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,

		//'��' ���
		0,1,0,0,1,1,0,0,0,1,0,0,0,0,0,0,   1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,   1,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,   0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,

		//'��'���
		1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,   1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,   1,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,   0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,

		//'��' ���
		1,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,   1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,   0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,0,   1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,

		//'Z' ���
		1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,   0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,   1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,   0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,

		//'S' ���
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
	void gotoxy(int x, int y);   //Ŀ���ű��
	void SetColor(int color);   //��ǥ��
	int init();               //�������� �ʱ�ȭ 
	int show_cur_block(int shape, int angle, int x, int y);   //�������� ���� ȭ�鿡 ǥ���Ѵ�
	void show_keep_block(int shape);
	int erase_cur_block(int shape, int angle, int x, int y);   //�� ������ �ܻ��� ����� ���� �Լ�
	void show_total_block();   //�׿����ִ� ���� ȭ�鿡 ǥ���Ѵ�.
	void show_next_block(int shape);   //���� �� ǥ��
	int make_new_block();   //return������ block�� ����ȣ�� �˷���
	int strike_check(int shape, int angle, int x, int y);   //���� ȭ�� �� �Ʒ��� �δ��ƴ��� �˻� �δ�ġ�� 1������ �ƴϸ� 0����
	void merge_block(int shape, int angle, int x, int y);   //���� �ٴڿ� ������� �������� ���� �׾��� ���� ��ħ
	int block_start(int& angle, int& x, int& y);   //���� ó�� ���ö� ��ġ�� ����� �˷���
	int block_start(int& shape, int& angle, int& x, int& y);
	int block_start2(int& shape, int& angle, int& x, int& y);
	int move_block(int& shape, int& angle, int& x, int& y, int& next_shape);   //���ӿ����� 1������ �ٴڿ� ���� ������ 2�� ����
	void rotate_block();
	void show_gameover();
	void show_gamestat(); //��������, ����, �� �� ���
	void show_logo();
	void input_data();//���� ���� �Է¹���
	int check_full_line();   //�� ���� ä�������� Ȯ���ϰ� ä�������� ����
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