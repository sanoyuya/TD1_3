#include"bullet.h"
#include"enemy.h"
#include"DxLib.h"
#include"map.h"
#include<math.h>

#pragma region 反射用

int EnemyBullet::Box_Line(float start_x, float start_y, float start2_x, float start2_y, float start3_x, float start3_y, float start4_x, float start4_y, float point1_x, float point1_y, float point2_x, float point2_y, float point3_x, float point3_y, float point4_x, float point4_y)
{

	//上
	if (LineAndLine(start_x, start_y, start2_x, start2_y,
		start3_x, start3_y, start4_x, start4_y,
		point1_x, point1_y, point2_x, point2_y) == true &&
		LineAndLine(start2_x, start2_y, start3_x, start3_y,
			start4_x, start4_y, start_x, start_y,
			point1_x, point1_y, point2_x, point2_y) == true)
	{
		return 1;
	}

	//下
	if (LineAndLine(start_x, start_y, start2_x, start2_y,
		start3_x, start3_y, start4_x, start4_y,
		point3_x, point3_y, point4_x, point4_y) == true &&
		LineAndLine(start2_x, start2_y, start3_x, start3_y,
			start4_x, start4_y, start_x, start_y,
			point3_x, point3_y, point4_x, point4_y) == true)
	{
		return 2;
	}

	//左
	if (LineAndLine(start2_x, start2_y, start3_x, start3_y,
		start4_x, start4_y, start_x, start_y,
		point2_x, point2_y, point4_x, point4_y) == true &&
		LineAndLine(start_x, start_y, start2_x, start2_y,
			start3_x, start3_y, start4_x, start4_y,
			point2_x, point2_y, point4_x, point4_y) == true)
	{
		return 3;
	}

	//右
	if (LineAndLine(start2_x, start2_y, start3_x, start3_y,
		start4_x, start4_y, start_x, start_y,
		point1_x, point1_y, point3_x, point3_y) == true &&
		LineAndLine(start_x, start_y, start2_x, start2_y,
			start3_x, start3_y, start4_x, start4_y,
			point1_x, point1_y, point3_x, point3_y) == true)
	{
		return 4;
	}

	return -1;
}

