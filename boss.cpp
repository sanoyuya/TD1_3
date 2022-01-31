#include"boss.h"
#include"player.h"
#include"enemy.h"
#include"item.h"
#include"score.h"
#include"DxLib.h"

int GetBossEnemyMax(int wave_num)
{
	switch (wave_num)
	{
	case 1:
		return 20;
	case 2:
		return 26;
	case 3:
		return 18;
	}

	return -1;
}

Boss::Boss()
{
	break_flag = false;
	ENEMY_MAX = 0;
	wave_num = 1;
	wave_up_flag = false;
	wave_set = false;

	zako_num = 0;
	zako_wannihilation_falg = false;

	tmp_num = 0;
	boss1_num = 0;
	boss1_wannihilation_falg = false;

	boomerang_num = 0;
	boomerang_wannihilation_falg = false;

	boss2_num = 0;
	boss2_wannihilation_falg = false;

	bommer_num = 0;
	bommer_wannihilation_falg = false;

	omnidirectional_num = 0;
	omnidirectional_wannihilation_falg = false;
}

Boss::~Boss()
{
}

void Boss::Move(Enemy** enemy, Player* player, Item* item, Score* score,
	int& recoveryflag, int& recoverytime, int& vibflag, int& screenshakeflag,
	int& shakeflag, int& damageflag, int& shaketime, int& damagetime,
	bool& reflection_flag, bool& movie_flag, char* keys)
{

#pragma region �G�f�[�^�ǂݍ���
	if (wave_set == false)
	{
		if (wave_up_flag == true)
		{
			wave_num++;
			//player->HPplus(wave_num, recoveryflag = 0, recoverytime = 0);
			wave_up_flag = false;
		}

		//�G�̐�
		ENEMY_MAX = GetBossEnemyMax(wave_num);

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

			EnemyForm("WAVE_ENEMY_DATA/boss1.csv", ENEMY_MAX, enemy, wave_num);
			zako_num = 10;
			boss1_num = 2;
			boss2_num = 2;
			boomerang_num = 6;
			omnidirectional_num = 1;
			bommer_num = 4;
			wave_set = true;
			break;
		case 2:
			EnemyForm("WAVE_ENEMY_DATA/boss2.csv", ENEMY_MAX, enemy, wave_num);
			wave_set = true;
			break;
		case 3:
			EnemyForm("WAVE_ENEMY_DATA/wave3.csv", ENEMY_MAX, enemy, wave_num);
			wave_set = true;
			break;
		case 4:
			wave_set = true;
			break;
		}
		//�G�����ʖ���
		//Score+=100;
	}
#pragma endregion

#pragma region �����蔻��

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		for (int j = 0; j < enemy[i]->GetBulletMax(); j++)
		{
			//���@�ƓG�̒e�̓����蔻��
			player->HP(*enemy[i]->GetBulletTransform(j), *enemy[i]->GetEnmyBullet(j), vibflag, screenshakeflag, shakeflag, damageflag, shaketime, damagetime);

			if (enemy[i]->GetEnemyFlag(wave_num) == true)
			{
				//���@�ƃ{�}�[�̓����蔻��
				enemy[i]->PlaterToEnemyHitBox(*player, i);
			}

		}
	}

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (enemy[i]->GetEnemyFlag(30) == true)
		{
			for (int k = 0; k < ENEMY_MAX; k++)
			{
				if (i != k)
				{
					if (enemy[k]->GetEnemyType() != 6)
					{
						//�G�ƃ{�}�[�̓����蔻��
						enemy[i]->ExplosionBommer(enemy[k]);

						for (int j = 0; j < enemy[k]->GetBulletMax(); j++)
						{
							//�G�ƓG�̒e�̓����蔻��
							enemy[i]->HP(*enemy[k]->GetBulletTransform(j), *enemy[k]->GetEnmyBullet(j), item);
						}
					}
				}
			}
		}
	}
#pragma endregion

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		//�G�̓���
		enemy[i]->Move(*player, reflection_flag, *score, item, 30, movie_flag, keys, i, vibflag, screenshakeflag, shakeflag, damageflag, shaketime, damagetime);
	}

	break_flag = false;

#pragma region wave�N���A����

	if (zako_wannihilation_falg == true && bommer_wannihilation_falg == true && boomerang_wannihilation_falg == true)
	{
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			//�G���S���|���ꂽ��e�̔��˂��Ȃ���
			if (enemy[i]->GetEnemyFlag(wave_num) == false && enemy[i]->GetAppearTime() == -1)
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

			if (enemy[i]->GetEnemyFlag(wave_num) == true ||
				enemy[i]->GetAppearTime() != -1 ||
				enemy[i]->GetExplosionFlag() == true)
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

		if (break_flag == false && reflection_flag == false)
		{
			wave_set = false;
			reflection_flag = true;
			wave_up_flag = true;

			for (int i = 0; i < ENEMY_MAX; i++)
			{
				delete enemy[i];
			}
		}
		else
		{
			break_flag = false;
		}
	}
#pragma endregion

	tmp_num = 0;

