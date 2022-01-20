#include "DxLib.h"
#include"player.h"
#include"enemy.h"
#include"bullet.h"
#include"subboss.h"
#include"Score.h"

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "���ŃQ�[";

// �E�B���h�E����
const int WIN_WIDTH = 1376;

// �E�B���h�E�c��
const int WIN_HEIGHT = 960;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {

	SetOutApplicationLogValidFlag(FALSE);

	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���
	int Layout = LoadGraph("resouce/Layout.png");

	int player_img[4];
	LoadDivGraph("resouce/player_kari.png", 4, 4, 1, 388, 406, player_img);
	int maba = 0;
	int maba2 = 0;
	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	const int ENEMY_MAX = 5;
	int sceneflag = 0;
	int pushflag = 0;
	int stageflag = 0;
	int resultflag = 0;


	bool reflection_flag = true;

	Player* player = new Player();
	Enemy* enemy = new Enemy[ENEMY_MAX];
	SubBoss* sub_boss = new SubBoss;
	Score* score = new Score;

	int wave_num = 6;
	bool game_set = false;
	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = { 0 };

	// �Q�[�����[�v
	while (true) {
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		for (int i = 0; i < 256; ++i)
		{
			oldkeys[i] = keys[i];
		}
		//�z��Ȃ̂�oldkey = keys;�̂悤�ɂł��Ȃ��A�v�f������R�s�[

		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����
		switch (sceneflag) {//�V�[���Ǘ�
		case 0:
			//�^�C�g��
			if (keys[KEY_INPUT_SPACE] == 0 && (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) == 0) {
				pushflag = 0;
			}
			if (pushflag == 0) {
				if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
					pushflag = 1;
					sceneflag = 1;
				}if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
					pushflag = 1;
					sceneflag = 1;
				}
			}

			break;

		case 1:
			//�X�e�[�W�I��
			if (keys[KEY_INPUT_SPACE] == 0 && (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) == 0) {
				pushflag = 0;
			}
			if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT) != 0 || keys[KEY_INPUT_A] == 1) {
				stageflag = 0;
			}if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT) != 0 || keys[KEY_INPUT_D] == 1) {
				stageflag = 1;
			}
			if (stageflag == 0) {
				if (pushflag == 0) {
					if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
						sceneflag = 10;
					}if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
						sceneflag = 10;
					}
				}
			}
			else {
				if (pushflag == 0) {
					if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
						sceneflag = 3;
					}if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
						sceneflag = 3;
					}
				}
			}
			break;

		case 2:
			//�v���C���
#pragma region
			score->TC(sceneflag);
			score->KDC();
			player->PlayerPadMove(keys, oldkeys);
			//�f�o�b�O�p(�{�ԏ���)
			if (keys[KEY_INPUT_R] == 1 && oldkeys[KEY_INPUT_R] == 0 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_6) != 0 && (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_5) != 0) {
				delete player;
				player = new Player();
				delete[]enemy;
				enemy = new Enemy[ENEMY_MAX];
				wave_num = 1;
				game_set = false;
			}

