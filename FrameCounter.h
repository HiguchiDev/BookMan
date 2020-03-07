#pragma once
class FrameCounter
{
private:
	int _count;
public:
	void update();
	int getCount();
	void reset();
	FrameCounter();
	~FrameCounter();
};

