#pragma once

#include <memory>
#include <vector>
#include "Item.h"

class Scene;
class PlayerDatas;
class BlackScreen;
class Trap;
class Obstalce;
class Item;

class SceneUpdater
{
private:
	std::shared_ptr<BlackScreen> _blackScreen;
	std::shared_ptr<Scene> _activeScene;
	std::vector<std::shared_ptr<Scene>> _gameScenes;
	std::shared_ptr<PlayerDatas> _playerDatas;
	static std::shared_ptr<SceneUpdater> _instance;
	std::string _activeStageName;
	std::shared_ptr<Scene> _activeStage;
	
	bool _finish = false;

public:
	static void create(){ _instance = std::make_shared<SceneUpdater>(); };
	SceneUpdater();
	void addStageMaterial(std::shared_ptr<Trap> trap);
	void addStageMaterial(std::shared_ptr<Item> item);
	bool isFinish(){ return this->_finish; };
	void update();
	std::string getActiveStageName();
	static std::shared_ptr<SceneUpdater> getInstance();
	~SceneUpdater();
};

