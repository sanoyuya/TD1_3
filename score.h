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
	void Draw(int randX,int randY);
	void Setscoreitem(int scoreitem);

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
};

