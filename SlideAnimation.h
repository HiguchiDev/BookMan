#pragma once
#include "Animation.h"
class SlideAnimation :
	public Animation
{
private:
public:
	void update();
	float getUpdatedPosition(float pos, float newPos, float speed);
	SlideAnimation(float speed);
	~SlideAnimation();
};

