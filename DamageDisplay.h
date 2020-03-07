#pragma once
#include <vector>
#include <unordered_map>
#include "DxLib.h"
#include <memory>
#include "BezierCurve.h"

class Position;

class DamageDisplay
{
private:
	BezierCurve_ThreePoint _bezierCurve;
	std::vector<std::shared_ptr<Position>> _damegePositions;
	std::unordered_map<std::shared_ptr<Position>, int> _damegeValueMap;
	std::unordered_map<std::shared_ptr<Position>, std::shared_ptr<BezierCurve_ThreePoint>> _damegePositionValueMap;
	static std::unique_ptr<DamageDisplay> _instance;
public:
	void add(std::shared_ptr<Position> pos, int damage);
	static void create(){ _instance = std::make_unique<DamageDisplay>(); };
	void update();
	static std::unique_ptr<DamageDisplay>& getInstance();
	DamageDisplay();
	~DamageDisplay();
};

