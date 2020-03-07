#include "Tutorial.h"


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

Turorial::Turorial(std::shared_ptr<PlayerDatas> playerDatas, std::string stageName) : Stage(playerDatas, stageName)
{
	this->_floorIndex = 0;
	this->_playerDatas = playerDatas;

	//messages keys ��p�ӂ��āA���ꂼ�ꏇ�Ԃɕ\��
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


	this->_tutorialOperation.push_back(KEY_INPUT_RIGHT);
	this->_tutorialMessage.push_back("�� : �J������]");

	this->_tutorialOperation.push_back(KEY_INPUT_LEFT);
	this->_tutorialMessage.push_back("�� : �J������]");

	this->_tutorialOperation.push_back(KEY_INPUT_L);
	this->_tutorialMessage.push_back("L : ���(�}�E�X�J�[�\���Ŏ��_�𓮂���)");

	this->_tutorialOperation.push_back(KEY_INPUT_M);
	this->_tutorialMessage.push_back("M : ��ω���");


	this->_tutorialOperation.push_back(KEY_INPUT_W);
	this->_tutorialMessage.push_back("W : �O�ɕ���");

	this->_tutorialOperation.push_back(KEY_INPUT_A);
	this->_tutorialMessage.push_back("A (���ȊO�������Ȃ���) : ��������");
	this->_tutorialOperation.push_back(KEY_INPUT_A);
	this->_tutorialMessage.push_back("A (���������Ȃ���) : ���ɕ���");

	this->_tutorialOperation.push_back(KEY_INPUT_D);
	this->_tutorialMessage.push_back("D (�E�ȊO�������Ȃ���) : �E������");
	this->_tutorialOperation.push_back(KEY_INPUT_D);
	this->_tutorialMessage.push_back("D (�E�������Ȃ���) : �E�ɕ���");

	this->_tutorialOperation.push_back(KEY_INPUT_X);
	this->_tutorialMessage.push_back("X (���ȊO�������Ȃ���) : ��������");
	this->_tutorialOperation.push_back(KEY_INPUT_X);
	this->_tutorialMessage.push_back("X (���������Ȃ���) : ���ɕ���");

	this->_tutorialOperation.push_back(KEY_INPUT_Q);
	this->_tutorialMessage.push_back("Q (�΂ߍ���ȊO�������Ȃ���) : �΂ߍ��������");
	this->_tutorialOperation.push_back(KEY_INPUT_Q);
	this->_tutorialMessage.push_back("Q (�΂ߍ���������Ȃ���) : �΂ߍ���ɕ���");

	this->_tutorialOperation.push_back(KEY_INPUT_E);
	this->_tutorialMessage.push_back("E (�΂߉E��ȊO�������Ȃ���) : �΂߉E�������");
	this->_tutorialOperation.push_back(KEY_INPUT_E);
	this->_tutorialMessage.push_back("E (�΂߉E��������Ȃ���) : �΂߉E��ɕ���");

	this->_tutorialOperation.push_back(KEY_INPUT_C);
	this->_tutorialMessage.push_back("C (�΂߉E���ȊO�������Ȃ���) : �΂߉E��������");
	this->_tutorialOperation.push_back(KEY_INPUT_C);
	this->_tutorialMessage.push_back("C (�΂߉E���������Ȃ���) : �΂߉E���ɕ���");

	this->_tutorialOperation.push_back(KEY_INPUT_Z);
	this->_tutorialMessage.push_back("Z (�΂ߍ����ȊO�������Ȃ���) : �΂ߍ���������");
	this->_tutorialOperation.push_back(KEY_INPUT_Z);
	this->_tutorialMessage.push_back("Z (�΂ߍ����������Ȃ���) : �΂ߍ����ɕ���");

	this->_tutorialOperation.push_back(KEY_INPUT_SPACE);
	this->_tutorialMessage.push_back("SPACE : �U��");

	this->_tutorialOperation.push_back(KEY_INPUT_D);
	this->_tutorialMessage.push_back("D : ��������");

	this->_tutorialOperation.push_back(KEY_INPUT_J);
	this->_tutorialMessage.push_back("J : ���ׂ�");

	this->_tutorialOperation.push_back(KEY_INPUT_W);
	this->_tutorialMessage.push_back("W : �O������");

	this->_tutorialOperation.push_back(KEY_INPUT_W);
	this->_tutorialMessage.push_back("W : �O�ɐi��");

	this->_tutorialOperation.push_back(KEY_INPUT_W);
	this->_tutorialMessage.push_back("W : �O�ɐi��");

	this->_tutorialOperation.push_back(KEY_INPUT_W);
	this->_tutorialMessage.push_back("W : �O�ɐi��");

	this->_tutorialOperation.push_back(KEY_INPUT_W);
	this->_tutorialMessage.push_back("W : �O�ɐi��");


	this->_messageSend = false;
	this->_messageSend1 = false;
}

