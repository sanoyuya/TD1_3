#pragma once

class Title
{
private:
	//ƒ^ƒCƒgƒ‹‚Ì•Ï”
	double title_easeX1;
	double title_easeX2;
	double title_easeX3;
	double title_easeX4;

	double title_easeY1;
	double title_easeY2;
	double title_easeY3;
	double title_easeY4;

	double title1_Frame;
	double title2_Frame;
	double title1_EndFrame;
	double title2_EndFrame;

	double title1_start;
	double title2_start;
	double title1_end;
	double title2_end;

	int title1_flag;
	int title2_flag;

	int title_flag_A;
	int title_flag_B;

	int Bright;
	int BrightLine;
	int BrightFlag;
	bool LineFlag;

	int BlendNum;
	int BlendNum2;
	int BlendFlag;
	int BlendFlag2;

	int titleTime;

	int Title1;
	int Title2;
	int Title3;
	int TitleBg;
	int TitleName;
	int Push_A;

public:
	void title();
	Title();
};