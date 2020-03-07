#pragma once
#include <memory>
#include <vector>

class HitBox;

class HitBoxUpdater
{
private:
	static std::shared_ptr<HitBoxUpdater> _instance;
	std::vector<std::shared_ptr<HitBox>> _hitBoxs;
public:
	static std::shared_ptr<HitBoxUpdater> getInstance(){
		if (_instance == nullptr){
			_instance = std::make_shared<HitBoxUpdater>();
		}
		return _instance;
	}

	bool isEmpty();
	static void create(){ _instance = std::make_shared<HitBoxUpdater>(); };
	void add(std::shared_ptr<HitBox> hitBox);
	void update();
	HitBoxUpdater();
	~HitBoxUpdater();
};

