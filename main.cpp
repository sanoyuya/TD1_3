#include "DxLib.h"
#include"player.h"
#include"enemy.h"
#include"bullet.h"
#include"subboss.h"
#include"Score.h"
#include"item.h"

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
	int ENEMY_MAX = 0;
	int sceneflag = 0;
	int pushflagA = 0;
	int stageflag = 0;
	int resultflag = 0;
	int Pauseflag = 0;
	int Pause = 0;
	int pushflagoption = 0;
	int pushUP = 0;
	int pushDOWN = 0;


	bool reflection_flag = true;

	Player* player = nullptr;
	Enemy* enemy[64] = { nullptr };
	SubBoss* sub_boss = nullptr;
	Score* score = new Score;
	Item* item = new Item;

	int wave_num = 6;
	bool wave_up_flag = false;
	bool game_set = false;
	bool break_flag = false;
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
				pushflagA = 0;
			}
			if (pushflagA == 0) {
				if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
					pushflagA = 1;
					sceneflag = 1;
				}if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
					pushflagA = 1;
					sceneflag = 1;
				}
			}

			break;

		case 1:
			//�X�e�[�W�I��
			if (keys[KEY_INPUT_SPACE] == 0 && (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) == 0) {
				pushflagA = 0;
			}
			if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT) != 0 || keys[KEY_INPUT_A] == 1) {
				stageflag = 0;
			}if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT) != 0 || keys[KEY_INPUT_D] == 1) {
				stageflag = 1;
			}
			if (stageflag == 0) {
				if (pushflagA == 0) {
					if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
						sceneflag = 10;
						player = new Player();
						enemy[0] = new Enemy;
					}if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
						sceneflag = 10;
						player = new Player();
						enemy[0] = new Enemy;
					}
				}
			}
			else {
				if (pushflagA == 0) {
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
			if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_8) == 0 && keys[KEY_INPUT_H] == 0 && oldkeys[KEY_INPUT_H] == 0) {
				pushflagoption = 0;
			}

			if (Pauseflag == 0) {
#pragma region
				score->TC(sceneflag);
				score->IC();
				player->PlayerPadMove(keys, oldkeys);
				//�f�o�b�O�p(�{�ԏ���)
				if (keys[KEY_INPUT_R] == 1 && oldkeys[KEY_INPUT_R] == 0 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_6) != 0 && (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_5) != 0) {
					delete player;
					player = new Player();
					wave_num = 16;
					game_set = false;
				}
				if (pushflagoption == 0) {
					if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_8) != 0 || keys[KEY_INPUT_H] == 1 && oldkeys[KEY_INPUT_H] == 0) {
						pushflagoption = 1;
						Pauseflag = 1;
					}
				}


#pragma region �G�f�[�^�ǂݍ���
				if (game_set == false)
				{
					if (wave_up_flag == true)
					{
						wave_num++;
						wave_up_flag = false;
					}

					//�G�̐�
					ENEMY_MAX = GetEnemyMax(wave_num);


					for (int i = 0; i < ENEMY_MAX; i++)
					{
						enemy[i] = new Enemy;
					}

					for (int i = 0; i < ENEMY_MAX; i++)
					{
						enemy[i]->SetReflectionNum();
					}


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
						sub_boss = new SubBoss;
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
						sub_boss = new SubBoss;
						EnemyForm("WAVE_ENEMY_DATA/wave20.csv", ENEMY_MAX, enemy);
						SubBossForm("WAVE_ENEMY_DATA/wave20_subboss.csv", 1, *sub_boss);
						game_set = true;
						break;
					}
					//�G�����ʖ���
					//Score+=100;

				}
#pragma endregion


