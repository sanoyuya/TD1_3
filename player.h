#pragma once
#include"Dxlib.h"
#include"Transform.h"


class EnemyBullet;

class Enemy;

typedef class Player
{
private:
	int X;
	int Y;
	int R;
	int speed;
	int hp;
	int stelsflag;
	int stelscooltimer;
	int reflectionflag;
	int reflectioncooltimer;
	int stelsAfterglow = 0;
	int reflectionAfterglow = 0;
	int COOLTIME;
	int COOLTIMEtimer;
	int itemflag;
	int Cgh;
	int Moveflag1; int Moveflag2; int Moveflag2_2; int Moveflag3; int Moveflag4; int Moveflag5; int Move2time; int rightflag; int leftflag; int Bflag; int Aflag; double CP;
	int txtflag;
	int pushflag;
	int txt1; int txt2; int txt3; int txt4; int txt5; int txt6; int txt7; int txt8; int txt9; int txt10; int txt11; int txt12; int txt13; int txt14; int txt15; int txt16; int txt17;

	//—Š‚Ü‚ê‚Ä‚½‚à‚Ì
	int easing_flag;
	double easing_end_frame;
	double easing_frame;
	double easing_start_x;
	double easing_end_x;
	double easing_start_y;
	double easing_end_y;
	double easing_y;
	double easing_x;


	int shot_flag;
public:
	Player();
	//void Rset();
	void PlayerPadMove(char* keys, char* oldkeys);
	void HP(Transform transform, EnemyBullet* bullet, int num);
	void Draw();
	int GetX();
	int GetY();
	int GetR();
	int Getstelsflag();
	int Getreflectionflag();
	int Result();
	void TutorialMove(char* keys, char* oldkeys, Enemy enemy[],int &sceneflag);
	void TutorialDraw();

	void TuTorialHP(Transform transform, EnemyBullet* bullet, int num, int& damage_flag);

}Player;