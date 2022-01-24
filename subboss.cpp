#include<DxLib.h>
#include"enemy.h"
#include"subboss.h"
#include"Transform.h"
#include"map.h"
#include<math.h>



#pragma region 生成

//ファイルオープンして
//ファイルポインタを受け取って各変数に代入する
//EOFになったら残りの変数はすべて0を代入

//メイン
void SubBossForm(const char* file_name, int max, SubBoss& sub_boss)
{
	FILE* fp;
	fopen_s(&fp, file_name, "r");

	if (fp != NULL)
	{
		sub_boss.form(fp);
		fclose(fp);
	}
}

void SubBoss::form(FILE* fp)
{
	if (fscanf_s(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%lf,%lf,%lf,%lf,%d,%d,%d,%d,%d,%d,%d"
		, &enemy_type, &appear_time, &shot_time, &hp, &transform.xr, &transform.yr, &bullet_x_speed, &bullet_y_speed, &x_speed, &y_speed, &end_frame, &start_x, &start_y, &end_x, &end_y, &move_time, &move_end_frame,
		&mime_initialize.transform_xr, &mime_initialize.transform_yr, &mime_initialize.explosion_r, &mime_initialize.def_explosion_time, &mime_initialize.def_bombs_time)
		!= EOF)
	{
		mine->initialize(mime_initialize);
	}
	else
	{
		enemy_type = 0;
		transform.xr = 0;
		transform.yr = 0;
		hp = 0;
		bullet_x_speed = 0;
		bullet_y_speed = 0;
		shot_time = 0;
		end_frame = 0;
		start_x = 0;
		end_x = 0;
		end_y = 0;
		appear_time = 0;
		move_time = 0;
		move_end_frame = 0;

		mime_initialize.transform_yr = 0;
		mime_initialize.transform_xr = 0;
		mime_initialize.def_bombs_time = 0;
		mime_initialize.def_explosion_time = 0;
		mime_initialize.explosion_r = 0;
	}

	transform.x = start_x;
	transform.y = start_y;
	exising_flag = false;
	damage_flag[0] = false;
	damage_flag[1] = false;
	damage_flag[2] = false;
	damage_flag[3] = false;
	fast_move_flag = false;

	move_flag = false;
	frame = 0;
	move_num = 0;
	move_frame = 0;

	def_move_time = move_time;
	def_shot_time = shot_time;

	anticipation = 50;
	teleport_flag = false;
}
#pragma endregion

#pragma region 動き

//出現時間時間を減らし0になったら最初の移動をする
//弾を打ったてすべて消えた後に移動する
//地雷と弾の動きをする

