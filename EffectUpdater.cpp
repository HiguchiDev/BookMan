#include "EffectUpdater.h"
#include "Effect.h"
#include "EffekseerForDXLib.h"
#include "MessgeBox.h"

EffectUpdater::EffectUpdater()
{
	this->_dammyHandle = LoadGraph("Health.png");
}


EffectUpdater::~EffectUpdater()
{
}

bool EffectUpdater::isEffectRegeneration()
{
	return !this->_effects.empty();
}

void EffectUpdater::add(std::shared_ptr<Effect> effect)
{
	this->_effects.push_back(effect);
	
}

void EffectUpdater::update()
{
	
	// Effekseerにより再生中のエフェクトを更新する。
	DrawGraph(-400, -400, this->_dammyHandle, TRUE);

	if (!MessgeBox::getInstance()->isDisplay()){	Effekseer_Sync3DSetting();
	UpdateEffekseer3D();
	DrawEffekseer3D();
		for (int i = 0; i < (signed)this->_effects.size(); i++){
			
			this->_effects[i]->update();

			if (this->_effects[i]->isEnd()){
				this->_effects.erase(this->_effects.begin() + i);
				i--;
			}
		}
	}


}

std::shared_ptr<EffectUpdater> EffectUpdater::_instance;

std::shared_ptr<EffectUpdater> EffectUpdater::getInstance()
{
	if (_instance == nullptr){
		_instance = std::make_shared<EffectUpdater>();
	}

	return _instance;
}