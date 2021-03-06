#include"boss.h"
#include"player.h"
#include"enemy.h"
#include"item.h"
#include"score.h"
#include<math.h>
#include"DxLib.h"

int GetBossEnemyMax(int wave_num)
{
	switch (wave_num)
	{
	case 0:
		return 0;
	case 1:
		return 22;
	case 2:
		return 26;
	case 3:
		return 2;
	}

	return -1;
}

Boss::Boss()
{
	break_flag = false;
	ENEMY_MAX = 0;
	wave_num = 0;
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

	transform.xr = 80;
	transform.yr = 80;
	ang = 4.7249999999999952f;
	transform.x = 480;
	transform.y = 0;
	flame = 0;
	x = 0;
	y = 0;

	easing_flag = false;
	easing_frame = 0;
	easing_start_x = 480;
	easing_start_y = 0;
	easing_end_x = 480;
	easing_end_y = 150;
	easing2_end_y = 482;
	easing_end_frame = 100;

	escape_frame = 0;
	escape_start_x = 480;
	escape_start_y = 150;
	escape_end_x = 480;
	escape_end_y = -150;
	escape_end_frame = 100;
	txt_flag = 0;
	LoadDivGraph("resouce/lastboss.png", 2, 2, 1, 160, 160, img);
	LoadDivGraph("resouce/lastboss_mugon.png", 2, 2, 1, 160, 160, mugon_img);
	LoadDivGraph("resouce/lastboss_talk.png", 2, 2, 1, 160, 160, talk_img);
	ron_se = LoadSoundMem("music/ron.mp3");
	img_anime = 0;
	img_anime_timer = 0;
	txt_cool_time = 0;
	move_flag = false;
	boss_txt_flag = 0;
}

Boss::~Boss()
{
}

void Boss::Move(Enemy** enemy, Player* player, Item* item, Score* score,
	int& recoveryflag, int& recoverytime, int& vibflag, int& screenshakeflag,
	int& shakeflag, int& damageflag, int& shaketime, int& damagetime,
	bool& reflection_flag, bool& movie_flag, char* keys, int& sceneflag, bool& txt_shake_flag, int& damageAlpha)
{

#pragma region 敵データ読み込み
	if (wave_set == false)
	{
		if (wave_up_flag == true)
		{
			wave_num++;
			wave_up_flag = false;
		}

		//敵の数
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
		case 0:
			easing_flag = true;
			wave_set = true;
			player->SetMoveFlag(0);
			player->SetEasingFlag(1);
			break;
		case 1:

			EnemyForm("WAVE_ENEMY_DATA/boss1.csv", ENEMY_MAX, enemy, wave_num);
			zako_num = 10;
			boss1_num = 2;
			boss2_num = 2;
			boomerang_num = 6;
			omnidirectional_num = 1;
			bommer_num = 4;
			player->SetMoveFlag(1);
			movie_flag = false;
			wave_set = true;
			break;
		case 2:
			EnemyForm("WAVE_ENEMY_DATA/boss2.csv", ENEMY_MAX, enemy, wave_num);
			wave_set = true;
			break;
		case 3:
			EnemyForm("WAVE_ENEMY_DATA/boss3.csv", ENEMY_MAX, enemy, wave_num);
			easing_frame = 0;
			player->SetMoveFlag(0);
			easing_flag = true;
			easing_start_x = transform.x;
			easing_start_y = transform.y;
			movie_flag = true;
			wave_set = true;
			break;
		case 4:
			wave_set = true;
			break;
		}
		//敵が死ぬ毎に
		//Score+=100;
	}
#pragma endregion

#pragma region 当たり判定

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		for (int j = 0; j < enemy[i]->GetBulletMax(); j++)
		{
			//時機と敵の弾の当たり判定
			player->HP(*enemy[i]->GetBulletTransform(j), *enemy[i]->GetEnmyBullet(j), vibflag, screenshakeflag, shakeflag, damageflag, shaketime, damagetime, damageAlpha);

			if (enemy[i]->GetEnemyFlag(wave_num) == true)
			{
				//時機とボマーの当たり判定
				enemy[i]->PlaterToEnemyHitBox(*player, i, vibflag, screenshakeflag, shakeflag, damageflag, shaketime, damagetime, damageAlpha);
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
						//敵とボマーの当たり判定
						enemy[i]->ExplosionBommer(enemy[k]);

						for (int j = 0; j < enemy[k]->GetBulletMax(); j++)
						{
							//敵と敵の弾の当たり判定
							enemy[i]->HP(*enemy[k]->GetBulletTransform(j), *enemy[k]->GetEnmyBullet(j), item, score);
						}
					}
				}
			}
		}
	}
#pragma endregion

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		//敵の動き
		enemy[i]->Move(*player, reflection_flag, *score, item, 30, movie_flag, keys, i, vibflag, screenshakeflag, shakeflag, damageflag, shaketime, damagetime, txt_shake_flag,damageAlpha);
	}

	break_flag = false;

