#include "Mushroom.h"


Mushroom::Mushroom(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController) :Enemy(fileName,position,turnController)
{
	this->_characterName = "Mushroom";
	this->_characterDatas = std::make_shared<CharacterData>(this->_characterName);
	this->_characterDatas->dataRead();
}


Mushroom::~Mushroom()
{
}
