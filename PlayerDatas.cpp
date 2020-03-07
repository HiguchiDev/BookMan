#include "PlayerDatas.h"
#include "PlayerItems.h"
#include "StatesPoint.h"
#include "PlayerKeyConfig.h"
#include <fstream>
#include "DxLib.h"
#include "ItemWarehouse.h"
#include "WeaponWarehouse.h"
#include "PlayerWeapons.h"
#include "Weapon.h"
#include "SwordOfTheTree.h"
#include "PlayerWearProtective.h"
#include "WearWarehouse.h"
#include "Object_3D_Duplicate.h"
#include "Object_2D.h"
#include "LeatherSuit.h"

std::shared_ptr<PlayerItems> PlayerDatas::getPlayerItems()
{
	return this->_playerItems;
}

PlayerDatas::PlayerDatas() : CharacterData("player")
{
	this->_playerItems = std::make_shared<PlayerItems>(20);
	this->_statesPoint = std::make_shared<StatesPoint>();
	this->_playerKeyConfig = std::make_shared<PlayerKeyConfig>();
	this->_itemWarehouse = std::make_shared<ItemWarehouse>();
	this->_playerWeapons = std::make_shared<PlayerWeapons>(3);
	this->_weaponWarehouse = std::make_shared<WeaponWarehouse>();
	this->_wearWarehouse = std::make_shared<WearWarehouse>();
	this->_playerWears = std::make_shared<PlayerWearProtective>();
	this->_stageFloor = -1;
	handle = LoadGraph("ステータスゲージ.png");
	mPHandle = LoadGraph("MPゲージ.png");

	//this->_statesPoint->upDateStatesPoint(State::HPMAX, 10000);
	//this->_statesPoint->upDateStatesPoint(State::HITPOINT, 10000);
}

void PlayerDatas::draw()
{
	double rate = (double)((double)this->_statesPoint->getStatesPoint(State::HITPOINT) / (double)this->_statesPoint->getStatesPoint(State::HPMAX));
	DrawRotaGraph(100, 100, 1.0, 0.0, this->mPHandle, TRUE, FALSE);

	if (rate > 0.0){
		DrawRotaGraph(220, 100, rate * 0.2, 0.0, this->handle, TRUE, FALSE);
	}
}

void PlayerDatas::equipWeapon(int index)
{
	
	if (this->_equipedWeapon != this->_playerWeapons->get(index)){
		if (this->_equipedWeapon != nullptr){
			this->_statesPoint->upDateStatesPoint(State::ATTACK, this->_statesPoint->getStatesPoint(State::ATTACK) - this->_equipedWeapon->getDamege());	//ステータス上昇
		}
		this->_equipedWeapon = this->_playerWeapons->get(index);

		this->_statesPoint->upDateStatesPoint(State::ATTACK, this->_statesPoint->getStatesPoint(State::ATTACK) + this->_equipedWeapon->getDamege());	//ステータス
		
		this->_statesPoint->setWeapon(this->_playerWeapons->get(index));
	}
	
}

void PlayerDatas::equipWear(int index)
{
	
	if (this->_equipedWear != this->_playerWears->get(index)){
		if (this->_equipedWear != nullptr){
			this->_statesPoint->upDateStatesPoint(State::DEFENSE, this->_statesPoint->getStatesPoint(State::DEFENSE) - this->_equipedWear->getStatesCorrection()->getStatesPoint(State::DEFENSE));	//ステータス下降
		}

		this->_equipedWear = this->_playerWears->get(index);	//変身

		this->_statesPoint->upDateStatesPoint(State::DEFENSE, this->_statesPoint->getStatesPoint(State::DEFENSE) + this->_equipedWear->getStatesCorrection()->getStatesPoint(State::DEFENSE));	//ステータス上昇
		this->_statesPoint->setWear(this->_playerWears->get(index));
	}
}

std::shared_ptr<WearWarehouse>  PlayerDatas::getWearWarehouse()
{
	return this->_wearWarehouse;
}

