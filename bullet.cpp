#include"bullet.h"
#include"enemy.h"
#include"DxLib.h"
#include"map.h"
#include<math.h>

#pragma region ���˗p

int EnemyBullet::Box_Line(float start_x, float start_y, float start2_x, float start2_y, float start3_x, float start3_y, float start4_x, float start4_y, float point1_x, float point1_y, float point2_x, float point2_y, float point3_x, float point3_y, float point4_x, float point4_y)
{

	//��
	if (LineAndLine(start_x, start_y, start2_x, start2_y,
		start3_x, start3_y, start4_x, start4_y,
		point1_x, point1_y, point2_x, point2_y) == true &&
		LineAndLine(start2_x, start2_y, start3_x, start3_y,
			start4_x, start4_y, start_x, start_y,
			point1_x, point1_y, point2_x, point2_y) == true)
	{
		return 1;
	}

	//��
	if (LineAndLine(start_x, start_y, start2_x, start2_y,
		start3_x, start3_y, start4_x, start4_y,
		point3_x, point3_y, point4_x, point4_y) == true &&
		LineAndLine(start2_x, start2_y, start3_x, start3_y,
			start4_x, start4_y, start_x, start_y,
			point3_x, point3_y, point4_x, point4_y) == true)
	{
		return 2;
	}

	//��
	if (LineAndLine(start2_x, start2_y, start3_x, start3_y,
		start4_x, start4_y, start_x, start_y,
		point2_x, point2_y, point4_x, point4_y) == true &&
		LineAndLine(start_x, start_y, start2_x, start2_y,
			start3_x, start3_y, start4_x, start4_y,
			point2_x, point2_y, point4_x, point4_y) == true)
	{
		return 3;
	}

	//�E
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

	VECTOR vec_line;		//�@���C���n�_���烉�C���I�_�܂ł̃x�N�g��
	VECTOR line_vec_point1;		//�@���C���n�_����|�C���g�܂ł̃x�N�g��
	VECTOR line_vec_point2;		//�@���C���n�_����|�C���g�܂ł̃x�N�g��

	//�@�O�ς̒l
	float  line_cross1;
	float  line_cross2;

	VECTOR vec_line2;		//�@���C���n�_���烉�C���I�_�܂ł̃x�N�g��
	VECTOR line2_vec_point1;		//�@���C���n�_����|�C���g�܂ł̃x�N�g��
	VECTOR line2_vec_point2;		//�@���C���n�_����|�C���g�܂ł̃x�N�g��

	//�@�O�ς̒l
	float  line2_cross1;
	float  line2_cross2;

	//���C���̃x�N�g��
	vec_line = VGet(end_x - start_x, end_y - start_y, 0.0);

	//���K��
	vec_line = VNorm(vec_line);

	//  ���C���̎n�_����J�[�\���܂ł̃|�C���g���
	line_vec_point1 = VGet(point1_x - start_x, point1_y - start_y, 0);
	line_vec_point2 = VGet(point2_x - start_x, point2_y - start_y, 0);

	line_vec_point1 = VNorm(line_vec_point1);
	line_vec_point2 = VNorm(line_vec_point2);

	//  �ϐ����g���ĊO�ς��v�Z���ĕϐ�cross�Ɋi�[
	line_cross1 = (vec_line.x * line_vec_point1.y) - (vec_line.y * line_vec_point1.x);
	line_cross2 = (vec_line.x * line_vec_point2.y) - (vec_line.y * line_vec_point2.x);

	//���C���̃x�N�g��
	vec_line2 = VGet(end2_x - start2_x, end2_y - start2_y, 0.0);

	//���K��
	vec_line2 = VNorm(vec_line2);

	//  ���C���̎n�_����J�[�\���܂ł̃x�N�g�����
	line2_vec_point1 = VGet(point1_x - start2_x, point1_y - start2_y, 0);
	line2_vec_point2 = VGet(point2_x - start2_x, point2_y - start2_y, 0);

	line2_vec_point1 = VNorm(line2_vec_point1);
	line2_vec_point2 = VNorm(line2_vec_point2);

	//  �ϐ����g���ĊO�ς��v�Z���ĕϐ�cross�Ɋi�[
	line2_cross1 = (vec_line2.x * line2_vec_point1.y) - (vec_line2.y * line2_vec_point1.x);
	line2_cross2 = (vec_line2.x * line2_vec_point2.y) - (vec_line2.y * line2_vec_point2.x);

	DrawFormatString(300, 115, GetColor(255, 255, 255), "%f ", line_cross1);
	DrawFormatString(300, 135, GetColor(255, 255, 255), "%f ", line_cross2);
	DrawFormatString(300, 155, GetColor(255, 255, 255), "%f ", line2_cross1);
	DrawFormatString(300, 175, GetColor(255, 255, 255), "%f ", line2_cross2);

	//  �ϐ�cross�̒l�ō��E�̔���
	//  (�J�[�\�������C�����E�������𕶎��ŕ\��)
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

#pragma region �R���X�g���N�^�E�f�X�g���N�^
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
}

