#pragma once
#include "Direction.h"
#include <string>
#include "DxLib.h"

class Effect
{
private:
	int _effectHandle;
	int _playingEffectHandle;
	int _time;

protected:
	VECTOR _position;
	bool _finish;
public:
	virtual void setPos(VECTOR position);
	void stop();
	virtual void update();
	virtual void start(Direction::Directions DIRECTION);
	bool isEnd();
	Effect(std::string fileName);
	~Effect();
	virtual void finalize();
};

