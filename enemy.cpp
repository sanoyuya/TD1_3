#include"DxLib.h"
#include"enemy.h"
#include"bullet.h"
#include"map.h"
#include"Transform.h"
#include<math.h>
#include"item.h"


// ウィンドウ横幅
const int WIN_WIDTH = 1856;

// ウィンドウ縦幅
const int WIN_HEIGHT = 960;

#define PI 3.1415926535f



double easeInSine(double x)
{
	return 1 - cos((x * PI) / 2);
}

int Box_Circle(int LeftTopBoxX, int LeftTopBoxY, int RightBottomX, int RightBottomY, int circleX, int circleY, int r)
{
	if ((circleX > LeftTopBoxX - r)
		&& (circleX < RightBottomX + r)
		&& (circleY > LeftTopBoxY - r)
		&& (circleY < RightBottomY + r)) {
		return 1;
	}
	else {
		return 0;
	}
}

void circularMotionL(double& posX, double& posY, float cPosX, float cPosY, float length, float& angle) {

	float radius = angle;

	double addX = cos(radius) * length;
	double addY = sin(radius) * length;

	posX = cPosX + addX;
	posY = cPosY + addY;

	angle -= 0.02f;//引くと反時計回り　足すと時計回り　数値を大きくすると早く回る

}

//空き番号を返す
int FlagSerch(EnemyBullet** bullet, int max)
{
	for (int i = 0; i < max; i++)
	{
		if (*bullet[i]->GetBulletFlag() == false)
		{
			return i;
		}
	}
	return -1;
}

int FlagSerch(bool flag[], int max)
{
	for (int i = 0; i < max; i++)
	{
		if (flag[i] == false)
		{
			return i;
		}
	}
	return -1;
}

#pragma region コントラスタ・デストラクタ
Enemy::Enemy()
{
	use_flag = false;//使うかフラグ
	enemy_type = 0;//敵のタイプ

	//座標
	transform.x = 0;
	transform.y = 0;
	transform.xr = 0;
	transform.yr = 0;
	hp = 0;//体力
	x_speed = 0;//弾のX座標のスピード
	y_speed = 0;//弾のY座標のスピード
	exising_flag = false;//存在フラグ
	action_flag = false;//動くかどうかフラグ
	shot_action_flag = false;
	for (int i = 0; i < 48; i++)
	{
		damage_flag[i] = false;
	}

	bullet_max = 3;
	shot_time = 0;
	//最初の移動のための変数
	frame = 0;
	end_frame = 0;
	start_x = 0;
	start_y = 0;
	end_x = 0;
	end_y = 0;
	fast_move_flag = false;
	appear_time = 0;
	//移動のための変数
	move_flag = false;
	move_time = 0;
	move_num = 0;
	move_frame = 0;
	move_end_frame = 00;
	for (int i = 0; i < 4; i++)
	{
		move_start_x[i] = .0;
		move_start_y[i] = 0;
		move_end_x[i] = 0;
		move_end_y[i] = 0;
	}

	//初期値
	def_move_time = move_time;
	def_shot_time = shot_time;

	//ボマー
	angle = 0.0f;
	vertex.top_left_x = 0;
	vertex.top_left_y = 0;
	vertex.down_left_x = 0;
	vertex.down_left_y = 0;
	vertex.top_right_x = 0;
	vertex.top_right_y = 0;
	vertex.down_right_x = 0;
	vertex.down_right_y = 0;
	explosion_time = 0;
	enemy_to_bommer = false;
	def_explosion_time = 0;
	explosion_bommer_flag = false;

	//全方位
	all_bullet_max = 1;
	bullet[0] = new EnemyBullet;

	mine = new Mine;
	color = GetColor(255, 255, 255);
	sub_boss_buiiet_max = 12;

	mime_initialize.transform_yr = 0;
	mime_initialize.transform_xr = 0;
	mime_initialize.def_bombs_time = 0;
	mime_initialize.def_explosion_time = 0;
	mime_initialize.explosion_r = 0;
	move_rand = 0;
	easing_num = 0;

	//画像
	LoadDivGraph("resouce/zako.png", 12, 12, 1, 96, 96, img);
	img_r = 48;
	anime = 0;
	anime_timer = 0;

	LoadDivGraph("resouce/boss1_64.png", 14, 14, 1, 64, 64, sub_boss1_img);
	sub_boss1_anime = 0;
	sub_boss1_anime_timer = 0;

	LoadDivGraph("resouce/zako_boomerang.png", 10, 10, 1, 64, 64, boomerang_img);
	boomerang_anime = 0;
	boomerang_anime_timer = 0;

	LoadDivGraph("resouce/Bomer.png", 10, 10, 1, 96, 96, bommer_img);
	bommer_anime_timer = 0;
	bommer_anime = 0;
}

Enemy::~Enemy()
{
	delete mine;
	for (int i = 0; i < all_bullet_max; i++)
	{
		delete bullet[i];
	}

}
#pragma endregion

#pragma region ベクトルの当たり判定

