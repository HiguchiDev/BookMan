#pragma once
#include "Animation.h"
#include <memory>

class BezierCurve_ThreePoint;

class WarpAnimation :
	public Animation
{
private:
	bool _warped;
	std::shared_ptr<BezierCurve_ThreePoint> _bezierCurveXY;
	std::shared_ptr<BezierCurve_ThreePoint> _bezierCurveXZ;
public:
	std::shared_ptr<Animation> getNextAnimation(float speed);
	void start(VECTOR pos, VECTOR destinationPos, float speed);
	void update();
	WarpAnimation();
	~WarpAnimation();
};

