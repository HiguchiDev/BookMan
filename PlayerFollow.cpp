#include "PlayerFollow.h"
#include "Collision.h"

PlayerFollow::PlayerFollow()
{
}


PlayerFollow::~PlayerFollow()
{
}

Direction::Directions PlayerFollow::getFollowDirection(std::shared_ptr<Character> character)
{
	std::shared_ptr<Position> pPos;

	pPos = Collision::getInstance()->getPlayerPos();

	if (pPos != nullptr){
		if (pPos->getRow() > character->getPos()->getRow()){
			if (pPos->getColumn() == character->getPos()->getColumn()){
				return Direction::Directions::SOUTH;
			}
			else if (pPos->getColumn() > character->getPos()->getColumn()){
				return Direction::Directions::EASTSOUTH;
			}
			else if (pPos->getColumn() < character->getPos()->getColumn()){
				return Direction::Directions::WESTSOUTH;
			}
		}
		else if (pPos->getRow() < character->getPos()->getRow()){
			if (pPos->getColumn() == character->getPos()->getColumn()){
				return Direction::Directions::NORTH;
			}
			else if (pPos->getColumn() > character->getPos()->getColumn()){
				return Direction::Directions::EASTNORTH;
			}
			else if (pPos->getColumn() < character->getPos()->getColumn()){
				return Direction::Directions::WESTNORTH;
			}
			
		}
		else if (pPos->getColumn() < character->getPos()->getColumn()){
			return Direction::Directions::WEST;
		}
		else if (pPos->getColumn() > character->getPos()->getColumn()){
			return Direction::Directions::EAST;
		}
	}
}