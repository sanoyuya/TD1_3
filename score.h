#pragma once
class Score
{
public:
	Score();
	~Score();
	void IC();
	void CC();//clear
	void RC();//rank
	void TC(int sceneflag);//time
	void Setnohitflag(int nohitflag);
	void Draw(int randX, int randY);
	void Setscoreitem(int scoreitem);
	void KnockDown();//knockdown
	void SetHp(int hp);
	void Death(int& sceneflag);
	void Clear(int& sceneflag);
	void ResultDraw();

	int LordScore();

	void PushScore();

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
	int RESULT;
	int resultnum[10];
};