bool EnemyBullet::LineAndLine(float start_x, float start_y, float end_x, float end_y, float start2_x, float start2_y, float end2_x, float end2_y, float point1_x, float point1_y, float point2_x, float point2_y)
{

	VECTOR vec_line;		//　ライン始点からライン終点までのベクトル
	VECTOR line_vec_point1;		//　ライン始点からポイントまでのベクトル
	VECTOR line_vec_point2;		//　ライン始点からポイントまでのベクトル

	//　外積の値
	float  line_cross1;
	float  line_cross2;

	VECTOR vec_line2;		//　ライン始点からライン終点までのベクトル
	VECTOR line2_vec_point1;		//　ライン始点からポイントまでのベクトル
	VECTOR line2_vec_point2;		//　ライン始点からポイントまでのベクトル

	//　外積の値
	float  line2_cross1;
	float  line2_cross2;

	//ラインのベクトル
	vec_line = VGet(end_x - start_x, end_y - start_y, 0.0);

	//正規化
	vec_line = VNorm(vec_line);

	//  ラインの始点からカーソルまでのポイント作る
	line_vec_point1 = VGet(point1_x - start_x, point1_y - start_y, 0);
	line_vec_point2 = VGet(point2_x - start_x, point2_y - start_y, 0);

	line_vec_point1 = VNorm(line_vec_point1);
	line_vec_point2 = VNorm(line_vec_point2);

	//  変数を使って外積を計算して変数crossに格納
	line_cross1 = (vec_line.x * line_vec_point1.y) - (vec_line.y * line_vec_point1.x);
	line_cross2 = (vec_line.x * line_vec_point2.y) - (vec_line.y * line_vec_point2.x);

	//ラインのベクトル
	vec_line2 = VGet(end2_x - start2_x, end2_y - start2_y, 0.0);

	//正規化
	vec_line2 = VNorm(vec_line2);

	//  ラインの始点からカーソルまでのベクトル作る
	line2_vec_point1 = VGet(point1_x - start2_x, point1_y - start2_y, 0);
	line2_vec_point2 = VGet(point2_x - start2_x, point2_y - start2_y, 0);

	line2_vec_point1 = VNorm(line2_vec_point1);
	line2_vec_point2 = VNorm(line2_vec_point2);

	//  変数を使って外積を計算して変数crossに格納
	line2_cross1 = (vec_line2.x * line2_vec_point1.y) - (vec_line2.y * line2_vec_point1.x);
	line2_cross2 = (vec_line2.x * line2_vec_point2.y) - (vec_line2.y * line2_vec_point2.x);

	//  変数crossの値で左右の判定
	//  (カーソルがラインより右か左かを文字で表示)
	if (line_cross1 <= 0 && line_cross2 <= 0 &&
		line2_cross1 <= 0 && line2_cross2 <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
#pragma endregion

void circularMotionL(double& posX, double& posY, float cPosX, float cPosY, float x_r, float y_r, float angle, float& angle2) {

	double thRad = angle;
	float Px0 = (float)(x_r * cos(angle2) * cos(thRad) - y_r * sin(angle2) * sin(thRad) + cPosX);
	float Py0 = (float)(x_r * cos(angle2) * sin(thRad) + y_r * sin(angle2) * cos(thRad) + cPosY);

	posX = Px0;
	posY = Py0;

	angle2 += 0.05f;
}



#pragma region コンストラクタ・デストラクタ
EnemyBullet::EnemyBullet()
{
	color = GetColor(255, 255, 255);
	transform.x = 0;
	transform.y = 0;
	transform.xr = 8;
	transform.yr = 8;
	vertex.top_left_x = 0;
	vertex.top_left_y = 0;
	vertex.down_left_x = 0;
	vertex.down_left_y = 0;
	vertex.top_right_x = 0;
	vertex.top_right_y = 0;
	vertex.down_right_x = 0;
	vertex.down_right_y = 0;
	reflection_num = 0;
	bullet_flag = false;
	x_speed = 0;
	y_speed = 0;
	angle = 0.0f;
	img = LoadGraph("resouce/bullet.png");

	go_time = 50;
	return_flag = false;

	center_x = 120;
	center_y = 270;
	boomerang_angle = 0.0f;
	boomerang_x_r = 120;
	boomerang_y_r = 270;
	flag = false;
	LoadDivGraph("resouce/boomerang.png", 8, 8, 1, 32, 32, boomerang_img);
	boomerang_anime_timer = 0;
	boomerang_anime = 0;

	reiza = LoadGraph("resouce/reiza.png");
	laser_magnification = 0;
	laser_range = 0;
}

EnemyBullet::~EnemyBullet()
{
}
#pragma endregion

#pragma region Move
void EnemyBullet::Move(int& enemy_type, bool& reflection_flag, Player& player, double& x, double& y, bool& exising_flag, Transform& transform)
{
	if (bullet_flag == true)
	{
		if (enemy_type == 1 || enemy_type == 4 || enemy_type == 10 || enemy_type == 5)
		{
#pragma region 移動
			if ((cos(angle) * x_speed) < 0)
			{
				//座標計算
				vertex.top_left_y = ((int)this->transform.y - this->transform.yr) / 32;
				vertex.down_left_y = ((int)this->transform.y + this->transform.yr - 1) / 32;

				vertex.top_left_x = (int)(((double)this->transform.x - this->transform.xr) + (cos(angle) * x_speed)) / 32;
				vertex.down_left_x = (int)(((double)this->transform.x - this->transform.xr) + (cos(angle) * x_speed)) / 32;

				//判定
				if (GetMap(vertex.top_left_x, vertex.top_left_y) == 0 &&
					GetMap(vertex.down_left_x, vertex.down_left_y) == 0)
				{
					this->transform.x += (cos(angle) * x_speed);
				}
				else
				{
					vertex.top_left_x = ((int)this->transform.x - this->transform.xr) / 32;
					vertex.down_left_x = ((int)this->transform.x - this->transform.xr) / 32;

					if (GetMap(vertex.top_left_x, vertex.top_left_y) == 0 &&
						GetMap(vertex.down_left_x, vertex.down_left_y) == 0)
					{
						while (1)//隙間埋め
						{
							vertex.top_left_x = (((int)this->transform.x - this->transform.xr) - 1) / 32;
							vertex.down_left_x = (((int)this->transform.x - this->transform.xr) - 1) / 32;

							if (GetMap(vertex.top_left_x, vertex.top_left_y) == 0 &&
								GetMap(vertex.down_left_x, vertex.down_left_y) == 0)
							{
								if (x_speed < 0)
								{
									this->transform.x += (cos(angle) * -1);
								}
								else
								{
									this->transform.x += (cos(angle) * 1);
								}
							}
							else
							{
								if (reflection_flag == true)
								{
									x_speed = -(x_speed);
									reflection_num++;
								}
								else
								{
									bullet_flag = false;
									reflection_num = 0;
								}
								break;
							}
						}
					}
					else
					{
						x_speed = -(x_speed);
						reflection_num++;
					}
				}
			}
			else if ((cos(angle) * x_speed) > 0)
			{
				//座標計算
				vertex.top_right_y = ((int)this->transform.y - this->transform.yr) / 32;
				vertex.down_right_y = ((int)this->transform.y + this->transform.yr - 1) / 32;

				vertex.top_right_x = (int)((this->transform.x + this->transform.xr - 1) + (cos(angle) * x_speed)) / 32;
				vertex.down_right_x = (int)((this->transform.x + this->transform.xr - 1) + (cos(angle) * x_speed)) / 32;

				//判定
				if (GetMap(vertex.top_right_x, vertex.top_right_y) == 0 &&
					GetMap(vertex.down_right_x, vertex.down_right_y) == 0)
				{
					this->transform.x += (cos(angle) * x_speed);
				}
				else
				{
					vertex.top_right_x = ((int)this->transform.x + this->transform.xr - 1) / 32;
					vertex.down_right_x = ((int)this->transform.x + this->transform.xr - 1) / 32;

					if (GetMap(vertex.top_right_x, vertex.top_right_y) == 0 &&
						GetMap(vertex.down_right_x, vertex.down_right_y) == 0)
					{
						while (1)//隙間埋め
						{
							vertex.top_right_x = (((int)this->transform.x + this->transform.xr - 1) + 1) / 32;
							vertex.down_right_x = (((int)this->transform.x + this->transform.xr - 1) + 1) / 32;

							if (GetMap(vertex.top_right_x, vertex.top_right_y) == 0 &&
								GetMap(vertex.down_right_x, vertex.down_right_y) == 0)
							{
								if (x_speed < 0)
								{
									this->transform.x += (cos(angle) * -1);
								}
								else
								{
									this->transform.x += (cos(angle) * 1);
								}
							}
							else
							{
								if (reflection_flag == true)
								{
									x_speed = -(x_speed);
									reflection_num++;
								}
								else
								{
									bullet_flag = false;
									reflection_num = 0;
								}
								break;
							}
						}
					}
				}
			}

			if ((sin(angle) * y_speed) < 0)
			{
				//座標計算
				vertex.top_left_x = ((int)this->transform.x - this->transform.xr) / 32;
				vertex.top_right_x = ((int)this->transform.x + this->transform.xr - 1) / 32;

				vertex.top_left_y = (int)((this->transform.y - this->transform.yr) + (sin(angle) * y_speed)) / 32;
				vertex.top_right_y = (int)((this->transform.y - this->transform.yr - 1) + (sin(angle) * y_speed)) / 32;

				//判定
				if (GetMap(vertex.top_left_x, vertex.top_left_y) == 0 &&
					GetMap(vertex.top_right_x, vertex.top_right_y) == 0)
				{
					this->transform.y += (sin(angle) * y_speed);
				}
				else
				{
					vertex.top_left_y = ((int)this->transform.y - this->transform.yr) / 32;
					vertex.top_right_y = ((int)this->transform.y - this->transform.yr - 1) / 32;

					if (GetMap(vertex.top_left_x, vertex.top_left_y) == 0 &&
						GetMap(vertex.top_right_x, vertex.top_right_y) == 0)
					{
						while (1)//隙間埋め
						{
							vertex.top_left_y = (int)((this->transform.y - this->transform.yr) + (sin(angle) * -1)) / 32;
							vertex.top_right_y = (int)((this->transform.y - this->transform.yr - 1) + (sin(angle) * -1)) / 32;

							if (GetMap(vertex.top_left_x, vertex.top_left_y) == 0 &&
								GetMap(vertex.top_right_x, vertex.top_right_y) == 0)
							{
								if (y_speed < 0)
								{
									this->transform.y += (sin(angle) * -1);
								}
								else
								{
									this->transform.y += (sin(angle) * 1);
								}
							}
							else
							{
								if (reflection_flag == true)
								{
									y_speed = -(y_speed);
									reflection_num++;
								}
								else
								{
									bullet_flag = false;
									reflection_num = 0;
								}
								break;
							}
						}
					}
					else
					{
						if (reflection_flag == true)
						{
							y_speed = -(y_speed);
							reflection_num++;
						}
						else
						{
							bullet_flag = false;
							reflection_num = 0;
						}
					}
				}
			}
			else if ((sin(angle) * y_speed) > 0)
			{
				//座標計算
				vertex.down_left_x = ((int)this->transform.x - this->transform.xr) / 32;
				vertex.down_right_x = ((int)this->transform.x + this->transform.xr - 1) / 32;

				vertex.down_left_y = (int)((this->transform.y + this->transform.yr - 1) + (sin(angle) * y_speed)) / 32;
				vertex.down_right_y = (int)((this->transform.y + this->transform.yr - 1) + (sin(angle) * y_speed)) / 32;

				//判定
				if (GetMap(vertex.down_left_x, vertex.down_left_y) == 0 &&
					GetMap(vertex.down_right_x, vertex.down_right_y) == 0)
				{
					this->transform.y += (sin(angle) * y_speed);
				}
				else
				{
					vertex.down_left_y = ((int)this->transform.y + this->transform.yr - 1) / 32;
					vertex.down_right_y = ((int)this->transform.y + this->transform.yr - 1) / 32;

					if (GetMap(vertex.down_left_x, vertex.down_left_y) == 0 &&
						GetMap(vertex.down_right_x, vertex.down_right_y) == 0)
					{
						while (1)//隙間埋め
						{
							vertex.down_left_y = (((int)this->transform.y + this->transform.yr - 1) + 1) / 32;

							vertex.down_right_y = (((int)this->transform.y + this->transform.yr - 1) + 1) / 32;

							if (GetMap(vertex.down_left_x, vertex.down_left_y) == 0 &&
								GetMap(vertex.down_right_x, vertex.down_right_y) == 0)
							{
								if (y_speed > 0)
								{
									this->transform.y += (sin(angle) * 1);
								}
								else
								{
									this->transform.y += (sin(angle) * -1);
								}
							}
							else
							{
								if (reflection_flag == true)
								{
									y_speed = -(y_speed);
									reflection_num++;
								}
								else
								{
									bullet_flag = false;
									reflection_num = 0;
								}

								break;
							}
						}
					}
					else
					{
						if (reflection_flag == true)
						{
							y_speed = -(y_speed);
							reflection_num++;
						}
						else
						{
							bullet_flag = false;
							reflection_num = 0;
						}
					}
				}
			}
#pragma endregion

#pragma region 反射
			if (player.Getreflectionflag() == 1)
			{
				int wey = Box_Line(
					//プレイヤー
					(float)player.GetX() + player.GetReflectionR(), (float)player.GetY() - player.GetReflectionR(),//右上
					(float)player.GetX() - player.GetReflectionR(), (float)player.GetY() - player.GetReflectionR(),//左上

					(float)player.GetX() - player.GetReflectionR(), (float)player.GetY() + player.GetReflectionR(),//左下
					(float)player.GetX() + player.GetReflectionR(), (float)player.GetY() + player.GetReflectionR(),//右下

					//弾
					(float)this->transform.x - this->transform.xr, (float)this->transform.y + this->transform.yr,//左下
					(float)this->transform.x + this->transform.xr, (float)this->transform.y + this->transform.yr,//右下

					(float)this->transform.x - this->transform.xr, (float)this->transform.y - this->transform.yr,//左上
					(float)this->transform.x + this->transform.xr, (float)this->transform.y - this->transform.yr);//右上

				switch (wey)
				{
				case 1:
					y_speed = -(y_speed);
					this->transform.y = (double)player.GetY() - player.GetReflectionR() - this->transform.yr;
					break;

				case 2:
					y_speed = -(y_speed);
					this->transform.y = (double)player.GetY() + player.GetReflectionR() + this->transform.yr;
					break;

				case 3:
					x_speed = -(x_speed);
					this->transform.x = (double)player.GetX() - player.GetReflectionR() - this->transform.xr;
					break;

				case 4:
					x_speed = -(x_speed);
					this->transform.x = (double)player.GetX() + player.GetReflectionR() + this->transform.xr;
					break;
				}
			}
#pragma endregion
		}
		if (enemy_type == 3 || enemy_type == 20)
		{
			if (exising_flag == true)
			{
				boomerang_x_r = 100;
				boomerang_y_r = 250;
				center_x = (float)(transform.x + cos(angle) * boomerang_x_r);
				center_y = (float)(transform.y + sin(angle) * boomerang_y_r);
				if (transform.x - center_x >= 90 && transform.x > center_x)
				{
					center_x = center_x - 130;
					boomerang_y_r = (float)transform.x - center_x + 130.0f;
				}
				else if (center_x - transform.x >= 90 && transform.x < center_x)
				{
					center_x = center_x + 130.0f;
					boomerang_y_r = center_x - (float)transform.x + 130.0f;
				}
				if (boomerang_angle > 26.00)
				{
					bullet_flag = false;
				}
				circularMotionL(this->transform.x, this->transform.y, center_x, center_y, boomerang_y_r, boomerang_x_r, angle, boomerang_angle);
				boomerang_anime_timer++;

				if (boomerang_anime_timer == 8 * 3)
				{
					boomerang_anime_timer = 0;
				}
				boomerang_anime = boomerang_anime_timer / 3;
			}
			else
			{
				if (bullet_flag == true)
				{
					bullet_flag = false;
				}
			}
		}

		if (enemy_type == 6)
		{
			this->transform.x = transform.x;
			this->transform.y = transform.y;
			angle = (float)atan2(transform.y - 482.0, transform.x - 482.0);

			if (laser_magnification < 85)
			{
				laser_magnification+=5;
			}

			laser_range = laser_magnification*16.0;

				if (LaserHitBox(player) == true)
				{
					player.HpSub(1);
				}
		}
	}
	else
	{
		if (enemy_type == 6)
		{
			this->transform.x = transform.x;
			this->transform.y = transform.y;
			angle = (float)atan2(transform.y - 482.0, transform.x - 482.0);
		}
	}
}

void EnemyBullet::Move(int enemy_type, bool reflection_flag)
{
	if (bullet_flag == true)
	{
		if (enemy_type == 1 || enemy_type == 4)
		{
#pragma region 移動
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
								if (reflection_flag == true)
								{
									x_speed = -(x_speed);
									reflection_num++;
								}
								else
								{
									bullet_flag = false;
									reflection_num = 0;
								}
								break;
							}
						}
					}
					else
					{
						x_speed = -(x_speed);
						reflection_num++;
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
								if (reflection_flag == true)
								{
									x_speed = -(x_speed);
									reflection_num++;
								}
								else
								{
									bullet_flag = false;
									reflection_num = 0;
								}
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
								if (reflection_flag == true)
								{
									y_speed = -(y_speed);
									reflection_num++;
								}
								else
								{
									bullet_flag = false;
									reflection_num = 0;
								}
								break;
							}

						}
					}
					else
					{
						if (reflection_flag == true)
						{
							y_speed = -(y_speed);
							reflection_num++;
						}
						else
						{
							bullet_flag = false;
							reflection_num = 0;
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
								if (reflection_flag == true)
								{
									y_speed = -(y_speed);
									reflection_num++;
								}
								else
								{
									bullet_flag = false;
									reflection_num = 0;
								}

								break;

							}

						}
					}
					else
					{
						if (reflection_flag == true)
						{
							y_speed = -(y_speed);
							reflection_num++;
						}
						else
						{
							bullet_flag = false;
							reflection_num = 0;
						}
					}

				}
			}
