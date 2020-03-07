#include "EquipScreen.h"
#include "PlayerDatas.h"
#include "Key.h"
#include "MoveType.h"
#include "Cursor.h"
#include "PlayerItems.h"
#include "Item.h"
#include "SceneNames.h"
#include "BlackScreen.h"
#include "CurorThereIsALimit.h"
#include "PlayerKeyConfig.h"
#include "MessgeBox.h"
#include "Action.h"
#include "SceneUpdater.h"
#include "PlayerWeapons.h"
#include "MessgeBox.h"
#include "Weapon.h"
#include "PlayerWearProtective.h"


EquipScreen::EquipScreen(std::shared_ptr<PlayerDatas> playerDatas)
{
	this->_screenLimit = 13;	//画面内に表示されるアイテムの数

	this->_menuBackHandle = LoadGraph("アイテム画面.png");
	this->_playerDatas = playerDatas;
	this->_cursor = std::make_shared<CurorThereIsALimit>(20, 25.0f, 45.0f, 100.0f, 100.0f, this->_screenLimit);
	this->_cursor2 = std::make_shared<CurorThereIsALimit>(20, 25.0f, 45.0f, 100.0f, 100.0f, this->_screenLimit);
	this->_equipmentNameInterval_x = 0.0f;
	this->_equipmentNameInterval_y = 10.0f;

	this->_sceneName = SceneNames::getName(SceneNames::SceneTypes::EQUIPSCREEN);

	this->_weapon = true;
}


EquipScreen::~EquipScreen()
{
}

