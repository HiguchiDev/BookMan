#include "WearProtective.h"
#include "Object_3D_Duplicate.h"
#include "MessgeBox.h"
#include "LeatherSuit.h"
#include "WitchWearProtective.h"
#include "SwordsMan.h"

WearProtective::WearProtective(std::string name)
{
	this->_broken = false;

	this->_name = name;
	this->_statesCorrection = std::make_shared<StatesPoint>();
	this->_statesCorrection->load(name);
	this->_statesCorrection->upDateStatesPoint(State::DURABILITY, 50);
}


WearProtective::~WearProtective()
{

}

void WearProtective::setDurability(int durability)                                          
{
	this->_statesCorrection->upDateStatesPoint(State::DURABILITY, durability);
}

std::shared_ptr<StatesPoint> WearProtective::getStatesCorrection()
{                 
	return this->_statesCorrection;
}

std::shared_ptr<WearProtective> WearProtective::createInstance(std::string name)
{

	if (name == "レザースーツ"){
		return std::make_shared<LeatherSuit>("レザースーツ");
	}
	else if (name == "ボロ布の魔服"){
		return std::make_shared<WitchWearProtective>("ボロ布の魔服");
	}
	else if (name == "魔法使いのローブ"){
		return std::make_shared<WitchWearProtective>("魔法使いのローブ");
	}
	else if (name == "ホーリーローブ"){
		return std::make_shared<WitchWearProtective>("ホーリーローブ");
	}
	else if (name == "しんりのローブ"){
		return std::make_shared<WitchWearProtective>("しんりのローブ");
	}
	else if (name == "賢者の服"){
		return std::make_shared<WitchWearProtective>("賢者の服");
	}
	else if (name == "鉄の鎧"){
		return std::make_shared<SwordsMan>("鉄の鎧");
	}
	else if (name == "はがねの鎧"){
		return std::make_shared<SwordsMan>("はがねの鎧");
	}
	else if (name == "ミスリルアーマー"){
		return std::make_shared<SwordsMan>("ミスリルアーマー");
	}
	else if (name == "マクシミリアン"){
		return std::make_shared<SwordsMan>("マクシミリアン");
	}


	else if (name == "風のローブ"){
		return std::make_shared<WitchWearProtective>("風のローブ");
	}
	else if (name == "ただのローブ"){
		return std::make_shared<WitchWearProtective>("ただのローブ");
	}
	else if (name == "勇者のローブ"){
		return std::make_shared<WitchWearProtective>("勇者のローブ");
	}
	else if (name == "ただの鎧"){
		return std::make_shared<SwordsMan>("ただの鎧");
	}
	else if (name == "戦士の鎧"){
		return std::make_shared<SwordsMan>("戦士の鎧");
	}
	else if (name == "聖騎士の鎧"){
		return std::make_shared<SwordsMan>("聖騎士の鎧");
	}

	else if (name == "ユニオソ剣士の鎧"){
		return std::make_shared<SwordsMan>("ユニオソ剣士の鎧");
	}
	else if (name == "ダイヤの鎧"){
		return std::make_shared<SwordsMan>("ダイヤの鎧");
	}
	else if (name == "金の鎧"){
		return std::make_shared<SwordsMan>("金の鎧");
	}

	else if (name == "熟練魔法使いのローブ"){
		return std::make_shared<WitchWearProtective>("熟練魔法使いのローブ");
	}
	else if (name == "覇者のローブ"){
		return std::make_shared<WitchWearProtective>("覇者のローブ");
	}
	else if (name == "黒魔法のローブ"){
		return std::make_shared<WitchWearProtective>("黒魔法のローブ");
	}


	else{
		return nullptr;
	}
}

void WearProtective::giveDamage(int point)
{
	if (!this->_broken){

		this->_statesCorrection->upDateStatesPoint(State::DURABILITY, this->_statesCorrection->getStatesPoint(State::DURABILITY) - point);

		if (this->_statesCorrection->getStatesPoint(State::DURABILITY) < 0){
			MessgeBox::getInstance()->add("そうび　が　こわれた！");

			this->_statesCorrection->upDateStatesPoint(State::DURABILITY, 1);
			this->_statesCorrection->upDateStatesPoint(State::ATTACK, 1);
			this->_statesCorrection->upDateStatesPoint(State::HITPOINT, 1);
			this->_statesCorrection->upDateStatesPoint(State::DEFENSE, 1);
			this->_statesCorrection->upDateStatesPoint(State::MAGICPOINT, 1);

			this->_broken = true;
		}
	}
}

WearProtective::Type WearProtective::getType()
{
	return this->_TYPE;
}