void PlayerDatas::updateStatesPoint()
{
	//equip時の装備のステータスと今の装備のステータスが違う場合は、壊れているので値更新
	if (this->_equipedWear->getStatesCorrection()->getStatesPoint(State::DEFENSE) != this->_statesPoint->getWearStatesPoint(State::DEFENSE)){
		this->_statesPoint->upDateStatesPoint(State::DEFENSE, this->_statesPoint->getStatesPoint(State::DEFENSE) - this->_statesPoint->getWearStatesPoint(State::DEFENSE));	//ステータスをなにも装備していない状態に戻す
		this->_statesPoint->upDateStatesPoint(State::DEFENSE, this->_statesPoint->getStatesPoint(State::DEFENSE) + this->_equipedWear->getStatesCorrection()->getStatesPoint(State::DEFENSE));	//ステータス再上昇（おそらく、 + 1）
		

		for (int i = 0; i < this->_playerWears->getSize(); i++){
			if (this->_equipedWear == this->_playerWears->get(i)){
				this->_statesPoint->setWear(this->_playerWears->get(i));
				break;
			}
		}
	}

	//equip時の装備のステータスと今の装備のステータスが違う場合は、壊れているので値更新
	if (this->_equipedWeapon->getDamege() != this->_statesPoint->getStatesPoint(State::ATTACK)){
		this->_statesPoint->upDateStatesPoint(State::ATTACK, this->_statesPoint->getStatesPoint(State::ATTACK) - this->_statesPoint->getStatesPoint(State::ATTACK));	//ステータスをなにも装備していない状態に戻す
		this->_statesPoint->upDateStatesPoint(State::ATTACK, this->_statesPoint->getStatesPoint(State::ATTACK) + this->_equipedWeapon->getDamege());	//ステータス再上昇（おそらく、 + 1）


		for (int i = 0; i < this->_playerWeapons->getSize(); i++){
			if (this->_equipedWeapon == this->_playerWeapons->get(i)){
				this->_statesPoint->setWeapon(this->_playerWeapons->get(i));
				break;
			}
		}
	}
}

std::shared_ptr<PlayerWearProtective>  PlayerDatas::getPlayerWears()
{
	return this->_playerWears;
}

std::shared_ptr<Weapon> PlayerDatas::getEquipedWeapon()
{
	return this->_equipedWeapon;
}

std::shared_ptr<WearProtective> PlayerDatas::getEquipedWear()
{
	return this->_equipedWear;
}

std::shared_ptr<PlayerWeapons> PlayerDatas::getPlayerWeapons()
{
	return this->_playerWeapons;
}

std::shared_ptr<PlayerKeyConfig> PlayerDatas::getPlayerKeyConfig()
{
	return this->_playerKeyConfig;
}

std::shared_ptr<WeaponWarehouse> PlayerDatas::getWeaponWarehouse()
{
	return this->_weaponWarehouse;
}

void PlayerDatas::initialize(std::shared_ptr<Character> player)
{
	if (this->_playerWeapons->isEmpty()){
		this->_playerWeapons->add(std::make_shared<SwordOfTheTree>("木の剣", WeaponType::SWORD));
		this->equipWeapon(0);
		
	}

	//std::make_shared<LeatherSuit>();
	if (this->_playerWears->isEmpty()){
		this->_playerWears->add(std::make_shared<LeatherSuit>("レザースーツ"));
		this->equipWear(0);
	}
}

PlayerDatas::~PlayerDatas()
{
}

bool PlayerDatas::load(int index)
{
	if (this->_statesPoint->load("Player" + std::to_string(index)))
	{
		this->_playerItems->load(index);
		this->_itemWarehouse->load(index);
		this->_weaponWarehouse->load(index);
		this->_wearWarehouse->load(index);
		this->_playerWeapons->load(index);
		this->_playerWears->load(index);


		this->_equipedWear;

		std::string fileName = "Save" + std::to_string(index + 1);
		fileName += ".csv";

		std::fstream ifs(fileName);

		if (!ifs.is_open()) {
			//printfDx("%s がありません\n", fileName.c_str());
		}
		else{

			std::string floorIndex_string;

			std::getline(ifs, floorIndex_string);

			this->_stageFloor = std::atoi(floorIndex_string.c_str());
			std::getline(ifs, this->_activeStageName);

		}

		std::string fileName3 = "EquipedWear" + std::to_string(index + 1);
		fileName3 += ".csv";

		std::fstream ifs3(fileName3);

		if (!ifs3.is_open()){
			//printfDx("%sがありません。\n", fileName3.c_str());
		}
		else{

			std::string weaponIndex_string;

			std::getline(ifs3, weaponIndex_string);

			this->_equipedWear = this->_playerWears->get(std::atoi(weaponIndex_string.c_str()));
		}


		std::string fileName2 = "EquipedWeapon" + std::to_string(index + 1);
		fileName2 += ".csv";

		std::fstream ifs2(fileName2);

		if (!ifs2.is_open()) {
		//	printfDx("%s がありません\n", fileName2.c_str());
		}
		else{

			std::string weaponIndex_string;

			std::getline(ifs2, weaponIndex_string);

			this->_equipedWeapon = this->_playerWeapons->get(std::atoi(weaponIndex_string.c_str()));
			if (index == 1 && this->_equipedWeapon == nullptr){
			//	exit(1);
			}
		}

		return true;
	}
	else{
		return false;
	}
}