#pragma region �̗͌���

				for (int i = 0; i < ENEMY_MAX; i++)
				{
					for (int j = 0; j < enemy[i]->GetBulletMax(); j++)
					{
						//���@�ƓG�̒e�̓����蔻��
						player->HP(*enemy[i]->GetBulletTransform(j), *enemy[i]->GetEnmyBullet(j));

						if (enemy[i]->GetEnemyFlag() == true)
						{
							//���@�ƃ{�}�[�̓����蔻��
							enemy[i]->PlaterToEnemyHitBox(*player);
						}

					}
				}

				for (int i = 0; i < ENEMY_MAX; i++)
				{
					if (enemy[i]->GetEnemyFlag() == true)
					{
						for (int k = 0; k < ENEMY_MAX; k++)
						{
							if (i != k)
							{
								//�G�ƃ{�}�[�̓����蔻��
								enemy[i]->ExplosionBommer(*enemy[k]);

								for (int j = 0; j < enemy[k]->GetBulletMax(); j++)
								{
									//�G�ƓG�̒e�̓����蔻��
									enemy[i]->HP(*enemy[k]->GetBulletTransform(j), *enemy[k]->GetEnmyBullet(j), item);
								}
							}
						}
					}
				}

				if (wave_num == 10 || wave_num == 20)
				{
					for (int i = 0; i < ENEMY_MAX; i++)
					{
						if (sub_boss->GetSubBossFlag() == true)
						{
							for (int j = 0; j < enemy[i]->GetBulletMax(); j++)
							{
								//���{�X�ƓG�̒e�̓����蔻��
								sub_boss->HP(*enemy[i]->GetBulletTransform(j), *enemy[i]->GetEnmyBullet(j));
							}
						}
					}

					for (int i = 0; i < sub_boss->GetBulletMax(); i++)
					{
						//���@�ƒ��{�X�̒e�̓����蔻��
						player->HP(*sub_boss->GetBulletTransform(i), *sub_boss->GetEnmyBullet(i));

						for (int j = 0; j < ENEMY_MAX; j++)
						{
							if (enemy[j]->GetEnemyFlag() == true)
							{
								//�G�ƒ��{�X�̒e�̓����蔻��
								enemy[j]->HP(*sub_boss->GetBulletTransform(i), *sub_boss->GetEnmyBullet(i), item);
							}
						}
					}

					//�n���Ǝ��@�̓����蔻��
					sub_boss->PlayerMineHit(*player);
				}

				for (int i = 0; i < ENEMY_MAX; i++)
				{
					//�G�̓���
					enemy[i]->Move(*player, reflection_flag, *score, item);
				}

				if (wave_num == 10 || wave_num == 20)
				{
					//���{�X�̓���
					sub_boss->Move(*player, reflection_flag);
				}

#pragma endregion
				//wave�N���A����
				if (wave_num != 10 && wave_num != 20)
				{
					for (int i = 0; i < ENEMY_MAX; i++)
					{
						//�G���S���|���ꂽ��e�̔��˂��Ȃ���
						if (enemy[i]->GetEnemyFlag() == false && enemy[i]->GetAppearTime() == -1)
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
				}
				else
				{
					for (int i = 0; i < ENEMY_MAX; i++)
					{
						//�G���S���|���ꂽ��e�̔��˂��Ȃ���
						if (enemy[i]->GetEnemyFlag() == false && enemy[i]->GetAppearTime() == -1 &&
							sub_boss->GetSubBossFlag() == false && sub_boss->GetAppearTime() == -1)
						{
							if (i == ENEMY_MAX - 1)
							{
								sub_boss->SetMineExplosion();
								reflection_flag = false;
							}
						}
						else
						{
							break;
						}
					}
				}

				for (int i = 0; i < ENEMY_MAX; i++)
				{
					
					if (enemy[i]->GetEnemyFlag() == true || enemy[i]->GetAppearTime() != -1)
					{
						i--;
						break_flag = true;
						break;
					}

					for (int j = 0; j < enemy[i]->GetBulletMax(); j++)
					{
						if (enemy[i]->GetBulletFlag(j) == true)
						{
							break_flag = true;
							break;
						}
					}
				}

				if (wave_num == 10 || wave_num == 20)
				{
					if (sub_boss->GetSubBossFlag() == true || sub_boss->GetAppearTime() != -1)
					{
						break_flag = true;
					}

					if (break_flag == false)
					{
						for (int i = 0; i < 12; i++)
						{
							if (sub_boss->GetEnmyBulletFlag(i) == true)
							{
								break_flag = true;
								break;
							}
						}
					}
				}

				if (break_flag == false)
				{
					game_set = false;
					reflection_flag = true;
					wave_up_flag = true;

					for (int i = 0; i < ENEMY_MAX; i++)
					{
						delete enemy[i];
					}

					if (wave_num == 10 || wave_num == 20)
					{
						delete sub_boss;
					}

					break;
				}
				else
				{
					break_flag = false;
				}

				if (wave_num > 32) {
					score->CC();
					sceneflag = 5;
				}
				sceneflag = player->Result();
				item->Move(*player, *score);
			}
			else {
#pragma region �|�[�Y��ʏ���
				if (pushflagoption == 0) {
					if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_8) != 0 || keys[KEY_INPUT_H] == 1 && oldkeys[KEY_INPUT_H] == 0) {
						pushflagoption = 1;
						Pauseflag = 0;
					}
				}

				if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP) == 0 && keys[KEY_INPUT_W] == 0) {
					pushUP = 0;
				}if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN) == 0 && keys[KEY_INPUT_S] == 0) {
					pushDOWN = 0;
				}
				if (pushUP == 0) {
					if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP) != 0 || keys[KEY_INPUT_W] == 1) {
						Pause = Pause - 1;
						pushUP = 1;
					}
				}if (pushDOWN == 0) {
					if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN) != 0 || keys[KEY_INPUT_S] == 1) {
						Pause = Pause + 1;
						pushDOWN = 1;
					}
				}

				if (Pause <= 0) {
					Pause = 0;
				}
				if (Pause >= 2) {
					Pause = 2;
				}
				if (Pause == 0) {//�߂�
					if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
						Pauseflag = 0;
					}if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
						Pauseflag = 0;
					}
				}if (Pause == 1) {//���߂����蒼��
					if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
						sceneflag = 2;
						delete player;
						player = new Player();
						delete score;
						score = new Score();
						wave_num = 1;
						game_set = false;
						Pauseflag = 0;
					}if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
						sceneflag = 2;
						delete player;
						player = new Player();
						delete score;
						score = new Score();
						wave_num = 1;
						game_set = false;
						Pauseflag = 0;
					}
				}if (Pause == 2) {//�^�C�g���ɖ߂�
					if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
						sceneflag = 0;
						delete player;

						delete score;
						Pauseflag = 0;
					}if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
						sceneflag = 0;
						delete player;

						delete score;
						Pauseflag = 0;
					}
				}
