#pragma once
#include "DxLib.h"
#include <memory>

class Animation 
	: public std::enable_shared_from_this<Animation>
{
protected:
	VECTOR _pos;
	VECTOR _destinationPos;
	bool _finish;
	float _speed;
public:
	void finalize();
	virtual std::shared_ptr<Animation> getNextAnimation(float speed);
	bool isFinish();
	virtual void start(VECTOR pos, VECTOR destinationPos, float speed);
	virtual void update() = 0;
	VECTOR getPos();
	Animation();
	~Animation();
};

