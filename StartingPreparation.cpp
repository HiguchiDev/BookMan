#include "StartingPreparation.h"
#include "PlayerDatas.h"
#include "Cursor.h"
#include "Key.h"
#include "PlayerItems.h"
#include "ItemWarehouse.h"
#include "ItemAbility.h"
#include "SceneNames.h"
#include "BlackScreen.h"
#include "PlayerWeapons.h"
#include "Weapon.h"
#include "WeaponWarehouse.h"
#include "PlayerWearProtective.h"
#include "WearWarehouse.h"
#include "MessgeBox.h"

StartingPreparation::StartingPreparation(std::shared_ptr<PlayerDatas> playerDatas)
{
	this->_playerDatas = playerDatas;

	this->_sceneName = SceneNames::getName(SceneNames::STARTINGPREPARATION);

	this->_finish = false;
	this->_weaponSelect = false;
	this->_wearSelect = false;
	this->_backGround = LoadGraph("倉庫.png");

}


StartingPreparation::~StartingPreparation()
{
}

void StartingPreparation::update()
{
	if (!this->_isInit){
		MessgeBox::getInstance()->add("ステージに持っていく物を選んでください。");
		this->_isInit = true;
	}
	DrawGraph(0, 0, this->_backGround, TRUE);
	if (this->_weaponSelect == false){
		DrawString(450, 80, "アイテム", GetColor(255, 255, 255));
		DrawString(100, 200, "手持ち", GetColor(255, 255, 255));
		DrawString(600, 200, "倉庫", GetColor(255, 255, 255));

		DrawString(50, 700, "F : 交換  W X D A : 移動          M : 終了", GetColor(200, 200, 0));
		if (this->_playerItemCursor == nullptr || this->_warehouseCursor == nullptr){
			this->_playerItemCursor = std::make_shared<Cursor>(this->_playerDatas->getPlayerItems()->getSize(), 25.0f, 25.0f, 90.0f, 230.0f);
			this->_warehouseCursor = std::make_shared<Cursor>(this->_playerDatas->getWarehouse()->getSize(), 25.0f, 25.0f, 590.0f, 230.0f);

			this->_activeCursor = this->_playerItemCursor;
		}

		for (int i = 0; i < this->_playerDatas->getPlayerItems()->getSize(); i++){
			DrawString(120, 230 + (i * 25), this->_playerDatas->getPlayerItems()->getName(i).c_str(), GetColor(255, 255, 255));
		}
		for (int i = 0; i < this->_playerDatas->getWarehouse()->getSize(); i++){

			DrawString(620, 230 + (i * 25), this->_playerDatas->getWarehouse()->get(i)->toString().c_str(), GetColor(255, 255, 255));
		}


		this->_activeCursor->update();



		if (!this->_finish){

			if (!MessgeBox::getInstance()->isDisplay()){
				if (Key::getInstance()->getHitFlame(KEY_INPUT_M) == 1){
					this->_weaponSelect = true;
				}
				else if (Key::getInstance()->getHitFlame(KEY_INPUT_A) && this->_activeCursor == this->_warehouseCursor){
					this->_activeCursor = this->_playerItemCursor;
				}
				else if (Key::getInstance()->getHitFlame(KEY_INPUT_D) && this->_activeCursor == this->_playerItemCursor){
					this->_activeCursor = this->_warehouseCursor;
				}
				else if (Key::getInstance()->getHitFlame(KEY_INPUT_X) == 1){
					this->_activeCursor->move(MoveType::DOWN);
				}
				else if (Key::getInstance()->getHitFlame(KEY_INPUT_W) == 1){
					this->_activeCursor->move(MoveType::UP);

				}
				else if (Key::getInstance()->getHitFlame(KEY_INPUT_F) == 1){
					if (this->_activeCursor == this->_playerItemCursor){
						if (!this->_playerDatas->getPlayerItems()->isEmpty()){
							this->_playerDatas->getWarehouse()->add(this->_playerDatas->getPlayerItems()->getAndErase(this->_activeCursor->getSelectedNum()));
						
							this->_warehouseCursor->updateMenuNum(this->_warehouseCursor->getMenuNum() + 1);
							this->_playerItemCursor->updateMenuNum(this->_playerItemCursor->getMenuNum() - 1);

							if (this->_activeCursor->getSelectedNum() > this->_playerDatas->getPlayerItems()->getSize() - 1){
								this->_activeCursor->move(MoveType::UP);
								this->_activeCursor->updateMenuNum(this->_activeCursor->getMenuNum() - 1);
							}
						}
						else{

						}
					}
					else{
						if (!this->_playerDatas->getWarehouse()->isEmpty()){
							if (!this->_playerDatas->getPlayerItems()->isFull()){

								this->_playerDatas->getPlayerItems()->add_startingPreparation(this->_playerDatas->getWarehouse()->getAndErase(this->_activeCursor->getSelectedNum()));	//アイテム移動
							
								this->_playerItemCursor->updateMenuNum(this->_playerItemCursor->getMenuNum() + 1);
								this->_warehouseCursor->updateMenuNum(this->_warehouseCursor->getMenuNum() - 1);

								if (this->_activeCursor->getSelectedNum() > this->_playerDatas->getWarehouse()->getSize() - 1){
									this->_activeCursor->move(MoveType::UP);
									this->_activeCursor->updateMenuNum(this->_activeCursor->getMenuNum() - 1);
								}
							}
							else{
								MessgeBox::getInstance()->add("アイテムがいっぱいです。（上限２０個）");
							}
						}
					}
				}
			}
			else{
				if (Key::getInstance()->getHitFlame(KEY_INPUT_SPACE) == 1){
					MessgeBox::getInstance()->displayToNextMessage();
				}
			}
		}
	}
	else if (!this->_wearSelect){
		DrawString(450, 80, "服", GetColor(255, 255, 255));
		DrawString(100, 200, "手持ち", GetColor(255, 255, 255));
		DrawString(600, 200, "倉庫", GetColor(255, 255, 255));

		DrawString(50, 700, "F : 交換  W X D A : 移動          M : 終了", GetColor(200, 200, 0));
		if (this->_playerWearCursor == nullptr || this->_wearWarehouseCursor == nullptr){
			this->_playerWearCursor = std::make_shared<Cursor>(this->_playerDatas->getPlayerWears()->getSize(), 25.0f, 25.0f, 90.0f, 230.0f);
			this->_wearWarehouseCursor = std::make_shared<Cursor>(this->_playerDatas->getWearWarehouse()->getSize(), 25.0f, 25.0f, 590.0f, 230.0f);

			this->_activeCursor = this->_playerWearCursor;
		}

		for (int i = 0; i < this->_playerDatas->getPlayerWears()->getSize(); i++){
			DrawString(120, 230 + (i * 25), this->_playerDatas->getPlayerWears()->get(i)->toString().c_str(), GetColor(255, 255, 255));
		}
		for (int i = 0; i < this->_playerDatas->getWearWarehouse()->getSize(); i++){

			DrawString(620, 230 + (i * 25), this->_playerDatas->getWearWarehouse()->get(i)->toString().c_str(), GetColor(255, 255, 255));
		}


		this->_activeCursor->update();



		if (!this->_finish){
			if (!MessgeBox::getInstance()->isDisplay()){
				if (Key::getInstance()->getHitFlame(KEY_INPUT_M) == 1){
					this->_wearSelect = true;
				}
				else if (Key::getInstance()->getHitFlame(KEY_INPUT_A) && this->_activeCursor == this->_wearWarehouseCursor){
					this->_activeCursor = this->_playerWearCursor;
				}
				else if (Key::getInstance()->getHitFlame(KEY_INPUT_D) && this->_activeCursor == this->_playerWearCursor){
					this->_activeCursor = this->_wearWarehouseCursor;
				}
				else if (Key::getInstance()->getHitFlame(KEY_INPUT_X) == 1){
					this->_activeCursor->move(MoveType::DOWN);
				}
				else if (Key::getInstance()->getHitFlame(KEY_INPUT_W) == 1){
					this->_activeCursor->move(MoveType::UP);

				}
				else if (Key::getInstance()->getHitFlame(KEY_INPUT_F) == 1){
					if (this->_activeCursor == this->_playerWearCursor){
						if (!this->_playerDatas->getPlayerWears()->isEmpty()){
							if (this->_playerDatas->getEquipedWear() != this->_playerDatas->getPlayerWears()->get(this->_activeCursor->getSelectedNum())){
								this->_playerDatas->getWearWarehouse()->add(this->_playerDatas->getPlayerWears()->getAndErase(this->_activeCursor->getSelectedNum()));

								this->_playerWearCursor->updateMenuNum(this->_playerWearCursor->getMenuNum() - 1);
								this->_wearWarehouseCursor->updateMenuNum(this->_wearWarehouseCursor->getMenuNum() + 1);

								if (this->_activeCursor->getSelectedNum() > this->_playerDatas->getPlayerWears()->getSize() - 1){
									this->_activeCursor->move(MoveType::UP);
								}
							}
							else{
								MessgeBox::getInstance()->add("装備中の服は移動できません。");
							}
						}
					}
					else{
						if (!this->_playerDatas->getWearWarehouse()->isEmpty()){
							if (!this->_playerDatas->getPlayerWears()->isFull()){
								this->_playerDatas->getPlayerWears()->add(this->_playerDatas->getWearWarehouse()->getAndErase(this->_activeCursor->getSelectedNum()));

								this->_playerWearCursor->updateMenuNum(this->_playerWearCursor->getMenuNum() + 1);
								this->_wearWarehouseCursor->updateMenuNum(this->_wearWarehouseCursor->getMenuNum() - 1);

								if (this->_activeCursor->getSelectedNum() > this->_playerDatas->getWearWarehouse()->getSize() - 1){
									this->_activeCursor->move(MoveType::UP);
								}
							}
							else{
								MessgeBox::getInstance()->add("服がいっぱいです。（上限３個）");
							}
						}
					}
				}
			}
			else{
				if (Key::getInstance()->getHitFlame(KEY_INPUT_SPACE) == 1){
					MessgeBox::getInstance()->displayToNextMessage();
				}
			}
		}
	}
	else if (!this->_finish){
		DrawString(450, 80, "武器", GetColor(255, 255, 255));
		DrawString(100, 200, "手持ち", GetColor(255, 255, 255));
		DrawString(600, 200, "倉庫", GetColor(255, 255, 255));

		DrawString(50, 700, "F : 交換  W X D A : 移動          M : 終了", GetColor(200, 200, 0));
		if (this->_playerWeaponCursor == nullptr || this->_weaponWarehouseCursor == nullptr){
			this->_playerWeaponCursor = std::make_shared<Cursor>(this->_playerDatas->getPlayerWeapons()->getSize(), 25.0f, 25.0f, 90.0f, 230.0f);
			this->_weaponWarehouseCursor = std::make_shared<Cursor>(this->_playerDatas->getWeaponWarehouse()->getSize(), 25.0f, 25.0f, 590.0f, 230.0f);

			this->_activeWeaponCursor = this->_playerWeaponCursor;
		}

		for (int i = 0; i < this->_playerDatas->getPlayerWeapons()->getSize(); i++){

			DrawString(120, 230 + (i * 25), this->_playerDatas->getPlayerWeapons()->getName(i).c_str(), GetColor(255, 255, 255));
		}
		for (int i = 0; i < this->_playerDatas->getWeaponWarehouse()->getSize(); i++){

			DrawString(620, 230 + (i * 25), this->_playerDatas->getWeaponWarehouse()->get(i)->toString().c_str(), GetColor(255, 255, 255));
		}


		this->_activeWeaponCursor->update();



		if (!this->_finish){
			if (!MessgeBox::getInstance()->isDisplay()){
			
				if (Key::getInstance()->getHitFlame(KEY_INPUT_M) == 1){

					if (!this->_playerDatas->getActiveStageName().empty()){
						this->_nextSceneName = this->_playerDatas->getActiveStageName();

					}
					else{
						this->_nextSceneName = SceneNames::getName(SceneNames::STAGESELECT);
					}

					this->_finish = true;

				}
				else if (Key::getInstance()->getHitFlame(KEY_INPUT_A) && this->_activeWeaponCursor == this->_weaponWarehouseCursor){
					this->_activeWeaponCursor = this->_playerWeaponCursor;
				}
				else if (Key::getInstance()->getHitFlame(KEY_INPUT_D) && this->_activeWeaponCursor == this->_playerWeaponCursor){
					this->_activeWeaponCursor = this->_weaponWarehouseCursor;
				}
				else if (Key::getInstance()->getHitFlame(KEY_INPUT_X) == 1){
					this->_activeWeaponCursor->move(MoveType::DOWN);
				}
				else if (Key::getInstance()->getHitFlame(KEY_INPUT_W) == 1){
					this->_activeWeaponCursor->move(MoveType::UP);

				}
				else if (Key::getInstance()->getHitFlame(KEY_INPUT_F) == 1){

					if (this->_activeWeaponCursor == this->_playerWeaponCursor){
						

						if (!this->_playerDatas->getPlayerWeapons()->isEmpty()){
							
							if (this->_playerDatas->getEquipedWeapon() != this->_playerDatas->getPlayerWeapons()->get(this->_activeWeaponCursor->getSelectedNum())){
								this->_playerDatas->getWeaponWarehouse()->add(this->_playerDatas->getPlayerWeapons()->getAndErase(this->_activeWeaponCursor->getSelectedNum()));

								this->_playerWeaponCursor->updateMenuNum(this->_playerWeaponCursor->getMenuNum() - 1);
								this->_weaponWarehouseCursor->updateMenuNum(this->_weaponWarehouseCursor->getMenuNum() + 1);

								if (this->_activeWeaponCursor->getSelectedNum() > this->_playerDatas->getPlayerWeapons()->getSize() - 1){
									this->_activeWeaponCursor->move(MoveType::UP);
								}
							}
							else{
								MessgeBox::getInstance()->add("装備中の武器は移動できません。");
							}
						}
					}
					else{
						if (!this->_playerDatas->getWeaponWarehouse()->isEmpty()){
							if (!this->_playerDatas->getPlayerWeapons()->isFull()){
								this->_playerDatas->getPlayerWeapons()->add(this->_playerDatas->getWeaponWarehouse()->getAndErase(this->_activeWeaponCursor->getSelectedNum()));

								this->_playerWeaponCursor->updateMenuNum(this->_playerWeaponCursor->getMenuNum() + 1);
								this->_weaponWarehouseCursor->updateMenuNum(this->_weaponWarehouseCursor->getMenuNum() - 1);

								if (this->_activeWeaponCursor->getSelectedNum() > this->_playerDatas->getWeaponWarehouse()->getSize() - 1){
									this->_activeWeaponCursor->move(MoveType::UP);
								}
							}
							else{
								MessgeBox::getInstance()->add("武器がいっぱいです。（上限３個）");
							}
						}
					}
				}
			}
			else{
				if (Key::getInstance()->getHitFlame(KEY_INPUT_SPACE) == 1){
					MessgeBox::getInstance()->displayToNextMessage();
				}
			}
		}

	}
	else{
		this->_blackScreen->out();
	}
}

void StartingPreparation::finalize()
{
	DeleteGraph(this->_backGround);
}