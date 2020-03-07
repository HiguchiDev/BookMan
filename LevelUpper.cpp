#include "LevelUpper.h"
#include "DxLib.h"
#include "MessgeBox.h"
#include "PlayerWeapons.h"
#include "PlayerWearProtective.h"

LevelUpper::LevelUpper(std::shared_ptr<PlayerDatas> statesPoint)
{

	_playerDatas = statesPoint;
	this->_exp_nextLevelUp = 100;
	for (int i = 0; i < statesPoint->getStatesPoint()->getStatesPoint(State::LEVEL); i++){
		_exp_nextLevelUp *= 1.1;
	}





}


LevelUpper::~LevelUpper()
{
}

void LevelUpper::addExp(std::shared_ptr<CharacterData> enemyStatesPoint, bool isInit)
{

	if (_playerDatas->getStatesPoint() != nullptr){
		_playerDatas->getStatesPoint()->upDateStatesPoint(State::EXP, _playerDatas->getStatesPoint()->getStatesPoint(State::EXP) + enemyStatesPoint->getStatesPoint()->getStatesPoint(State::EXP));

		

		while (_playerDatas->getStatesPoint()->getStatesPoint(State::EXP) >= _exp_nextLevelUp){
			//500の場合
			_playerDatas->getStatesPoint()->upDateStatesPoint(State::LEVEL, _playerDatas->getStatesPoint()->getStatesPoint(State::LEVEL) + 1);
			_playerDatas->getStatesPoint()->upDateStatesPoint(State::EXP, _playerDatas->getStatesPoint()->getStatesPoint(State::EXP) - _exp_nextLevelUp);	//500 - 100 = 400
			_playerDatas->getStatesPoint()->upDateStatesPoint(State::HPMAX, _playerDatas->getStatesPoint()->getStatesPoint(State::HPMAX) + 15);
			_playerDatas->getStatesPoint()->upDateStatesPoint(State::DEFENSE, _playerDatas->getStatesPoint()->getStatesPoint(State::DEFENSE) + 1);

			
			/*
			for (int i = 0; i < _playerDatas->getPlayerWears()->getSize(); i++){
				if (_playerDatas->getPlayerWears()->get(i) == _playerDatas->getEquipedWear()){
					_playerDatas->equipWear(i);
				}
			}


			for (int i = 0; i < _playerDatas->getPlayerWeapons()->getSize(); i++){
				if (_playerDatas->getPlayerWeapons()->get(i) == _playerDatas->getEquipedWeapon()){
					_playerDatas->equipWeapon(i);
				}
			}*/


			if (!isInit){
				MessgeBox::getInstance()->add("レベルがあがった！");
			}
			_exp_nextLevelUp *= 1.1;
		}


	}
}

void LevelUpper::addExp(std::shared_ptr<CharacterData> enemyStatesPoint)
{

	if (_playerDatas->getStatesPoint() != nullptr){
		_playerDatas->getStatesPoint()->upDateStatesPoint(State::EXP, _playerDatas->getStatesPoint()->getStatesPoint(State::EXP) + enemyStatesPoint->getStatesPoint()->getStatesPoint(State::EXP));

		

		while (_playerDatas->getStatesPoint()->getStatesPoint(State::EXP) >= _exp_nextLevelUp){
			//500の場合
			_playerDatas->getStatesPoint()->upDateStatesPoint(State::LEVEL, _playerDatas->getStatesPoint()->getStatesPoint(State::LEVEL) + 1);
			_playerDatas->getStatesPoint()->upDateStatesPoint(State::EXP, _playerDatas->getStatesPoint()->getStatesPoint(State::EXP) - _exp_nextLevelUp);	//500 - 100 = 400
			_playerDatas->getStatesPoint()->upDateStatesPoint(State::HPMAX, _playerDatas->getStatesPoint()->getStatesPoint(State::HPMAX) + 15);
			_playerDatas->getStatesPoint()->upDateStatesPoint(State::DEFENSE, _playerDatas->getStatesPoint()->getStatesPoint(State::DEFENSE) + 1);
			_playerDatas->getStatesPoint()->upDateStatesPoint(State::HITPOINT, _playerDatas->getStatesPoint()->getStatesPoint(State::HPMAX));
			for (int i = 0; i < _playerDatas->getPlayerWears()->getSize(); i++){
				if (_playerDatas->getPlayerWears()->get(i) == _playerDatas->getEquipedWear()){
					_playerDatas->equipWear(i);
				}
			}


			for (int i = 0; i < _playerDatas->getPlayerWeapons()->getSize(); i++){
				if (_playerDatas->getPlayerWeapons()->get(i) == _playerDatas->getEquipedWeapon()){
					_playerDatas->equipWeapon(i);
				}
			}


			//	if (!isInit){
			MessgeBox::getInstance()->add("レベルがあがった！");
			//	}
			_exp_nextLevelUp *= 1.1;
		}


	}
}



int LevelUpper::nextLevelUpExp()
{
	return _exp_nextLevelUp - _playerDatas->getStatesPoint()->getStatesPoint(State::EXP);
}

void LevelUpper::initialize(std::shared_ptr<PlayerDatas> statesPoint)
{
	_playerDatas = statesPoint;


	_exp_nextLevelUp = 100;
}