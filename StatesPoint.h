#pragma once
#include <map>
#include"State.h"
#include <memory>

class WearProtective;
class Weapon;

class StatesPoint
{
private:
	typedef struct{
		int _attack;
		int _hp;         //HP
		int _mp;         //MP
		int _money;      //������
		int _exp;        //�o���l
		int _level;
		int _paralysisResistance;
		int _poisonResistance;
		int _defense;
		int _durability;
		int _hpMax;
		int _mpMax;
	}StatesPoints;

	StatesPoints _statesPoints;
	StatesPoints _wearPoints;
	StatesPoints _weaponPoints;
	int _hpMax;
	int _mpMax;

	std::map<State::States, int*> _point_stateMap;    //  States �� ���� �̘A�z�z��
	std::map<State::States, int*> _point_wearStateMap;    //  States �� ���� �̘A�z�z��
public:

	void updateMax(State::States STATE);
	int getStatesPoint(State::States STATE);
	bool save(int index);
	bool save(std::string dataFileName);
	bool load(std::string dataFileName);
	bool load(int index);

	int getWeaponDamage();
	int getWearStatesPoint(State::States STATE);
	void setWear(std::shared_ptr<WearProtective> wear);
	void setWeapon(std::shared_ptr<Weapon> weapon);
	void temporarilyUpdateStatesPoint(State::States STATE, int point, int turn);
	void upDateStatesPoint(State::States STATE, int point);
	StatesPoint();
	~StatesPoint();
};

