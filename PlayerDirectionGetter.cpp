#include "PlayerDirectionGetter.h"
#include "DxLib.h"

PlayerDirectionGetter::PlayerDirectionGetter()
{
}


PlayerDirectionGetter::~PlayerDirectionGetter()
{
}

Direction::Directions PlayerDirectionGetter::get(Direction::Directions CAMERADIRECTION, MoveType::MoveTypes CHARACTERMOVETYPE)
{
	if (CAMERADIRECTION == Direction::Directions::EAST){
		if (CHARACTERMOVETYPE == MoveType::MoveTypes::RIGHT){
			return Direction::Directions::SOUTH;
		}
		else if (CHARACTERMOVETYPE == MoveType::MoveTypes::LEFT){
			return Direction::Directions::NORTH;
		}
		else if (CHARACTERMOVETYPE == MoveType::MoveTypes::UP){
			return Direction::Directions::EAST;
		}
		else if (CHARACTERMOVETYPE == MoveType::MoveTypes::DOWN){
			return Direction::Directions::WEST;
		}
		else if (CHARACTERMOVETYPE == MoveType::MoveTypes::LEFTLOWER){
			return Direction::Directions::WESTNORTH;
		}
		else if (CHARACTERMOVETYPE == MoveType::MoveTypes::LEFTUPPER){
			return Direction::Directions::EASTNORTH;
		}
		else if (CHARACTERMOVETYPE == MoveType::MoveTypes::RIGHTLOWER){
			return Direction::Directions::WESTSOUTH;
		}
		else if (CHARACTERMOVETYPE == MoveType::MoveTypes::RIGHTUPPER){
			return Direction::Directions::EASTSOUTH;
		}
	}
	else if (CAMERADIRECTION == Direction::Directions::WEST){
		if (CHARACTERMOVETYPE == MoveType::MoveTypes::RIGHT){
			return Direction::Directions::NORTH;
		}
		else if (CHARACTERMOVETYPE == MoveType::MoveTypes::LEFT){
			return Direction::Directions::SOUTH;
		}
		else if (CHARACTERMOVETYPE == MoveType::MoveTypes::UP){
			return Direction::Directions::WEST;
		}
		else if (CHARACTERMOVETYPE == MoveType::MoveTypes::DOWN){
			return Direction::Directions::EAST;
		}
		else if (CHARACTERMOVETYPE == MoveType::MoveTypes::LEFTLOWER){
			return Direction::Directions::EASTSOUTH;
		}
		else if (CHARACTERMOVETYPE == MoveType::MoveTypes::LEFTUPPER){
			return Direction::Directions::WESTSOUTH;
		}
		else if (CHARACTERMOVETYPE == MoveType::MoveTypes::RIGHTLOWER){
			return Direction::Directions::EASTNORTH;
		}
		else if (CHARACTERMOVETYPE == MoveType::MoveTypes::RIGHTUPPER){
			return Direction::Directions::WESTNORTH;
		}
	}
	else if (CAMERADIRECTION == Direction::Directions::NORTH){
		if (CHARACTERMOVETYPE == MoveType::MoveTypes::RIGHT){
			return Direction::Directions::EAST;
		}
		else if (CHARACTERMOVETYPE == MoveType::MoveTypes::LEFT){
			return Direction::Directions::WEST;
		}
		else if (CHARACTERMOVETYPE == MoveType::MoveTypes::UP){
			return Direction::Directions::NORTH;
		}
		else if (CHARACTERMOVETYPE == MoveType::MoveTypes::DOWN){
			return Direction::Directions::SOUTH;
		}
		else if (CHARACTERMOVETYPE == MoveType::MoveTypes::LEFTLOWER){
			return Direction::Directions::WESTSOUTH;
		}
		else if (CHARACTERMOVETYPE == MoveType::MoveTypes::LEFTUPPER){
			return Direction::Directions::WESTNORTH;
		}
		else if (CHARACTERMOVETYPE == MoveType::MoveTypes::RIGHTLOWER){
			return Direction::Directions::EASTSOUTH;
		}
		else if (CHARACTERMOVETYPE == MoveType::MoveTypes::RIGHTUPPER){
			return Direction::Directions::EASTNORTH;
		}
	}
	else if (CAMERADIRECTION == Direction::Directions::SOUTH){
		if (CHARACTERMOVETYPE == MoveType::MoveTypes::RIGHT){
			return Direction::Directions::WEST;
		}
		else if (CHARACTERMOVETYPE == MoveType::MoveTypes::LEFT){
			return Direction::Directions::EAST;
		}
		else if (CHARACTERMOVETYPE == MoveType::MoveTypes::UP){
			return Direction::Directions::SOUTH;
		}
		else if (CHARACTERMOVETYPE == MoveType::MoveTypes::DOWN){
			return Direction::Directions::NORTH;
		}
		else if (CHARACTERMOVETYPE == MoveType::MoveTypes::LEFTLOWER){
			return Direction::Directions::EASTNORTH;
		}
		else if (CHARACTERMOVETYPE == MoveType::MoveTypes::LEFTUPPER){
			return Direction::Directions::EASTSOUTH;
		}
		else if (CHARACTERMOVETYPE == MoveType::MoveTypes::RIGHTLOWER){
			return Direction::Directions::WESTNORTH;
		}
		else if (CHARACTERMOVETYPE == MoveType::MoveTypes::RIGHTUPPER){
			return Direction::Directions::WESTSOUTH;
		}
	}
	else{
		return Direction::COUNT;
	}

	return Direction::COUNT;
}