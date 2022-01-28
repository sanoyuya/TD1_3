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
	//�N���A���ꂽ��
	score += 5000;
	if (nohitflag == 0) {
		score += 10000;
	}
}

void Score::TC(int sceneflag) {
	if (sceneflag == 2 || sceneflag == 3) {
		flame++;
	}if (sceneflag == 5) {
		score += (30000 - flame);//10��-�N���A�t���[��
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
	//�N���A�{�[�i�X     +5000
	//�chp�@�@�@�@�@�@�@ +1000*hp
	//�A�C�e�����E������ +1000*item
	//�m�[�_���{�[�i�X   +50000
	//�^�C���{�[�i�X     +total-�{�[�i�X��
	//--------------------------------------------
	//total = 
}