#pragma endregion
		}
	}
}
#pragma endregion


void EnemyBullet::TutorialMove(int y)
{
	if (bullet_flag == true)
	{
		transform.y += y_speed;

		if (transform.y + 56 + y_speed > y)
		{
			y_speed = -y_speed;
		}
	}
}

#pragma region Draw
//描画
void EnemyBullet::Draw(int enemy_type, int shot_time, bool fast_move_flag, bool exising_flag)
{
	if (enemy_type == 6 && shot_time < 50 && fast_move_flag == false && exising_flag == true)
	{

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 90);
		DrawRotaGraph3((int)transform.x, (int)transform.y, 16, 5, 85.0, 1.0, angle, reiza, true, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	if (bullet_flag == true)
	{
		if (enemy_type == 1 || enemy_type == 10 || enemy_type == 4 || enemy_type == 5)
		{
			DrawGraph((int)transform.x - transform.xr, (int)transform.y - transform.yr, img, true);
		}
		if (enemy_type == 3 || enemy_type == 20)
		{
			DrawGraph((int)transform.x - transform.xr, (int)transform.y - transform.yr, boomerang_img[boomerang_anime], true);
		}
		if (enemy_type == 6)
		{
			DrawRotaGraph3((int)transform.x, (int)transform.y, 16, 5, laser_magnification, 1.0, angle, reiza, true, true);
		}
	}
}
#pragma endregion

#pragma region Form
//生成
void EnemyBullet::Form(Transform transform, Player& player, int x_speed, int y_speed, int& enemy_type)
{
	bullet_flag = true;
	this->transform.x = transform.x;
	this->transform.y = transform.y;
	go_time = 50;
	return_flag = false;
	flag = false;

	if (player.Getstelsflag() == 0)
	{
		angle = (float)atan2(player.GetY() - this->transform.y, player.GetX() - this->transform.x);
	}
	else
	{
		int rand = GetRand(1);
		int rand2 = GetRand(1);
		int X;
		int Y;
		if (rand == 1)
		{
			X = 128;
		}
		else
		{
			X = -128;
		}

		if (rand2 == 1)
		{
			Y = 128;
		}
		else
		{
			Y = -128;
		}

		angle = (float)atan2((double)player.GetY() + Y - this->transform.y, (double)player.GetX() + X - this->transform.x);
	}

	this->x_speed = x_speed;
	this->y_speed = y_speed;

	if (enemy_type == 3 || enemy_type == 20)
	{
		boomerang_x_r = 100;
		boomerang_y_r = 250;

		center_x = (float)(transform.x + cos(angle) * boomerang_x_r);
		center_y = (float)(transform.y + sin(angle) * boomerang_y_r);

		if (transform.x - center_x >= 90 && transform.x > center_x)
		{
			boomerang_y_r = (float)transform.x - center_x + 130.0f;
		}

		if (center_x - transform.x >= 90 && transform.x < center_x)
		{
			boomerang_y_r = center_x - (float)transform.x + 130.0f;
		}

		if (angle <= -2.335 && angle > -3.14)
		{
			boomerang_angle = 3.85f;//
		}
		else if (angle > -2.355 && angle < -1.57)
		{
			boomerang_angle = 3.90f;//
		}
		else if (angle >= -1.57 && angle < -0.785)
		{
			boomerang_angle = 2.75;//
		}
		else if (angle < 0 && angle >= -0.785)
		{
			boomerang_angle = 2.95f;//
		}
		else if (angle > 0 && angle <= 0.785)
		{
			boomerang_angle = 3.95f;//
		}
		else if (angle > 0.785 && angle <= 1.57)
		{
			boomerang_angle = 3.74f;//
		}
		else if (angle > 1.57 && angle <= 2.335)
		{
			boomerang_angle = 2.75f;//
		}
		else if (angle > 2.335 && angle <= 3.14)
		{
			boomerang_angle = 2.85f;//
		}
	}
}

void EnemyBullet::OmniFormHex(Transform transform, Player& player, int x_speed, int y_speed, int& enemy_type, int num, float angle)
{
	bullet_flag = true;
	this->transform.x = transform.x;
	this->transform.y = transform.y;
	go_time = 50;
	return_flag = false;
	flag = false;

	if (num == 0)
	{
		this->angle = (float)atan2(player.GetY() - this->transform.y, player.GetX() - this->transform.x);
	}
	else
	{
		this->angle = angle + (float)((DX_PI * 2 / 16) * num);
	}
	this->x_speed = x_speed;
	this->y_speed = y_speed;
}

void EnemyBullet::OmniFormOct(Transform transform, Player& player, int x_speed, int y_speed, int& enemy_type, int num, float angle)
{
	bullet_flag = true;
	this->transform.x = transform.x;
	this->transform.y = transform.y;
	go_time = 50;
	return_flag = false;
	flag = false;

	if (num == 0)
	{
		this->angle = (float)atan2(player.GetY() - this->transform.y, player.GetX() - this->transform.x);
	}
	else
	{
		this->angle = angle + (float)((DX_PI * 2 / 8) * num);
	}
	this->x_speed = x_speed;
	this->y_speed = y_speed;
}
void EnemyBullet::TuTorialForm(Transform transform, int x, int y, int x_speed, int y_speed, int stelsflag)
{
	bullet_flag = true;
	this->transform.x = transform.x;
	this->transform.y = transform.y;
	if (stelsflag == 0)
	{
		angle = (float)atan2(y - this->transform.y, x - this->transform.x);
	}
	else
	{
		angle = (float)atan2(y - this->transform.y, x + 64.0 - this->transform.x);
	}

	this->x_speed = x_speed;
	this->y_speed = y_speed;
}
#pragma endregion

#pragma region ゲッター

Vertex EnemyBullet::GetVertex()
{
	return vertex;
}

Transform* EnemyBullet::GetTransform()
{
	return &transform;
}

bool* EnemyBullet::GetBulletFlag()
{
	return &bullet_flag;
}

int EnemyBullet::GetReflectionNum()
{
	return reflection_num;
}

float EnemyBullet::GetAngle()
{
	return angle;
}



#pragma endregion

#pragma region セッター

void EnemyBullet::SetReflectionNum(int reflection_num)
{
	this->reflection_num = reflection_num;
}

void EnemyBullet::SetBulletFlag(bool bullet_flag)
{
	this->bullet_flag = bullet_flag;
}

bool EnemyBullet::LaserHitBox(Player player)
{
	VECTOR bommr[4];

	VECTOR vec_player[4][4];

	float cross[4][4];

	float player_left = (float)player.GetX() - player.GetR();
	float player_right = (float)player.GetX() + player.GetR();
	float player_top = (float)player.GetY() - player.GetR();
	float player_down = (float)player.GetY() + player.GetR();

	float left_top_x = ((-laser_range) * cosf(angle) + ((-5.0f) * -sinf(angle)) + (float)transform.x);
	float left_top_y = ((-laser_range) * sinf(angle) + ((-5.0f) * cosf(angle)) + (float)transform.y);

	float right_top_x = ((laser_range) * cosf(angle) + ((-5.0f) * -sinf(angle)) + (float)transform.x);
	float right_top_y = ((laser_range) * sinf(angle) + ((-5.0f) * cosf(angle)) + (float)transform.y);
	float left_down_x = ((-laser_range) * cosf(angle) + ((5.0f) * -sinf(angle)) + (float)transform.x);
	float left_down_y = ((-laser_range) * sinf(angle) + ((5.0f) * cosf(angle)) + (float)transform.y);
	float right_down_x = ((laser_range) * cosf(angle) + ((5.0f) * -sinf(angle)) + (float)transform.x);
	float right_down_y = ((laser_range) * sinf(angle) + ((5.0f) * cosf(angle)) + (float)transform.y);



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

void EnemyBullet::SetAngle(float _angle)
{
	this->angle = _angle;
}
#pragma endregion