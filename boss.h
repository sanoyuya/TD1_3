#pragma once
#include"Transform.h"
class Player;

class Score;

class Enemy;

class Item;


class Boss
{
public:
	Boss();
	~Boss();
	void Move(Enemy** enemy, Player* player, Item* item, Score* score,
		int& recoveryflag, int& recoverytime, int& vibflag, int& screenshakeflag,
		int& shakeflag, int& damageflag, int& shaketime, int& damagetime,
		bool& reflection_flag, bool& movie_flag, char* keys, int& sceneflag, bool& txt_shake_flag, int& damageAlpha);
	void Draw(Enemy** enemy);

	int GetBossTxtFlag();
private:
	bool wave_set;
	int wave_num;
	int ENEMY_MAX;
	bool wave_up_flag;
	bool break_flag;

	bool zako_wannihilation_falg;
	int zako_num;

	bool boss1_wannihilation_falg;
	int boss1_num;

	bool boomerang_wannihilation_falg;
	int boomerang_num;

	bool boss2_wannihilation_falg;
	int boss2_num;

	bool bommer_wannihilation_falg;
	int bommer_num;

	bool omnidirectional_wannihilation_falg;
	int omnidirectional_num;

	int tmp_num;

	Transform transform;
	int flame;
	double ang;
	double x;
	double y;

	bool easing_flag;
	double easing_start_x;
	double easing_start_y;
	double easing_end_x;
	double easing_end_y;
	double easing2_end_y;
	double easing_frame;
	double easing_end_frame;

	double escape_start_x;
	double escape_start_y;
	double escape_end_x;
	double escape_end_y;
	double escape_frame;
	double escape_end_frame;

	int txt_flag;

	int img[2];
	int mugon_img[2];
	int talk_img[2];


	int img_anime;
	int img_anime_timer;

	int txt_cool_time;

	bool move_flag;

	int boss_txt_flag;

};