#pragma endregion
			}

			break;

		case 3:
			//�v���C���
			score->TC(sceneflag);
			score->IC();
			break;

		case 4:
			if (keys[KEY_INPUT_SPACE] == 0 && (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) == 0) {
				pushflagA = 0;
			}
			if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP) != 0 || keys[KEY_INPUT_W] == 1) {
				resultflag = 0;
			}if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN) != 0 || keys[KEY_INPUT_S] == 1) {
				resultflag = 1;
			}
			if (resultflag == 0) {//�X�e�[�W�I����ʂɖ߂�
				if (pushflagA == 0) {
					if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
						sceneflag = 1;
					}if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
						sceneflag = 1;
					}
				}
			}
			else {//�^�C�g���֖߂�
				if (pushflagA == 0) {
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
				pushflagA = 0;
			}
			if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP) != 0 || keys[KEY_INPUT_W] == 1) {
				resultflag = 0;
			}if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN) != 0 || keys[KEY_INPUT_S] == 1) {
				resultflag = 1;
			}
			if (resultflag == 0) {//�X�e�[�W�I����ʂɖ߂�
				if (pushflagA == 0) {
					if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
						sceneflag = 1;
					}if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
						sceneflag = 1;
					}
				}
			}
			else {//�^�C�g���֖߂�
				if (pushflagA == 0) {
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
			player->TutorialMove(keys, oldkeys, enemy, sceneflag, wave_num, pushflagoption);
			score->IC();
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

			if (game_set == true)
			{
				//�v���C���
				for (int i = 0; i < ENEMY_MAX; i++)
				{
					enemy[i]->Draw(60 * i);
				}
			}

			if (wave_num == 10 && wave_up_flag == false || wave_num == 20 && wave_up_flag == false)
			{
				sub_boss->Draw();
			}

			player->D();
			DrawGraph(0, 0, Layout, true);
			DrawGraph(958, 128, player_img[maba2], true);
			item->Draw();
			player->Draw();
			score->Draw();

			if (Pauseflag == 1) {
				DrawBox(220, 120, 740, 860, GetColor(255, 255, 255), false);
				if (Pause == 0) {
					DrawBox(280, 180, 680, 340, GetColor(255, 255, 255), false);
					DrawFormatString(400, 300, GetColor(255, 255, 255), "�߂�");
				}if (Pause == 1) {
					DrawBox(280, 360, 680, 520, GetColor(255, 255, 255), false);
					DrawFormatString(400, 480, GetColor(255, 255, 255), "�Ē���");
				}if (Pause == 2) {
					DrawBox(280, 640, 680, 800, GetColor(255, 255, 255), false);
					DrawFormatString(400, 660, GetColor(255, 255, 255), "�^�C�g��");
				}
			}

			break;
			delete player;
		case 3:
			//�v���C���
			score->Draw();
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
			enemy[0]->Draw(0);
			DrawGraph(0, 0, Layout, true);
			DrawGraph(958, 128, player_img[maba2], true);
			score->Draw();
			player->TutorialDraw();


			break;
			delete player;
		}

		//DrawFormatString(480, 480, GetColor(255, 255, 255), "pushflagoption:%d", pushflagoption);

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
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}
