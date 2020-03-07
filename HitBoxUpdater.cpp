#include "HitBoxUpdater.h"
#include "HitBox.h"
#include "DxLib.h"

HitBoxUpdater::HitBoxUpdater()
{
}


HitBoxUpdater::~HitBoxUpdater()
{
}

void HitBoxUpdater::add(std::shared_ptr<HitBox> hitBox)
{
	this->_hitBoxs.push_back(hitBox);
}

bool HitBoxUpdater::isEmpty()
{
	return this->_hitBoxs.empty();
}

std::shared_ptr<HitBoxUpdater> HitBoxUpdater::_instance;

void HitBoxUpdater::update()
{
	for (int i = 0; i < this->_hitBoxs.size(); i++){
		this->_hitBoxs[i]->action();

		if (this->_hitBoxs[i]->isFinish()){
			this->_hitBoxs.erase(this->_hitBoxs.begin() + i);
			if (i > 0){
				i--;
			}
		}
	}
}