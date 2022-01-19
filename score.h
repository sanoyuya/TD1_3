#pragma once
class Score
{
public:
	Score();
	~Score();
	void KDC();//knockdown
	void CC();//clear
	void RC();//rank
	void TC(int sceneflag);//time
	void Setnohitflag(int nohitflag);
	void Draw();

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
};

