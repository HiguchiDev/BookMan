#pragma once
#include "Effect.h"
#include "ScreenMaterial.h"
#include <vector>
#include <memory>
#include "BezierCurve.h"
#include "PositionConverter.h"

class ExpEffect :
	public Effect
{
private:
	PositionConverter _pc;
	std::vector<std::shared_ptr<ScreenMaterial>> _materials;
	std::vector<std::shared_ptr<BezierCurve_ThreePoint>> _beziers;
	std::vector<std::shared_ptr<BezierCurve_ThreePoint>> _beziersZ;
public:
	void setPos(VECTOR position);
	void update();
	void start();
	void finalize();
	ExpEffect();
	~ExpEffect();
};

