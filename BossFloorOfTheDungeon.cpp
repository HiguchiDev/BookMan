#include "BossFloorOfTheDungeon.h"
#include "Character.h"
#include "TurnController.h"
#include "DxLib.h"
#include "LoadScreen.h"
#include "Floor.h"
#include "Obstacle.h"
#include "Stairs.h"
#include "Item.h"
#include "EffectUpdater.h"
#include "MessgeBox.h"
#include "Key.h"
#include "Trap.h"
#include "CharacterData.h"
#include "StatesPoint.h"


BossFloorOfTheDungeon::BossFloorOfTheDungeon(std::string floorFileName, std::shared_ptr<Stairs> stairs, std::vector< std::shared_ptr<Character> > enemys, std::shared_ptr< Character > player, std::vector< std::shared_ptr<Obstacle> > obstacles, std::vector< std::shared_ptr<Floor>> floors, std::vector<std::shared_ptr<Item>> items, std::vector<std::shared_ptr<Trap>> traps, std::shared_ptr<TurnController> turnController, std::shared_ptr<Character> bossCharacter)
	: FloorOfTheDungeon(floorFileName, stairs, enemys, player, obstacles, floors, items, traps, turnController)
{
	this->_bossCharacter = bossCharacter;
}


BossFloorOfTheDungeon::~BossFloorOfTheDungeon()
{

}

bool BossFloorOfTheDungeon::isFinish()
{
	if (this->_bossCharacter != nullptr){
		return this->_bossCharacter->isFinish();

	}
	else{
		return true;
	}
}

void BossFloorOfTheDungeon::start()
{

	if (_player->isInitialized()){



		for (std::shared_ptr<Floor> floor : _floors){
			floor->draw();
		}


		for (int i = 0; i < this->_obstacles.size(); i++){
			this->_obstacles[i]->action();

			if (this->_obstacles[i]->isFinish()){
				//MessgeBox::getInstance()->add("a\na");
				this->_obstacles[i]->finalize();
				this->_obstacles.erase(this->_obstacles.begin() + i);
				i--;
			}

		}


		if (this->_bossCharacter->getCharacterData()->getStatesPoint()->getStatesPoint(State::HITPOINT) > 0){
			if (!MessgeBox::getInstance()->isDisplay()){
				if (this->_turnController->isMyTurn(CharacterType::CharacterTypes::PLAYER)){
					_player->action();


				}
				else if (this->_turnController->isMyTurn(CharacterType::CharacterTypes::ENEMY)){

					for (auto enemy : this->_enemys){
						enemy->action();
					}
				}
			}

		}
		std::vector<std::shared_ptr<Character>>::iterator it = this->_enemys.begin();
		while (it != this->_enemys.end()){
			if (it->get()->isFinish()){
				this->_turnController->setTurnFinishedCharacter(*it);
				it->get()->finalize();
				it = this->_enemys.erase(it);

				if (this->_enemys.empty()){
					break;
				}
			}
			else{
				++it;
			}
		}

	}

	this->_player->update();

	for (auto enemy : _enemys){
		enemy->update();
	}

	if (this->_stairs != nullptr){
		this->_stairs->action();
	}


	for (int i = 0; i < (signed)this->_items.size(); i++){
		this->_items[i]->draw();

		if (this->_items[i]->isFinish()){
			this->_items.erase(this->_items.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < (signed)this->_traps.size(); i++){
		this->_traps[i]->draw();
	}


	if (this->_turnController->isFinish()){
		this->_turnController->initialize(_enemys, _player);
	}


	if (this->_transparency >= 0){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, this->_transparency);

		this->_transparency -= this->_value;




		DrawGraph(0, 0, this->_floorHandle, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}


}