#pragma once
/// status animation
struct Md2State
{
	int	startFrame;
	int	endFrame;
	int	fps;
	float currTime;
	float prevTime;
	float interpol;
	int	type;
	int	currFrame;
	int	nextFrame;

};
