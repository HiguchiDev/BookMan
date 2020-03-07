#pragma once
#include "Scene.h"
#include <vector>
#include "SceneNames.h"
#include <memory>

class ScreenMaterial;
class Cursor;
class Motion;
class PlayerDatas;

class StageSelect :
	public Scene
{
private:
	std::shared_ptr<PlayerDatas> _playerDatas;
	std::shared_ptr<Cursor> _cursor;
	std::vector<std::string> _stageNames;
	std::vector<std::shared_ptr<ScreenMaterial>> _books;
	std::vector<std::shared_ptr<Motion>> _motions;
	std::vector<std::string> _difficlutys;
	int _bh;
public:
	void update();
	void finalize();
	StageSelect(std::shared_ptr<PlayerDatas> playerDatas);
	~StageSelect();
};