#pragma region �G�f�[�^�ǂݍ���
			if (game_set == false)
			{

				
				for (int i = 0; i < ENEMY_MAX; i++)
				{
					enemy[i].SetReflectionNum();
				}
				wave_num = 10;
				switch (wave_num)
				{
				case 1:
					EnemyForm("WAVE_ENEMY_DATA/wave1.csv", ENEMY_MAX, enemy);
					delete player;
					player = new Player();
					game_set = true;
					break;
				case 2:
					EnemyForm("WAVE_ENEMY_DATA/wave2.csv", ENEMY_MAX, enemy);
					game_set = true;
					break;
				case 3:
					EnemyForm("WAVE_ENEMY_DATA/wave3.csv", ENEMY_MAX, enemy);
					game_set = true;
					break;
				case 4:
					EnemyForm("WAVE_ENEMY_DATA/wave4.csv", ENEMY_MAX, enemy);
					game_set = true;
					break;
				case 5:
					EnemyForm("WAVE_ENEMY_DATA/wave5.csv", ENEMY_MAX, enemy);
					game_set = true;
					break;
				case 6:
					EnemyForm("WAVE_ENEMY_DATA/wave6.csv", ENEMY_MAX, enemy);
					game_set = true;
					break;
				case 7:
					EnemyForm("WAVE_ENEMY_DATA/wave7.csv", ENEMY_MAX, enemy);
					game_set = true;
					break;
				case 8:
					EnemyForm("WAVE_ENEMY_DATA/wave8.csv", ENEMY_MAX, enemy);
					game_set = true;
					break;
				case 9:
					EnemyForm("WAVE_ENEMY_DATA/wave9.csv", ENEMY_MAX, enemy);
					game_set = true;
					break;
				case 10:
					EnemyForm("WAVE_ENEMY_DATA/wave10.csv", ENEMY_MAX, enemy);
					SubBossForm("WAVE_ENEMY_DATA/wave10_subboss.csv", 1, *sub_boss);
					game_set = true;
					break;
				case 11:
					EnemyForm("WAVE_ENEMY_DATA/wave11.csv", ENEMY_MAX, enemy);
					game_set = true;
					break;
				case 12:
					EnemyForm("WAVE_ENEMY_DATA/wave12.csv", ENEMY_MAX, enemy);
					game_set = true;
					break;
				case 13:
					EnemyForm("WAVE_ENEMY_DATA/wave13.csv", ENEMY_MAX, enemy);
					game_set = true;
					break;
				case 14:
					EnemyForm("WAVE_ENEMY_DATA/wave14.csv", ENEMY_MAX, enemy);
					game_set = true;
					break;
				case 15:
					EnemyForm("WAVE_ENEMY_DATA/wave15.csv", ENEMY_MAX, enemy);
					game_set = true;
					break;
				case 16:
					EnemyForm("WAVE_ENEMY_DATA/wave16.csv", ENEMY_MAX, enemy);
					game_set = true;
					break;
				case 17:
					EnemyForm("WAVE_ENEMY_DATA/wave17.csv", ENEMY_MAX, enemy);
					game_set = true;
					break;
				case 18:
					EnemyForm("WAVE_ENEMY_DATA/wave18.csv", ENEMY_MAX, enemy);
					game_set = true;
					break;
				case 19:
					EnemyForm("WAVE_ENEMY_DATA/wave19.csv", ENEMY_MAX, enemy);
					game_set = true;
					break;
				case 20:
					EnemyForm("WAVE_ENEMY_DATA/wave20.csv", ENEMY_MAX, enemy);
					SubBossForm("WAVE_ENEMY_DATA/wave20_subboss.csv", 1, *sub_boss);
					game_set = true;
					break;
				}
				//�G�����ʖ���
				//Score+=100;
			}
#pragma endregion

			for (int i = 0; i < ENEMY_MAX; i++)
			{
				enemy[i].Move(*player, reflection_flag);
			}

			if (wave_num == 10 || wave_num == 20)
			{
				sub_boss->Move(*player, reflection_flag);
			}
#pragma region �̗͌���

			for (int i = 0; i < ENEMY_MAX; i++)
			{
				for (int j = 0; j < 48; j++)
				{
					player->HP(*enemy[i].GetBulletTransform(j), *enemy[i].GetEnmyBullet(j));
					sub_boss->HP(*enemy[i].GetBulletTransform(j), *enemy[i].GetEnmyBullet(j));
					enemy[i].PlaterToEnemyHitBox(*player);
					for (int k = 0; k < ENEMY_MAX; k++)
					{
						if (i != k)
						{
							enemy[i].HP(*enemy[k].GetBulletTransform(j), *enemy[k].GetEnmyBullet(j));
							
							
							enemy[i].ExplosionBommer(enemy[k]);
						}
					}
				}
			}

			for (int i = 0; i < 4; i++)
			{
				player->HP(*sub_boss->GetBulletTransform(i), *sub_boss->GetEnmyBullet(i));
			}
			sub_boss->PlayerMineHit(*player);

