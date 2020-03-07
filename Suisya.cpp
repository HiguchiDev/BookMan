#include "Suisya.h"


Suisya::Suisya(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController) : Enemy(fileName, position, turnController)
{
	this->_characterName = "Suisya";
	this->_characterDatas = std::make_shared<CharacterData>(this->_characterName);
	this->_characterDatas->dataRead();

}


Suisya::~Suisya()
{
}