#pragma region �G���G�S�ŏ����E���{�X1�G���o��

	if (zako_wannihilation_falg == false)
	{
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			//�S�ł�����
			if (enemy[i]->GetEnemyType() == 1 && enemy[i]->GetAppearTime() == -1 && enemy[i]->GetEnemyFlag(30) == false)
			{
				tmp_num++;
			}
		}
		if (tmp_num == zako_num)
		{
			zako_wannihilation_falg = true;
		}
		else
		{
			tmp_num = 0;
		}

		//������
		if (zako_wannihilation_falg == true)
		{
			FILE* fp;
			fopen_s(&fp, "WAVE_ENEMY_DATA/initialization.csv", "r");

			for (int i = 0; i < ENEMY_MAX; i++)
			{
				if (enemy[i]->GetEnemyType() == 1)
				{
					if (fp != NULL)
					{
						enemy[i]->form(fp, 30);
					}
				}
			}

			if (fp != NULL)
			{
				fclose(fp);
			}
		}

		//���{�X1�G���f�[�^�ǂݍ���
		if (zako_wannihilation_falg == true)
		{
			tmp_num = 0;

			FILE* fp;
			fopen_s(&fp, "WAVE_ENEMY_DATA/boss1_boss1.csv", "r");

			if (fp != NULL)
			{
				for (int i = 0; i < ENEMY_MAX; i++)
				{
					if (enemy[i]->GetEnemyType() == 0)
					{
						enemy[i]->form(fp, 30);
						tmp_num++;
						if (tmp_num == boss1_num)
						{
							fclose(fp);
							break;
						}
					}
				}
			}
		}

		tmp_num = 0;
	}

#pragma endregion

#pragma region �u�[�������S�ŏ����E���{�X�G��2�o��
	if (boomerang_wannihilation_falg == false)
	{
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			//�S�ł�����
			if (enemy[i]->GetEnemyType() == 3 && enemy[i]->GetAppearTime() == -1 && enemy[i]->GetEnemyFlag(30) == false)
			{
				tmp_num++;
			}
		}
		if (tmp_num == boomerang_num)
		{
			boomerang_wannihilation_falg = true;
		}
		else
		{
			tmp_num = 0;
		}

		//������
		if (boomerang_wannihilation_falg == true)
		{
			FILE* fp;
			fopen_s(&fp, "WAVE_ENEMY_DATA/initialization.csv", "r");

			for (int i = 0; i < ENEMY_MAX; i++)
			{
				if (enemy[i]->GetEnemyType() == 3)
				{
					if (fp != NULL)
					{
						enemy[i]->form(fp, 30);
					}
				}
			}

			if (fp != NULL)
			{
				fclose(fp);
			}
		}

		//���{�X1�G���f�[�^�ǂݍ���
		if (boomerang_wannihilation_falg == true)
		{
			tmp_num = 0;

			FILE* fp;
			fopen_s(&fp, "WAVE_ENEMY_DATA/boss1_boss2.csv", "r");

			if (fp != NULL)
			{
				for (int i = 0; i < ENEMY_MAX; i++)
				{
					if (enemy[i]->GetEnemyType() == 0)
					{
						enemy[i]->form(fp, 30);
						tmp_num++;
						if (tmp_num == boss2_num)
						{
							fclose(fp);
							break;
						}
					}
				}
			}
		}

		tmp_num = 0;
	}

#pragma endregion

#pragma region �{�}�[�S�ŏ����E�S���ʏo��
	if (bommer_wannihilation_falg == false)
	{
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			//�S�ł�����
			if (enemy[i]->GetEnemyType() == 2 && enemy[i]->GetAppearTime() == -1 && enemy[i]->GetEnemyFlag(30) == false)
			{
				tmp_num++;
			}
		}
		if (tmp_num == bommer_num)
		{
			bommer_wannihilation_falg = true;
		}
		else
		{
			tmp_num = 0;
		}

		//������
		if (bommer_wannihilation_falg == true)
		{
			FILE* fp;
			fopen_s(&fp, "WAVE_ENEMY_DATA/initialization.csv", "r");

			for (int i = 0; i < ENEMY_MAX; i++)
			{
				if (enemy[i]->GetEnemyType() == 2)
				{
					if (fp != NULL)
					{
						enemy[i]->form(fp, 30);
					}
				}
			}

			if (fp != NULL)
			{
				fclose(fp);
			}
		}

		//���{�X1�G���f�[�^�ǂݍ���
		if (bommer_wannihilation_falg == true)
		{
			tmp_num = 0;

			FILE* fp;
			fopen_s(&fp, "WAVE_ENEMY_DATA/boss1_omnidirectional.csv", "r");

			if (fp != NULL)
			{
				for (int i = 0; i < ENEMY_MAX; i++)
				{
					if (enemy[i]->GetEnemyType() == 0)
					{
						enemy[i]->form(fp, 30);
						tmp_num++;
						if (tmp_num == omnidirectional_num)
						{
							fclose(fp);
							break;
						}
					}
				}
			}
		}

		tmp_num = 0;
	}

#pragma endregion

}

void Boss::Draw(Enemy** enemy)
{
	if (wave_set == true)
	{
		//�v���C���
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			if (enemy[i] != nullptr)
			{
				enemy[i]->Draw(i, 30);
			}

		}
	}
}
