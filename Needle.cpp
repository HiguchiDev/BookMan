#include "Needle.h"
#include "Character.h"
#include "ScreenMaterial.h"
#include "CharacterData.h"
#include "WarpAnimation.h"
#include "PositionConverter.h"
#include "Collision.h"
#include "DxLib.h"
#include "FieldLength.h"
#include "Collision.h"
#include "HitBox.h"
#include "MessgeBox.h"

Needle::Needle(std::string fileName, std::shared_ptr<Position> position) : Trap(fileName, position)
{
}


Needle::~Needle()
{
}

void Needle::according(std::shared_ptr<CharacterData> characterData, std::shared_ptr<Character> character)
{
	this->_visible = true;
	if (character->getType() == CharacterType::ENEMY){
		Collision::getInstance()->add(std::make_shared<HitBox>(character->getPos(), CharacterType::PLAYER, characterData->getStatesPoint()->getStatesPoint(State::HPMAX) / 4), character->getPos());
	}
	else{
		Collision::getInstance()->add(std::make_shared<HitBox>(character->getPos(), CharacterType::ENEMY, characterData->getStatesPoint()->getStatesPoint(State::HPMAX) / 4), character->getPos());
		
	}

	std::string message = character->getName() + " ‚Í j‚ÌŽR‚É‚Ð‚Á‚©‚©‚Á‚Ä‚µ‚Ü‚Á‚½I";
	MessgeBox::getInstance()->add(message);
}