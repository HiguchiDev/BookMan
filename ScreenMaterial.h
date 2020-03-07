#pragma once
#include "DxLib.h"
#include <string>
#include <memory>
class Animation;

class ScreenMaterial
{
protected:
	std::shared_ptr<Animation> _animation;
	std::string _fileName;
	VECTOR _position;
	bool _visible;
	bool _finish;
	bool _loadCompletion;
	float _angle;
	int _handle;
public:
	virtual void finalize() = 0;
	virtual void draw() = 0;

	int getHandle();
	bool isFinish();
	
	float getAngle();
	virtual bool isCameraIn(){ return true; };
	void initializePos(VECTOR position);
	bool isLoadCompletion();
	VECTOR ScreenMaterial::getPosition();
	bool isVisible();
	void setVisible(bool visible);
	void setAnimation(std::shared_ptr<Animation> animation);
	virtual void animation(VECTOR newPos, float speed) = 0;
	virtual bool isAnimationFinish() = 0;
	virtual void rotate(float angle) = 0;
	virtual void setPosition(VECTOR position) = 0;
	ScreenMaterial(std::string fileName);
	~ScreenMaterial();
};