#include"mine.h"
#include"DxLib.h"
#include"Transform.h"
#include"enemy.h"
#include"player.h"

#pragma region コントラスタ・デストラクタ
//コントラスタ
Mine::Mine()
{
	rand = 0;
	damage_flag = false;
	explosion_r = 0;
	mine_flag = false;
	def_explosion_time = 0;
	def_bombs_time = 0;

	for (int i = 0; i < 10; i++)
	{
		transform[i].x = 0;
		transform[i].xr = 0;
		transform[i].y = 0;
		transform[i].yr = 0;
		explosion_time[i] = 0;
		explosion_flag[i] = 0;
		bombs_time[i] = 0;
		exising_flag[i] = 0;
		mine_anime_timer[i] = 0;
		mine_anime[i] = 0;
		explosion_img_anime[i] = 0;
	explosion_img_anime_timer[i] = 0;
	}
	mine_r = 8;
	LoadDivGraph("resouce/bom.png", 10, 10, 1, 32, 32, mine_img);

	LoadDivGraph("resouce/explosion.png", 8, 8, 1, 48, 48, explosion_img);
	explosion_se = LoadSoundMem("music/knockdouwn.mp3");

}

//デストラクタ
Mine::~Mine()
{
}
#pragma endregion

#pragma region 生成

//フラグがtrueになったらランダムを取り(0～rand_num)
//ランダムがrand_divより下だったら
//空いているラベルを探して座標とフラグを代入する

void Mine::form(Transform transForm, int& frame)
{
	if (mine_flag == true)
	{
		if (rand == frame)
		{
			int i = FlagSerch(exising_flag, 10);
			transform[i].x = transForm.x;
			transform[i].y = transForm.y;
			exising_flag[i] = true;
			explosion_time[i] = def_explosion_time;
			bombs_time[i] = def_bombs_time;
			mine_flag = false;
		}
	}
}
#pragma endregion

#pragma region 当たり判定

//設置状態で当たったら爆発させて
//爆発している時に当たったら体力を減らす
//フラグを使い1ダメージしか与えないようにしている

void Mine::HitBox(Transform transform, int& hp, bool& damage_effect)
{
	for (int i = 0; i < 10; i++)
	{
		if (exising_flag[i] == true && explosion_flag[i] == false && explosion_time[i] < def_explosion_time - 30)
		{
			if (this->transform[i].x - this->transform[i].xr < transform.x + transform.xr &&
				this->transform[i].x + this->transform[i].xr > transform.x - transform.xr)
			{
				if (this->transform[i].y - this->transform[i].yr < transform.y + transform.yr &&
					this->transform[i].y + this->transform[i].yr > transform.y - transform.yr)
				{
					explosion_flag[i] = true;
					PlaySoundMem(explosion_se, DX_PLAYTYPE_BACK);

				}

			}

		}

		if (explosion_flag[i] == true)
		{
			if (this->transform[i].x - explosion_r < transform.x + transform.xr &&
				this->transform[i].x + explosion_r > transform.x - transform.xr)
			{
				if (this->transform[i].y - explosion_r < transform.y + transform.yr &&
					this->transform[i].y + explosion_r > transform.y - transform.yr)
				{
					if (damage_flag == false)
					{
						hp--;
						damage_effect = true;
					}
					damage_flag = true;
				}
				else
				{
					damage_flag = false;
				}
			}
			else
			{
				damage_flag = false;

			}
		}
	}
}

void Mine::HitBox(Transform transform, int& hp, bool damage_flag, bool& damage_effect)
{
	for (int i = 0; i < 10; i++)
	{
		if (exising_flag[i] == true && explosion_flag[i] == false && explosion_time[i] < def_explosion_time - 30)
		{
			if (this->transform[i].x - this->transform[i].xr < transform.x + transform.xr &&
				this->transform[i].x + this->transform[i].xr > transform.x - transform.xr)
			{
				if (this->transform[i].y - this->transform[i].yr < transform.y + transform.yr &&
					this->transform[i].y + this->transform[i].yr > transform.y - transform.yr)
				{
					explosion_flag[i] = true;
					PlaySoundMem(explosion_se, DX_PLAYTYPE_BACK);
				}

			}

		}

		if (explosion_flag[i] == true)
		{
			if (this->transform[i].x - explosion_r < transform.x + transform.xr &&
				this->transform[i].x + explosion_r > transform.x - transform.xr)
			{
				if (this->transform[i].y - explosion_r < transform.y + transform.yr &&
					this->transform[i].y + explosion_r > transform.y - transform.yr)
				{
					if (damage_flag == false)
					{
						hp--;
						damage_effect = true;
					}
					damage_flag = true;
				}
				else
				{
					damage_flag = false;
				}
			}
			else
			{
				damage_flag = false;

			}
		}
	}
}

