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
			MessgeBox::getInstance()->add("�Ԃ��@���@����ꂽ�I");

			this->_damege = 1;

			this->_broken = true;
		}
	}
}

std::shared_ptr<Weapon> Weapon::createInstance(std::string name)
{
	if (name == "�؂̌�"){
		return std::make_shared<SwordOfTheTree>("�؂̌�", WeaponType::SWORD);
	}
	else if (name == "�^���̗�"){
		return std::make_shared<Thunder>("�^���̗�");
	}
	else if (name == "���̏�"){
		return std::make_shared<Thunder>("���̏�");
	}
	else if (name == "��C���̏�"){
		return std::make_shared<WaterBall>("��C���̏�");
	}
	else if (name == "���ׂ̏�"){
		return std::make_shared<Dark>("���ׂ̏�");
	}
	else if (name == "�k���̏�"){
		return std::make_shared<FlameBall>("�k���̏�");
	}
	else if (name == "���̑���"){
		return std::make_shared<FlameBall>("���̑���");
	}
	else if (name == "��΍ӂ�"){
		return std::make_shared<SwordOfTheTree>("��΍ӂ�", WeaponType::HAMMER);
	}
	else if (name == "覐΍ӂ�"){
		return std::make_shared<SwordOfTheTree>("覐΍ӂ�", WeaponType::HAMMER);
	}
	else if (name == "��΍ӂ�"){
		return std::make_shared<SwordOfTheTree>("��΍ӂ�", WeaponType::HAMMER);
	}
	else if (name == "���j�I���n���}�["){
		return std::make_shared<SwordOfTheTree>("���j�I���n���}�[", WeaponType::HAMMER);
	}
	else if (name == "���j�I���\�[�h"){
		return std::make_shared<SwordOfTheTree>("���j�I���\�[�h", WeaponType::SWORD);
	}
	else if (name == "�œ�"){
		return std::make_shared<SwordOfTheTree>("���j�I���\�[�h", WeaponType::SWORD);
	}
	else if (name == "���j�I�\�\�[�h"){
		return std::make_shared<SwordOfTheTree>("���j�I�\�\�[�h", WeaponType::SWORD);
	}


	else if (name == "�o�X�^�[�\�[�h"){
		return std::make_shared<SwordOfTheTree>("�o�X�^�[�\�[�h", WeaponType::SWORD);
	}
	else if (name == "�t�H�[�X�C�[�^�["){
		return std::make_shared<SwordOfTheTree>("�t�H�[�X�C�[�^�[", WeaponType::SWORD);
	}
	else if (name == "�N���X�^���\�[�h"){
		return std::make_shared<SwordOfTheTree>("�N���X�^���\�[�h", WeaponType::SWORD);
	}
	else if (name == "�A�|�J���v�X"){
		return std::make_shared<SwordOfTheTree>("�A�|�J���v�X", WeaponType::SWORD);
	}
	else if (name == "������"){
		return std::make_shared<SwordOfTheTree>("������", WeaponType::SWORD);
	}
	else if (name == "���O�i���N"){
		return std::make_shared<SwordOfTheTree>("���O�i���N", WeaponType::SWORD);
	}
	else if (name == "�E�H�[�n���}�["){
		return std::make_shared<SwordOfTheTree>("�E�H�[�n���}�[", WeaponType::HAMMER);
	}
	else if (name == "�~�X�����n���}�["){
		return std::make_shared<SwordOfTheTree>("�~�X�����n���}�[", WeaponType::HAMMER);
	}
	else if (name == "�~�����j��"){
		return std::make_shared<SwordOfTheTree>("�~�����j��", WeaponType::HAMMER);
	}
	else if (name == "���҂̒�"){
		return std::make_shared<SwordOfTheTree>("���҂̒�", WeaponType::HAMMER);
	}
	else if (name == "�P�����P�C�I��"){
		return std::make_shared<FlameBall>("�P�����P�C�I��");
	}
	else if (name == "�~�d���"){
		return std::make_shared<WaterBall>("�~�d���");
	}
	else if (name == "�ł̒e"){
		return std::make_shared<Dark>("�ł̒e");
	}
	else if (name == "�j���g�R�̏�"){
		return std::make_shared<Dark>("�j���g�R�̏�");
	}
	else if (name == "�Ód�C"){
		return std::make_shared<Thunder>("�Ód�C");
	}
	else if (name == "���@�W����"){
		return std::make_shared<Thunder>("���@�W����");
	}


	else if (name == "�S�̌�"){
		return std::make_shared<SwordOfTheTree>("�S�̌�", WeaponType::SWORD);
	}
	else if (name == "��m�̌�"){
		return std::make_shared<SwordOfTheTree>("��m�̌�", WeaponType::SWORD);
	}
	else if (name == "�����G�N�X�J���o�["){
		return std::make_shared<SwordOfTheTree>("�����G�N�X�J���o�[", WeaponType::SWORD);
	}
	else if (name == "���̏�"){
		return std::make_shared<FlameBall>("���̏�");
	}
	else if (name == "���̏�"){
		return std::make_shared<WaterBall>("���̏�");
	}
	else if (name == "�ł̏�"){
		return std::make_shared<Dark>("�ł̏�");
	}
	else if (name == "���̏�"){
		return std::make_shared<Thunder>("���̏�");
	}
	else if (name == "�N���[�P���L���["){
		return std::make_shared<Thunder>("�N���[�P���L���[");
	}



	else{
		return nullptr;
	}
}

std::shared_ptr<Weapon> Weapon::createInstance(int damage)
{
	return std::make_shared<EnemyStandardWeapon>(damage);
}