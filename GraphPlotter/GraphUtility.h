#pragma once
#include "olcPixelGameEngine.h"

olc::vf2d panOffset;
float zoom;

int graphWindowHeight;
int graphWindowWidth;

float GraphSpaceToPixelSpaceX(float x)
{
	return ((x - panOffset.x) / zoom + 0.5) * graphWindowWidth;
}

float GraphSpaceToPixelSpaceY(float y)
{
	return ((panOffset.y - y) / zoom + 0.5) * graphWindowHeight;
}

olc::vf2d GraphSpaceToPixelSpace(olc::vf2d point)
{
	return olc::vf2d(GraphSpaceToPixelSpaceX(point.x), GraphSpaceToPixelSpaceY(point.y));
}

float ScreenSpaceToGraphSpaceX(float x)
{
	return (-0.5 * zoom + panOffset.x) + x * zoom / graphWindowWidth;
}

float ScreenSpaceToGraphSpaceY(float y)
{

	return (0.5 * zoom + panOffset.y) - y * zoom / graphWindowHeight;
}

olc::vf2d ScreenSpaceToGraphSpace(olc::vf2d point)
{
	return olc::vf2d(ScreenSpaceToGraphSpaceX(point.x), ScreenSpaceToGraphSpaceY(point.y));
}
