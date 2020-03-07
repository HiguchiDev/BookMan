#include "PlayerKeyConfig.h"
#include "DxLib.h"

PlayerKeyConfig::PlayerKeyConfig()
{
	this->_moveKeyConfig[MoveType::MoveTypes::LEFT] = KEY_INPUT_A;
	this->_moveKeyConfig[MoveType::MoveTypes::RIGHT] = KEY_INPUT_D;
	this->_moveKeyConfig[MoveType::MoveTypes::DOWN] = KEY_INPUT_X;
	this->_moveKeyConfig[MoveType::MoveTypes::UP] = KEY_INPUT_W;

	this->_moveKeyConfig[MoveType::MoveTypes::LEFTLOWER] = KEY_INPUT_Z;
	this->_moveKeyConfig[MoveType::MoveTypes::LEFTUPPER] = KEY_INPUT_Q;

	this->_moveKeyConfig[MoveType::MoveTypes::RIGHTLOWER] = KEY_INPUT_C;
	this->_moveKeyConfig[MoveType::MoveTypes::RIGHTUPPER] = KEY_INPUT_E;

	this->_actionKeyConfig[Action::Actions::ATTACK] = KEY_INPUT_SPACE;
	this->_actionKeyConfig[Action::Actions::EXAMINED] = KEY_INPUT_K;
	this->_actionKeyConfig[Action::Actions::MENUOPEN] = KEY_INPUT_F;
	this->_actionKeyConfig[Action::Actions::DECISION] = KEY_INPUT_SPACE;
	this->_actionKeyConfig[Action::Actions::CANCEL] = KEY_INPUT_M;

	this->_cameraDirectionKeyConfig[Direction::Directions::NORTH] = KEY_INPUT_W;
	this->_cameraDirectionKeyConfig[Direction::Directions::SOUTH] = KEY_INPUT_X;
	this->_cameraDirectionKeyConfig[Direction::Directions::EAST] = KEY_INPUT_D;
	this->_cameraDirectionKeyConfig[Direction::Directions::WEST] = KEY_INPUT_A;

}


PlayerKeyConfig::~PlayerKeyConfig()
{
}

int PlayerKeyConfig::getMoveTypeKey(MoveType::MoveTypes MOVETYPE)
{
	return this->_moveKeyConfig[MOVETYPE];
}

int PlayerKeyConfig::getActionTypeKey(Action::Actions ACTION)
{
	return this->_actionKeyConfig[ACTION];
}

int PlayerKeyConfig::getCameraDirectionKey(Direction::Directions DIRECTION)
{
	return this->_cameraDirectionKeyConfig[DIRECTION];
}

void PlayerKeyConfig::setConfig(int key, Direction::Directions DIRECTION)
{
	this->_cameraDirectionKeyConfig[DIRECTION] = key;
}

void PlayerKeyConfig::setConfig(int key, MoveType::MoveTypes MOVETYPE)
{
	this->_moveKeyConfig[MOVETYPE] = key;
}