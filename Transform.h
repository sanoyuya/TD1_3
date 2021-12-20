#pragma once

typedef struct {
	double x;
	double y;
	int xr;
	int yr;
} Transform;

typedef struct
{
	int top_right_x;
	int top_right_y;
	int down_right_x;
	int down_right_y;
	int top_left_x;
	int top_left_y;
	int down_left_x;
	int down_left_y;
}Vertex;