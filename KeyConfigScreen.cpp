#include "KeyConfigScreen.h"
#include "Key.h"
#include "DxLib.h"
#include "Cursor.h"
#include "PlayerKeyConfig.h"
#include "SceneNames.h"
#include "BlackScreen.h"

KeyConfigScreen::KeyConfigScreen(std::shared_ptr<PlayerKeyConfig> playerKeyConfig)
{
	this->_cursor = std::make_shared<Cursor>(4, 25.0f, 25.0f, 100.0f, 100.0f);
	this->_playerKeyConfig = playerKeyConfig;
	this->_keyChange = false;


	this->_moveTypes.push_back(MoveType::MoveTypes::DOWN);
	this->_moveTypes.push_back(MoveType::MoveTypes::LEFT);
	this->_moveTypes.push_back(MoveType::MoveTypes::RIGHT);
	this->_moveTypes.push_back(MoveType::MoveTypes::UP);

	this->_moveTypeToStringMap[MoveType::MoveTypes::DOWN] = "‰º";
	this->_moveTypeToStringMap[MoveType::MoveTypes::UP] = "ã";
	this->_moveTypeToStringMap[MoveType::MoveTypes::RIGHT] = "‰E";
	this->_moveTypeToStringMap[MoveType::MoveTypes::LEFT] = "¶";

	this->_sceneName = SceneNames::getName(SceneNames::SceneTypes::KEYCONFIG);
	this->_nextSceneName = SceneNames::getName(SceneNames::SceneTypes::TUTORIALSTAGE);	//‰¼
}


KeyConfigScreen::~KeyConfigScreen()
{

}

void KeyConfigScreen::update()
{
		
	for (int i = 0; i < this->_moveTypes.size(); i++){
			DrawString(100, 100 + (i * 25), this->_moveTypeToStringMap[this->_moveTypes[i]].c_str(), GetColor(255, 255, 255));
	}
	
	this->_cursor->update();

	if (!this->_finish){
		if (Key::getInstance()->getHitFlame(KEY_INPUT_W) == 1){
			this->_cursor->move(MoveType::UP);
		}
		else if (Key::getInstance()->getHitFlame(KEY_INPUT_X) == 1){
			this->_cursor->move(MoveType::DOWN);
		}
		else if (Key::getInstance()->getHitFlame(KEY_INPUT_O) == 1){
			if (this->_keyChange == false){
				this->_keyChange = true;
			}
		}
		
		else if (Key::getInstance()->getHitFlame(KEY_INPUT_F) == 1){
			this->_finish = true;
		}

		else if (this->_keyChange && Key::getInstance()->getHitKey()){
			
			this->_playerKeyConfig->setConfig(Key::getInstance()->getHitKey(), this->_moveTypes[this->_cursor->getSelectedNum()]);
			this->_keyChange = false;
		}
	}
	else{
		this->_blackScreen->out();
	}

}

void KeyConfigScreen::finalize()
{

}