void SubBoss::Move(Player& player, bool reflection_flag)
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
		//if (enemy_type == 1)
		{
			if (exising_flag == true)
			{
				//最初の移動
				if (fast_move_flag == true)
				{
					frame++;
					//イージング
					transform.x = start_x + (end_x - start_x) * easeInSine((double)frame / (double)end_frame);
					transform.y = start_y + (end_y - start_y) * easeInSine((double)frame / (double)end_frame);

					if (frame == end_frame)
					{
						fast_move_flag = false;
					}
				}

				//移動
				if (fast_move_flag == false)
				{
					if (enemy_type == 1 && move_time == 1)
					{
						//地雷設置フラフを立てる
						mine->SetMineFlag(true);
						mine->SetRand(7);
					}

					if (enemy_type == 3 && move_time == 1)
					{
						rand = GetRand(7);
					}

					if (move_time > 0)
					{
						move_time--;
					}

					if (move_time == 0)
					{
						move_flag = true;

						int rand2 = GetRand(7);

						if (enemy_type == 3 && rand == rand2)
						{
							move_flag = false;
							teleport_flag = true;
						}
					}

#pragma region 移動
					if (move_flag == true)
					{
						if (move_frame == 0)
						{
							rand = GetRand(7) + 1;

							if ((int)transform.y == 128)//上
							{
								while (rand == 3 || rand == 5 || rand == 7)
								{
									rand = GetRand(7) + 1;
								}
							}
							else if ((int)transform.y == 864)//下
							{
								while (rand == 4 || rand == 6 || rand == 8)
								{
									rand = GetRand(7) + 1;
								}
							}
							else if ((int)transform.x >= 776)//右
							{
								while (rand == 1 || rand == 5 || rand == 6)
								{
									rand = GetRand(7) + 1;
								}
							}
							else if ((int)transform.x <= 178)//左
							{
								while (rand == 2 || rand == 7 || rand == 8)
								{
									rand = GetRand(7) + 1;
								}
							}
						}

						switch (rand)
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
#pragma endregion

					if (teleport_flag == true)
					{
						if (anticipation > 0)
						{
							anticipation--;
						}

						if (anticipation == 0)
						{
							transform.x = (double)GetRand(560) + 207;
							transform.y = (double)GetRand(576) + 192;
							teleport_flag = false;
							anticipation = 50;
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
					if (enemy_type == 1)
					{
						shot_time = def_shot_time;
					}
					else
					{
						Refresh_ReflectionNum(4);
					}

				}

				//当たり判定
				for (int i = 0; i < bullet_max; i++)
				{
					if (*bullet[i]->GetBulletFlag() == true)
					{

						HitBox(*bullet[i]->GetTransform(), bullet[i], i);
					}
				}

				//弾の生成
				if (shot_time == 0)
				{

					if (enemy_type == 1)
					{
						int k[4] = { 0,0,0,0 };
						bool end = false;
						int i;
						int length = 0;

						for (i = 0; i < 4; i++)
						{
							int j = FlagSerch(bullet, bullet_max);

							if (j != -1)
							{
								bullet[j]->Form(transform, player, bullet_x_speed, bullet_y_speed, enemy_type);
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
					}
					else
					{
						for (int i = 0; i < 4; i++)
						{
							if (*bullet[i]->GetBulletFlag() == false)
							{
								bullet[i]->Form(transform, player, bullet_x_speed, bullet_y_speed, enemy_type);
								damage_flag[i] = true;
								//角度を90度ずつずらす
								bullet[1]->SetAngle(bullet[0]->GetAngle() + (DX_PI_F / 2));
								bullet[2]->SetAngle(bullet[1]->GetAngle() + (DX_PI_F / 2));
								bullet[3]->SetAngle(bullet[2]->GetAngle() + (DX_PI_F / 2));
							}
						}
					}



					shot_time = -1;
				}

				if (hp <= 0)
				{
					exising_flag = false;
				}
			}

			if (enemy_type == 1)
			{
				//地雷の動き
				mine->form(transform, rand);
				mine->HitBox(transform, hp);
			}
		}
	}

	if (enemy_type == 1)
	{
		mine->Move();
	}

	for (int i = 0; i < bullet_max; i++)
	{
		//弾の動き
		bullet[i]->Move(enemy_type, reflection_flag, player, transform.x, transform.y, exising_flag, transform);
	}

	if (enemy_type == 1)
	{
		boss1_anime_timer++;

		if (boss1_anime_timer == 14 * 6)
		{
			boss1_anime_timer = 0;
		}

		boss1_anime = boss1_anime_timer / 6;
	}
}
#pragma endregion

#pragma region 描画

//存在フラグが立っていたら描画する
//弾と地雷を描画する
//デバック

void SubBoss::Draw()
{
	if (exising_flag == true)
	{
		if (enemy_type == 1 || enemy_type == 3)
		{

			DrawGraphF((float)transform.x - img_r, (float)transform.y - img_r, boss1_img[boss1_anime], true);
			
			if (teleport_flag == true)
			{
				DrawBox((float)transform.x - img_r, (float)transform.y - img_r, (float)transform.x + img_r, (float)transform.y + img_r, GetColor(255, 255, 255), true);
			}
		}
	}

	for (int i = 0; i < bullet_max; i++)
	{
		bullet[i]->Draw(enemy_type);

		if (bullet[i]->GetReflectionNum() >= 3)
		{
			bullet[i]->SetBulletFlag(false);
			bullet[i]->SetReflectionNum(0);
		}
	}

	mine->Draw();

	DrawFormatString(0, 100, GetColor(255, 255, 255), "sub_boss hp:%d", hp);
	DrawFormatString(0, 120, GetColor(255, 255, 255), "sub_boss move_num:%d", move_num);
	DrawFormatString(0, 140, GetColor(255, 255, 255), "move_time :%d", move_time);
	DrawFormatString(500, 160, GetColor(255, 255, 255), "x:%lf", transform.x);
	DrawFormatString(0, 180, GetColor(255, 255, 255), "y:%lf", transform.y);
}
#pragma endregion

#pragma region 当たり判定

//bullet_flagが立っていたら判定をする
//ダメージフラグがfalseなら体力を減らし
//各種フラグを代入

void SubBoss::HitBox(Transform& transform, EnemyBullet* enemyBullet, int i)
{
	if (*enemyBullet->GetBulletFlag() == true)
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
					enemyBullet->SetBulletFlag(false);
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

void SubBoss::HP(Transform& transform, EnemyBullet& enemyBullet)
{
	//当たり判定(複数)
	if (*enemyBullet.GetBulletFlag() == true && exising_flag == true)
	{
		if (this->transform.x - this->transform.xr < transform.x + transform.xr &&
			this->transform.x + this->transform.xr > transform.x - transform.xr)
		{
			if (this->transform.y - this->transform.yr < transform.y + transform.yr &&
				this->transform.y + this->transform.yr > transform.y - transform.yr)
			{
				hp -= 1;
				enemyBullet.SetBulletFlag(false);

				if (hp <= 0)
				{
					exising_flag = false;
				}

			}
		}
	}
}


#pragma endregion

#pragma region 当たり判定付き移動

void SubBoss::XMove(int x_speed, bool right_flag)
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

void SubBoss::YMove(int y_speed, bool up_flag)
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

void SubBoss::MineHit(Transform transform, int& hp, bool damage_flag)
{
	mine->HitBox(transform, hp, damage_flag);
}

void SubBoss::PlayerMineHit(Player& player)
{
	mine->PlayerHitBox(player);
}
#pragma endregion

#pragma region 反射回数初期化

//bullet_flagがすべてfalseだったら
//全ての反射回数を0にして
//移動フラグを立てる

void SubBoss::Refresh_ReflectionNum(int max)
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

#pragma region ゲッター
Transform* SubBoss::GetBulletTransform(int num)
{
	return bullet[num]->GetTransform();
}

EnemyBullet* SubBoss::GetEnmyBullet(int i)
{
	return bullet[i];
}

bool SubBoss::GetEnmyBulletFlag(int i)
{
	return *bullet[i]->GetBulletFlag();
}

bool SubBoss::GetSubBossFlag()
{
	return exising_flag;
}

int SubBoss::GetAppearTime()
{
	return appear_time;
}

int SubBoss::GetBulletMax()
{
	return bullet_max;
}

void SubBoss::SetMineExplosion()
{
	mine->SetExplosionTime(1);
}

#pragma endregion

#pragma region コントラスタ・デストラクタ

SubBoss::SubBoss()
{
	enemy_type = 0;//敵のタイプ
	//座標
	transform.x = 0;
	transform.y = 0;
	transform.xr = 0;
	transform.yr = 0;

	//頂点
	vertex.top_left_x = 0;
	vertex.top_left_y = 0;
	vertex.down_left_x = 0;
	vertex.down_left_y = 0;
	vertex.top_right_x = 0;
	vertex.top_right_y = 0;
	vertex.down_right_x = 0;
	vertex.down_right_y = 0;

	hp = 0;//体力
	bullet_x_speed = 0;//弾のX座標のスピード
	bullet_y_speed = 0;//弾のY座標のスピード
	x_speed = 0;//X座標のスピード
	y_speed = 0;//Y座標のスピード
	exising_flag = false;//存在フラグ
	damage_flag[0] = false;
	damage_flag[1] = false;
	damage_flag[2] = false;
	damage_flag[3] = false;
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
	move_end_frame = 0;

	//初期値
	def_move_time = move_time;
	def_shot_time = shot_time;

	for (int i = 0; i < 12; i++)
	{
		bullet[i] = new EnemyBullet;
	}

	mine = new Mine;

	mime_initialize.transform_yr = 0;
	mime_initialize.transform_xr = 0;
	mime_initialize.def_bombs_time = 0;
	mime_initialize.def_explosion_time = 0;
	rand = 0;

	anticipation = 50;
	teleport_flag = false;
	LoadDivGraph("resouce/boss1.png", 14, 14, 1, 128, 128, boss1_img);
	boss1_anime_timer = 0;
	boss1_anime = 0;
	img_r = 64;

	bullet_max = 12;

}

SubBoss::~SubBoss()
{
	delete mine;

	for (int i = 0; i < bullet_max; i++)
	{
		delete bullet[i];
	}

}
#pragma endregion

