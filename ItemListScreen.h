#pragma once
#include "Scene.h"
#include <memory>
#include <vector>
#include <string>

class PlayerDatas;
class Cursor;

class ItemListScreen
	: public Scene
{
private:
	int _menuBackHandle;
	int _screenLimit;
	int _explanatoryTextHandle;
	float _itemNameInterval_x;
	float _itemNameInterval_y;
	std::shared_ptr<Cursor> _cursor;
public:
	void update();
	void finalize();
	ItemListScreen(std::shared_ptr<PlayerDatas> playerDatas);
	~ItemListScreen();
};

