#include "DataWrite.h"
#include "SceneNames.h"
#include "DxLib.h"
#include "MoveType.h"
#include "PlayerDatas.h"
#include "Key.h"
#include "Cursor.h"
#include "Stage.h"
#include "MessgeBox.h"
#include "Action.h"
#include "PlayerKeyConfig.h"
#include "BlackScreen.h"
#include "SceneUpdater.h"

DataWrite::DataWrite(std::shared_ptr<PlayerDatas> playerDatas)
{
	this->_menuDistanceRow = 0.0f;
	this->_menuDistanceColumn = 250.0f;
	this->_stringPositionX = 230.0f;
	this->_cursor = std::make_shared<Cursor>(3, this->_menuDistanceRow, this->_menuDistanceColumn, this->_stringPositionX - 60, 70.0f);

	this->_sceneName = SceneNames::getName(SceneNames::SceneTypes::DATAWRITE);

	for (int i = 0; i < 3; i++){
		this->_playerDatas_show.push_back(std::make_shared<PlayerDatas>());
		if (this->_playerDatas_show[i]->load(i)){
			this->_playerDatasMap[i] = this->_playerDatas_show[i];
		}
	}


	this->_playerDatas = playerDatas;

	this->_saveDataFileNames.push_back("saveData1.dat");
	this->_saveDataFileNames.push_back("saveData2.dat");
	this->_saveDataFileNames.push_back("saveData3.dat");

	this->_menuHandle = LoadGraph("メッセージ画面.png");
}


DataWrite::~DataWrite()
{
}

void DataWrite::update()

{
	DrawGraph(0, 0, this->_menuHandle, TRUE);
	DrawGraph(0, 250, this->_menuHandle, TRUE);
	DrawGraph(0, 500, this->_menuHandle, TRUE);

	this->_cursor->update();

	int menuY;

	for (int i = 0; i < (signed)this->_saveDataFileNames.size(); i++){
		std::string massage = "セーブデータ" + std::to_string(i + 1);
		menuY = 70 + (250 * i);
		DrawString((int)this->_stringPositionX, menuY, massage.c_str(), GetColor(255, 255, 255));

		if (this->_playerDatasMap.find(i) != this->_playerDatasMap.end()){

			menuY += 50;
			massage = "レベル : " + std::to_string(this->_playerDatasMap[i]->getStatesPoint()->getStatesPoint(State::LEVEL));
			DrawString((int)this->_stringPositionX + 20, menuY, massage.c_str(), GetColor(255, 255, 255));


			menuY += 50;
			if (this->_playerDatasMap[i]->getStageFloor() != -1){
				massage = this->_playerDatasMap[i]->getActiveStageName() + " : " + std::to_string(this->_playerDatasMap[i]->getStageFloor()) + "階";

			}
			else{
				massage = "ステージセレクト";
			}
			DrawString((int)this->_stringPositionX + 20, menuY, massage.c_str(), GetColor(255, 255, 255));
		}
		else{
			menuY += 50;
			DrawString((int)this->_stringPositionX, menuY, "NO DATA", GetColor(255, 255, 255));
			menuY += 50;
		}
	}

	if (!this->_finish){
		if (MessgeBox::getInstance()->isDisplay()){
			if (Key::getInstance()->getHitFlame(this->_playerDatas->getPlayerKeyConfig()->getActionTypeKey(Action::DECISION)) == 1){
				MessgeBox::getInstance()->displayToNextMessage();
			}
		}

		else if (Key::getInstance()->getHitFlame(KEY_INPUT_W) == 1){
			this->_cursor->move(MoveType::UP);
		}
		else if (Key::getInstance()->getHitFlame(KEY_INPUT_X) == 1){
			this->_cursor->move(MoveType::DOWN);
		}
		else if (Key::getInstance()->getHitFlame(KEY_INPUT_A) == 1){
			this->_cursor->move(MoveType::LEFT);
		}
		else if (Key::getInstance()->getHitFlame(KEY_INPUT_D) == 1){
			this->_cursor->move(MoveType::RIGHT);
		}
		else if (Key::getInstance()->getHitFlame(KEY_INPUT_SPACE) == 1){
			if (this->_playerDatas->getStageFloor() != -1){
				
				_playerDatas->save_stageDataIncludes(this->_cursor->getSelectedNum());
				this->_changedSceneName = SceneUpdater::getInstance()->getActiveStageName();
				this->_nextSceneName = SceneUpdater::getInstance()->getActiveStageName();
			}
			else{
				
				_playerDatas->save(this->_cursor->getSelectedNum());
				this->_changedSceneName = SceneNames::getName(SceneNames::STAGESELECT);
				this->_nextSceneName = SceneNames::getName(SceneNames::STAGESELECT);
			}
			this->_finish = true;

	
		}
		else if (Key::getInstance()->getHitFlame(this->_playerDatas->getPlayerKeyConfig()->getActionTypeKey(Action::CANCEL)) == 1){
			this->_changedSceneName = SceneUpdater::getInstance()->getActiveStageName();

			if (this->_playerDatas->getStageFloor() != -1){
				this->_nextSceneName = SceneUpdater::getInstance()->getActiveStageName();
			}
			else{
				this->_nextSceneName = SceneNames::getName(SceneNames::STAGESELECT);
			}

			this->_finish = true;

		}

		DrawString(100, 700, "移動 : ↓ ↑  決定 : SPACE  戻る : M", GetColor(255,255, 0));
	}
	else{
		this->_blackScreen->out();
	}


}

void DataWrite::finalize()
{

}