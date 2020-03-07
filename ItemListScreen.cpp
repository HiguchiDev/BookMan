#include "ItemListScreen.h"
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
#include "ItemAbility.h"

ItemListScreen::ItemListScreen(std::shared_ptr<PlayerDatas> playerDatas)
{
	this->_screenLimit = 9;	//画面内に表示されるアイテムの数

	this->_menuBackHandle = LoadGraph("アイテム画面.png");
	this->_explanatoryTextHandle = LoadGraph("説明文.png");

	this->_playerDatas = playerDatas;
	this->_cursor = std::make_shared<CurorThereIsALimit>(20, 25.0f, 45.0f, 100.0f, 100.0f, this->_screenLimit);
	this->_itemNameInterval_x = 0.0f;
	this->_itemNameInterval_y = 10.0f;

	this->_sceneName = SceneNames::getName(SceneNames::SceneTypes::ITEMSCREEN);
}


ItemListScreen::~ItemListScreen()
{
}

void ItemListScreen::update()
{	
	
	DrawGraph(0, 0, this->_menuBackHandle, TRUE);

	

	int startNum = 0;

	if (this->_cursor->getSelectedNum() >= this->_screenLimit){
		startNum = this->_cursor->getSelectedNum() - this->_screenLimit;
	}

	int startPosY = 0;

	for (int i = startNum; i < this->_playerDatas->getPlayerItems()->getSize(); i++){
		DrawString(140, 100 + (startPosY * 45), std::to_string(i).c_str(), GetColor(255, 255, 255));
		DrawString(180, 100 + (startPosY * 45), this->_playerDatas->getPlayerItems()->getName(i).c_str(), GetColor(255, 255, 255));

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
		else if (Key::getInstance()->getHitFlame(KEY_INPUT_X) == 1 && this->_cursor->getSelectedNum() < this->_playerDatas->getPlayerItems()->getSize() - 1){
			this->_cursor->move(MoveType::DOWN);
			//if ()
		}
		else if (Key::getInstance()->getHitFlame(KEY_INPUT_A) == 1){
			this->_cursor->move(MoveType::LEFT);
		}
		else if (Key::getInstance()->getHitFlame(KEY_INPUT_D) == 1){
			this->_cursor->move(MoveType::RIGHT);
		}
		else if (Key::getInstance()->getHitFlame(KEY_INPUT_SPACE) == 1 && !this->_playerDatas->getPlayerItems()->isEmpty()){
			this->_playerDatas->getPlayerItems()->use(this->_cursor->getSelectedNum(), this->_playerDatas);
			this->_finish = true;
			this->_changedSceneName = SceneUpdater::getInstance()->getActiveStageName();
			this->_nextSceneName = SceneUpdater::getInstance()->getActiveStageName();
			if (this->_cursor->getSelectedNum() > this->_playerDatas->getPlayerItems()->getSize() - 1){
				this->_cursor->move(MoveType::UP);
			}
		}
		else if (Key::getInstance()->getHitFlame(KEY_INPUT_J) == 1 && !this->_playerDatas->getPlayerItems()->isEmpty()){
			this->_playerDatas->getPlayerItems()->getAndErase(this->_cursor->getSelectedNum());
		
			if (this->_cursor->getSelectedNum() > this->_playerDatas->getPlayerItems()->getSize() - 1){
				this->_cursor->move(MoveType::UP);
			}
		}
		else if (Key::getInstance()->getHitFlame(KEY_INPUT_F) == 1 && !this->_playerDatas->getPlayerItems()->isEmpty()){
			if (this->_playerDatas->getPlayerItems()->throwItem(this->_cursor->getSelectedNum(), this->_playerDatas)){
				this->_finish = true;
				this->_changedSceneName = SceneUpdater::getInstance()->getActiveStageName();
				this->_nextSceneName = SceneUpdater::getInstance()->getActiveStageName();
			}
			else{
				MessgeBox::getInstance()->add("このアイテムはなげることができません。");
			}
		}
		else if (Key::getInstance()->getHitFlame(KEY_INPUT_M) == 1){
			this->_finish = true;
			this->_changedSceneName = SceneNames::getName(SceneNames::PAUSEMENU);
			this->_nextSceneName = SceneNames::getName(SceneNames::PAUSEMENU);
		}
		DrawGraph(0, 550, this->_menuBackHandle, TRUE);
		if (!this->_playerDatas->getPlayerItems()->isEmpty()){
			DrawString(180, 600, this->_playerDatas->getPlayerItems()->get(this->_cursor->getSelectedNum())->getExplanatoryText().c_str(), GetColor(255, 255, 255));
		}

		
		DrawString(180, 700, "つかう : SPACE    なげる : F	　すてる : J   もどる : M", GetColor(255, 255, 0));
	}
	else{
		this->_blackScreen->out();
	}

}

void ItemListScreen::finalize()
{
	DeleteGraph(this->_menuBackHandle);
	DeleteGraph(this->_explanatoryTextHandle);
}