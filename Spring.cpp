#include "Spring.h"
#include "Character.h"
#include "ScreenMaterial.h"
#include "CharacterData.h"
#include "WarpAnimation.h"
#include "PositionConverter.h"
#include "Collision.h"
#include "DxLib.h"
#include "FieldLength.h"
#include "MessgeBox.h"

Spring::Spring(std::string fileName, std::shared_ptr<Position> position) : Trap(fileName, position)
{
}


Spring::~Spring()
{
}

void Spring::according(std::shared_ptr<CharacterData> characterData, std::shared_ptr<Character> character)
{

	this->_visible = true;

	std::shared_ptr<WarpAnimation> warpAnimation = std::make_shared<WarpAnimation>();

	PositionConverter pc;

	std::shared_ptr<Position> newPos;
	newPos = std::make_shared<Position>(GetRand(FieldLength::_ROW - 1), GetRand(FieldLength::_COLUMN - 1), 1);

	while (Collision::getInstance()->isMovableTrapIncluding(character, newPos) == false){
		newPos = std::make_shared<Position>(GetRand(FieldLength::_ROW - 1), GetRand(FieldLength::_COLUMN - 1), 1);
	}
	
	std::string message = character->getName() + "‚Íƒoƒl‚Å”ò‚Î‚³‚ê‚½I";

	MessgeBox::getInstance()->add(message);
	
	warpAnimation->start(pc.get3DPosition(character->getPos()), pc.get3DPosition(newPos), 0.01f);
	character->setFieldPos(newPos);
	character->getScreenMaterial()->setAnimation(warpAnimation);
	character->updateCollisionInformation(newPos);
	


}