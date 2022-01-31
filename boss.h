#pragma once

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
		bool& reflection_flag, bool& movie_flag, char* keys);
	void Draw(Enemy** enemy);
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
};

