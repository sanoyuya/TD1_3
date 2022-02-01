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
	hp = 0;
	knock = 0;
	item = 0;
	time = 0;
	nodama = 0;
	clear = 0;
	hps = 0;
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

void Score::SetHp(int hp) {
	this->hp = hp;
}

void Score::IC(int scoreitem) {
	score += 1000;
	item = scoreitem * 1000;

}

void Score::CC() {
	//クリアされたら
	score += 5000;
	clear = 5000;

	score += 1000 * hp;
	hps = 1000 * hp;
	if (nohitflag == 0) {
		score += 50000;
		nodama = 50000;
	}
}

void Score::TC(int sceneflag) {
	if (sceneflag == 2 || sceneflag == 3) {
		flame++;
	}if (sceneflag == 5) {
		score += (30000 - flame);//10分-クリアフレーム
		time = (30000 - flame);//10分-クリアフレーム
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

void Score::KnockDown() {//敵を倒した数*100
	score += 100;
	knock += 100;
}

void Score::Death(int& sceneflag) {//プレイヤーが死んだとき
	if (hp <= 0) {
		KnockDown();
		IC(scoreitem);
		RC();
		sceneflag = 5;
	}
}

void Score::Clear(int& sceneflag) {//クリアされたとき
	IC(scoreitem);
	CC();
	TC(sceneflag);
	KnockDown();

	TC(sceneflag);
	sceneflag = 5;
}

void Score::Draw(int randX, int randY) {//ゲーム内スコア表示
	div = 1;
	for (int i = 0; i < 7; i++)
	{
		index = score / div % 10;
		DrawGraph((7 - 1 - i) * 48 + 985 + randX, 30 + 36 + randY, scoregh[index], true);
		div = div * 10;
	}

	/*DrawFormatString(480, 480, GetColor(255, 255, 255), "score:%d", score);
	DrawFormatString(480, 500, GetColor(255, 255, 255), "scoreitem:%d", scoreitem);*/
}

void Score::ResultDraw() {
	for (int i = 0; i < 7; i++)
	{
		//---------------------------------------------------------------------ランキング
		div = 1;
		for (int i = 0; i < 7; i++)
		{
			index = Toptier / div % 10;
			DrawGraph((7 - 1 - i) * 48 + 300, 30 + 100, scoregh[index], true);//1位
			div = div * 10;
		}div = 1;
		for (int i = 0; i < 7; i++)
		{
			index = Secondtier / div % 10;
			DrawGraph((7 - 1 - i) * 48 + 300, 30 + 300, scoregh[index], true);//2位
			div = div * 10;
		}div = 1;
		for (int i = 0; i < 7; i++)
		{
			index = Thirdtier / div % 10;
			DrawGraph((7 - 1 - i) * 48 + 300, 30 + 500, scoregh[index], true);//3位
			div = div * 10;
		}
		//---------------------------------------------------------------------ランキング

		//result
		//クリアボーナス     +5000
		//残hp　　　　　　　 +1000*hp
		//敵を倒した数　　　 +倒した数*100
		//アイテムを拾った数 +1000*item
		//ノーダメボーナス   +50000
		//タイムボーナス     +total-ボーナス類
		//--------------------------------------------
		//total = 


		div = 1;
		for (int i = 0; i < 7; i++)
		{
			index = clear / div % 10;
			DrawGraph((7 - 1 - i) * 48 + 800, 30 + 300, scoregh[index], true);//クリアボーナス
			div = div * 10;
		}

		div = 1;
		for (int i = 0; i < 7; i++)
		{
			index = hps / div % 10;
			DrawGraph((7 - 1 - i) * 48 + 800, 30 + 400, scoregh[index], true);//残hp
			div = div * 10;
		}

		div = 1;
		for (int i = 0; i < 7; i++)
		{
			index = knock / div % 10;
			DrawGraph((7 - 1 - i) * 48 + 800, 30 + 500, scoregh[index], true);//敵を倒した数
			div = div * 10;
		}

		div = 1;
		for (int i = 0; i < 7; i++)
		{
			index = item / div % 10;
			DrawGraph((7 - 1 - i) * 48 + 800, 30 + 600, scoregh[index], true);//アイテムを拾った数
			div = div * 10;
		}

		div = 1;
		for (int i = 0; i < 7; i++)
		{
			index = nodama / div % 10;
			DrawGraph((7 - 1 - i) * 48 + 800, 30 + 700, scoregh[index], true);//ノーダメボーナス
			div = div * 10;
		}

		div = 1;
		for (int i = 0; i < 7; i++)
		{
			index = time / div % 10;
			DrawGraph((7 - 1 - i) * 48 + 800, 30 + 800, scoregh[index], true);//タイムボーナス
			div = div * 10;
		}

		div = 1;
		for (int i = 0; i < 7; i++)
		{
			index = score / div % 10;
			DrawGraph((7 - 1 - i) * 48 + 800, 30 + 900, scoregh[index], true);//total
			div = div * 10;
		}
	}
}