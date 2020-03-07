#include "TreasureChest.h"
#include "Collision.h"
#include "Item.h"
#include "MessgeBox.h"
#include "ScreenMaterial.h"
#include "SceneUpdater.h"
#include "Motion.h"
#include "PositionConverter.h"

TreasureChest::TreasureChest(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<Item> item) : Obstacle("TreasureChest/TreasureChest.pmd", position)
{
	this->_item = item;

	this->_motion = std::make_shared<Motion>(this->_screenMaterial->getHandle(), Action::ATTACK, Action::ATTACK, 1.7f);

}


TreasureChest::~TreasureChest()
{
}

void TreasureChest::action()
{
	this->draw();
	if (this->_open){
		this->_motion->update();

		if (this->_motion->isMotionFinish(Action::ATTACK)){
			this->_finish = true;
			this->_visible = false;
		}
	}

	//PositionConverter pc;
	//pc.get3DPosition(this->_position).y;
}

bool TreasureChest::beExamined()
{
	MessgeBox::getInstance()->add("‚½‚©‚ç‚Î‚±@‚ð@‚ ‚¯‚½I");

	SceneUpdater::getInstance()->addStageMaterial(this->_item);

	this->_motion->start(false, Action::ATTACK);
	this->_open = true;

	return true;
}

std::shared_ptr<Item> TreasureChest::getChangedItem()
{
	return  this->_item;
}