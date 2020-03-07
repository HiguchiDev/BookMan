#include "Stage.h"
#include "FieldLength.h"
#include <array>
#include "Obstacle.h"
#include "Player.h"
#include "Enemy.h"
#include "Position.h"
#include "Floor.h"
#include "TurnController.h"
#include "PositionConverter.h"
#include "Stairs.h"
//#include "EffekseerForDXLib.h"
#include "StatesPoint.h"
#include "PlayerDatas.h"
#include "Item.h"
#include "HealthItem.h"
#include "Collision.h"
#include "Key.h"
#include "StageDataLoader.h"
#include "SceneNames.h"
#include <fstream>
#include "BlackScreen.h"
#include "DungeonLength.h"
#include "MessgeBox.h"
#include "Trap.h"
#include "PlayerKeyConfig.h"
#include "SaveBook.h"
#include "SceneUpdater.h"
#include "HitBoxUpdater.h"
#include "DamageDisplay.h"
#include "EffectUpdater.h"
#include "BossFloorOfTheDungeon.h"
#include "HitBoxUpdater.h"
#include "LevelUpper.h"

Stage::Stage(std::shared_ptr<PlayerDatas> playerDatas, std::string stageName)
{
	this->_floorIndex = 0;
	this->_playerDatas = playerDatas;

	Collision::getInstance()->setPlayerDatas(playerDatas);

	this->_stageClearHandle = LoadGraph("StageClear.png");
	this->_gameOverHandle = LoadGraph("GameOver.png");

	this->_time = 0;
	this->_time_gameOver = 0;
	this->_stopX = 1024 / 2 - 580;
	this->_stopX_gameOver = 1024 / 2 - 380;
	this->_x = 1024;
	this->_x_gameOver = 1024;
	this->_y = 764 / 2;
	this->_y_gameOver = 764 / 2;
	this->_stopTime = 100;
	this->_stopTime_gameOver = 100;

	this->_stageName = stageName;
	this->_sceneName = stageName;
	this->_nextSceneName = SceneNames::getName(SceneNames::SceneTypes::STAGESELECT);
	this->_changedSceneName = SceneNames::getName(SceneNames::SceneTypes::ITEMSCREEN);
}

bool Stage::isInitialized()
{
	return this->_blackScreen->isBlackIn() && this->_floorOfTheDungeons != nullptr;
}

void Stage::addStageMaterial(std::shared_ptr<Item> item)
{
	this->_floorOfTheDungeons->addStageMaterial(item);
}

void Stage::addStageMaterial(std::shared_ptr<Trap> trap)
{
	this->_floorOfTheDungeons->addStageMaterial(trap);
}
void Stage::initialize()
{
	if (this->_floorOfTheDungeons == nullptr){
		if (this->_playerDatas->getStageFloor() != this->_floorIndex &&
			this->_playerDatas->getActiveStageName() == this->_stageName){
			this->_floorIndex = this->_playerDatas->getStageFloor();	//直前にプレイヤーが居たフロアを取得		
		}


		if (this->_floorIndex < DungeonLength::FLOORNUM){
			this->initializeFloor();
		}
		else{
			this->_nextSceneName = SceneNames::getName(SceneNames::STAGESELECT);
			if (this->_stageName == SceneNames::getName(SceneNames::HANSELANDGRETELSTAGE)){
				this->_nextSceneName = SceneNames::getName(SceneNames::ENDING);
			}
			this->_finish = true;
			this->_playerDatas->removeStageData();	//これぬかしたらダメッス
		}
	}

	if (this->_floorOfTheDungeons != nullptr && !this->_floorOfTheDungeons->isFinish()){
		this->_blackScreen->in();	//明るくなっていく
	}
}

Stage::~Stage()
{
}

void Stage::finalize()
{




	//this->_playerDatas->setActiveStageName(nullptr);
	this->_playerDatas->setStageFloor(-1);







}

void Stage::returnAction()
{
	if (this->_saveBook != nullptr && this->_saveBook->isSave()){
		this->_saveBook->resetSave();
	}

	this->_sceneChange = false;
	this->_blackScreen = std::make_shared<BlackScreen>();
}

