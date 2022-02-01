#include "DxLib.h"
#include "Title.h"
#include <math.h>

double easeOutSine(double x)
{
	return sin((x * 3.14) / 2);
}

Title::Title()
{
	//タイトルの変数
	title_easeX1 = 0;
	title_easeX2 = 0;
	title_easeX3 = 0;
	title_easeX4 = 0;

	title_easeY1 = 0;
	title_easeY2 = 0;
	title_easeY3 = 0;
	title_easeY4 = 0;

	title1_Frame = 0;
	title2_Frame = 0;
	title1_EndFrame = 50;
	title2_EndFrame = 50;

	title1_start = -1376;
	title2_start = 1376;
	title1_end = 0;
	title2_end = 0;

	 title1_flag = 0;
	 title2_flag = 0;

	 title_flag_A = 0;
	 title_flag_B = 0;

	 Bright = 0;
	 BrightLine = 50;
	 BrightFlag = 0;
	 LineFlag = true;

	 BlendNum = 0;
	 BlendNum2 = 0;
	 BlendFlag = 0;
	 BlendFlag2 = 0;

	 titleTime = 0;

	 //Title
	 Title1 = LoadGraph("resouce/Title1.png");
	 Title2 = LoadGraph("resouce/Title2.png");
	 Title3 = LoadGraph("resouce/Title3.png");
	 TitleBg = LoadGraph("resouce/TitleBg.png");
	 TitleName = LoadGraph("resouce/Hide_og_Sigra.png");
	 Push_A = LoadGraph("resouce/Push_A.png");
}

void Title::title()
{

	if (titleTime < 250)
	{
		titleTime++;
	}

	//イージング処理1
	if (title1_flag == 0 && title2_flag == 0 && title_flag_A == 0 && title_flag_B == 0)
	{
		title1_flag = 1;
		title1_Frame = 0;
	}
	if (title1_flag == 1)
	{
		title_flag_A = 1;
		title1_Frame++;
	}
	if (title1_Frame == title1_EndFrame)
	{
		title1_flag = 0;
	}

	//イージング処理2
	if (title1_flag == 0 && title2_flag == 0 && titleTime > 70 && title_flag_A == 1 && title_flag_B == 0)
	{
		title2_flag = 1;
		title2_Frame = 0;
	}

	if (title2_flag == 1)
	{
		title_flag_B = 1;
		title2_Frame++;
	}

	if (title2_Frame == title2_EndFrame)
	{
		title2_flag = 0;
	}

	//目の光る処理
	if (titleTime > 150 && BrightFlag == 0)
	{
		BrightFlag = 1;
	}

	if (BrightFlag == 1)
	{
		LineFlag = true;
		BrightLine -= 1;
	}

	if (BrightLine < -1)
	{
		BrightFlag = 0;
		BrightLine = -1;
	}

	if (BrightFlag == 0)
	{
		LineFlag = false;
	}

	if (titleTime > 150)
	{
		Bright += 10;
	}

	if (Bright == 256)
	{
		Bright = 255;
	}

	//背景のフラッシュ
	if (titleTime == 140 && BlendFlag == 0)
	{
		BlendNum = 255;
		BlendFlag = 1;
	}

	if (BlendFlag == 1)
	{
		BlendNum -= 10;
	}

	if (BlendNum < 0)
	{
		BlendNum = 0;
		BlendFlag = 0;
	}

	if (titleTime == 250)
	{
		BlendFlag2 = 1;
	}

	if (BlendFlag2 == 1)
	{
		BlendNum2 += 2;
	}

	if (BlendNum > 255)
	{
		BlendNum2 = 255;
		BlendFlag2 = 0;
	}

	title_easeX4 = title1_start + (title1_end - title1_start) * easeOutSine(title1_Frame / title1_EndFrame); //ヘルメット
	title_easeX2 = title2_start + (title2_end - title2_start) * easeOutSine(title2_Frame / title2_EndFrame); //影

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, BlendNum2);
	DrawGraph((int)title_easeX1, (int)title_easeY1, TitleBg, true); //背景色
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, BlendNum2);

	DrawGraph((int)title_easeX2, (int)title_easeY2, Title3, true); //影

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, Bright);
	DrawGraph((int)title_easeX3, (int)title_easeY3, Title2, true); //目

	if (LineFlag == true)
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, Bright);
		DrawLine((int)title_easeX3 - 1376, (int)title_easeY3 + 240,
			(int)title_easeX3 + 1376, (int)title_easeY3 + 240,
			GetColor(255, 255, 255), BrightLine); //目の横ライン
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, BlendNum);
	DrawBox(0, 0, 1376, 960, GetColor(255, 255, 255), true); //フラッシュ用
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, BlendNum);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, Bright);
	DrawGraph((int)title_easeX4, (int)title_easeY4, Title1, true); //ヘルメット

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, BlendNum2);
	DrawGraph(775, 550, TitleName, true); //タイトル名
	DrawGraph(860, 700, Push_A, true); //Push_A
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, BlendNum2);
}