#pragma once
class Score
{
public:
	Score();
	~Score();
	void IC();//knockdown
	void CC();//clear
	void RC();//rank
	void TC(int sceneflag);//time
	void Setnohitflag(int nohitflag);
	void Draw(int randX, int randY);
	void Setscoreitem(int scoreitem);
	void KnockDown();
	void SetHp(int hp);
	void Death(int& sceneflag);
	void Clear(int& sceneflag);
	void ResultDraw();

private:
	int score;
	int Toptier;
	int Secondtier;
	int Thirdtier;
	int flame;
	int nohitflag;
	int scoregh[10];
	int div;
	int index;
	int scoreitem;
	int hp;
	int knock;
	int item;
	int time;
	int nodama;
	int clear;
	int hps;
};

