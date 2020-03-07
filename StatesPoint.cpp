#include "StatesPoint.h"
#include <stdio.h>
#include "DxLib.h"
#include <string>
#include <fstream>
#include "Weapon.h"
#include "WearProtective.h"

StatesPoint::StatesPoint()
{

	this->_statesPoints._attack = 0;
	this->_statesPoints._hp = 50;
	this->_statesPoints._mp = 0;
	this->_statesPoints._money = 0;
	this->_statesPoints._exp = 0;
	this->_statesPoints._level = 0;
	this->_statesPoints._defense = 0;
	this->_statesPoints._durability = 0;
	this->_statesPoints._hpMax = 50;
	this->_statesPoints._mpMax = 0;

	this->_wearPoints._attack = 0;
	this->_wearPoints._hp = 90;
	this->_wearPoints._mp = 0;
	this->_wearPoints._money = 0;
	this->_wearPoints._exp = 0;
	this->_wearPoints._level = 0;
	this->_wearPoints._defense = 0;
	this->_wearPoints._durability = 0;

	this->_weaponPoints._attack = 0;
	this->_weaponPoints._hp = 90;
	this->_weaponPoints._mp = 0;
	this->_weaponPoints._money = 0;
	this->_weaponPoints._exp = 0;
	this->_weaponPoints._level = 0;
	this->_weaponPoints._defense = 0;
	this->_weaponPoints._durability = 0;

	_point_stateMap[State::States::ATTACK] = &this->_statesPoints._attack;
	_point_stateMap[State::States::HITPOINT] = &this->_statesPoints._hp;
	_point_stateMap[State::States::MAGICPOINT] = &this->_statesPoints._mp;
	_point_stateMap[State::States::DEFENSE] = &this->_statesPoints._defense;
	_point_stateMap[State::States::EXP] = &this->_statesPoints._exp;
	_point_stateMap[State::States::LEVEL] = &this->_statesPoints._level;
	_point_stateMap[State::States::MONEY] = &this->_statesPoints._money;
	_point_stateMap[State::States::DURABILITY] = &this->_statesPoints._durability;
	_point_stateMap[State::States::HPMAX] = &this->_statesPoints._hpMax;
	_point_stateMap[State::States::MPMAX] = &this->_statesPoints._mpMax;

	_point_wearStateMap[State::States::ATTACK] = &this->_wearPoints._attack;
	_point_wearStateMap[State::States::HITPOINT] = &this->_wearPoints._hp;
	_point_wearStateMap[State::States::MAGICPOINT] = &this->_wearPoints._mp;
	_point_wearStateMap[State::States::DEFENSE] = &this->_wearPoints._defense;
	_point_wearStateMap[State::States::EXP] = &this->_wearPoints._exp;
	_point_wearStateMap[State::States::LEVEL] = &this->_wearPoints._level;
	_point_wearStateMap[State::States::MONEY] = &this->_wearPoints._money;
	_point_wearStateMap[State::States::DURABILITY] = &this->_wearPoints._durability;
}

void StatesPoint::setWear(std::shared_ptr<WearProtective> wear)
{
	this->_wearPoints._attack = wear->getStatesCorrection()->getStatesPoint(State::States::ATTACK);
	this->_wearPoints._hp = wear->getStatesCorrection()->getStatesPoint(State::States::HITPOINT);
	this->_wearPoints._mp = wear->getStatesCorrection()->getStatesPoint(State::States::MAGICPOINT);
	this->_wearPoints._defense = wear->getStatesCorrection()->getStatesPoint(State::States::DEFENSE);
	this->_wearPoints._exp = wear->getStatesCorrection()->getStatesPoint(State::States::EXP);
	this->_wearPoints._level = wear->getStatesCorrection()->getStatesPoint(State::States::LEVEL);
	this->_wearPoints._money = wear->getStatesCorrection()->getStatesPoint(State::States::MONEY);
}

void StatesPoint::setWeapon(std::shared_ptr<Weapon> weapon)
{
	this->_weaponPoints._attack = weapon->getDamege();
}

StatesPoint::~StatesPoint()
{
}
// STATEを受け取り、それに対応した能力値を返す
int StatesPoint::getStatesPoint(State::States STATE){
	return *_point_stateMap[STATE];
};

// 能力値の更新
void StatesPoint::upDateStatesPoint(State::States STATE, int point)
{
	//HP回復量に限界をつけている
	if (STATE == State::HITPOINT && *_point_stateMap[State::HPMAX] <= point){
		*_point_stateMap[STATE] = *_point_stateMap[State::HPMAX];
	}
	//普通に更新
	else{
		*_point_stateMap[STATE] = point;
	}
};

