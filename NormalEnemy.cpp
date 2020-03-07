#include "NormalEnemy.h"


NormalEnemy::NormalEnemy(std::string characterName, std::string characterFileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController) : Enemy(characterFileName, position, turnController)
{
	this->_characterName = characterFileName;

	this->_characterName2 = characterName;
	this->_characterDatas = std::make_shared<CharacterData>(characterName);

	this->_characterDatas->dataRead();

	this->_TYPE = CharacterType::CharacterTypes::ENEMY;	//キャラクタータイプはENEMY
}


NormalEnemy::~NormalEnemy()
{

}
