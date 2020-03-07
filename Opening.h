#pragma once
#include "Scene.h"
#include "ScreenMaterial.h"
#include <vector>
#include <string>
#include <unordered_map>

class Cursor;

class Opening
	: public Scene
{
private:
	std::unordered_map<std::string, std::string> _nextSceneNameMap;
	std::shared_ptr<Cursor> _cursor;
	std::vector<std::string> _menu;
	std::shared_ptr<ScreenMaterial>_openingTitle;
	VECTOR _position;
	int _bh;
	float _menuDistanceRow;
	float _menuDistanceColumn;
	float _stringPositionX;
	float _openingTitlePosx;
public:
	void update();
	void finalize();
	Opening();
	~Opening();
};

