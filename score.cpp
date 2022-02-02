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
	RESULT = LoadGraph("resouce/result.png");
	LoadDivGraph("resouce/scorenum_128.png", 10, 10, 1, 84, 91, resultnum);
}

Score::~Score()
{
	PushScore();
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

void Score::IC() {
	score += 1000;
	item += 1000;
}

void Score::CC() {
	//�N���A���ꂽ��
	score += 5000;
	clear = 5000;

	score += 1000 * hp;
	hps = 1000 * hp;
	if (nohitflag == 0) {
		//score += 50000;
		//nodama = 50000;
	}
}

void Score::TC(int sceneflag) {
	if (sceneflag == 2) {
		flame++;
	}
}

void Score::RC() {
	if (Toptier < score) {//�X�R�A�������L���O���܂߈�ԍ���������
		Thirdtier = Secondtier;//2�ʂ�3�ʂ�
		Secondtier = Toptier;//1�ʂ�2�ʂ�
		Toptier = score;//�����L���O�Ƀ����N�C��
	}if (Toptier > score && Secondtier < score) {//�X�R�A�������L���O���܂ߓ�Ԗڂɍ���������
		Thirdtier = Secondtier;//2�ʂ�3�ʂ�
		Secondtier = score;//�����L���O�Ƀ����N�C��
	}if (Secondtier > score && Thirdtier < score) {//�X�R�A�������L���O���܂ߎO�Ԗڂɍ���������
		Thirdtier = score;//�����L���O�Ƀ����N�C��
	}
}

void Score::KnockDown() {//�G��|������*100
	score += 100;
	knock += 100;
}

void Score::Death(int& sceneflag, Boss* boss, Enemy** enemy, int ene_mex) {//�v���C���[�����񂾂Ƃ�
	if (sceneflag == 2) {
		if (hp <= 0) {
			for (int i = 0; i < ene_mex; i++)
			{
				delete enemy[i];
			}
			delete boss;
			LordScore();
			RC();
			sceneflag = 5;
		}
	}
}

void Score::Clear(int& sceneflag) {//�N���A���ꂽ�Ƃ�
	CC();
	TC(sceneflag);
	score += (45000 - flame);//15��-�N���A�t���[��
	time = (45000 - flame);//15��-�N���A�t���[��
	LordScore();
	RC();
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
	DrawGraph(0, 0, RESULT, true);
	for (int i = 0; i < 7; i++)
	{
		//---------------------------------------------------------------------�����L���O
		div = 1;
		for (int i = 0; i < 7; i++)
		{
			index = Toptier / div % 10;
			DrawGraph((7 - 1 - i) * 48 + 115, 104, scoregh[index], true);//1��
			div = div * 10;
		}div = 1;
		for (int i = 0; i < 7; i++)
		{
			index = Secondtier / div % 10;
			DrawGraph((7 - 1 - i) * 48 + 115, 358, scoregh[index], true);//2��
			div = div * 10;
		}div = 1;
		for (int i = 0; i < 7; i++)
		{
			index = Thirdtier / div % 10;
			DrawGraph((7 - 1 - i) * 48 + 115, +634, scoregh[index], true);//3��
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
			DrawGraph((7 - 1 - i) * 48 + 864, 74, scoregh[index], true);//�N���A�{�[�i�X
			div = div * 10;
		}

		div = 1;
		for (int i = 0; i < 7; i++)
		{
			index = hps / div % 10;
			DrawGraph((7 - 1 - i) * 48 + 864, 197, scoregh[index], true);//�chp
			div = div * 10;
		}

		div = 1;
		for (int i = 0; i < 7; i++)
		{
			index = knock / div % 10;
			DrawGraph((7 - 1 - i) * 48 + 864, 334, scoregh[index], true);//�G��|������
			div = div * 10;
		}

		div = 1;
		for (int i = 0; i < 7; i++)
		{
			index = item / div % 10;
			DrawGraph((7 - 1 - i) * 48 + 864, 466, scoregh[index], true);//�A�C�e�����E������
			div = div * 10;
		}

		//div = 1;
		//for (int i = 0; i < 7; i++)
		//{
		//	index = nodama / div % 10;
		//	DrawGraph((7 - 1 - i) * 48 + 800, 30 + 400, scoregh[index], true);//�m�[�_���{�[�i�X
		//	div = div * 10;
		//}

		if (hp >= 1) {
			div = 1;
			for (int i = 0; i < 7; i++)
			{
				index = time / div % 10;
				DrawGraph((7 - 1 - i) * 48 + 864, 606, scoregh[index], true);//�^�C���{�[�i�X
				div = div * 10;
			}
		}
		else {
			for (int i = 0; i < 7; i++)
			{
				index = 0 / div % 10;
				DrawGraph((7 - 1 - i) * 48 + 864, 607, scoregh[index], true);//�^�C���{�[�i�X
				div = div * 10;
			}
		}

		div = 1;
		for (int i = 0; i < 7; i++)
		{
			index = score / div % 10;
			DrawGraph((7 - 1 - i) * 96 + 644, 799, resultnum[index], true);//total
			div = div * 10;
		}
	}
}

int Score::LordScore()
{
	FILE* fp;
	fopen_s(&fp, "score/Toptier.txt", "r");
	int score_num;
	if (fp == NULL)
	{
		return -1;
	}
	fscanf_s(fp, "%d", &score_num);
	fclose(fp);
	Toptier = score_num;

	fopen_s(&fp, "score/Secondtier.txt", "r");

	if (fp == NULL)
	{
		return -1;
	}
	fscanf_s(fp, "%d", &score_num);
	fclose(fp);
	Secondtier = score_num;

	fopen_s(&fp, "score/Thirdtier.txt", "r");

	if (fp == NULL)
	{
		return -1;
	}
	fscanf_s(fp, "%d", &score_num);
	fclose(fp);
	Thirdtier = score_num;

	return 0;
}

void Score::PushScore()
{
	FILE* fp;
	fopen_s(&fp, "score/Toptier.txt", "w");

	if (fp != NULL)
	{
		fprintf_s(fp, "%d", Toptier);
		fclose(fp);
	}
	fopen_s(&fp, "score/Secondtier.txt", "w");

	if (fp != NULL)
	{
		fprintf_s(fp, "%d", Secondtier);
		fclose(fp);
	}
	fopen_s(&fp, "score/Thirdtier.txt", "w");

	if (fp != NULL)
	{
		fprintf_s(fp, "%d", Thirdtier);
		fclose(fp);
	}
}