void PlayerDatas::setStageFloor(int index)
{
	this->_stageFloor = index;
}

void PlayerDatas::setActiveStageName(std::string name)
{
	//if (name == nullptr){
		this->_activeStageName = name;
	//}
	//else{

	//}
}

void PlayerDatas::save(int index)
{
	this->_statesPoint->save("Player" + std::to_string(index));
	this->_playerItems->save(index);
	this->_itemWarehouse->save(index);
	this->_weaponWarehouse->save(index);
	this->_playerWeapons->save(index);
	this->_playerWears->save(index);


	std::string fileName = "Save" + std::to_string(index + 1);
	fileName += ".csv";

	std::ofstream afs(fileName, std::ios_base::trunc);

	if (!afs.is_open()){
		//printfDx("%sをセーブできませんでした。\n", fileName.c_str());
	}
	else{

		afs << this->_stageFloor << std::endl;
		afs << "StageSelect";
	}

	std::string fileName3 = "EquipedWear" + std::to_string(index + 1);
	fileName3 += ".csv";

	std::ofstream afs3(fileName3, std::ios_base::trunc);

	if (!afs3.is_open()){
		//printfDx("%sをセーブできませんでした。\n", fileName3.c_str());
	}
	else{


		int wearIndex = 0;

		while (this->_playerWears->get(wearIndex) != this->_equipedWear){

			wearIndex++;
		}
		afs3 << wearIndex << std::endl;
	}


	std::string fileName2 = "EquipedWeapon" + std::to_string(index + 1);
	fileName2 += ".csv";

	std::ofstream afs2(fileName2, std::ios_base::trunc);

	if (!afs2.is_open()){
		//printfDx("%sをセーブできませんでした。\n", fileName2.c_str());
	}
	else{
	

		int weaponIndex = 0;

		while (this->_playerWeapons->get(weaponIndex) != this->_equipedWeapon){

			weaponIndex++;
		}
		afs2 << weaponIndex << std::endl;
	}


}

std::shared_ptr<ItemWarehouse> PlayerDatas::getWarehouse()
{
	return this->_itemWarehouse;
}

void PlayerDatas::save_stageDataIncludes(int index)
{
	this->_statesPoint->save("Player" + std::to_string(index));
	this->_playerItems->save(index);
	this->_itemWarehouse->save(index);
	this->_weaponWarehouse->save(index);
	this->_playerWeapons->save(index);
	this->_playerWears->save(index);


	//this->_equipedWear = this->_playerWears->get(0);
	

	std::string fileName = "Save" + std::to_string(index + 1);
	fileName += ".csv";

	std::ofstream afs(fileName, std::ios_base::trunc);

	if (!afs.is_open()){
		//printfDx("%sをセーブできませんでした。\n", fileName.c_str());
	}
	else{

		afs << this->_stageFloor << std::endl;
		afs << this->_activeStageName;
	}




	std::string fileName3 = "EquipedWear" + std::to_string(index + 1);
	fileName3 += ".csv";

	std::ofstream afs3(fileName3, std::ios_base::trunc);

	if (!afs3.is_open()){
		//printfDx("%sをセーブできませんでした。\n", fileName3.c_str());
	}
	else{


		int wearIndex = 0;

		while (this->_playerWears->get(wearIndex) != this->_equipedWear){
			
			wearIndex++;
		}
		afs3 << wearIndex << std::endl;
	}


	std::string fileName2 = "EquipedWeapon" + std::to_string(index + 1);
	fileName2 += ".csv";

	std::ofstream afs2(fileName2, std::ios_base::trunc);

	if (!afs2.is_open()){
		//printfDx("%sをセーブできませんでした。\n", fileName2.c_str());
	}
	else{


		int weaponIndex = 0;

		while (this->_playerWeapons->get(weaponIndex) != this->_equipedWeapon){

			weaponIndex++;
		}

		afs2 << weaponIndex << std::endl;
	}

}

void PlayerDatas::removeStageData()
{
	this->_stageFloor = -1;
	this->_activeStageName.clear();
}

int PlayerDatas::getStageFloor()
{
	return this->_stageFloor;
}

std::string PlayerDatas::getActiveStageName()
{
	return this->_activeStageName;
}