#include "Weapon.h"
#include "HitBox.h"
#include "SwordOfTheTree.h"
#include "FlameBall.h"
#include "WaterBall.h"
#include "EnemyStandardWeapon.h"
#include "MessgeBox.h"
#include "Dark.h"
#include "Thunder.h"

Weapon::Weapon()
{
	this->_broken = false;
	this->_durability = 20;
}


Weapon::~Weapon()
{
}

void Weapon::setDurability(int durability)
{
	this->_durability = durability;
}

int Weapon::getDurability()
{
	return this->_durability;
}


void Weapon::giveDamage(int point)
{
	if (!this->_broken){
		this->_durability -= point;

		if (this->_durability < 0){
			MessgeBox::getInstance()->add("ぶき　が　こわれた！");

			this->_damege = 1;

			this->_broken = true;
		}
	}
}

std::shared_ptr<Weapon> Weapon::createInstance(std::string name)
{
	if (name == "木の剣"){
		return std::make_shared<SwordOfTheTree>("木の剣", WeaponType::SWORD);
	}
	else if (name == "真理の雷"){
		return std::make_shared<Thunder>("真理の雷");
	}
	else if (name == "雷鳴の杖"){
		return std::make_shared<Thunder>("雷鳴の杖");
	}
	else if (name == "大海原の杖"){
		return std::make_shared<WaterBall>("大海原の杖");
	}
	else if (name == "混沌の杖"){
		return std::make_shared<Dark>("混沌の杖");
	}
	else if (name == "楊炎の杖"){
		return std::make_shared<FlameBall>("楊炎の杖");
	}
	else if (name == "炎の息吹"){
		return std::make_shared<FlameBall>("炎の息吹");
	}
	else if (name == "岩石砕き"){
		return std::make_shared<SwordOfTheTree>("岩石砕き", WeaponType::HAMMER);
	}
	else if (name == "隕石砕き"){
		return std::make_shared<SwordOfTheTree>("隕石砕き", WeaponType::HAMMER);
	}
	else if (name == "岩石砕き"){
		return std::make_shared<SwordOfTheTree>("岩石砕き", WeaponType::HAMMER);
	}
	else if (name == "ユニオンハンマー"){
		return std::make_shared<SwordOfTheTree>("ユニオンハンマー", WeaponType::HAMMER);
	}
	else if (name == "ユニオンソード"){
		return std::make_shared<SwordOfTheTree>("ユニオンソード", WeaponType::SWORD);
	}
	else if (name == "打刀"){
		return std::make_shared<SwordOfTheTree>("ユニオンソード", WeaponType::SWORD);
	}
	else if (name == "ユニオソソード"){
		return std::make_shared<SwordOfTheTree>("ユニオソソード", WeaponType::SWORD);
	}


	else if (name == "バスターソード"){
		return std::make_shared<SwordOfTheTree>("バスターソード", WeaponType::SWORD);
	}
	else if (name == "フォースイーター"){
		return std::make_shared<SwordOfTheTree>("フォースイーター", WeaponType::SWORD);
	}
	else if (name == "クリスタルソード"){
		return std::make_shared<SwordOfTheTree>("クリスタルソード", WeaponType::SWORD);
	}
	else if (name == "アポカリプス"){
		return std::make_shared<SwordOfTheTree>("アポカリプス", WeaponType::SWORD);
	}
	else if (name == "舞雷刀"){
		return std::make_shared<SwordOfTheTree>("舞雷刀", WeaponType::SWORD);
	}
	else if (name == "ラグナロク"){
		return std::make_shared<SwordOfTheTree>("ラグナロク", WeaponType::SWORD);
	}
	else if (name == "ウォーハンマー"){
		return std::make_shared<SwordOfTheTree>("ウォーハンマー", WeaponType::HAMMER);
	}
	else if (name == "ミスリルハンマー"){
		return std::make_shared<SwordOfTheTree>("ミスリルハンマー", WeaponType::HAMMER);
	}
	else if (name == "ミョルニル"){
		return std::make_shared<SwordOfTheTree>("ミョルニル", WeaponType::HAMMER);
	}
	else if (name == "王者の槌"){
		return std::make_shared<SwordOfTheTree>("王者の槌", WeaponType::HAMMER);
	}
	else if (name == "ケリュケイオン"){
		return std::make_shared<FlameBall>("ケリュケイオン");
	}
	else if (name == "降妖宝杖"){
		return std::make_shared<WaterBall>("降妖宝杖");
	}
	else if (name == "闇の弾"){
		return std::make_shared<Dark>("闇の弾");
	}
	else if (name == "ニワトコの杖"){
		return std::make_shared<Dark>("ニワトコの杖");
	}
	else if (name == "静電気"){
		return std::make_shared<Thunder>("静電気");
	}
	else if (name == "ヴァジュラ"){
		return std::make_shared<Thunder>("ヴァジュラ");
	}


	else if (name == "鉄の剣"){
		return std::make_shared<SwordOfTheTree>("鉄の剣", WeaponType::SWORD);
	}
	else if (name == "戦士の剣"){
		return std::make_shared<SwordOfTheTree>("戦士の剣", WeaponType::SWORD);
	}
	else if (name == "聖剣エクスカリバー"){
		return std::make_shared<SwordOfTheTree>("聖剣エクスカリバー", WeaponType::SWORD);
	}
	else if (name == "炎の杖"){
		return std::make_shared<FlameBall>("炎の杖");
	}
	else if (name == "水の杖"){
		return std::make_shared<WaterBall>("水の杖");
	}
	else if (name == "闇の杖"){
		return std::make_shared<Dark>("闇の杖");
	}
	else if (name == "雷の杖"){
		return std::make_shared<Thunder>("雷の杖");
	}
	else if (name == "クラーケンキラー"){
		return std::make_shared<Thunder>("クラーケンキラー");
	}



	else{
		return nullptr;
	}
}

std::shared_ptr<Weapon> Weapon::createInstance(int damage)
{
	return std::make_shared<EnemyStandardWeapon>(damage);
}