#pragma once
#include"Dxlib.h"
#include"Transform.h"
#include "score.h"


class EnemyBullet;

class Enemy;

class Item;

typedef class Player
{
public:
	Player();
	//void Rset();
	void PlayerPadMove(char* keys, char* oldkeys, int wave_num);
	void HP(Transform transform, EnemyBullet& bullet, int flag, int screenshakeflag, int& shakeflag, int& damageflag, int& shaketime, int& damagetime, int& damageAlpha);
	void HPplus(int wave, int& recoveryflag, int& recoverytime);
	void Draw(int randX, int randY);
	void D(int randX, int randY);
	int GetX();
	int GetY();
	int GetR();
	int Getstelsflag();
	int Getreflectionflag();
	int GetReflectionR();
	int GetDamageFlag(int num);
	int GetEnemyDamage(int num);
	int GetHp();
	int Result();
	int Getnohitflag();
	int Getscoreitem();
	void pushB();

	void TutorialMove(char* keys, char* oldkeys, Enemy** enemy, int& sceneflag, int& wave_num, int& pushflagoption, int& flag, int& screenshakeflag, int& shakeflag, int& damageflag, int& damageAlpha);
	void TutorialDraw(int randX, int randY, char* keys);
	void TuTorialHP(Transform transform, EnemyBullet& bullet, int& damage_flag, int& shaketime, int& damagetime);
	void ItemFlagAdd(int num, Score& score);
	void HpSub(int num);
	void SetDamageFlag(int i, int num);
	void SetMoveFlag(int flag);

	int EasingMove(double end_x, double end_y, int end_frame);
	void SetEasingFlag(int num);
	void DeleteItem();

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
	int itemflag; int scoreitem;
	int Cgh;
	int Moveflag1; int Moveflag2; int Moveflag2_2; int Moveflag3; int Moveflag4; int Moveflag5; int Move2time; int rightflag; int leftflag; int Bflag; int Aflag; double CP;
	int txtflag;
	int pushflag;
	int pushflagB;
	int txt1; int txt2; int txt3; int txt4; int txt5; int txt6; int txt7; int txt8; int txt9; int txt10; int txt11; int txt12; int txt13; int txt14; int txt15; int txt16; int txt17;
	int A; int option; int Apflag; int Apushflag; int SetAtime;
	int HPgh; int MPgh; int itemline; int itemback; int bigitem; int Alpha;
	int nohitflag;
	int maba;
	int maba2;
	int player_img1[12] = { 0 };
	int player_img2[12] = { 0 };
	int txtcooltime;

	//頼まれてたもの

	int itemflag2;

	int move_flag;

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
	int damage_flag[10];

	int enemy_damage[32];

	int item_1_img;

	Vertex vertex;
}Player;