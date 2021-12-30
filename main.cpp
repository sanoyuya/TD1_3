#include "DxLib.h"
#include"player.h"
#include"enemy.h"
#include"bullet.h"
#include"subboss.h"

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "���ŃQ�[";

// �E�B���h�E����
const int WIN_WIDTH = 1376;

// �E�B���h�E�c��
const int WIN_HEIGHT = 960;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {
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


	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	const int ENEMY_MAX = 5;
	int sceneflag = 0;
	Player* player = new Player();
	Enemy* enemy = new Enemy[ENEMY_MAX];
	SubBoss* sub_boss = new SubBoss;

	SubBossForm("subbosstest.csv", 1, *sub_boss);

	int wave_num = 1;
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
			if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
				sceneflag = 2;
			}if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
				sceneflag = 2;
			}

			break;

		case 1:
			//�X�e�[�W�I��
			break;

		case 2:
			//�v���C���

#pragma region �G�f�[�^�ǂݍ���
			if (game_set == false)
			{
				switch (wave_num)
				{
				case 1:
					EnemyForm("WAVE_ENEMY_DATA/wave1.csv", ENEMY_MAX, enemy);
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
				}

			}
#pragma endregion

			for (int i = 0; i < ENEMY_MAX; i++)
			{
				enemy[i].Move(*player);
			}

			/*enemy[0].Move(*player);
			enemy[1].Move(*player);
			enemy[0].ExplosionBommer(enemy[1], *player);*/

			//sub_boss->Move(*player);

#pragma region �̗͌���
			for (int i = 0; i < ENEMY_MAX; i++)
			{
				for (int j = 0; j < 2; j++)
				{
					player->HP(enemy[i].GetBulletTransform(j), enemy[i].GetEnmyBullet(), j);

					for (int k = 0; k < ENEMY_MAX; k++)
					{
						if (i != k)
						{
							if (enemy[i].GetEnemyFlag() == true && enemy[k].GetEnemyFlag() == true)
							{
								enemy[i].HP(enemy[k].GetBulletTransform(j), enemy[k].GetEnmyBullet(), j);
							}
						}
					}
				}
			}
			for (int i = 0; i < 4; i++)
			{
				player->HP(sub_boss->GetBulletTransform(i), sub_boss->GetEnmyBullet(), i);
			}
#pragma endregion

			//wave�N���A����
			for (int i = 0; i < ENEMY_MAX; i++)
			{
				if (enemy[i].GetEnemyFlag() == true ||
					
					enemy[i].GetAppearTime() != -1)
				{
					i--;
					break;
				}

				if (i == ENEMY_MAX-1)
				{
					game_set = false;
					wave_num++;
				}
			}

			player->PlayerPadMove(keys, oldkeys);

			sceneflag = player->Result();

			break;

		case 3:
			//���U���g���(�Q�[���I�[�o�[)
			break;

		case 4:
			//���U���g���(�Q�[���N���A)
			break;
		}
		// �`�揈��
		switch (sceneflag) {//�V�[���Ǘ�
		case 0:
			//�^�C�g��
			break;

		case 1:
			//�X�e�[�W�I��
			break;

		case 2:
			//�v���C���
			for (int i = 0; i < ENEMY_MAX; i++)
			{
			enemy[i].Draw(40*i);
			}

			player->Draw();
			sub_boss->Draw();

			break;
			delete player;
		case 3:
			//���U���g���(�Q�[���I�[�o�[)
			break;

		case 4:
			//���U���g���(�Q�[���N���A)
			break;
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