void temporarilyUpdateStatesPoint(State::States STATE, int point, int turn)
{
	
}

int StatesPoint::getWeaponDamage()
{
	return this->_weaponPoints._attack;
}

int StatesPoint::getWearStatesPoint(State::States STATE)
{
	return *this->_point_wearStateMap[STATE];
}

bool StatesPoint::save(int index)
{
	FILE *fp;
	
	std::string fileName = "saveData" + std::to_string(index + 1);
	fileName += ".dat";

	fopen_s(&fp, fileName.c_str(), "wb");//バイナリファイルを開く

	if (fp == NULL){//エラーが起きたらNULLを返す
		return false;
	}

	fwrite(&this->_statesPoints, sizeof(this->_statesPoints), 1, fp); // SaveData_t構造体の中身を出力
	fclose(fp);//ファイルを閉じる




	return true;
}

bool StatesPoint::load(int index)
{
	FILE *fp;

	std::string fileName = "saveData" + std::to_string(index + 1);
	fileName += ".dat";

	fopen_s(&fp, fileName.c_str(), "wb");//バイナリファイルを開く

	if (fp == NULL){//エラーが起きたらNULLを返す
		return false;
	}

	fread(&this->_statesPoints, sizeof(this->_statesPoints), 1, fp);
	fclose(fp);//ファイルを閉じる

	return true;
}

bool StatesPoint::save(std::string dataFileName)
{

	std::string fileName = dataFileName + "StatesData.csv";

	std::ofstream ifs(fileName, std::ios_base::trunc);

	if (!ifs.is_open()) {
	//	printfDx("%sをロードできませんでした。\n", fileName.c_str());
		return false;
	}
	else{
		int i = 0;

		//while (1){
		std::string statesPoint;


		if (ifs.eof() || ifs.fail()){
			return false;
		}

		ifs << this->_statesPoints._hp << std::endl;
		ifs << this->_statesPoints._mp << std::endl;
		ifs << this->_statesPoints._exp << std::endl;
		ifs << this->_statesPoints._attack << std::endl;
		ifs << this->_statesPoints._defense << std::endl;
		ifs << this->_statesPoints._level << std::endl;
		ifs << this->_statesPoints._money << std::endl;
		ifs << this->_statesPoints._paralysisResistance << std::endl;
		ifs << this->_statesPoints._poisonResistance << std::endl;
		ifs << this->_statesPoints._hpMax << std::endl;

	}

	return true;
}


bool StatesPoint::load(std::string dataFileName)
{
	
	std::string fileName = dataFileName + "StatesData.csv";

	std::fstream ifs(fileName);

	if (!ifs.is_open()) {
		//printfDx("%sをロードできませんでした。\n", fileName.c_str());
		return false;
	}
	else{
		int i = 0;

		//while (1){
			std::string statesPoint;
			

			if (ifs.eof() || ifs.fail()){
				return false;
			}
			
			std::getline(ifs, statesPoint);
			this->_statesPoints._hp = std::atoi(statesPoint.c_str());

			std::getline(ifs, statesPoint);
			this->_statesPoints._mp = std::atoi(statesPoint.c_str());

			std::getline(ifs, statesPoint);
			this->_statesPoints._exp = std::atoi(statesPoint.c_str());

			std::getline(ifs, statesPoint);
			this->_statesPoints._attack = std::atoi(statesPoint.c_str());

			std::getline(ifs, statesPoint);
			this->_statesPoints._defense = std::atoi(statesPoint.c_str());

			std::getline(ifs, statesPoint);
			this->_statesPoints._level = std::atoi(statesPoint.c_str());

			std::getline(ifs, statesPoint);
			this->_statesPoints._money = std::atoi(statesPoint.c_str());

			std::getline(ifs, statesPoint);
			this->_statesPoints._paralysisResistance = std::atoi(statesPoint.c_str());

			std::getline(ifs, statesPoint);
			this->_statesPoints._poisonResistance = std::atoi(statesPoint.c_str());
			
			std::getline(ifs, statesPoint);
			this->_statesPoints._hpMax = std::atoi(statesPoint.c_str());
			//if (dataFileName == "魔女"){
			//	printfDx("%s : %d\n", dataFileName.c_str(), this->_statesPoints._hp);
			//}
			this->_statesPoints._hpMax = this->_statesPoints._hp;
	}

	return true;
}