void Stage::update()
{
	DrawGraph(0, 0, handle1, TRUE);
	if (this->_floorOfTheDungeons != nullptr)

	if (this->_floorOfTheDungeons != nullptr && this->_floorOfTheDungeons->isInitialized()){
		this->_floorOfTheDungeons->start();


		if (!this->_finish && !this->_sceneChange && !this->_player->isFinish() && !this->_floorOfTheDungeons->isFinish()){
			if (MessgeBox::getInstance()->isDisplay()){
				if (Key::getInstance()->getHitFlame(this->_playerDatas->getPlayerKeyConfig()->getActionTypeKey(Action::DECISION)) == 1){
					MessgeBox::getInstance()->displayToNextMessage();
				}
			}
			else if (Key::getInstance()->getHitFlame(this->_playerDatas->getPlayerKeyConfig()->getActionTypeKey(Action::MENUOPEN)) == 1 && HitBoxUpdater::getInstance()->isEmpty()){
				this->_sceneChange = true;
				this->_changedSceneName = SceneNames::getName(SceneNames::SceneTypes::PAUSEMENU);
			}


			if (this->_saveBook != nullptr && this->_saveBook->isSave()){
				this->_sceneChange = true;
				this->_changedSceneName = SceneNames::getName(SceneNames::SceneTypes::DATAWRITE);
			}
		}
		else{
			if (this->_floorIndex >= DungeonLength::FLOORNUM - 1 && this->_floorOfTheDungeons->isFinish()){
				DrawGraph(this->_x, 0, this->_stageClearHandle, TRUE);
				if (this->_x >= this->_stopX){
					this->_x -= 50;
				}
				else{
					this->_time++;
			
				}
				
				if(this->_time >= this->_stopTime){
					this->_blackScreen->out();
					if (this->_blackScreen->isBlackOut()){
						this->actionBlackOuted();
					}
				}

			}
			else if (this->_playerDatas->getStatesPoint()->getStatesPoint(State::HITPOINT) <= 0){
				DrawGraph(this->_x_gameOver, this->_y_gameOver, this->_gameOverHandle, TRUE);
				if (this->_x_gameOver >= this->_stopX_gameOver){
					this->_x_gameOver -= 25;
				
				}
				else{
					this->_time_gameOver++;
					
				}

				if (this->_time_gameOver >= this->_stopTime_gameOver){
					this->_blackScreen->out();
					if (this->_blackScreen->isBlackOut()){
						this->actionBlackOuted();
					}
				}
			}
			else{

				this->_blackScreen->out();
				if (this->_blackScreen->isBlackOut()){
					this->actionBlackOuted();
				}

			}
		}

	}
}

void Stage::initializeFloor()
{
	std::vector<std::shared_ptr<Obstacle>> obstacles;
	std::vector<std::shared_ptr<Character>> enemy;
	std::vector<std::shared_ptr<Floor>> floors;
	std::vector< std::shared_ptr<Item>> items;
	std::vector< std::shared_ptr<Trap>> traps;
	std::shared_ptr<Stairs> stairs;
	this->_turnController = std::make_shared<TurnController>();

	this->_playerDatas->setStageFloor(this->_floorIndex);
	this->_playerDatas->setActiveStageName(this->_stageName);

	//フロアデータ読み込み
	StageDataLoader stageDataloader(_stageName);

	stageDataloader.loadData(this->_floorIndex, this->_saveBook, obstacles, items, traps, enemy, this->_player, stairs, _turnController, _playerDatas);


	//saveBookもObstaclesに入れる
	if (this->_saveBook != nullptr){

		std::string floorName = this->_stageName + "SaveFloor.pmd";

		floors.push_back(std::make_shared<Floor>(floorName, std::make_shared<Position>(FieldLength::_ROW / 2, FieldLength::_COLUMN / 2, 0)));

		obstacles.push_back(this->_saveBook);
	}
	else{
		std::string floorName = this->_stageName + "Floor.pmd";

		
		floors.push_back(std::make_shared<Floor>(floorName, std::make_shared<Position>(FieldLength::_ROW / 2, FieldLength::_COLUMN / 2, 0)));
	}

	_turnController->initialize(enemy, this->_player);	//TurnController初期化

	std::string floorFileName = this->_stageName + std::to_string(this->_floorIndex) + ".png";

	if (this->_floorIndex == DungeonLength::FLOORNUM - 1){

		//this->_floorOfTheDungeons = std::make_shared<FloorOfTheDungeon>(floorFileName, stairs, enemy, this->_player, obstacles, floors, items, traps, turnController);

		for (auto e : enemy){
			if (e->isBoss()){


				this->_floorOfTheDungeons = std::make_shared<BossFloorOfTheDungeon>(floorFileName, stairs, enemy, this->_player, obstacles, floors, items, traps, _turnController, e);
				break;
			}
		}

	}
	else{
		this->_floorOfTheDungeons = std::make_shared<FloorOfTheDungeon>(floorFileName, stairs, enemy, this->_player, obstacles, floors, items, traps, _turnController);
	}

	this->_floorOfTheDungeons->initialize();
}


void Stage::actionBlackOuted()
{
	if (this->_player->isFinish()){
		Collision::getInstance()->removeAll();
		
		LevelUpper::initialize(this->_playerDatas);
		SceneUpdater::create();
		HitBoxUpdater::create();
		DamageDisplay::create();
		MessgeBox::create();
		EffectUpdater::create();

		

	}
	else if (this->_floorOfTheDungeons->isFinish()){
		this->_floorOfTheDungeons->finalize();
		this->_floorOfTheDungeons = nullptr;
		Collision::getInstance()->removeAll();



		HitBoxUpdater::create();
		DamageDisplay::create();
		MessgeBox::create();
		EffectUpdater::create();

		this->_player = nullptr;
		this->_saveBook = nullptr;

		this->_floorIndex++;
		this->_playerDatas->setStageFloor(this->_floorIndex);
		this->_playerDatas->setActiveStageName(this->_stageName);

		if (this->_floorIndex < DungeonLength::FLOORNUM){
			this->_blackScreen = std::make_shared<BlackScreen>();
		}
		else{
			if (this->_stageName == SceneNames::getName(SceneNames::HANSELANDGRETELSTAGE)){
				this->_nextSceneName = SceneNames::getName(SceneNames::ENDING);
			}

			this->_finish = true;

		}
	}
}