bool Enemy::BommerHitBox(Player& player)
{
	VECTOR bommr[4];

	VECTOR vec_player[4][4];

	float cross[4][4];

	float player_left = (float)player.GetX() - player.GetR();
	float player_right = (float)player.GetX() + player.GetR();
	float player_top = (float)player.GetY() - player.GetR();
	float player_down = (float)player.GetY() + player.GetR();

	float left_top_x = ((-transform.xr) * cosf(angle) + ((-transform.yr) * -sinf(angle)) + (float)transform.x);
	float left_top_y = ((-transform.xr) * sinf(angle) + ((-transform.yr) * cosf(angle)) + (float)transform.y);
	float right_top_x = ((transform.xr) * cosf(angle) + ((-transform.yr) * -sinf(angle)) + (float)transform.x);
	float right_top_y = ((transform.xr) * sinf(angle) + ((-transform.yr) * cosf(angle)) + (float)transform.y);
	float left_down_x = ((-transform.xr) * cosf(angle) + ((transform.yr) * -sinf(angle)) + (float)transform.x);
	float left_down_y = ((-transform.xr) * sinf(angle) + ((transform.yr) * cosf(angle)) + (float)transform.y);
	float right_down_x = ((transform.xr) * cosf(angle) + ((transform.yr) * -sinf(angle)) + (float)transform.x);
	float right_down_y = ((transform.xr) * sinf(angle) + ((transform.yr) * cosf(angle)) + (float)transform.y);


	bommr[0] = VGet(left_top_x - left_down_x, left_top_y - left_down_y, 0.0f);//|
	bommr[1] = VGet(left_down_x - right_down_x, left_down_y - right_down_y, 0.0f);//_
	bommr[2] = VGet(right_down_x - right_top_x, right_down_y - right_top_y, 0.0f);// |
	bommr[3] = VGet(right_top_x - left_top_x, right_top_y - left_top_y, 0.0f);//￣

	bommr[0] = VNorm(bommr[0]);
	bommr[1] = VNorm(bommr[1]);
	bommr[2] = VNorm(bommr[2]);
	bommr[3] = VNorm(bommr[3]);

	vec_player[0][0] = VGet(player_left - left_top_x, player_top - left_top_y, 0.0f);
	vec_player[0][1] = VGet(player_left - left_down_x, player_top - left_down_y, 0.0f);
	vec_player[0][2] = VGet(player_left - right_down_x, player_top - right_down_y, 0.0f);
	vec_player[0][3] = VGet(player_left - left_top_x, player_top - left_top_y, 0.0f);

	vec_player[1][0] = VGet(player_left - left_top_x, player_down - left_top_y, 0.0f);
	vec_player[1][1] = VGet(player_left - left_down_x, player_down - left_down_y, 0.0f);
	vec_player[1][2] = VGet(player_left - right_down_x, player_down - right_down_y, 0.0f);
	vec_player[1][3] = VGet(player_left - left_top_x, player_down - left_top_y, 0.0f);

	vec_player[2][0] = VGet(player_right - left_top_x, player_top - left_top_y, 0.0f);
	vec_player[2][1] = VGet(player_right - left_down_x, player_top - left_down_y, 0.0f);
	vec_player[2][2] = VGet(player_right - right_down_x, player_top - right_down_y, 0.0f);
	vec_player[2][3] = VGet(player_right - left_top_x, player_top - left_top_y, 0.0f);

	vec_player[3][0] = VGet(player_right - left_top_x, player_down - left_top_y, 0.0f);
	vec_player[3][1] = VGet(player_right - left_down_x, player_down - left_down_y, 0.0f);
	vec_player[3][2] = VGet(player_right - right_down_x, player_down - right_down_y, 0.0f);
	vec_player[3][3] = VGet(player_right - left_top_x, player_down - left_top_y, 0.0f);

	vec_player[0][0] = VNorm(vec_player[0][0]);
	vec_player[0][1] = VNorm(vec_player[0][1]);
	vec_player[0][2] = VNorm(vec_player[0][2]);
	vec_player[0][3] = VNorm(vec_player[0][3]);

	vec_player[1][0] = VNorm(vec_player[1][0]);
	vec_player[1][1] = VNorm(vec_player[1][1]);
	vec_player[1][2] = VNorm(vec_player[1][2]);
	vec_player[1][3] = VNorm(vec_player[1][3]);

	vec_player[2][0] = VNorm(vec_player[2][0]);
	vec_player[2][1] = VNorm(vec_player[2][1]);
	vec_player[2][2] = VNorm(vec_player[2][2]);
	vec_player[2][3] = VNorm(vec_player[2][3]);

	vec_player[3][0] = VNorm(vec_player[3][0]);
	vec_player[3][1] = VNorm(vec_player[3][1]);
	vec_player[3][2] = VNorm(vec_player[3][2]);
	vec_player[3][3] = VNorm(vec_player[3][3]);

	cross[0][0] = (bommr[0].x * vec_player[0][0].y) - (bommr[0].y * vec_player[0][0].x);
	cross[0][1] = (bommr[1].x * vec_player[0][1].y) - (bommr[1].y * vec_player[0][1].x);
	cross[0][2] = (bommr[2].x * vec_player[0][2].y) - (bommr[2].y * vec_player[0][2].x);
	cross[0][3] = (bommr[3].x * vec_player[0][3].y) - (bommr[3].y * vec_player[0][3].x);

	cross[1][0] = (bommr[0].x * vec_player[1][0].y) - (bommr[0].y * vec_player[1][0].x);
	cross[1][1] = (bommr[1].x * vec_player[1][1].y) - (bommr[1].y * vec_player[1][1].x);
	cross[1][2] = (bommr[2].x * vec_player[1][2].y) - (bommr[2].y * vec_player[1][2].x);
	cross[1][3] = (bommr[3].x * vec_player[1][3].y) - (bommr[3].y * vec_player[1][3].x);

	cross[2][0] = (bommr[0].x * vec_player[2][0].y) - (bommr[0].y * vec_player[2][0].x);
	cross[2][1] = (bommr[1].x * vec_player[2][1].y) - (bommr[1].y * vec_player[2][1].x);
	cross[2][2] = (bommr[2].x * vec_player[2][2].y) - (bommr[2].y * vec_player[2][2].x);
	cross[2][3] = (bommr[3].x * vec_player[2][3].y) - (bommr[3].y * vec_player[2][3].x);

	cross[3][0] = (bommr[0].x * vec_player[3][0].y) - (bommr[0].y * vec_player[3][0].x);
	cross[3][1] = (bommr[1].x * vec_player[3][1].y) - (bommr[1].y * vec_player[3][1].x);
	cross[3][2] = (bommr[2].x * vec_player[3][2].y) - (bommr[2].y * vec_player[3][2].x);
	cross[3][3] = (bommr[3].x * vec_player[3][3].y) - (bommr[3].y * vec_player[3][3].x);

	if (cross[0][0] >= 0 && cross[0][1] >= 0 && cross[0][2] >= 0 && cross[0][3] >= 0 ||
		cross[1][0] >= 0 && cross[1][1] >= 0 && cross[1][2] >= 0 && cross[1][3] >= 0 ||
		cross[2][0] >= 0 && cross[2][1] >= 0 && cross[2][2] >= 0 && cross[2][3] >= 0 ||
		cross[3][0] >= 0 && cross[3][1] >= 0 && cross[3][2] >= 0 && cross[3][3] >= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Enemy::BommerHitBox(Transform transform)
{
	VECTOR bommr[4];

	VECTOR vec_player[4][4];

	float cross[4][4];

	float player_left = (float)transform.x - transform.xr;
	float player_right = (float)transform.x + transform.xr;
	float player_top = (float)transform.y - transform.yr;
	float player_down = (float)transform.y + transform.yr;

	float left_top_x = ((-this->transform.xr) * cosf(angle) + ((-this->transform.yr) * -sinf(angle)) + (float)this->transform.x);
	float left_top_y = ((-this->transform.xr) * sinf(angle) + ((-this->transform.yr) * cosf(angle)) + (float)this->transform.y);
	float right_top_x = ((this->transform.xr) * cosf(angle) + ((-this->transform.yr) * -sinf(angle)) + (float)this->transform.x);
	float right_top_y = ((this->transform.xr) * sinf(angle) + ((-this->transform.yr) * cosf(angle)) + (float)this->transform.y);
	float left_down_x = ((-this->transform.xr) * cosf(angle) + ((this->transform.yr) * -sinf(angle)) + (float)this->transform.x);
	float left_down_y = ((-this->transform.xr) * sinf(angle) + ((this->transform.yr) * cosf(angle)) + (float)this->transform.y);
	float right_down_x = ((this->transform.xr) * cosf(angle) + ((this->transform.yr) * -sinf(angle)) + (float)this->transform.x);
	float right_down_y = ((this->transform.xr) * sinf(angle) + ((this->transform.yr) * cosf(angle)) + (float)this->transform.y);


	bommr[0] = VGet(left_top_x - left_down_x, left_top_y - left_down_y, 0.0f);//|
	bommr[1] = VGet(left_down_x - right_down_x, left_down_y - right_down_y, 0.0f);//_
	bommr[2] = VGet(right_down_x - right_top_x, right_down_y - right_top_y, 0.0f);// |
	bommr[3] = VGet(right_top_x - left_top_x, right_top_y - left_top_y, 0.0f);//￣

	bommr[0] = VNorm(bommr[0]);
	bommr[1] = VNorm(bommr[1]);
	bommr[2] = VNorm(bommr[2]);
	bommr[3] = VNorm(bommr[3]);

	vec_player[0][0] = VGet(player_left - left_top_x, player_top - left_top_y, 0.0f);
	vec_player[0][1] = VGet(player_left - left_down_x, player_top - left_down_y, 0.0f);
	vec_player[0][2] = VGet(player_left - right_down_x, player_top - right_down_y, 0.0f);
	vec_player[0][3] = VGet(player_left - left_top_x, player_top - left_top_y, 0.0f);

	vec_player[1][0] = VGet(player_left - left_top_x, player_down - left_top_y, 0.0f);
	vec_player[1][1] = VGet(player_left - left_down_x, player_down - left_down_y, 0.0f);
	vec_player[1][2] = VGet(player_left - right_down_x, player_down - right_down_y, 0.0f);
	vec_player[1][3] = VGet(player_left - left_top_x, player_down - left_top_y, 0.0f);

	vec_player[2][0] = VGet(player_right - left_top_x, player_top - left_top_y, 0.0f);
	vec_player[2][1] = VGet(player_right - left_down_x, player_top - left_down_y, 0.0f);
	vec_player[2][2] = VGet(player_right - right_down_x, player_top - right_down_y, 0.0f);
	vec_player[2][3] = VGet(player_right - left_top_x, player_top - left_top_y, 0.0f);

	vec_player[3][0] = VGet(player_right - left_top_x, player_down - left_top_y, 0.0f);
	vec_player[3][1] = VGet(player_right - left_down_x, player_down - left_down_y, 0.0f);
	vec_player[3][2] = VGet(player_right - right_down_x, player_down - right_down_y, 0.0f);
	vec_player[3][3] = VGet(player_right - left_top_x, player_down - left_top_y, 0.0f);

	vec_player[0][0] = VNorm(vec_player[0][0]);
	vec_player[0][1] = VNorm(vec_player[0][1]);
	vec_player[0][2] = VNorm(vec_player[0][2]);
	vec_player[0][3] = VNorm(vec_player[0][3]);

	vec_player[1][0] = VNorm(vec_player[1][0]);
	vec_player[1][1] = VNorm(vec_player[1][1]);
	vec_player[1][2] = VNorm(vec_player[1][2]);
	vec_player[1][3] = VNorm(vec_player[1][3]);

	vec_player[2][0] = VNorm(vec_player[2][0]);
	vec_player[2][1] = VNorm(vec_player[2][1]);
	vec_player[2][2] = VNorm(vec_player[2][2]);
	vec_player[2][3] = VNorm(vec_player[2][3]);

	vec_player[3][0] = VNorm(vec_player[3][0]);
	vec_player[3][1] = VNorm(vec_player[3][1]);
	vec_player[3][2] = VNorm(vec_player[3][2]);
	vec_player[3][3] = VNorm(vec_player[3][3]);

	cross[0][0] = (bommr[0].x * vec_player[0][0].y) - (bommr[0].y * vec_player[0][0].x);
	cross[0][1] = (bommr[1].x * vec_player[0][1].y) - (bommr[1].y * vec_player[0][1].x);
	cross[0][2] = (bommr[2].x * vec_player[0][2].y) - (bommr[2].y * vec_player[0][2].x);
	cross[0][3] = (bommr[3].x * vec_player[0][3].y) - (bommr[3].y * vec_player[0][3].x);

	cross[1][0] = (bommr[0].x * vec_player[1][0].y) - (bommr[0].y * vec_player[1][0].x);
	cross[1][1] = (bommr[1].x * vec_player[1][1].y) - (bommr[1].y * vec_player[1][1].x);
	cross[1][2] = (bommr[2].x * vec_player[1][2].y) - (bommr[2].y * vec_player[1][2].x);
	cross[1][3] = (bommr[3].x * vec_player[1][3].y) - (bommr[3].y * vec_player[1][3].x);

	cross[2][0] = (bommr[0].x * vec_player[2][0].y) - (bommr[0].y * vec_player[2][0].x);
	cross[2][1] = (bommr[1].x * vec_player[2][1].y) - (bommr[1].y * vec_player[2][1].x);
	cross[2][2] = (bommr[2].x * vec_player[2][2].y) - (bommr[2].y * vec_player[2][2].x);
	cross[2][3] = (bommr[3].x * vec_player[2][3].y) - (bommr[3].y * vec_player[2][3].x);

	cross[3][0] = (bommr[0].x * vec_player[3][0].y) - (bommr[0].y * vec_player[3][0].x);
	cross[3][1] = (bommr[1].x * vec_player[3][1].y) - (bommr[1].y * vec_player[3][1].x);
	cross[3][2] = (bommr[2].x * vec_player[3][2].y) - (bommr[2].y * vec_player[3][2].x);
	cross[3][3] = (bommr[3].x * vec_player[3][3].y) - (bommr[3].y * vec_player[3][3].x);

	if (cross[0][0] >= 0 && cross[0][1] >= 0 && cross[0][2] >= 0 && cross[0][3] >= 0 ||
		cross[1][0] >= 0 && cross[1][1] >= 0 && cross[1][2] >= 0 && cross[1][3] >= 0 ||
		cross[2][0] >= 0 && cross[2][1] >= 0 && cross[2][2] >= 0 && cross[2][3] >= 0 ||
		cross[3][0] >= 0 && cross[3][1] >= 0 && cross[3][2] >= 0 && cross[3][3] >= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
#pragma endregion

#pragma region Move
//動き
void Enemy::Move(Player& player, bool reflection_flag, Score& score, Item* item,int wave_num)
{
	if (use_flag == true)
	{
		//出現時間管理
		if (appear_time == 0)
		{
			fast_move_flag = true;
			exising_flag = true;
			appear_time = -1;

			if (enemy_type == 2)
			{
				angle = (float)atan2(end_y - start_y, end_x - start_x);
			}

			if (enemy_type == 5)
			{
				player.SetEasingFlag(1);
			}

		}
		else if (appear_time != 0 && appear_time != -1)
		{
			appear_time--;
		}

		if (exising_flag == true)
		{
			//最初の移動
			if (fast_move_flag == true)
			{
				frame++;
				transform.x = start_x + (end_x - start_x) * easeInSine((double)frame / (double)end_frame);
				transform.y = start_y + (end_y - start_y) * easeInSine((double)frame / (double)end_frame);

				if (frame == end_frame)
				{
					fast_move_flag = false;

					if (enemy_type == 2)
					{
						angle = (float)atan2(player.GetY() - this->transform.y, player.GetX() - this->transform.x);
					}

					if (enemy_type == 5)
					{
						angle = (float)atan2(transform.x - 480.0, transform.y - 480.0);
					}
				}
			}
		}

		if (enemy_type == 1 || enemy_type == 3 || enemy_type == 4)
		{
			if (exising_flag == true)
			{
				//移動
				if (action_flag == true && fast_move_flag == false)
				{
					if (move_time > 0)
					{
						move_time--;
					}

					if (move_time == 0)
					{
						move_frame++;
						transform.x = move_start_x[move_num] + (move_end_x[move_num] - move_start_x[move_num]) * easeInSine((double)move_frame / (double)move_end_frame);
						transform.y = move_start_y[move_num] + (move_end_y[move_num] - move_start_y[move_num]) * easeInSine((double)move_frame / (double)move_end_frame);

						if (move_frame == move_end_frame)
						{
							move_num++;
							move_time = def_move_time;
							move_frame = 0;

							switch (easing_num)
							{
							case 2:
								if (move_num == 2)
								{
									move_num = 0;
								}
								break;
							case 3:
								if (move_num == 3)
								{
									move_num = 0;
								}
								break;
							case 4:
								if (move_num == 4)
								{
									move_num = 0;
								}
								break;
							}

						}
					}
				}
				else if (action_flag == false)
				{
					if (move_flag == true)
					{
						shot_time = def_shot_time;
						move_flag = false;
					}
				}

				if (shot_action_flag == true)
				{
					//発射時間管理
					if (fast_move_flag == false && shot_time > 0)
					{
						shot_time--;
					}

					//弾の生成
					if (shot_time == 0)
					{
						shot_time = def_shot_time;
						if (enemy_type == 1 || enemy_type == 3)
						{

							for (int i = 0; i < bullet_max; i++)
							{
								//弾の生成
								if (*bullet[i]->GetBulletFlag() == false)
								{
									bullet[i]->Form(transform, player, x_speed, y_speed, enemy_type);
									damage_flag[i] = true;

									break;
								}
							}
						}
						else if (enemy_type == 4)
						{
							int j;
							float angl = (float)atan2((double)player.GetY() - this->transform.y, (double)player.GetX() - this->transform.x);
							if (wave_num >= 20)
							{
								for (int i = 0; i < 16; i++)
								{
									//全方位弾生成
									j = FlagSerch(bullet, 48);

									bullet[j]->OmniFormHex(transform, player, x_speed, y_speed, enemy_type, i, angl);
									damage_flag[j] = true;
								}
							}
							else
							{
								for (int i = 0; i < 8; i++)
								{
									//全方位弾生成
									j = FlagSerch(bullet, 24);

									bullet[j]->OmniFormOct(transform, player, x_speed, y_speed, enemy_type, i, angl);
									damage_flag[j] = true;
								}
							}
						}
					}
				}
			}
		}
#pragma region ボマー
		//ボマー
		if (enemy_type == 2)
		{
			//最初の移動
			if (exising_flag == true && fast_move_flag == false && explosion_bommer_flag == false)
			{
				if (move_time > 0)
				{
					move_time--;
				}

				if (move_time == 0)
				{
					if (transform.x < 960.0 && transform.x> 0 + 64 &&
						transform.y < 960.0 && transform.y> 0 + 64)
					{
						if ((cos(angle) * x_speed) < 0)
						{
							//座標計算
							vertex.top_left_y = ((int)transform.y - transform.yr) / 32;
							vertex.down_left_y = ((int)transform.y + transform.yr - 1) / 32;

							vertex.top_left_x = (int)(((double)transform.x - transform.xr) + (cos(angle) * x_speed)) / 32;
							vertex.down_left_x = (int)(((double)transform.x - transform.xr) + (cos(angle) * x_speed)) / 32;

							//判定
							if (GetMap(vertex.top_left_x, vertex.top_left_y) == 0 &&
								GetMap(vertex.down_left_x, vertex.down_left_y) == 0)
							{
								transform.x += (cos(angle) * x_speed);
							}
							else
							{
								vertex.top_left_x = ((int)transform.x - transform.xr) / 32;
								vertex.down_left_x = ((int)transform.x - transform.xr) / 32;

								if (GetMap(vertex.top_left_x, vertex.top_left_y) == 0 &&
									GetMap(vertex.down_left_x, vertex.down_left_y) == 0)
								{
									while (1)//隙間埋め
									{
										vertex.top_left_x = (((int)transform.x - transform.xr) - 1) / 32;
										vertex.down_left_x = (((int)transform.x - transform.xr) - 1) / 32;

										if (GetMap(vertex.top_left_x, vertex.top_left_y) == 0 &&
											GetMap(vertex.down_left_x, vertex.down_left_y) == 0)
										{
											if (x_speed < 0)
											{
												transform.x += (cos(angle) * -1);
											}
											else
											{
												transform.x += (cos(angle) * 1);
											}
										}
										else
										{
											explosion_bommer_flag = true;
											break;

										}
									}
								}
							}
						}
						else if ((cos(angle) * x_speed) > 0)
						{
							//座標計算
							vertex.top_right_y = ((int)transform.y - transform.yr) / 32;
							vertex.down_right_y = ((int)transform.y + transform.yr - 1) / 32;

							vertex.top_right_x = (int)((transform.x + transform.xr - 1) + (cos(angle) * x_speed)) / 32;
							vertex.down_right_x = (int)((transform.x + transform.xr - 1) + (cos(angle) * x_speed)) / 32;

							//判定
							if (GetMap(vertex.top_right_x, vertex.top_right_y) == 0 &&
								GetMap(vertex.down_right_x, vertex.down_right_y) == 0)
							{
								transform.x += (cos(angle) * x_speed);
							}
							else
							{
								vertex.top_right_x = ((int)transform.x + transform.xr - 1) / 32;
								vertex.down_right_x = ((int)transform.x + transform.xr - 1) / 32;

								if (GetMap(vertex.top_right_x, vertex.top_right_y) == 0 &&
									GetMap(vertex.down_right_x, vertex.down_right_y) == 0)
								{
									while (1)//隙間埋め
									{
										vertex.top_right_x = (((int)transform.x + transform.xr - 1) + 1) / 32;
										vertex.down_right_x = (((int)transform.x + transform.xr - 1) + 1) / 32;

										if (GetMap(vertex.top_right_x, vertex.top_right_y) == 0 &&
											GetMap(vertex.down_right_x, vertex.down_right_y) == 0)
										{
											if (x_speed < 0)
											{
												transform.x += (cos(angle) * -1);
											}
											else
											{
												transform.x += (cos(angle) * 1);
											}

										}
										else
										{
											explosion_bommer_flag = true;
											break;

										}

									}
								}

							}
						}

						if ((sin(angle) * y_speed) < 0)
						{
							//座標計算
							vertex.top_left_x = ((int)transform.x - transform.xr) / 32;
							vertex.top_right_x = ((int)transform.x + transform.xr - 1) / 32;

							vertex.top_left_y = (int)((transform.y - transform.yr) + (sin(angle) * y_speed)) / 32;
							vertex.top_right_y = (int)((transform.y - transform.yr - 1) + (sin(angle) * y_speed)) / 32;

							//判定
							if (GetMap(vertex.top_left_x, vertex.top_left_y) == 0 &&
								GetMap(vertex.top_right_x, vertex.top_right_y) == 0)
							{
								transform.y += (sin(angle) * y_speed);
							}
							else
							{
								vertex.top_left_y = ((int)transform.y - transform.yr) / 32;
								vertex.top_right_y = ((int)transform.y - transform.yr - 1) / 32;

								if (GetMap(vertex.top_left_x, vertex.top_left_y) == 0 &&
									GetMap(vertex.top_right_x, vertex.top_right_y) == 0)
								{
									while (1)//隙間埋め
									{
										vertex.top_left_y = (int)((transform.y - transform.yr) + (sin(angle) * -1)) / 32;
										vertex.top_right_y = (int)((transform.y - transform.yr - 1) + (sin(angle) * -1)) / 32;

										if (GetMap(vertex.top_left_x, vertex.top_left_y) == 0 &&
											GetMap(vertex.top_right_x, vertex.top_right_y) == 0)
										{
											if (y_speed < 0)
											{
												transform.y += (sin(angle) * -1);
											}
											else
											{
												transform.y += (sin(angle) * 1);
											}
										}
										else
										{
											explosion_bommer_flag = true;
											break;
										}
									}
								}
							}
						}
						else if ((sin(angle) * y_speed) > 0)
						{
							//座標計算
							vertex.down_left_x = ((int)transform.x - transform.xr) / 32;
							vertex.down_right_x = ((int)transform.x + transform.xr - 1) / 32;

							vertex.down_left_y = (int)((transform.y + transform.yr - 1) + (sin(angle) * y_speed)) / 32;
							vertex.down_right_y = (int)((transform.y + transform.yr - 1) + (sin(angle) * y_speed)) / 32;

							//判定
							if (GetMap(vertex.down_left_x, vertex.down_left_y) == 0 &&
								GetMap(vertex.down_right_x, vertex.down_right_y) == 0)
							{
								transform.y += (sin(angle) * y_speed);
							}
							else
							{
								vertex.down_left_y = ((int)transform.y + transform.yr - 1) / 32;
								vertex.down_right_y = ((int)transform.y + transform.yr - 1) / 32;

								if (GetMap(vertex.down_left_x, vertex.down_left_y) == 0 &&
									GetMap(vertex.down_right_x, vertex.down_right_y) == 0)
								{
									while (1)//隙間埋め
									{
										vertex.down_left_y = (((int)transform.y + transform.yr - 1) + 1) / 32;

										vertex.down_right_y = (((int)transform.y + transform.yr - 1) + 1) / 32;

										if (GetMap(vertex.down_left_x, vertex.down_left_y) == 0 &&
											GetMap(vertex.down_right_x, vertex.down_right_y) == 0)
										{
											if (y_speed > 0)
											{
												transform.y += (sin(angle) * 1);
											}
											else
											{
												transform.y += (sin(angle) * -1);
											}
										}
										else
										{
											explosion_bommer_flag = true;
											break;

										}
									}
								}
							}
						}
					}
					else
					{
						transform.y += (sin(angle) * y_speed);
						transform.x += (cos(angle) * x_speed);
					}
				}
			}

			if (explosion_bommer_flag == true)
			{
				explosion_time--;

				if (explosion_time == 0)
				{
					exising_flag = false;
				}
			}
		}
#pragma endregion

#pragma region 中ボス

		if (enemy_type == 10)
		{
			if (exising_flag == true)
			{
				//移動
				if (fast_move_flag == false)
				{
					if (move_time == 1)
					{//地雷設置フラフを立てる
						mine->SetMineFlag(true);
						mine->SetRand(7);
					}

					if (move_time > 0)
					{
						move_time--;
					}

					if (move_time == 0)
					{
						move_flag = true;
					}

					if (move_flag == true)
					{
						if (move_frame == 0)
						{
							move_rand = GetRand(7) + 1;

							if ((int)transform.y == 128)//上
							{
								while (move_rand == 3 || move_rand == 5 || move_rand == 7)
								{
									move_rand = GetRand(7) + 1;
								}
							}
							else if ((int)transform.y == 864)//下
							{
								while (move_rand == 4 || move_rand == 6 || move_rand == 8)
								{
									move_rand = GetRand(7) + 1;
								}
							}
							else if ((int)transform.x >= 776)//右
							{
								while (move_rand == 1 || move_rand == 5 || move_rand == 6)
								{
									move_rand = GetRand(7) + 1;
								}
							}
							else if ((int)transform.x <= 178)//左
							{
								while (move_rand == 2 || move_rand == 7 || move_rand == 8)
								{
									move_rand = GetRand(7) + 1;
								}
							}
						}

						switch (move_rand)
						{

						case 1://右
							XMove(x_speed, true);
							break;

						case 2://左
							XMove(x_speed, false);
							break;

						case 3://上
							YMove(y_speed, true);
							break;

						case 4://下
							YMove(y_speed, false);
							break;

						case 5://右上
							XMove(x_speed, true);
							YMove(y_speed, true);
							break;

						case 6://右下
							XMove(x_speed, true);
							YMove(y_speed, false);
							break;

						case 7://左上
							XMove(x_speed, false);
							YMove(y_speed, true);
							break;

						case 8://左下
							XMove(x_speed, false);
							YMove(y_speed, false);
							break;
						}

						move_frame++;

						if (move_frame == move_end_frame)
						{
							move_frame = 0;
							move_time = def_move_time;
							move_flag = false;
						}
					}
				}

				//発射時間管理
				if (fast_move_flag == false && shot_time > 0)
				{
					shot_time--;
				}

				if (shot_time == -1)
				{
					//反射回数初期化
					shot_time = def_shot_time;
				}

				//当たり判定
				for (int i = 0; i < 4; i++)
				{
					if (*bullet[i]->GetBulletFlag() == true)
					{

						HitBox(*bullet[i]->GetTransform(), *bullet[i], i);
					}
				}

				//弾の生成
				if (shot_time == 0)
				{
					int k[4] = { 0,0,0,0 };
					bool end = false;
					int i;
					int length = 0;

					for (i = 0; i < 4; i++)
					{
						int j = FlagSerch(bullet, all_bullet_max);

						if (j != -1)
						{
							bullet[j]->Form(transform, player, x_speed, y_speed, enemy_type);
							damage_flag[j] = true;
							k[i] = j;
						}
						else
						{
							length = i;
							break;
						}
					}

					if (i == 4)
					{
						end = true;
					}

					if (end == true)
					{
						//角度を90度ずつずらす
						bullet[k[1]]->SetAngle(bullet[k[0]]->GetAngle() + (DX_PI_F / 2));
						bullet[k[2]]->SetAngle(bullet[k[1]]->GetAngle() + (DX_PI_F / 2));
						bullet[k[3]]->SetAngle(bullet[k[2]]->GetAngle() + (DX_PI_F / 2));
					}
					else
					{
						for (int i = 0; i < length; i++)
						{
							int j = k[i];
							bullet[j]->SetBulletFlag(false);

							damage_flag[j] = false;
						}
					}

					shot_time = -1;
				}

				if (hp <= 0)
				{
					exising_flag = false;
				}

				//地雷の動き
				mine->form(transform, move_rand);
			}

			mine->HitBox(transform, hp);

			mine->Move();
			mine->PlayerHitBox(player);
		}
#pragma endregion

#pragma region フォーメーション

		if (enemy_type == 5)
		{
			if (exising_flag == true)
			{
				//移動
				if (action_flag == true && fast_move_flag == false)
				{
					circularMotionL(transform.y, transform.x, 482.0f,482.0f ,380.0f, angle);
				}

				if (shot_action_flag == true)
				{
					//発射時間管理
					if (fast_move_flag == false && shot_time > 0)
					{
						shot_time--;
					}

					//弾の生成
					if (shot_time == 0)
					{
						shot_time = def_shot_time;

						for (int i = 0; i < bullet_max; i++)
						{
							if (*bullet[i]->GetBulletFlag() == false)
							{
								bullet[i]->Form(transform, player, x_speed, y_speed, enemy_type);
								damage_flag[i] = true;

								break;
							}
						}

					}
				}
			}
		}
#pragma endregion

		//弾の動き
		for (int i = 0; i < all_bullet_max; i++)
		{
			bullet[i]->Move(enemy_type, reflection_flag, player, transform.x, transform.y, exising_flag, transform);
		}

		//当たり判定
		for (int i = 0; i < all_bullet_max; i++)
		{

			if (*bullet[i]->GetBulletFlag() == true && exising_flag == true)
			{
				HitBox(*bullet[i]->GetTransform(), i, item);
			}
		}

		switch (enemy_type)
		{
		case 1:
			anime_timer++;

			if (anime_timer == 12 * 6)
			{
				anime_timer = 0;
			}

			anime = anime_timer / 6;
			break;

		case 2:
			bommer_anime_timer++;

			if (bommer_anime_timer == 10 * 6)
			{
				bommer_anime_timer = 0;
			}

			bommer_anime = bommer_anime_timer / 6;
			break;

		case 3:
			boomerang_anime_timer++;

			if (boomerang_anime_timer == 10 * 6)
			{
				boomerang_anime_timer = 0;
			}

			boomerang_anime = boomerang_anime_timer / 6;
			break;

		case 10:
			sub_boss1_anime_timer++;

			if (sub_boss1_anime_timer == 10 * 6)
			{
				sub_boss1_anime_timer = 0;
			}

			sub_boss1_anime = sub_boss1_anime_timer / 6;
			break;
		}


	}

}
#pragma endregion

#pragma region 反射回数初期化

//bullet_flagがすべてfalseだったら
//全ての反射回数を0にして
//移動フラグを立てる

void Enemy::Refresh_ReflectionNum(int max)
{
	int i = 0;

	for (i = 0; i < max; i++)
	{
		//反射回数初期化
		if (*bullet[i]->GetBulletFlag() == true)
		{
			i -= 1;
			break;

		}
	}
	if (i == max && shot_time == -1)
	{
		for (int j = 0; j < max; j++)
		{
			bullet[j]->SetReflectionNum(0);
			shot_time = def_shot_time;
		}
	}
}

#pragma endregion

#pragma region チュートリアル
void Enemy::TuTorialMove(int x, int y, int r, int& shot_flag, int stelsflag, int reflectionflag)
{
	if (use_flag == true)
	{
		//出現時間管理
		if (appear_time == 0)
		{
			fast_move_flag = true;
			exising_flag = true;
			appear_time = -1;
		}
		else if (appear_time != 0 && appear_time != -1)
		{
			appear_time--;
		}

		if (exising_flag == true)
		{
			//最初の移動
			if (fast_move_flag == true)
			{
				frame++;
				transform.x = start_x + (end_x - start_x) * easeInSine((double)frame / (double)end_frame);
				transform.y = start_y + (end_y - start_y) * easeInSine((double)frame / (double)end_frame);

				if (frame == end_frame)
				{
					fast_move_flag = false;
				}
			}
		}

		if (shot_action_flag == true)
		{
			//弾の生成

			//発射時間管理
			if (shot_flag == 1 && shot_time > 0)
			{
				shot_time--;
			}

			//弾の生成
			if (shot_time == 0)
			{
				shot_time = -1;

				if (*bullet[0]->GetBulletFlag() == false)
				{
					bullet[0]->TuTorialForm(transform, x, y, x_speed, y_speed, stelsflag);
					damage_flag[0] = true;
					shot_flag = false;
				}
			}

			if (hp <= 0)
			{
				exising_flag = false;
			}
		}
	}

	if (reflectionflag != 1)
	{
		//弾の動き
		bullet[0]->Move(enemy_type, false);
	}
	else
	{
		bullet[0]->TutorialMove(y);
	}

	//当たり判定

	if (*bullet[0]->GetBulletFlag() == true && exising_flag == true)
	{
		TutorialHitBox(*bullet[0]->GetTransform(), 0);
	}
}
#pragma endregion

#pragma region ボマー当たり判定
//爆発エフェクト
void Enemy::ExplosionBommer(Enemy& enemy)
{
	if (enemy_type == 2)
	{
		if (transform.x != enemy.transform.x && transform.y != enemy.transform.y &&
			enemy.exising_flag == true && exising_flag == true)
		{
			if (BommerHitBox(enemy.GetTransform()) == true)
			{
				explosion_bommer_flag = true;
				enemy_to_bommer = true;
				enemy.SetEnemyFlag(false);
			}
		}
	}
}
//敵と敵
void Enemy::EnemyToEnemyHitBox(Enemy& enemy)
{
	if (enemy_type == 2)
	{
		if (BommerHitBox(enemy.GetTransform()) == true)
		{
			if (damage_flag[0] == false || damage_flag[1] == false || damage_flag[2] == false)
			{
				explosion_bommer_flag = true;
				enemy_to_bommer = true;

			}
		}
	}
}

void Enemy::PlaterToEnemyHitBox(Player& player,int enemy_num)
{
	if (enemy_type == 2)
	{
		if (BommerHitBox(player) == true && exising_flag == true)
		{
			if (player.GetDamageFlag(enemy_num) == 0)
			{
				player.HpSub(1);
			}

			explosion_bommer_flag = true;
			enemy_to_bommer = true;

			player.SetDamageFlag(enemy_num, 1);

		}
		else
		{
			player.SetDamageFlag(enemy_num, 0);
		}
	}
}
#pragma endregion

#pragma region 当たり判定
void Enemy::HP(Transform transform, EnemyBullet& bullet, Item* item)
{
	//当たり判定(複数)
	if (*bullet.GetBulletFlag() == true && exising_flag == true)
	{
		if (this->transform.x - this->transform.xr < transform.x + transform.xr &&
			this->transform.x + this->transform.xr > transform.x - transform.xr)
		{
			if (this->transform.y - this->transform.yr < transform.y + transform.yr &&
				this->transform.y + this->transform.yr > transform.y - transform.yr)
			{
				hp -= 1;
				bullet.SetBulletFlag(false);

				if (hp <= 0)
				{
					exising_flag = false;
					item->Form(transform);
				}

			}
		}
	}
}

//当たり判定(単体)
void Enemy::HitBox(Transform transform, int num, Item* item)
{
	if (this->transform.x - this->transform.xr < transform.x + transform.xr &&
		this->transform.x + this->transform.xr > transform.x - transform.xr)
	{
		if (this->transform.y - this->transform.yr < transform.y + transform.yr &&
			this->transform.y + this->transform.yr > transform.y - transform.yr)
		{
			if (damage_flag[num] == false)
			{
				hp--;
				bullet[num]->SetBulletFlag(false);

				if (hp <= 0)
				{
					exising_flag = false;
					item->Form(transform);
				}
			}

			damage_flag[num] = true;
		}
		else
		{
			damage_flag[num] = false;
		}
	}
	else
	{
		damage_flag[num] = false;
	}

}

void Enemy::HitBox(Transform& transform, EnemyBullet& enemyBullet, int i)
{
	if (*enemyBullet.GetBulletFlag() == true)
	{
		if (this->transform.x - this->transform.xr < transform.x + transform.xr &&
			this->transform.x + this->transform.xr > transform.x - transform.xr)
		{
			if (this->transform.y - this->transform.yr < transform.y + transform.yr &&
				this->transform.y + this->transform.yr > transform.y - transform.yr)
			{
				if (damage_flag[i] == false)
				{
					hp--;
					damage_flag[i] = true;
					enemyBullet.SetBulletFlag(false);
				}

			}
			else
			{
				damage_flag[i] = false;
			}
		}
		else
		{
			damage_flag[i] = false;
		}
	}
}

void Enemy::TutorialHitBox(Transform transform, int num)
{
	if (this->transform.x - this->transform.xr < transform.x + transform.xr &&
		this->transform.x + this->transform.xr > transform.x - transform.xr)
	{
		if (this->transform.y - this->transform.yr < transform.y + transform.yr &&
			this->transform.y + this->transform.yr > transform.y - transform.yr)
		{
			if (damage_flag[num] == false)
			{
				hp--;
				bullet[num]->SetBulletFlag(false);

				if (hp <= 0)
				{
					exising_flag = false;
				}
			}

			damage_flag[num] = true;
		}
		else
		{
			damage_flag[num] = false;
		}
	}
	else
	{
		damage_flag[num] = false;
	}
}
#pragma endregion

#pragma region Draw
//描画
void Enemy::Draw(int num)
{
	if (true)
	{

	}
	if (exising_flag == true)
	{
		switch (enemy_type)
		{
		case 1://雑魚
			DrawGraphF((float)transform.x - img_r, (float)transform.y - img_r, img[anime], true);
			break;
		case 2://ボマー
			if (explosion_bommer_flag == false)
			{
				DrawRotaGraphF((float)transform.x, (float)transform.y, 1.0, angle, bommer_img[bommer_anime], true, true);
			}
			else
			{
				DrawBox((int)transform.x - transform.xr, (int)transform.y - transform.yr,
					(int)transform.x + transform.xr, (int)transform.y + transform.yr, GetColor(255, 0, 0), true);
			}
			break;
		case 3://ブーメラン
			DrawGraphF((float)transform.x - img_r, (float)transform.y - img_r, boomerang_img[boomerang_anime], true);
			break;
		case 10://中ボス雑魚
			DrawGraphF((float)transform.x - img_r, (float)transform.y - img_r, sub_boss1_img[sub_boss1_anime], true);
			break;
		default:
			DrawBox((int)transform.x - transform.xr, (int)transform.y - transform.yr,
				(int)transform.x + transform.xr, (int)transform.y + transform.yr, GetColor(0, 255, 0), true);
			DrawCircle((int)transform.x, (int)transform.y, 2, GetColor(255, 255, 255), true);
			break;
		}

	}

	for (int i = 0; i < all_bullet_max; i++)
	{
		bullet[i]->Draw(enemy_type);
		//DrawFormatString(0, 300 + num + (i * 20), GetColor(255, 255, 255), "damage_flag[%d]:%d", i, damage_flag[i]);

		if (bullet[i]->GetReflectionNum() >= 3)
		{
			bullet[i]->SetBulletFlag(false);
			bullet[i]->SetReflectionNum(0);
		}
	}



	mine->Draw();
}
#pragma endregion

#pragma region 生成
//ファイルからデータ読みこみ
void Enemy::form(FILE* fp, int wave_num)
{
	delete bullet[0];

	int a = 0;
	int b = 0;
	int c = 0;
	if (fscanf_s(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%lf,%lf,%lf,%lf,%d,%d,%lf,%lf,%lf,%lf,%lf,%lf,%d,%d,%d,%d,%d,%d"
		, &a, &b, &c, &enemy_type, &appear_time, &shot_time, &explosion_time, &hp, &transform.xr, &transform.yr, &x_speed, &y_speed, &end_frame, &start_x, &start_y, &end_x, &end_y, &move_time, &move_end_frame,
		&move_end_x[0], &move_end_y[0], &move_end_x[1], &move_end_y[1], &move_end_x[2], &move_end_y[2], &easing_num,
		&mime_initialize.transform_xr, &mime_initialize.transform_yr, &mime_initialize.explosion_r, &mime_initialize.def_explosion_time, &mime_initialize.def_bombs_time)
		!= EOF)
	{
		use_flag = a;
		action_flag = b;
		shot_action_flag = c;
		mine->initialize(mime_initialize);
	}
	else
	{
		use_flag = false;
		enemy_type = 0;
		transform.xr = 0;
		transform.yr = 0;
		hp = 0;
		x_speed = 0;
		y_speed = 0;
		action_flag = false;
		shot_time = 0;
		end_frame = 0;
		start_x = 0;
		end_x = 0;
		end_y = 0;
		appear_time = -1;
		move_time = 0;
		move_end_frame = 0;
		move_end_x[0] = 0;
		move_end_y[0] = 0;
		move_end_x[1] = 0;
		move_end_y[1] = 0;
		move_end_x[2] = 0;
		move_end_y[2] = 0;
		easing_num = 0;
		shot_action_flag = false;
		mime_initialize.transform_yr = 0;
		mime_initialize.transform_xr = 0;
		mime_initialize.def_bombs_time = 0;
		mime_initialize.def_explosion_time = 0;
		mime_initialize.explosion_r = 0;

	}

	move_start_x[0] = end_x;
	move_start_y[0] = end_y;
	transform.x = start_x;
	transform.y = start_y;
	exising_flag = false;
	damage_flag[0] = false;
	damage_flag[1] = false;
	damage_flag[2] = false;
	fast_move_flag = false;

	move_flag = false;
	frame = 0;
	move_num = 0;
	move_frame = 0;

	switch (easing_num)
	{
	case 2:
		move_start_x[1] = move_end_x[0];
		move_start_y[1] = move_end_y[0];
		move_end_x[1] = move_start_x[0];
		move_end_y[1] = move_start_y[0];
		break;
	case 3:
		move_start_x[1] = move_end_x[0];
		move_start_y[1] = move_end_y[0];
		move_start_x[2] = move_end_x[1];
		move_start_y[2] = move_end_y[1];
		move_end_x[2] = move_start_x[0];
		move_end_y[2] = move_start_y[0];
		break;
	case 4:
		move_start_x[1] = move_end_x[0];
		move_start_y[1] = move_end_y[0];
		move_start_x[2] = move_end_x[1];
		move_start_y[2] = move_end_y[1];
		move_start_x[3] = move_end_x[2];
		move_start_y[3] = move_end_y[2];
		move_end_x[3] = move_start_x[0];
		move_end_y[3] = move_start_y[0];
		break;

	}

	def_move_time = move_time;
	def_shot_time = shot_time;

	angle = 0.0f;
	vertex.top_left_x = 0;
	vertex.top_left_y = 0;
	vertex.down_left_x = 0;
	vertex.down_left_y = 0;
	vertex.top_right_x = 0;
	vertex.top_right_y = 0;
	vertex.down_right_x = 0;
	vertex.down_right_y = 0;
	explosion_bommer_flag = false;
	def_explosion_time = explosion_time;

	switch (enemy_type)
	{
	case 1:
		all_bullet_max = 3;
		break;
	case 2:
		all_bullet_max = 1;
		break;
	case 3:
		all_bullet_max = 3;
		break;
	case 4:
		if (wave_num >=20)
		{
			all_bullet_max = 48;
		}
		else
		{
			all_bullet_max = 24;
		}
		break;
	case 5:
		all_bullet_max = 3;
		break;
	case 10:
		all_bullet_max = 12;
		break;
	}

	for (int i = 0; i < all_bullet_max; i++)
	{
		bullet[i] = new EnemyBullet;
	}
}

//生成メイン
void EnemyForm(const char* file_name, int max, Enemy** enemy,int wave_num)
{

	FILE* fp;
	fopen_s(&fp, file_name, "r");

	if (fp != NULL)
	{
		for (int i = 0; i < max; i++)
		{
			enemy[i]->form(fp, wave_num);
		}
		fclose(fp);
	}
}

//ファイルからデータ読みこみ
void Enemy::Tutorialform(FILE* fp)
{
	int a = 0;
	int b = 0;
	int c = 0;
	if (fscanf_s(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%lf,%lf,%lf,%lf,%d,%d,%lf,%lf,%lf,%lf,%lf,%lf,%d,%d,%d,%d,%d,%d"
		, &a, &b, &c, &enemy_type, &appear_time, &shot_time, &explosion_time, &hp, &transform.xr, &transform.yr, &x_speed, &y_speed, &end_frame, &start_x, &start_y, &end_x, &end_y, &move_time, &move_end_frame,
		&move_end_x[0], &move_end_y[0], &move_end_x[1], &move_end_y[1], &move_end_x[2], &move_end_y[2], &easing_num,
		&mime_initialize.transform_xr, &mime_initialize.transform_yr, &mime_initialize.explosion_r, &mime_initialize.def_explosion_time, &mime_initialize.def_bombs_time)
		!= EOF)
	{
		use_flag = a;
		action_flag = b;
		shot_action_flag = c;
		mine->initialize(mime_initialize);
	}
	else
	{
		use_flag = false;
		enemy_type = 0;
		transform.xr = 0;
		transform.yr = 0;
		hp = 0;
		x_speed = 0;
		y_speed = 0;
		action_flag = false;
		shot_time = 0;
		end_frame = 0;
		start_x = 0;
		end_x = 0;
		end_y = 0;
		appear_time = -1;
		move_time = 0;
		move_end_frame = 0;
		move_end_x[0] = 0;
		move_end_y[0] = 0;
		move_end_x[1] = 0;
		move_end_y[1] = 0;
		move_end_x[2] = 0;
		move_end_y[2] = 0;
		easing_num = 0;
		shot_action_flag = false;
		mime_initialize.transform_yr = 0;
		mime_initialize.transform_xr = 0;
		mime_initialize.def_bombs_time = 0;
		mime_initialize.def_explosion_time = 0;
		mime_initialize.explosion_r = 0;

	}

	move_start_x[0] = end_x;
	move_start_y[0] = end_y;
	transform.x = start_x;
	transform.y = start_y;
	exising_flag = false;
	damage_flag[0] = false;
	damage_flag[1] = false;
	damage_flag[2] = false;
	fast_move_flag = false;

	move_flag = false;
	frame = 0;
	move_num = 0;
	move_frame = 0;

	switch (easing_num)
	{
	case 2:
		move_start_x[1] = move_end_x[0];
		move_start_y[1] = move_end_y[0];
		move_end_x[1] = move_start_x[0];
		move_end_y[1] = move_start_y[0];
		break;
	case 3:
		move_start_x[1] = move_end_x[0];
		move_start_y[1] = move_end_y[0];
		move_start_x[2] = move_end_x[1];
		move_start_y[2] = move_end_y[1];
		move_end_x[2] = move_start_x[0];
		move_end_y[2] = move_start_y[0];
		break;
	case 4:
		move_start_x[1] = move_end_x[0];
		move_start_y[1] = move_end_y[0];
		move_start_x[2] = move_end_x[1];
		move_start_y[2] = move_end_y[1];
		move_start_x[3] = move_end_x[2];
		move_start_y[3] = move_end_y[2];
		move_end_x[3] = move_start_x[0];
		move_end_y[3] = move_start_y[0];
		break;

	}

	def_move_time = move_time;
	def_shot_time = shot_time;

	angle = 0.0f;
	vertex.top_left_x = 0;
	vertex.top_left_y = 0;
	vertex.down_left_x = 0;
	vertex.down_left_y = 0;
	vertex.top_right_x = 0;
	vertex.top_right_y = 0;
	vertex.down_right_x = 0;
	vertex.down_right_y = 0;
	explosion_bommer_flag = false;
	def_explosion_time = explosion_time;
}

//生成メイン
void TutorialEnemyForm(const char* file_name, int max, Enemy** enemy)
{

	FILE* fp;
	fopen_s(&fp, file_name, "r");

	if (fp != NULL)
	{
		for (int i = 0; i < max; i++)
		{
			enemy[i]->Tutorialform(fp);
		}
		fclose(fp);
	}
}
#pragma endregion

#pragma region 当たり判定付き移動

void Enemy::XMove(int x_speed, bool right_flag)
{
	if (right_flag == false)
	{
		//座標計算
		vertex.top_left_y = ((int)transform.y - transform.yr) / 32;
		vertex.down_left_y = ((int)transform.y + transform.yr - 1) / 32;

		vertex.top_left_x = (int)(((double)transform.x - transform.xr) - x_speed) / 32;
		vertex.down_left_x = (int)(((double)transform.x - transform.xr) - x_speed) / 32;

		//判定
		if (GetMap(vertex.top_left_x, vertex.top_left_y) == 0 &&
			GetMap(vertex.down_left_x, vertex.down_left_y) == 0 &&
			transform.x > 178)
		{
			transform.x -= x_speed;
		}
		else
		{
			vertex.top_left_x = ((int)transform.x - transform.xr) / 32;
			vertex.down_left_x = ((int)transform.x - transform.xr) / 32;

			if (GetMap(vertex.top_left_x, vertex.top_left_y) == 0 &&
				GetMap(vertex.down_left_x, vertex.down_left_y) == 0 &&
				transform.x > 178)
			{
				while (1)//隙間埋め
				{
					vertex.top_left_x = (((int)transform.x - transform.xr) - 1) / 32;
					vertex.down_left_x = (((int)transform.x - transform.xr) - 1) / 32;

					if (GetMap(vertex.top_left_x, vertex.top_left_y) == 0 &&
						GetMap(vertex.down_left_x, vertex.down_left_y) == 0 &&
						transform.x > 178)
					{
						transform.x -= 1;
					}
					else
					{
						break;
					}

				}
			}

		}
	}
	else
	{
		//座標計算
		vertex.top_right_y = ((int)transform.y - transform.yr) / 32;
		vertex.down_right_y = ((int)transform.y + transform.yr - 1) / 32;

		vertex.top_right_x = ((int)(transform.x + transform.xr - 1) + x_speed) / 32;
		vertex.down_right_x = ((int)(transform.x + transform.xr - 1) + x_speed) / 32;

		//判定
		if (GetMap(vertex.top_right_x, vertex.top_right_y) == 0 &&
			GetMap(vertex.down_right_x, vertex.down_right_y) == 0 &&
			transform.x < 776)
		{
			transform.x += x_speed;
		}
		else
		{
			vertex.top_right_x = ((int)transform.x + transform.xr - 1) / 32;
			vertex.down_right_x = ((int)transform.x + transform.xr - 1) / 32;

			if (GetMap(vertex.top_right_x, vertex.top_right_y) == 0 &&
				GetMap(vertex.down_right_x, vertex.down_right_y) == 0 &&
				transform.x < 776)
			{
				while (1)//隙間埋め
				{
					vertex.top_right_x = (((int)transform.x + transform.xr - 1) + 1) / 32;
					vertex.down_right_x = (((int)transform.x + transform.xr - 1) + 1) / 32;

					if (GetMap(vertex.top_right_x, vertex.top_right_y) == 0 &&
						GetMap(vertex.down_right_x, vertex.down_right_y) == 0 &&
						transform.x < 776)
					{
						transform.x += 1;
					}
					else
					{
						break;

					}
				}
			}
		}
	}
}

void Enemy::YMove(int y_speed, bool up_flag)
{
	if (up_flag == true)
	{
		//座標計算
		vertex.top_left_x = ((int)transform.x - transform.xr) / 32;
		vertex.top_right_x = ((int)transform.x + transform.xr - 1) / 32;

		vertex.top_left_y = (int)((transform.y - transform.yr) - y_speed) / 32;
		vertex.top_right_y = (int)((transform.y - transform.yr) - y_speed) / 32;

		//判定
		if (GetMap(vertex.top_left_x, vertex.top_left_y) == 0 &&
			GetMap(vertex.top_right_x, vertex.top_right_y) == 0)
		{
			transform.y -= y_speed;
		}
		else
		{
			vertex.top_left_y = ((int)transform.y - transform.yr) / 32;
			vertex.top_right_y = ((int)transform.y - transform.yr) / 32;

			if (GetMap(vertex.top_left_x, vertex.top_left_y) == 0 &&
				GetMap(vertex.top_right_x, vertex.top_right_y) == 0)
			{
				while (1)//隙間埋め
				{
					vertex.top_left_y = ((int)(transform.y - transform.yr) - 1) / 32;
					vertex.top_right_y = ((int)(transform.y - transform.yr) - 1) / 32;

					if (GetMap(vertex.top_left_x, vertex.top_left_y) == 0 &&
						GetMap(vertex.top_right_x, vertex.top_right_y) == 0)
					{
						transform.y -= 1;
					}
					else
					{
						break;
					}
				}
			}

		}
	}
	else
	{
		//座標計算
		vertex.down_left_x = ((int)transform.x - transform.xr) / 32;
		vertex.down_right_x = ((int)transform.x + transform.xr - 1) / 32;

		vertex.down_left_y = (int)((transform.y + transform.yr - 1) + y_speed) / 32;
		vertex.down_right_y = (int)((transform.y + transform.yr - 1) + y_speed) / 32;

		//判定
		if (GetMap(vertex.down_left_x, vertex.down_left_y) == 0 &&
			GetMap(vertex.down_right_x, vertex.down_right_y) == 0)
		{
			transform.y += y_speed;
		}
		else
		{
			vertex.down_left_y = ((int)transform.y + transform.yr - 1) / 32;
			vertex.down_right_y = ((int)transform.y + transform.yr - 1) / 32;

			if (GetMap(vertex.down_left_x, vertex.down_left_y) == 0 &&
				GetMap(vertex.down_right_x, vertex.down_right_y) == 0)
			{
				while (1)//隙間埋め
				{
					vertex.down_left_y = (((int)transform.y + transform.yr - 1) + 1) / 32;

					vertex.down_right_y = (((int)transform.y + transform.yr - 1) + 1) / 32;

					if (GetMap(vertex.down_left_x, vertex.down_left_y) == 0 &&
						GetMap(vertex.down_right_x, vertex.down_right_y) == 0)
					{
						transform.y += 1;
					}
					else
					{
						break;
					}
				}
			}
		}
	}
}

#pragma endregion

#pragma region ゲッター
Transform* Enemy::GetBulletTransform(int num)
{
	return bullet[num]->GetTransform();
}

Transform Enemy::GetTransform()
{
	return transform;
}

int Enemy::GetShotTime()
{
	return shot_time;
}

bool Enemy::GetBulletFlag(int i)
{
	return *bullet[i]->GetBulletFlag();
}

bool Enemy::GetEnemyFlag()
{
	return exising_flag;
}

int Enemy::GetAppearTime()
{
	return appear_time;
}

EnemyBullet* Enemy::GetEnmyBullet(int i)
{
	return bullet[i];
}

int Enemy::GetBulletMax()
{
	return all_bullet_max;
}
#pragma endregion

#pragma region セッター

void Enemy::SetReflectionNum()
{
	for (int i = 0; i < all_bullet_max; i++)
	{
		bullet[i]->SetReflectionNum(0);
	}
}
void Enemy::SetShotTime(int shot_time)
{
	this->shot_time = shot_time;
}

void Enemy::SetEnemyFlag(bool flag)
{
	exising_flag = flag;
}

#pragma endregion

int GetEnemyMax(int& wave_num)
{
	switch (wave_num)
	{
	case 1:
		return 1;
	case 2:
		return 2;
	case 3:
		return 4;
	case 4:
		return 2;
	case 5:
		return 4;
	case 6:
		return 1;
	case 7:
		return 3;
	case 8:
		return 5;
	case 9:
		return 5;
	case 10:
		return 3;
	case 11:
		return 2;
	case 12:
		return 4;
	case 13:
		return 4;
	case 14:
		return 5;
	case 15:
		return 1;
	case 16:
		return 5;
	case 17:
		return 4;
	case 18:
		return 4;
	case 19:
		return 4;
	case 20:
		return 4;
	case 21:
		return 8;
	case 22:
		return 16;
	}
	return -1;
}

