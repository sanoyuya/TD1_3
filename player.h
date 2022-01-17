#pragma once
#include"Dxlib.h"
#include"Transform.h"


class EnemyBullet;

class Enemy;

class Item;

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
	int A; int option; int Apflag; int Apushflag; int SetAtime; int HPgh; int MPgh;

	//頼まれてたもの

	int itemflag2;

	//イージング
	int easing_flag;
	double easing_end_frame;
	double easing_frame;
	double easing_start_x;
	double easing_end_x;
	double easing_start_y;
	double easing_end_y;
	double easing_y;
	double easing_x;

	//体力
	int hp_img;

	//時機アニメーション
	int img[16];
	int img_r;
	int anime_timer;
	int anime;

	//アイテムを取得した数
	int item_x[3];
	int item_y[2];
	int item_r;
	int item_img;

	//反射
	int reflection_img;
	int reflection_r;

	//ステルスアニメーション
	int stealth_img[16];
	int stealth_img_r;
	int stealth_anime_timer;
	int stealth_anime;

	Item* tutorial_item;

	int shot_flag;
	int damage_flag;
public:
	Player();
	//void Rset();
	void PlayerPadMove(char* keys, char* oldkeys);
	void HP(Transform transform, EnemyBullet& bullet);
	void Draw();
	int GetX();
	int GetY();
	int GetR();
	int Getstelsflag();
	int Getreflectionflag();
	int GetReflectionR();
	int GetDamageFlag();
	int GetHp();
	int Result();

	void TutorialMove(char* keys, char* oldkeys, Enemy enemy[],int &sceneflag, int& wave_num);
	void TutorialDraw();
	void TuTorialHP(Transform transform, EnemyBullet& bullet,int& damage_flag);

	void ItemFlagAdd(int num);
	void HpSub(int num);
	void SetDamageFlag(int num);
}Player;