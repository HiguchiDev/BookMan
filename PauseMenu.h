#pragma once
#include "Scene.h"
#include <memory>
#include <vector>

class Cursor;

class PauseMenu
	: public Scene
{
private:
	std::shared_ptr<Cursor> _cursor;
	std::vector<std::string> _menuNames;
	std::vector<std::string> _names;
	int _menuBackHandle;
public:
	void update();
	void finalize();
	PauseMenu(std::shared_ptr<PlayerDatas> playerDatas);
	~PauseMenu();
};