void EquipScreen::update()
{

	DrawGraph(0, 0, this->_menuBackHandle, TRUE);

	if (this->_weapon){
		int startNum = 0;

		if (this->_cursor->getSelectedNum() >= this->_screenLimit){
			startNum = this->_cursor->getSelectedNum() - this->_screenLimit;
		}

		int startPosY = 0;

		for (int i = startNum; i < this->_playerDatas->getPlayerWeapons()->getSize(); i++){
			DrawString(140, 100 + (startPosY * 45), std::to_string(i).c_str(), GetColor(255, 255, 255));
			if (this->_playerDatas->getEquipedWeapon() == this->_playerDatas->getPlayerWeapons()->get(i)){
				DrawString(80, 100 + (startPosY * 45), "E : ", GetColor(255, 255, 255));
			}
			DrawString(180, 100 + (startPosY * 45), this->_playerDatas->getPlayerWeapons()->getName(i).c_str(), GetColor(255, 255, 255));

			startPosY++;
		}
		this->_cursor->update();

		if (!this->_finish){

			if (MessgeBox::getInstance()->isDisplay()){
				if (Key::getInstance()->getHitFlame(this->_playerDatas->getPlayerKeyConfig()->getActionTypeKey(Action::DECISION)) == 1){
					MessgeBox::getInstance()->displayToNextMessage();
				}
			}
			else if (Key::getInstance()->getHitFlame(KEY_INPUT_W) == 1){
				this->_cursor->move(MoveType::UP);
			}
			else if (Key::getInstance()->getHitFlame(KEY_INPUT_X) == 1 && this->_cursor->getSelectedNum() < this->_playerDatas->getPlayerWeapons()->getSize() - 1){
				this->_cursor->move(MoveType::DOWN);
				//if ()
			}
			else if (Key::getInstance()->getHitFlame(KEY_INPUT_A) == 1){
				this->_weapon = false;
			}
			else if (Key::getInstance()->getHitFlame(KEY_INPUT_D) == 1){
				this->_cursor->move(MoveType::RIGHT);
			}
			else if (Key::getInstance()->getHitFlame(KEY_INPUT_M) == 1){
				this->_finish = true;
				this->_changedSceneName = SceneNames::getName(SceneNames::PAUSEMENU);
				this->_nextSceneName = SceneNames::getName(SceneNames::PAUSEMENU);
			}
			else if (!this->_playerDatas->getPlayerWeapons()->isEmpty() && ((Key::getInstance()->getHitFlame(KEY_INPUT_SPACE) == 1) || (Key::getInstance()->getHitFlame(KEY_INPUT_J) == 1))){

				if ((Key::getInstance()->getHitFlame(KEY_INPUT_SPACE) == 1)){
					this->_playerDatas->equipWeapon(this->_cursor->getSelectedNum());
					std::string message = this->_playerDatas->getEquipedWeapon()->toString() + "をそうびしました。";
					MessgeBox::getInstance()->add(message);

				}
				else if (Key::getInstance()->getHitFlame(KEY_INPUT_J) == 1){
					if (this->_playerDatas->getEquipedWeapon() != this->_playerDatas->getPlayerWeapons()->get(this->_cursor->getSelectedNum())){

						std::string message = this->_playerDatas->getPlayerWeapons()->get(this->_cursor->getSelectedNum())->toString() + "を捨てました。";
						MessgeBox::getInstance()->add(message);
						this->_playerDatas->getPlayerWeapons()->getAndErase(this->_cursor->getSelectedNum());

						if (this->_cursor->getSelectedNum() > this->_playerDatas->getPlayerWeapons()->getSize() - 1){
							this->_cursor->move(MoveType::UP);
						}
					}
					else{
						std::string message = this->_playerDatas->getPlayerWeapons()->get(this->_cursor->getSelectedNum())->toString() + "は現在そうび中です。捨てられません。";
						MessgeBox::getInstance()->add(message);
					}
				}

			}
			else if (Key::getInstance()->getHitFlame(this->_playerDatas->getPlayerKeyConfig()->getActionTypeKey(Action::MENUOPEN)) == 1){
				this->_finish = true;
				this->_changedSceneName = SceneUpdater::getInstance()->getActiveStageName();
				this->_nextSceneName = SceneUpdater::getInstance()->getActiveStageName();
			}

			std::string attack = "こうげきりょく : " + std::to_string(this->_playerDatas->getPlayerWeapons()->get(this->_cursor->getSelectedNum())->getDamege());

			std::string durability = "耐久力 : " + std::to_string(this->_playerDatas->getPlayerWeapons()->get(this->_cursor->getSelectedNum())->getDurability());

			DrawString(600, 100, attack.c_str(), GetColor(255, 255, 255));
			DrawString(600, 150, durability.c_str(), GetColor(255, 255, 255));

			DrawString(30, 700, "そうび : SPACE    すてる : J	   ぼうぐそうび画面へ : A  戻る : M", GetColor(255, 255, 0));
		}
		else{
			this->_blackScreen->out();
		}
	}
	else{
		int startNum = 0;

		if (this->_cursor2->getSelectedNum() >= this->_screenLimit){
			startNum = this->_cursor2->getSelectedNum() - this->_screenLimit;
		}

		int startPosY = 0;

		for (int i = startNum; i < this->_playerDatas->getPlayerWears()->getSize(); i++){
			DrawString(140, 100 + (startPosY * 45), std::to_string(i).c_str(), GetColor(255, 255, 255));
			if (this->_playerDatas->getEquipedWear() == this->_playerDatas->getPlayerWears()->get(i)){
				DrawString(80, 100 + (startPosY * 45), "E : ", GetColor(255, 255, 255));
			}
			DrawString(180, 100 + (startPosY * 45), this->_playerDatas->getPlayerWears()->get(i)->toString().c_str(), GetColor(255, 255, 255));

			startPosY++;
		}
		this->_cursor2->update();

		if (!this->_finish){

			if (MessgeBox::getInstance()->isDisplay()){
				if (Key::getInstance()->getHitFlame(this->_playerDatas->getPlayerKeyConfig()->getActionTypeKey(Action::DECISION)) == 1){
					MessgeBox::getInstance()->displayToNextMessage();
				}
			}
			else if (Key::getInstance()->getHitFlame(KEY_INPUT_W) == 1){
				this->_cursor2->move(MoveType::UP);
			}
			else if (Key::getInstance()->getHitFlame(KEY_INPUT_X) == 1 && this->_cursor2->getSelectedNum() < this->_playerDatas->getPlayerWears()->getSize() - 1){
				this->_cursor2->move(MoveType::DOWN);
				//if ()
			}
			else if (Key::getInstance()->getHitFlame(KEY_INPUT_A) == 1){
				//this->_weapon = false;
			}
			else if (Key::getInstance()->getHitFlame(KEY_INPUT_D) == 1){
				this->_weapon = true;
			}
			else if (Key::getInstance()->getHitFlame(KEY_INPUT_M) == 1){
				this->_finish = true;
				this->_changedSceneName = SceneNames::getName(SceneNames::PAUSEMENU);
				this->_nextSceneName = SceneNames::getName(SceneNames::PAUSEMENU);
			}
			else if (!this->_playerDatas->getPlayerWears()->isEmpty() && ((Key::getInstance()->getHitFlame(KEY_INPUT_SPACE) == 1) || (Key::getInstance()->getHitFlame(KEY_INPUT_J) == 1))){

				//	MessgeBox::getInstance()->addNotErase("ssssssssssssssssssssss : Spaceキー / すてる : Mキー\n");

				if ((Key::getInstance()->getHitFlame(KEY_INPUT_SPACE) == 1)){
					this->_playerDatas->equipWear(this->_cursor2->getSelectedNum());
					std::string message = this->_playerDatas->getEquipedWear()->toString() + "をそうびしました。";
					MessgeBox::getInstance()->add(message);

				}
				else if (Key::getInstance()->getHitFlame(KEY_INPUT_J) == 1){
					if (this->_playerDatas->getEquipedWear() != this->_playerDatas->getPlayerWears()->get(this->_cursor2->getSelectedNum())){

						std::string message = this->_playerDatas->getPlayerWears()->get(this->_cursor2->getSelectedNum())->toString() + "を捨てました。";
						MessgeBox::getInstance()->add(message);
						this->_playerDatas->getPlayerWears()->getAndErase(this->_cursor2->getSelectedNum());

						if(this->_cursor2->getSelectedNum() > this->_playerDatas->getPlayerWears()->getSize() - 1){
							this->_cursor2->move(MoveType::UP);
						}
					}
					else{
						std::string message = this->_playerDatas->getPlayerWears()->get(this->_cursor2->getSelectedNum())->toString() + "は現在そうび中です。捨てられません。";
						MessgeBox::getInstance()->add(message);
					}
				}

			}
			else if (Key::getInstance()->getHitFlame(this->_playerDatas->getPlayerKeyConfig()->getActionTypeKey(Action::MENUOPEN)) == 1){
				this->_finish = true;
				this->_changedSceneName = SceneUpdater::getInstance()->getActiveStageName();
				this->_nextSceneName = SceneUpdater::getInstance()->getActiveStageName();
			}

			std::string defense = "防御力 : " + std::to_string(this->_playerDatas->getPlayerWears()->get(this->_cursor2->getSelectedNum())->getStatesCorrection()->getStatesPoint(State::DEFENSE));
			std::string durability = "耐久力 : " + std::to_string(this->_playerDatas->getPlayerWears()->get(this->_cursor2->getSelectedNum())->getStatesCorrection()->getStatesPoint(State::DURABILITY));

			DrawString(600, 100, defense.c_str(), GetColor(255, 255, 255));
			DrawString(600, 150, durability.c_str(), GetColor(255, 255, 255));

			DrawString(30, 700, "そうび : SPACE    すてる : J	   ぶきそうび画面へ : D  戻る : M", GetColor(255, 255, 0));
		}

		else{
			this->_blackScreen->out();
		}
	}

}

void EquipScreen::finalize()
{
}