#pragma region waveクリア判定
	if (wave_num != 3)
	{
		if (zako_wannihilation_falg == true && bommer_wannihilation_falg == true && boomerang_wannihilation_falg == true)
		{
			for (int i = 0; i < ENEMY_MAX; i++)
			{
				//敵が全員倒されたら弾の反射をなくす
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
	}
#pragma endregion

	tmp_num = 0;
	if (wave_num == 0)
	{
		if (easing_flag == true)
		{
			easing_frame++;
			transform.y = easing_start_y + (easing2_end_y - easing_start_y) * easeInSine((double)easing_frame / (double)easing_end_frame);

			if (easing_frame == easing_end_frame)
			{
				easing_flag = false;
				boss_txt_flag = 1;
				txt_flag = 3;
				PlaySoundMem(ron_se, DX_PLAYTYPE_BACK);
			}
		}

		if (boss_txt_flag == 1)
		{
			if (keys[KEY_INPUT_SPACE] == 1 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0)
			{
				boss_txt_flag++;
				txt_flag = 0;
				txt_cool_time = 0;
				
			}
		}

		if (boss_txt_flag == 2)
		{
			wave_set = false;
			wave_num = 1;
			move_flag = true;
		}
	}

	if (wave_num == 1 && wave_set == true)
	{
#pragma region 雑魚敵全滅処理・中ボス1雑魚出現

		if (zako_wannihilation_falg == false)
		{
			for (int i = 0; i < ENEMY_MAX; i++)
			{
				//全滅したか
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

			//初期化
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

			//中ボス1雑魚データ読み込み
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

#pragma region ブーメラン全滅処理・中ボス雑魚2出現
		if (boomerang_wannihilation_falg == false)
		{
			for (int i = 0; i < ENEMY_MAX; i++)
			{
				//全滅したか
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

			//初期化
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

			//中ボス1雑魚データ読み込み
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

#pragma region ボマー全滅処理・全方位出現
		if (bommer_wannihilation_falg == false)
		{
			for (int i = 0; i < ENEMY_MAX; i++)
			{
				//全滅したか
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

			//初期化
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

			//中ボス1雑魚データ読み込み
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
	if (wave_num != 3)
	{
		if (move_flag == true)
		{
			if (flame == 0) {
				x = 482;
				y = 482;
			}

			flame++;
			ang += 0.015;

			transform.x = x + 300 * (cos(ang) * 2);
			transform.y = y + 150 * (sin(2 * ang) * 2);
		}
	}
	else
	{
		//最初の移動
		if (easing_flag == true)
		{
			easing_frame++;
			transform.x = easing_start_x + (easing_end_x - easing_start_x) * easeInSine((double)easing_frame / (double)easing_end_frame);
			transform.y = easing_start_y + (easing_end_y - easing_start_y) * easeInSine((double)easing_frame / (double)easing_end_frame);

			if (easing_frame == easing_end_frame)
			{
				easing_flag = false;
			}
		}
		if (enemy[0]->GetTxtFlag() == 4 && enemy[1]->GetTxtFlag() == 4)
		{
			escape_frame++;
			transform.x = escape_start_x + (escape_end_x - escape_start_x) * easeInSine((double)escape_frame / (double)escape_end_frame);
			transform.y = escape_start_y + (escape_end_y - escape_start_y) * easeInSine((double)escape_frame / (double)escape_end_frame);

			if (escape_frame == easing_end_frame)
			{
				sceneflag = 1;
			}
		}
	}

	img_anime_timer++;

	if (img_anime_timer == 2 * 5)
	{
		img_anime_timer = 0;
	}

	img_anime = img_anime_timer / 5;

	if (txt_flag == 3 && txt_cool_time < 70)
	{
		txt_cool_time++;
	}

	if (wave_num == 3)
	{
		txt_flag = enemy[0]->GetTxtFlag();
	}
}

void Boss::Draw(Enemy** enemy)
{
	if (txt_flag == 0)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 130);
		DrawGraph((int)transform.x - transform.xr, (int)transform.y - transform.yr, img[img_anime], true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else if (txt_flag == 1 || txt_flag == 2 || txt_flag == 4)
	{
		DrawGraph((int)transform.x - transform.xr, (int)transform.y - transform.yr, mugon_img[img_anime], true);
	}
	else if (txt_flag == 3)
	{
		if (txt_cool_time < 70)
		{
			DrawGraph((int)transform.x - transform.xr, (int)transform.y - transform.yr, talk_img[img_anime], true);
		}
		else
		{
			DrawGraph((int)transform.x - transform.xr, (int)transform.y - transform.yr, mugon_img[img_anime], true);
		}
	}
	if (wave_set == true)
	{
		//プレイ画面
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			if (enemy[i] != nullptr)
			{
				enemy[i]->Draw(i, 30);
			}

		}
	}
}

void Boss::PictureBookDraw(int x, int y)
{
	img_anime_timer++;

	if (img_anime_timer == 2 * 5)
	{
		img_anime_timer = 0;
	}

	img_anime = img_anime_timer / 5;

	DrawRotaGraph(x+229, 250, 2.0, 0.0, img[img_anime], true, true);
	DrawRotaGraph(x + 688, 250, 2.0, 0.0, talk_img[img_anime], true, true);
	DrawRotaGraph(x + 1147, 250, 2.0, 0.0, mugon_img[img_anime], true, true);

}

int Boss::GetBossTxtFlag()
{
	return boss_txt_flag;
}

int Boss::GetENEMY_MAX()
{
	return ENEMY_MAX;
}

