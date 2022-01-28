#include"Dxlib.h"
#include "score.h"
#include"player.h"

Score::Score()
{
	score = 0000000;
	flame = 0;
	nohitflag = 0;
	Toptier = 0;
	Secondtier = 0;
	Thirdtier = 0;
	scoregh[9] = { 0 };
	div = 1;
	index = 0;
	scoreitem = 0;
	LoadDivGraph("resouce/scorenum.png", 10, 10, 1, 40, 60, scoregh);
}

Score::~Score()
{

}

void Score::Setnohitflag(int nohitflag) {
	this->nohitflag = nohitflag;
}

void Score::Setscoreitem(int scoreitem) {
	this->scoreitem = scoreitem;
}

void Score::IC() {
	score = scoreitem * 1000;
}

void Score::CC() {
	//クリアされたら
	score += 5000;
	if (nohitflag == 0) {
		score += 10000;
	}
}

void Score::TC(int sceneflag) {
	if (sceneflag == 2 || sceneflag == 3) {
		flame++;
	}if (sceneflag == 5) {
		score += (30000 - flame);//10分-クリアフレーム
	}
}

void Score::RC() {
	if (Toptier < score) {//スコアがランキングも含め一番高かったら
		Toptier = score;//ランキングにランクイン
	}if (Toptier > score && Secondtier < score) {//スコアがランキングも含め二番目に高かったら
		Secondtier = score;//ランキングにランクイン
	}if (Secondtier > score && Thirdtier < score) {//スコアがランキングも含め三番目に高かったら
		Thirdtier = score;//ランキングにランクイン
	}
}

void Score::Draw(int randX,int randY) {
	div = 1;
	for (int i = 0; i < 7; i++)
	{
		index = score / div % 10;
		DrawGraph((7-1-i) * 48 + 985+randX, 30 + 36+randY, scoregh[index], true);
		div = div * 10;
	}

	/*DrawFormatString(480, 480, GetColor(255, 255, 255), "score:%d", score);
	DrawFormatString(480, 500, GetColor(255, 255, 255), "scoreitem:%d", scoreitem);*/

	//result
	//クリアボーナス     +5000
	//残hp　　　　　　　 +1000*hp
	//アイテムを拾った数 +1000*item
	//ノーダメボーナス   +50000
	//タイムボーナス     +total-ボーナス類
	//--------------------------------------------
	//total = 
}