EnemyBullet::~EnemyBullet()
{
}
#pragma endregion

#pragma region Move
void EnemyBullet::Move(int enemy_type, bool reflection_flag, Player& player)
{
	if (bullet_flag == true)
	{
		if (enemy_type == 1)
		{
#pragma region �ړ�
			if ((cos(angle) * x_speed) < 0)
			{
				//���W�v�Z
				vertex.top_left_y = ((int)transform.y - transform.yr) / 32;
				vertex.down_left_y = ((int)transform.y + transform.yr - 1) / 32;

				vertex.top_left_x = (int)(((double)transform.x - transform.xr) + (cos(angle) * x_speed)) / 32;
				vertex.down_left_x = (int)(((double)transform.x - transform.xr) + (cos(angle) * x_speed)) / 32;

				//����
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
						while (1)//���Ԗ���
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
				//���W�v�Z
				vertex.top_right_y = ((int)transform.y - transform.yr) / 32;
				vertex.down_right_y = ((int)transform.y + transform.yr - 1) / 32;

				vertex.top_right_x = (int)((transform.x + transform.xr - 1) + (cos(angle) * x_speed)) / 32;
				vertex.down_right_x = (int)((transform.x + transform.xr - 1) + (cos(angle) * x_speed)) / 32;

				//����
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
						while (1)//���Ԗ���
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
				//���W�v�Z
				vertex.top_left_x = ((int)transform.x - transform.xr) / 32;
				vertex.top_right_x = ((int)transform.x + transform.xr - 1) / 32;

				vertex.top_left_y = (int)((transform.y - transform.yr) + (sin(angle) * y_speed)) / 32;
				vertex.top_right_y = (int)((transform.y - transform.yr - 1) + (sin(angle) * y_speed)) / 32;

				//����
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
						while (1)//���Ԗ���
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
				//���W�v�Z
				vertex.down_left_x = ((int)transform.x - transform.xr) / 32;
				vertex.down_right_x = ((int)transform.x + transform.xr - 1) / 32;

				vertex.down_left_y = (int)((transform.y + transform.yr - 1) + (sin(angle) * y_speed)) / 32;
				vertex.down_right_y = (int)((transform.y + transform.yr - 1) + (sin(angle) * y_speed)) / 32;

				//����
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
						while (1)//���Ԗ���
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

			if (player.Getreflectionflag() == 1)
			{
				int wey = Box_Line(
					//�v���C���[
					(float)player.GetX() + player.GetReflectionR(), (float)player.GetY() - player.GetReflectionR(),//�E��
					(float)player.GetX() - player.GetReflectionR(), (float)player.GetY() - player.GetReflectionR(),//����

					(float)player.GetX() - player.GetReflectionR(), (float)player.GetY() + player.GetReflectionR(),//����
					(float)player.GetX() + player.GetReflectionR(), (float)player.GetY() + player.GetReflectionR(),//�E��

					//�e
					(float)transform.x - transform.xr, (float)transform.y + transform.yr,//����
					(float)transform.x + transform.xr, (float)transform.y + transform.yr,//�E��

					(float)transform.x - transform.xr, (float)transform.y - transform.yr,//����
					(float)transform.x + transform.xr, (float)transform.y - transform.yr);//�E��

				switch (wey)
				{
				case 1:
					y_speed = -(y_speed);
					transform.y = (double)player.GetY() - player.GetReflectionR() - transform.yr;
					break;

				case 2:
					y_speed = -(y_speed);
					transform.y = (double)player.GetY() + player.GetReflectionR() + transform.yr;
					break;

				case 3:
					x_speed = -(x_speed);
					transform.x = (double)player.GetX() - player.GetReflectionR() - transform.xr;
					break;

				case 4:
					x_speed = -(x_speed);
					transform.x = (double)player.GetX() + player.GetReflectionR() + transform.xr;
					break;
				}

			}
		}

	}
}
void EnemyBullet::Move(int enemy_type, bool reflection_flag)
{
	if (bullet_flag == true)
	{
		if (enemy_type == 1)
		{
#pragma region �ړ�
			if ((cos(angle) * x_speed) < 0)
			{
				//���W�v�Z
				vertex.top_left_y = ((int)transform.y - transform.yr) / 32;
				vertex.down_left_y = ((int)transform.y + transform.yr - 1) / 32;

				vertex.top_left_x = (int)(((double)transform.x - transform.xr) + (cos(angle) * x_speed)) / 32;
				vertex.down_left_x = (int)(((double)transform.x - transform.xr) + (cos(angle) * x_speed)) / 32;

				//����
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
						while (1)//���Ԗ���
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
				//���W�v�Z
				vertex.top_right_y = ((int)transform.y - transform.yr) / 32;
				vertex.down_right_y = ((int)transform.y + transform.yr - 1) / 32;

				vertex.top_right_x = (int)((transform.x + transform.xr - 1) + (cos(angle) * x_speed)) / 32;
				vertex.down_right_x = (int)((transform.x + transform.xr - 1) + (cos(angle) * x_speed)) / 32;

				//����
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
						while (1)//���Ԗ���
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
				//���W�v�Z
				vertex.top_left_x = ((int)transform.x - transform.xr) / 32;
				vertex.top_right_x = ((int)transform.x + transform.xr - 1) / 32;

				vertex.top_left_y = (int)((transform.y - transform.yr) + (sin(angle) * y_speed)) / 32;
				vertex.top_right_y = (int)((transform.y - transform.yr - 1) + (sin(angle) * y_speed)) / 32;

				//����
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
						while (1)//���Ԗ���
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
				//���W�v�Z
				vertex.down_left_x = ((int)transform.x - transform.xr) / 32;
				vertex.down_right_x = ((int)transform.x + transform.xr - 1) / 32;

				vertex.down_left_y = (int)((transform.y + transform.yr - 1) + (sin(angle) * y_speed)) / 32;
				vertex.down_right_y = (int)((transform.y + transform.yr - 1) + (sin(angle) * y_speed)) / 32;

				//����
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
						while (1)//���Ԗ���
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
//�`��
void EnemyBullet::Draw()
{
	if (bullet_flag == true)
	{
		DrawGraph((int)transform.x - transform.xr, (int)transform.y - transform.yr, img, true);

	}
}
#pragma endregion

#pragma region Form
//����
void EnemyBullet::Form(Transform transform, Player& player, int x_speed, int y_speed)
{
	bullet_flag = true;
	this->transform.x = transform.x;
	this->transform.y = transform.y;
	angle = (float)atan2(player.GetY() - this->transform.y, player.GetX() - this->transform.x);
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

#pragma region �Q�b�^�[

Vertex EnemyBullet::GetVertex()
{
	return vertex;
}

Transform EnemyBullet::GetTransform()
{
	return transform;
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

#pragma region �Z�b�^�[

void EnemyBullet::SetReflectionNum(int reflection_num)
{
	this->reflection_num = reflection_num;
}

void EnemyBullet::SetBulletFlag(bool bullet_flag)
{
	this->bullet_flag = bullet_flag;
}

void EnemyBullet::SetAngle(float _angle)
{
	this->angle = _angle;
}
#pragma endregion


