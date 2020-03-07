#include "FloorOfTheDungeon.h"
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


FloorOfTheDungeon::FloorOfTheDungeon(std::string floorFileName, std::shared_ptr<Stairs> stairs, std::vector< std::shared_ptr<Character> > enemys, std::shared_ptr< Character > player, std::vector< std::shared_ptr<Obstacle> > obstacles, std::vector< std::shared_ptr<Floor>> floors, std::vector<std::shared_ptr<Item>> items, std::vector<std::shared_ptr<Trap>> traps, std::shared_ptr<TurnController> turnController)
{
	this->_floorHandle = LoadGraph(floorFileName.c_str());

	this->_traps = traps;
	this->_enemys = enemys;
	this->_floors = floors;
	this->_obstacles = obstacles;
	this->_player = player;
	this->_turnController = turnController;
	this->_stairs = stairs;
	this->_finish = false;
	this->_items = items;
	this->_allInitialized = false;

	this->_transparency = 255;
	this->_value = 3;


	this->_next = false;
	this->_messageHandle = LoadGraph("メッセージ画面.png");
}


void FloorOfTheDungeon::addStageMaterial(std::shared_ptr<Trap> trap)
{
	this->_traps.push_back(trap);
}

void FloorOfTheDungeon::addStageMaterial(std::shared_ptr<Item> item)
{
	this->_items.push_back(item);
}

FloorOfTheDungeon::~FloorOfTheDungeon()
{
}

void FloorOfTheDungeon::initialize()
{

	//if (!_player->isInitialized()){
	_player->initialize();
	//}
	for (std::shared_ptr<Character> enemy : _enemys){
		enemy->initialize();
	}

	for (std::shared_ptr<Obstacle> obstacle : _obstacles){
		obstacle->initialize();
	}
	for (auto item : this->_items){
		item->initialize();
	}
	for (auto trap : this->_traps){
		trap->initialize();
	}

	_stairs->initialize();
}

bool FloorOfTheDungeon::isInitialized()
{

	if (this->_allInitialized == false){
		bool enemyInitialize = false;
		bool obstacleInitialize = false;
		bool floorInitialize = false;

		for (std::shared_ptr<Obstacle> obstacle : _obstacles){
			obstacleInitialize = true;
			if (!obstacle->isInitialized()){
				obstacleInitialize = false;
				break;
			}
		}

		for (std::shared_ptr<Floor> floor : _floors){
			floorInitialize = true;
			if (!floor->isLoadCompetion()){
				floorInitialize = false;
				break;
			}
		}

		for (std::shared_ptr<Character> enemy : _enemys){
			enemyInitialize = true;
			if (!enemy->isInitialized()){
				enemyInitialize = false;
				break;
			}
		}
		if (_enemys.empty()){
			enemyInitialize = true;
		}
		if (_obstacles.empty()){
			obstacleInitialize = true;
		}
		if (_floors.empty()){
			floorInitialize = true;
		}

		if (enemyInitialize && obstacleInitialize && floorInitialize){
			this->_allInitialized = true;
		}
	}

	return this->_allInitialized && this->_player->isInitialized();
}

void FloorOfTheDungeon::finalize()
{

	for (auto enemy : this->_enemys){
		enemy->finalize();
	}

	for (auto obstacle : this->_obstacles){
		obstacle->finalize();
	}

	for (auto trap : this->_traps){
		trap->finalize();
	}

	for (auto item : this->_items){
		item->finalize();
	}

	this->_stairs->finalize();

	Collision::getInstance()->removeAll();
}

bool FloorOfTheDungeon::isFinish()
{
	/*if (this->_stairs->isPlayerCollision()){
		for (auto enemy : this->_enemys){
		enemy->finalize();
		}

		for (auto obstacle : this->_obstacles){
		obstacle->finalize();
		}

		for (auto trap : this->_traps){
		trap->finalize();
		}

		for (auto item : this->_items){
		item->finalize();
		}

		this->_stairs->finalize();

		Collision::getInstance()->removeAll();
		}*/

	return this->_stairs->isPlayerCollision() && !MessgeBox::getInstance()->isDisplay();


}


void FloorOfTheDungeon::start(int key, std::string message)
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

		this->_next = false;


		if (!this->_stairs->isPlayerCollision()){
			if (!MessgeBox::getInstance()->isDisplay()){
				if (this->_turnController->isMyTurn(CharacterType::CharacterTypes::PLAYER)){
					if (Key::getInstance()->getHitFlame(key) == 1 && _player->isFree()){
						_player->action(key);
						this->_next = true;
					}

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


	DrawGraph(0, 600, this->_messageHandle, TRUE);
	DrawString(300, 650, message.c_str(), GetColor(255, 255, 0), TRUE);

	

}


void FloorOfTheDungeon::start()
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


		if (!this->_stairs->isPlayerCollision()){
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