#include "SpringThrowType.h"
#include "Trap.h"
#include "Collision.h"
#include "SceneUpdater.h"
#include "MessgeBox.h"
#include "PlayerDatas.h"
#include "Position.h"

SpringThrowType::SpringThrowType()
{
	this->_name = "ワープ";
	this->_explanatoryText = "踏むと、ランダムな場所にワープします。";
}


SpringThrowType::~SpringThrowType()
{
}

bool SpringThrowType::throwAbility(std::shared_ptr<PlayerDatas> playerDatas)
{
	this->_spring = Trap::createInstance("Spring", std::make_shared<Position>(Collision::getInstance()->getPlayerPos()->getRow(), Collision::getInstance()->getPlayerPos()->getColumn(), 1));


	MessgeBox::getInstance()->add("バネを投げた！");
	playerDatas->addThrowTrap(this->_spring);
	SceneUpdater::getInstance()->addStageMaterial(this->_spring);

	return true;
}

void SpringThrowType::use(std::shared_ptr<PlayerDatas> playerDatas)
{
	this->_spring = Trap::createInstance("Spring", std::make_shared<Position>(Collision::getInstance()->getPlayerPos()->getRow(), Collision::getInstance()->getPlayerPos()->getColumn(), 1));


	MessgeBox::getInstance()->add("バネを置いた！");
	this->_spring->initialize();
	SceneUpdater::getInstance()->addStageMaterial(this->_spring);
}