Turorial::~Turorial()
{
}

void Turorial::initializeFloor()
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

	//�t���A�f�[�^�ǂݍ���
	StageDataLoader stageDataloader(_stageName);

	stageDataloader.loadData(this->_floorIndex, this->_saveBook, obstacles, items, traps, enemy, this->_player, stairs, _turnController, _playerDatas);


	//saveBook��Obstacles�ɓ����
	if (this->_saveBook != nullptr){

		std::string floorName = this->_stageName + "SaveFloor.pmd";

		floors.push_back(std::make_shared<Floor>(floorName, std::make_shared<Position>(FieldLength::_ROW / 2, FieldLength::_COLUMN / 2, 0)));

		obstacles.push_back(this->_saveBook);
	}
	else{
		std::string floorName = this->_stageName + "Floor.pmd";


		floors.push_back(std::make_shared<Floor>(floorName, std::make_shared<Position>(FieldLength::_ROW / 2, FieldLength::_COLUMN / 2, 0)));
	}

	_turnController->initialize(enemy, this->_player);	//TurnController������

	std::string floorFileName = this->_stageName + std::to_string(this->_floorIndex) + ".png";

	if (this->_floorIndex == 1){

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

void Turorial::update()
{
	DrawGraph(0, 0, handle1, TRUE);

	if (this->_floorOfTheDungeons != nullptr){
		if (!this->_messageSend){
			MessgeBox::getInstance()->add("�`���[�g���A�����J�n���܂��B");
			MessgeBox::getInstance()->add("�t���A�̂ǂ����ɂ���K�i�������ĂQ�O�K�܂œo���Ă�������");
			MessgeBox::getInstance()->add("�Q�O�K�w�ڂɋ���{�X��|���΃N���A�ł��B");
			MessgeBox::getInstance()->add("�ł́A����������J�n���܂��B");
			MessgeBox::getInstance()->add("��ʉ��̃��b�Z�[�W�ɂ��������đ��삵�Ă�������");
			this->_messageSend = true;
		}
		if (!this->_messageSend1 && this->_floorIndex == 1){
			MessgeBox::getInstance()->add("�{�X��|���Ă��������B");
			this->_messageSend1 = true;
		}





		if (this->_index < this->_tutorialOperation.size()){


			this->_floorOfTheDungeons->start(this->_tutorialOperation[this->_index], this->_tutorialMessage[this->_index]);

			if (this->_floorOfTheDungeons->isNext()){
				this->_index++;
			}
		}
		else{
			this->_floorOfTheDungeons->start();
		}


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
		else {
			if (this->_floorIndex >= 1 && this->_floorOfTheDungeons->isFinish()){
				DrawGraph(this->_x, 0, this->_stageClearHandle, TRUE);
				if (this->_x >= this->_stopX){
					this->_x -= 50;
				}
				else{
					this->_time++;
				}

				if (this->_time >= this->_stopTime){
					this->_blackScreen->out();
					if (this->_blackScreen->isBlackOut()){
						//this->actionBlackOuted();

						this->_finish = true;
						Collision::getInstance()->removeAll();

						HitBoxUpdater::create();
						DamageDisplay::create();
						MessgeBox::create();
						EffectUpdater::create();
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
						this->_finish = true;
						Collision::getInstance()->removeAll();

						HitBoxUpdater::create();
						DamageDisplay::create();
						MessgeBox::create();
						EffectUpdater::create();
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

void Turorial::actionBlackOuted()
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



		if (this->_floorIndex < 2){
			this->_blackScreen = std::make_shared<BlackScreen>();
		}
		else{
			this->_finish = true;

		}

	}
}