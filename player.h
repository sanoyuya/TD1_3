#pragma once
#include"Dxlib.h"
#include"Transform.h"

class EnemyBullet;

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
	int Moveflag; int Bflag; int Aflag; double CP;
	int txtflag;
public:
	Player();
	//void Rset();
	void PlayerPadMove(char* keys, char* oldkeys);
	void HP(Transform transform, EnemyBullet* bullet, int num);
	void Draw();
	int GetX();
	int GetY();
	int Result();
	void TutorialMove(char* keys, char* oldkeys);
	void TutorialDraw();
}Player;