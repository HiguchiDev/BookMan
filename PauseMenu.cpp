#include "PauseMenu.h"
#include "Cursor.h"
#include "Key.h"
#include "DxLib.h"
#include "SceneNames.h"
#include "BlackScreen.h"
#include "MessgeBox.h"
#include "Action.h"
#include "PlayerDatas.h"
#include "PlayerKeyConfig.h"
#include "SceneUpdater.h"
#include "LevelUpper.h"


PauseMenu::PauseMenu(std::shared_ptr<PlayerDatas> playerDatas)
{
	this->_playerDatas = playerDatas;
	this->_sceneName = SceneNames::getName(SceneNames::SceneTypes::PAUSEMENU);

	this->_menuNames.push_back(SceneNames::getName(SceneNames::SceneTypes::ITEMSCREEN));
	this->_menuNames.push_back(SceneNames::getName(SceneNames::SceneTypes::EQUIPSCREEN));
	this->_names.push_back("アイテム");
	this->_names.push_back("装備");
	this->_cursor = std::make_shared<Cursor>(this->_menuNames.size(), 20.0f, 45.0f, 680.0f, 97.0f);

	this->_menuBackHandle = LoadGraph("ステータス画面.png");

	
}


PauseMenu::~PauseMenu()
{
}

void PauseMenu::update()
{	
	DrawGraph(0, 0, this->_menuBackHandle, TRUE);

	this->_cursor->update();

	for (int i = 0; i < this->_menuNames.size(); i++){
		DrawString(720, 100 + (i * 45), this->_names[i].c_str(), GetColor(255, 255, 255));
	}

	int statesX = 80;
	int statesY = 400;

	int stateYValue = 40;

	std::string hitPoint = "HP : " + std::to_string(this->_playerDatas->getStatesPoint()->getStatesPoint(State::HITPOINT));
	hitPoint += " / " + std::to_string(this->_playerDatas->getStatesPoint()->getStatesPoint(State::HPMAX));
	
	DrawString(statesX, statesY, hitPoint.c_str(), GetColor(255, 255, 255));
	
	std::string magicPoint = "MP : " + std::to_string(this->_playerDatas->getStatesPoint()->getStatesPoint(State::MAGICPOINT));

	DrawString(statesX, statesY + stateYValue * 1, magicPoint.c_str(), GetColor(255, 255, 255));

	std::string attackPoint = "こうげき : " + std::to_string(this->_playerDatas->getStatesPoint()->getStatesPoint(State::ATTACK));

	DrawString(statesX, statesY + stateYValue * 2, attackPoint.c_str(), GetColor(255, 255, 255));

	std::string defencePoint = "ぼうぎょ : " + std::to_string(this->_playerDatas->getStatesPoint()->getStatesPoint(State::DEFENSE));

	DrawString(statesX, statesY + stateYValue * 3, defencePoint.c_str(), GetColor(255, 255, 255));

	std::string expPoint = "けいけんち : " + std::to_string(this->_playerDatas->getStatesPoint()->getStatesPoint(State::EXP));

	DrawString(statesX, statesY + stateYValue * 4, expPoint.c_str(), GetColor(255, 255, 255));

	std::string levelPoint = "レベル : " + std::to_string(this->_playerDatas->getStatesPoint()->getStatesPoint(State::LEVEL));

	DrawString(statesX, statesY + stateYValue * 5, levelPoint.c_str(), GetColor(255, 255, 255));

	std::string levelNextPoint = "次のレベルまであと: " + std::to_string(LevelUpper::nextLevelUpExp());

	DrawString(statesX, statesY + stateYValue * 6, levelNextPoint.c_str(), GetColor(255, 255, 255));

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
			this->_nextSceneName = this->_menuNames[this->_cursor->getSelectedNum()];
			this->_finish = true;
		}
		else if (Key::getInstance()->getHitFlame(this->_playerDatas->getPlayerKeyConfig()->getActionTypeKey(Action::CANCEL)) == 1){
			this->_changedSceneName = SceneUpdater::getInstance()->getActiveStageName();
			this->_nextSceneName = SceneUpdater::getInstance()->getActiveStageName();
			this->_finish = true;
		}

		DrawString(30, 700, "移動 : X or W   決定 : SPACE  戻る : M", GetColor(255, 255, 0));
	}
	else{
		this->_blackScreen->out();
	}

}

void PauseMenu::finalize()
{
	DeleteGraph(this->_menuBackHandle);
}