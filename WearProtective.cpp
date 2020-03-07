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

	if (name == "���U�[�X�[�c"){
		return std::make_shared<LeatherSuit>("���U�[�X�[�c");
	}
	else if (name == "�{���z�̖���"){
		return std::make_shared<WitchWearProtective>("�{���z�̖���");
	}
	else if (name == "���@�g���̃��[�u"){
		return std::make_shared<WitchWearProtective>("���@�g���̃��[�u");
	}
	else if (name == "�z�[���[���[�u"){
		return std::make_shared<WitchWearProtective>("�z�[���[���[�u");
	}
	else if (name == "�����̃��[�u"){
		return std::make_shared<WitchWearProtective>("�����̃��[�u");
	}
	else if (name == "���҂̕�"){
		return std::make_shared<WitchWearProtective>("���҂̕�");
	}
	else if (name == "�S�̊Z"){
		return std::make_shared<SwordsMan>("�S�̊Z");
	}
	else if (name == "�͂��˂̊Z"){
		return std::make_shared<SwordsMan>("�͂��˂̊Z");
	}
	else if (name == "�~�X�����A�[�}�["){
		return std::make_shared<SwordsMan>("�~�X�����A�[�}�[");
	}
	else if (name == "�}�N�V�~���A��"){
		return std::make_shared<SwordsMan>("�}�N�V�~���A��");
	}


	else if (name == "���̃��[�u"){
		return std::make_shared<WitchWearProtective>("���̃��[�u");
	}
	else if (name == "�����̃��[�u"){
		return std::make_shared<WitchWearProtective>("�����̃��[�u");
	}
	else if (name == "�E�҂̃��[�u"){
		return std::make_shared<WitchWearProtective>("�E�҂̃��[�u");
	}
	else if (name == "�����̊Z"){
		return std::make_shared<SwordsMan>("�����̊Z");
	}
	else if (name == "��m�̊Z"){
		return std::make_shared<SwordsMan>("��m�̊Z");
	}
	else if (name == "���R�m�̊Z"){
		return std::make_shared<SwordsMan>("���R�m�̊Z");
	}

	else if (name == "���j�I�\���m�̊Z"){
		return std::make_shared<SwordsMan>("���j�I�\���m�̊Z");
	}
	else if (name == "�_�C���̊Z"){
		return std::make_shared<SwordsMan>("�_�C���̊Z");
	}
	else if (name == "���̊Z"){
		return std::make_shared<SwordsMan>("���̊Z");
	}

	else if (name == "�n�����@�g���̃��[�u"){
		return std::make_shared<WitchWearProtective>("�n�����@�g���̃��[�u");
	}
	else if (name == "�e�҂̃��[�u"){
		return std::make_shared<WitchWearProtective>("�e�҂̃��[�u");
	}
	else if (name == "�����@�̃��[�u"){
		return std::make_shared<WitchWearProtective>("�����@�̃��[�u");
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
			MessgeBox::getInstance()->add("�����с@���@����ꂽ�I");

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