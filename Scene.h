#pragma once
#include <string>
#include <memory>

class PlayerDatas;
class BlackScreen;
class Trap;
class Item;

class Scene
{
protected:
	std::shared_ptr<BlackScreen> _blackScreen;
	bool _finish;
	bool _sceneChange;
	std::string _nextSceneName;
	std::string _changedSceneName;
	std::string _sceneName;
	std::shared_ptr<PlayerDatas> _playerDatas;
public:
	virtual void addStageMaterial(std::shared_ptr<Item> item){};
	virtual void addStageMaterial(std::shared_ptr<Trap> trap){};
	virtual bool isInitialized();
	virtual void initialize();
	virtual void update() = 0;
	bool isChangeScene();
	virtual void returnAction();
	std::string getChangedSceneName();
	std::string getNextSceneName();
	std::string getSceneName();
	bool isFinish();
	virtual void finalize() = 0;
	static std::shared_ptr<Scene> createScene(std::string sceneName, std::shared_ptr<PlayerDatas> playerData);
	Scene();
	~Scene();
};

