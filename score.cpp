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
	//�N���A���ꂽ��
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
		score += (30000 - flame);//10��-�N���A�t���[��
		time = (30000 - flame);//10��-�N���A�t���[��
	}
}

void Score::RC() {
	if (Toptier < score) {//�X�R�A�������L���O���܂߈�ԍ���������
		Toptier = score;//�����L���O�Ƀ����N�C��
	}if (Toptier > score && Secondtier < score) {//�X�R�A�������L���O���܂ߓ�Ԗڂɍ���������
		Secondtier = score;//�����L���O�Ƀ����N�C��
	}if (Secondtier > score && Thirdtier < score) {//�X�R�A�������L���O���܂ߎO�Ԗڂɍ���������
		Thirdtier = score;//�����L���O�Ƀ����N�C��
	}
}

void Score::KnockDown() {//�G��|������*100
	score += 100;
	knock += 100;
}

void Score::Death(int& sceneflag) {//�v���C���[�����񂾂Ƃ�
	if (hp <= 0) {
		KnockDown();
		IC(scoreitem);
		RC();
		sceneflag = 5;
	}
}

void Score::Clear(int& sceneflag) {//�N���A���ꂽ�Ƃ�
	IC(scoreitem);
	CC();
	TC(sceneflag);
	KnockDown();

	TC(sceneflag);
	sceneflag = 5;
}

void Score::Draw(int randX, int randY) {//�Q�[�����X�R�A�\��
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
		//---------------------------------------------------------------------�����L���O
		div = 1;
		for (int i = 0; i < 7; i++)
		{
			index = Toptier / div % 10;
			DrawGraph((7 - 1 - i) * 48 + 300, 30 + 100, scoregh[index], true);//1��
			div = div * 10;
		}div = 1;
		for (int i = 0; i < 7; i++)
		{
			index = Secondtier / div % 10;
			DrawGraph((7 - 1 - i) * 48 + 300, 30 + 300, scoregh[index], true);//2��
			div = div * 10;
		}div = 1;
		for (int i = 0; i < 7; i++)
		{
			index = Thirdtier / div % 10;
			DrawGraph((7 - 1 - i) * 48 + 300, 30 + 500, scoregh[index], true);//3��
			div = div * 10;
		}
		//---------------------------------------------------------------------�����L���O

		//result
		//�N���A�{�[�i�X     +5000
		//�chp�@�@�@�@�@�@�@ +1000*hp
		//�G��|�������@�@�@ +�|������*100
		//�A�C�e�����E������ +1000*item
		//�m�[�_���{�[�i�X   +50000
		//�^�C���{�[�i�X     +total-�{�[�i�X��
		//--------------------------------------------
		//total = 


		div = 1;
		for (int i = 0; i < 7; i++)
		{
			index = clear / div % 10;
			DrawGraph((7 - 1 - i) * 48 + 800, 30 + 300, scoregh[index], true);//�N���A�{�[�i�X
			div = div * 10;
		}

		div = 1;
		for (int i = 0; i < 7; i++)
		{
			index = hps / div % 10;
			DrawGraph((7 - 1 - i) * 48 + 800, 30 + 400, scoregh[index], true);//�chp
			div = div * 10;
		}

		div = 1;
		for (int i = 0; i < 7; i++)
		{
			index = knock / div % 10;
			DrawGraph((7 - 1 - i) * 48 + 800, 30 + 500, scoregh[index], true);//�G��|������
			div = div * 10;
		}

		div = 1;
		for (int i = 0; i < 7; i++)
		{
			index = item / div % 10;
			DrawGraph((7 - 1 - i) * 48 + 800, 30 + 600, scoregh[index], true);//�A�C�e�����E������
			div = div * 10;
		}

		div = 1;
		for (int i = 0; i < 7; i++)
		{
			index = nodama / div % 10;
			DrawGraph((7 - 1 - i) * 48 + 800, 30 + 700, scoregh[index], true);//�m�[�_���{�[�i�X
			div = div * 10;
		}

		div = 1;
		for (int i = 0; i < 7; i++)
		{
			index = time / div % 10;
			DrawGraph((7 - 1 - i) * 48 + 800, 30 + 800, scoregh[index], true);//�^�C���{�[�i�X
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