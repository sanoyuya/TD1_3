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
		transform[i].xr = 32;
		transform[i].y = 32;
		transform[i].yr = 0;
		explosion_time[i] = 0;
		explosion_flag[i] = 0;
		bombs_time[i] = 0;
		exising_flag[i] = 0;
	}

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

void Mine::form(Transform transForm,int&frame)
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

void Mine::HitBox(Transform transform, int& hp)
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

void Mine::HitBox(Transform transform, int& hp, bool damage_flag)
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

void Mine::PlayerHitBox(Player& player)
{
	for (int i = 0; i < 10; i++)
	{
		if (exising_flag[i] == true && explosion_flag[i] == false && explosion_time[i] < def_explosion_time - 30)
		{
			if (transform[i].x - transform[i].xr < (double)player.GetX() + (double)player.GetR() &&
				transform[i].x + transform[i].xr >(double)player.GetX() - (double)player.GetR())
			{
				if (transform[i].y - transform[i].yr < (double)player.GetY() + (double)player.GetR() &&
					transform[i].y + transform[i].yr > (double)player.GetY() - (double)player.GetR())
				{
					explosion_flag[i] = true;
				}

			}

		}

		if (explosion_flag[i] == true)
		{
			if (transform[i].x - explosion_r < (double)player.GetX() + (double)player.GetR() &&
				transform[i].x + explosion_r > (double)player.GetX() - (double)player.GetR())
			{
				if (transform[i].y - explosion_r < (double)player.GetY() + (double)player.GetR() &&
					transform[i].y + explosion_r > (double)player.GetY() - (double)player.GetR())
				{
					if (player.GetDamageFlag() == 0)
					{
						player.HpSub(1);
					}
					player.SetDamageFlag(1);
				}
				else
				{
					player.SetDamageFlag(0);
				}
			}
			else
			{
				player.SetDamageFlag(0);

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

			if (explosion_time[i] == 0)
			{
				explosion_flag[i] = true;
			}
		}

		if (explosion_flag[i] == true)
		{
			bombs_time[i]--;

			if (bombs_time[i] == 0)
			{
				explosion_flag[i] = false;
				exising_flag[i] = false;
				bombs_time[i] = def_bombs_time;
				explosion_time[i] = def_explosion_time;
			}
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
			DrawBox((int)transform[i].x - explosion_r, (int)transform[i].y - explosion_r,
				(int)transform[i].x + explosion_r, (int)transform[i].y + explosion_r, GetColor(255, 0, 0), true);
		}
		else if (exising_flag[i] == true)
		{
			DrawBox((int)transform[i].x - transform[i].xr, (int)transform[i].y - transform[i].yr,
				(int)transform[i].x + transform[i].xr, (int)transform[i].y + transform[i].yr, GetColor(255, 255, 255), true);
		}
	}

	DrawFormatString(0, 200, GetColor(255, 255, 255), "mine explosion_time[0]:%d", explosion_time[0]);
	DrawFormatString(0, 220, GetColor(255, 255, 255), "mine bombs_time[0]:%d", bombs_time[0]);
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
#pragma endregion