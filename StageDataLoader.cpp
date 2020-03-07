#include "StageDataLoader.h"
#include <fstream>
#include "FieldLength.h"
#include "TurnController.h"
#include "PlayerDatas.h"
#include "Position.h"
#include "Stairs.h"
#include "Player.h"
#include "SaveBook.h"

StageDataLoader::StageDataLoader(std::string stageDataName)
{
	this->_stageDataName = stageDataName;
}


StageDataLoader::~StageDataLoader()
{
}

bool StageDataLoader::loadData(int floorIndex, std::shared_ptr<SaveBook> &saveBook, std::vector<std::shared_ptr<Obstacle> >& obstacles, std::vector<std::shared_ptr<Item> >& items, std::vector<std::shared_ptr<Trap> >& traps, std::vector<std::shared_ptr<Character> >& characters, std::shared_ptr<Character> &player, std::shared_ptr<Stairs> &stairs, std::shared_ptr<TurnController> turnController, std::shared_ptr<PlayerDatas> playerDatas)
{
	std::string floorDataName = this->_stageDataName + std::to_string( floorIndex ) + ".csv";

	std::fstream ifs(floorDataName.c_str());
	
	if (!ifs.is_open()) {
		printfDx("StageData‚ğƒ[ƒh‚Å‚«‚Ü‚¹‚ñ‚Å‚µ‚½B\n");
		return false;
	}

	for (int i = 0; i < FieldLength::_ROW; i++){
		for (int j = 0; j < FieldLength::_COLUMN; j++){

			std::string fileName;

			ifs >> fileName;

			if (fileName != "NULL"){
				
				std::shared_ptr<Character> createdCharacter = Character::createCharacter(fileName, std::make_shared<Position>(i, j, 1), turnController);
				if (createdCharacter != nullptr){
					characters.push_back(createdCharacter);
				}

				if (player == nullptr){
					player = Character::createCharacter(fileName, std::make_shared<Position>(i, j, 1), turnController, playerDatas);
				}
				
				std::shared_ptr<Obstacle> createdObstacle = Obstacle::createObstacle(fileName, std::make_shared<Position>(i, j, 1));

				if (createdObstacle != nullptr){
					obstacles.push_back(createdObstacle);
				}

				std::shared_ptr<Trap> createdTrap = Trap::createInstance(fileName, std::make_shared<Position>(i, j, 1));

				if (createdTrap != nullptr){
					traps.push_back(createdTrap);
				}

				if (fileName == "saveBook"){
					saveBook = std::make_shared<SaveBook>("saveBook.pmd", std::make_shared<Position>(i, j, 1));
				}
				
				if (stairs == nullptr){
					stairs = Stairs::createStairs(fileName, std::make_shared<Position>(i, j, 1));
				}



			}
		}
	}

	return true;
}