#pragma endregion
			//wave�N���A����
			for (int i = 0; i < ENEMY_MAX; i++)
			{
				if (enemy[i].GetEnemyFlag() == false && enemy[i].GetAppearTime() == -1 && sub_boss->GetSubBossFlag() == false)
				{
					if (i == ENEMY_MAX - 1)
					{
						reflection_flag = false;
					}
				}
				else
				{
					break;
				}
			}

			for (int i = 0; i < ENEMY_MAX; i++)
			{
				if (enemy[i].GetEnemyFlag() == true || enemy[i].GetAppearTime() != -1 ||
					enemy[i].GetBulletFlag(0) == true || enemy[i].GetBulletFlag(1) == true || enemy[i].GetBulletFlag(2) == true
					|| sub_boss->GetSubBossFlag() == true)
				{

					i--;
					break;
				}

				if (i == ENEMY_MAX - 1)
				{
					game_set = false;
					reflection_flag = true;
					wave_num++;
				}
			}

			if (wave_num > 32) {
				score->CC();
				sceneflag = 5;
			}
			sceneflag = player->Result();

			break;

		case 3:
			//�v���C���
			score->TC(sceneflag);
			score->KDC();
			break;

		case 4:
			if (keys[KEY_INPUT_SPACE] == 0 && (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) == 0) {
				pushflag = 0;
			}
			if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP) != 0 || keys[KEY_INPUT_W] == 1) {
				resultflag = 0;
			}if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN) != 0 || keys[KEY_INPUT_S] == 1) {
				resultflag = 1;
			}
			if (resultflag == 0) {//�X�e�[�W�I����ʂɖ߂�
				if (pushflag == 0) {
					if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
						sceneflag = 1;
					}if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
						sceneflag = 1;
					}
				}
			}
			else {//�^�C�g���֖߂�
				if (pushflag == 0) {
					if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
						sceneflag = 0;
						resultflag = 0;
					}if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
						sceneflag = 0;
						resultflag = 0;
					}
				}
			}
			break;

		case 5:
			//���U���g���(�Q�[���N���A)
			score->TC(sceneflag);
			score->RC();
			if (keys[KEY_INPUT_SPACE] == 0 && (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) == 0) {
				pushflag = 0;
			}
			if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP) != 0 || keys[KEY_INPUT_W] == 1) {
				resultflag = 0;
			}if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN) != 0 || keys[KEY_INPUT_S] == 1) {
				resultflag = 1;
			}
			if (resultflag == 0) {//�X�e�[�W�I����ʂɖ߂�
				if (pushflag == 0) {
					if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
						sceneflag = 1;
					}if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
						sceneflag = 1;
					}
				}
			}
			else {//�^�C�g���֖߂�
				if (pushflag == 0) {
					if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
						sceneflag = 0;
						resultflag = 0;
					}if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
						sceneflag = 0;
						resultflag = 0;
					}
				}
			}
			break;

		case 10:
			//�`���[�g���A��
			player->TutorialMove(keys, oldkeys, enemy, sceneflag,wave_num);
			break;
		}
		// �`�揈��
		switch (sceneflag) {//�V�[���Ǘ�
		case 0:
			//�^�C�g��
			break;

		case 1:
			//�X�e�[�W�I��
			if (stageflag == 0) {
				DrawBox(64, 64, 460, 896, GetColor(255, 255, 255), false);
			}if (stageflag == 1) {
				DrawBox(500, 64, 896, 896, GetColor(255, 255, 255), false);
			}

			break;

		case 2:
			maba++;

			maba2 = maba / 10;

			if (maba2 == 4)
			{
				maba = 0;
				maba2 = 0;
			}




			//�v���C���
			for (int i = 0; i < ENEMY_MAX; i++)
			{
				enemy[i].Draw(60 * i);
			}
			sub_boss->Draw();
			player->D();
			DrawGraph(0, 0, Layout, true);
			DrawGraph(958, 128, player_img[maba2], true);

			player->Draw();


			break;
			delete player;
		case 3:
			//�v���C���
			break;

		case 4:
			//���U���g���(�Q�[���I�[�o�[)
			if (resultflag == 0) {
				DrawBox(50, 760, 910, 810, GetColor(255, 255, 255), false);
			}
			else {
				DrawBox(50, 860, 910, 910, GetColor(255, 255, 255), false);
			}

			break;

		case 5:
			//���U���g���(�Q�[���N���A)
			if (resultflag == 0) {
				DrawBox(50, 760, 910, 810, GetColor(255, 255, 255), false);
			}
			else {
				DrawBox(50, 860, 910, 910, GetColor(255, 255, 255), false);
			}
			break;

		case 10:
			//�`���[�g���A��

			maba++;

			maba2 = maba / 10;

			if (maba2 == 4)
			{
				maba = 0;
				maba2 = 0;
			}

			player->D();//itemback
			enemy[0].Draw(0);
			DrawGraph(0, 0, Layout, true);
			DrawGraph(958, 128, player_img[maba2], true);
			score->Draw();
			player->TutorialDraw();
		

			break;
			delete player;
		}

		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1) {
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	delete[]enemy;
	delete sub_boss;
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}
