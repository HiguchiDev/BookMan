#include "Stairs.h"
#include "Collision.h"
#include "Position.h"
#include "Player.h"
#include "PositionConverter.h"
#include "MessgeBox.h"

Stairs::Stairs(std::string fileName, std::shared_ptr<Position> position) : FieldMaterial(fileName, position)
{
	this->_playerCollision = false;
}


Stairs::~Stairs()
{

}

void Stairs::initializePosition()
{
	Collision::getInstance()->add(shared_from_this(), this->_position);
	this->_position->updateHeight(1, shared_from_this());
}

std::shared_ptr<Stairs> Stairs::createStairs(std::string fileName, std::shared_ptr<Position> position)
{
	if (fileName == "Stairs"){
		return std::make_shared<Stairs>("Stairs.pmd", position);
	}
	else if (fileName == "StairsCracker"){
		return std::make_shared<Stairs>("StairsCracker.pmd", position);
	}
	else if (fileName == "Stairskoke"){
		return std::make_shared<Stairs>("StairsCracker.pmd", position);
	}
	else{
		return nullptr;
	}
}

void Stairs::updateCollisionInformation(std::shared_ptr<Position> newPosition)
{
	//Collision::update(shared_from_this(), newPosition);
}

void Stairs::checkPlayerCollision(std::shared_ptr<Character> player)
{
	if (player == nullptr){
		
	}
	else if(!this->_playerCollision){
		if (player->getPos()->getRow() == this->_position->getRow() &&
			player->getPos()->getColumn() == this->_position->getColumn() &&
			player->getPos()->getHeight() == this->_position->getHeight()){
			this->_playerCollision = true;
			MessgeBox::getInstance()->add("ŠK’i‚ðŒ©‚Â‚¯‚½I@ŽŸ‚ÌŠK‚Öi‚Ý‚Ü‚·");
		}
	}
}

void Stairs::action()
{
	PositionConverter converter;
	this->_screenMaterial->setPosition(converter.get3DPosition(this->_position));
	this->_screenMaterial->draw();
}

bool Stairs::isPlayerCollision()
{
	return this->_playerCollision;
}