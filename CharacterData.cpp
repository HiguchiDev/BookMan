#include "CharacterData.h"


CharacterData::CharacterData(std::string chractername)
{
	this->_characterName = chractername;

	this->_statesPoint = std::make_shared<StatesPoint>();	//テスト用

}

CharacterData::~CharacterData()
{
}

std::shared_ptr<StatesPoint> CharacterData::getStatesPoint()
{
	return this->_statesPoint;
}

void CharacterData::dataRead()
{
	this->_statesPoint->load(this->_characterName);
}