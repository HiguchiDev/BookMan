#include "Obstacle.h"
#include "Object_3D.h"
#include "PositionConverter.h"
#include "Position.h"
#include "Collision.h"
#include <memory>
#include "SaveBook.h"
#include "TreasureChest.h"
#include "Weapon.h"
#include "DropWeapon.h"
#include "Item.h"
#include "WearProtective.h"

Obstacle::Obstacle(std::string fileName, std::shared_ptr<Position> position) : FieldMaterial(fileName, position)
{
}


Obstacle::~Obstacle()
{
}

void Obstacle::action()
{
	this->draw();
}

void Obstacle::initializePosition()
{
	Collision::getInstance()->add(shared_from_this(), this->_position);
	this->_position->updateHeight(1	, shared_from_this());

}


void Obstacle::updateCollisionInformation(std::shared_ptr<Position> newPosition){
	Collision::getInstance()->update(shared_from_this(), newPosition);
	this->_position = newPosition;
}

std::vector<std::string> Obstacle::_obstacleNames;

std::shared_ptr<Obstacle> Obstacle::createObstacle(std::string fileName, std::shared_ptr<Position> position)
{
	if (_obstacleNames.empty()){
		_obstacleNames.push_back("cake");
		_obstacleNames.push_back("strawberry");
		_obstacleNames.push_back("cracker");
		_obstacleNames.push_back("crackerSingle");
		_obstacleNames.push_back("chocolate");
		_obstacleNames.push_back("bigrock");
		_obstacleNames.push_back("beautifulrock");
		_obstacleNames.push_back("table");
		_obstacleNames.push_back("savetableyoko");
		_obstacleNames.push_back("savetabletate");
		_obstacleNames.push_back("savetablecorner");
		_obstacleNames.push_back("savewall");
		_obstacleNames.push_back("tallglass");
		_obstacleNames.push_back("tree");
		_obstacleNames.push_back("cobble");
		_obstacleNames.push_back("woodbox");
		_obstacleNames.push_back("TutorialBlock");
		_obstacleNames.push_back("koke");
	}
	
	std::vector<std::string>::iterator cIter = std::find(_obstacleNames.begin(), _obstacleNames.end(), fileName);

	std::string name = fileName + ".pmd";
	
	if (cIter != _obstacleNames.end()){
		return std::make_shared<Obstacle>(name, position);
	}
	else{
		std::shared_ptr<Item> createdItem = Item::createItem(fileName, position);

		if (createdItem != nullptr){
			createdItem->initialize();
			return std::make_shared<TreasureChest>(name, position, createdItem);
		}
		else{
			return nullptr;
		}
	}
}