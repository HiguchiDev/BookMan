#pragma once
#include <memory>
#include <vector>

class Effect;

class EffectUpdater
{
private:
	std::vector<std::shared_ptr<Effect>> _effects;
	static std::shared_ptr<EffectUpdater> _instance;
	int _time = 0;
	int _dammyHandle;
public:
	static std::shared_ptr<EffectUpdater> getInstance();
	bool isEffectRegeneration();
	void add(std::shared_ptr<Effect> effect);
	static void create(){ _instance = std::make_shared<EffectUpdater>(); };
	void update();
	EffectUpdater();
	~EffectUpdater();
};