void Mine::PlayerHitBox(Player& player, int vibflag, int screenshakeflag, int& shakeflag, int& damageflag, int& shaketime, int& damagetime)
{
	for (int i = 0; i < 10; i++)
	{
		if (exising_flag[i] == true && explosion_flag[i] == false && explosion_time[i] < def_explosion_time - 30)
		{
			if (transform[i].x - transform[i].xr < (double)player.GetX() + (double)player.GetR() &&
				transform[i].x + transform[i].xr >(double)player.GetX() - (double)player.GetR())
			{
				if (transform[i].y - transform[i].yr < (double)player.GetY() + (double)player.GetR() &&
					transform[i].y + transform[i].yr >(double)player.GetY() - (double)player.GetR())
				{
					explosion_flag[i] = true;
					PlaySoundMem(explosion_se, DX_PLAYTYPE_BACK);

				}
			}
		}

		if (explosion_flag[i] == true)
		{
			if (transform[i].x - explosion_r < (double)player.GetX() + (double)player.GetR() &&
				transform[i].x + explosion_r >(double)player.GetX() - (double)player.GetR())
			{
				if (transform[i].y - explosion_r < (double)player.GetY() + (double)player.GetR() &&
					transform[i].y + explosion_r >(double)player.GetY() - (double)player.GetR())
				{
					if (player.GetDamageFlag(i) == 0)
					{
						if (vibflag == 1) {
							StartJoypadVibration(DX_INPUT_PAD1, 500, 500, -1);//パッド振動
						}
						if (screenshakeflag == 1) {
							shaketime = 0;
							shakeflag = 1;
						}
						damagetime = 0;
						damageflag = 1;

						player.HpSub(1);
					}
					player.SetDamageFlag(i, 1);
				}
				else
				{
					player.SetDamageFlag(i, 0);
				}
			}
			else
			{
				player.SetDamageFlag(i, 0);
			}
		}
	}
}

#pragma endregion

#pragma region 動き

//爆発時間が0より上なら減らし0になったら爆発フラグをtureにする
//爆発フラグがtureだったら爆発時間を減らして
//爆発時間が0になったら各種変数を初期化

void Mine::Move()
{
	for (int i = 0; i < 10; i++)
	{
		if (exising_flag[i] == true && explosion_time[i] > 0)
		{
			explosion_time[i]--;

			if (explosion_time[i] <= 0)
			{
				explosion_flag[i] = true;
			}

			mine_anime_timer[i]++;

			if (mine_anime_timer[i] == 10 * 4)
			{
				mine_anime_timer[i] = 0;
			}

			mine_anime[i] = mine_anime_timer[i] / 4;
		}

		if (explosion_flag[i] == true)
		{
			bombs_time[i]--;

			if (bombs_time[i] <= 0)
			{
				explosion_flag[i] = false;
				exising_flag[i] = false;
				bombs_time[i] = def_bombs_time;
				explosion_time[i] = def_explosion_time;
			}

			explosion_img_anime_timer[i]++;

			if (explosion_img_anime_timer[i] == 8 * 1)
			{
				explosion_img_anime_timer[i] = 0;
			}

			explosion_img_anime[i] = explosion_img_anime_timer[i] / 1;

			
		}


	}



}
#pragma endregion

#pragma region 描画

//存在フラグと爆発フラグが立っていたら
//存在フラグが立っていたら
//デバック

void Mine::Draw()
{
	for (int i = 0; i < 10; i++)
	{
		if (exising_flag[i] == true && explosion_flag[i] == true)
		{
			DrawGraph((int)transform[i].x - 16, (int)transform[i].y - 16, explosion_img[explosion_img_anime[i]], true);

		}
		else if (exising_flag[i] == true)
		{
			DrawGraph((int)transform[i].x - mine_r, (int)transform[i].y - mine_r, mine_img[mine_anime[i]], true);
		}
	}


}
#pragma endregion

#pragma region 初期化

//構造体から受け取って代入

void Mine::initialize(MimeInitialize& mimeinitialize)
{
	def_explosion_time = mimeinitialize.def_explosion_time;
	def_bombs_time = mimeinitialize.def_bombs_time;
	explosion_r = mimeinitialize.explosion_r;

	for (int i = 0; i < 10; i++)
	{
		transform[i].xr = mimeinitialize.transform_xr;
		transform[i].yr = mimeinitialize.transform_yr;
	}
}
#pragma endregion

#pragma region セッター

void Mine::SetMineFlag(bool flag)
{
	mine_flag = flag;
}

void Mine::SetRand(int end_frame)
{
	rand = GetRand(end_frame);
}
void Mine::SetExplosionTime(int num)
{
	for (int i = 0; i < 10; i++)
	{
		if (exising_flag[i] == true)
		{
			explosion_time[i] = num;
		}
	}

}
void Mine::PictureBookDraw(int x, int y)
{

	mine_anime_timer[0]++;

	if (mine_anime_timer[0] == 10 * 4)
	{
		mine_anime_timer[0] = 0;
	}

	mine_anime[0] = mine_anime_timer[0] / 4;

	DrawRotaGraph(x, y, 2.5, 0.0, mine_img[mine_anime[0]], true, true);
}
#pragma endregion