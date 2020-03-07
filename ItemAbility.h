#pragma once
#include <memory>
#include <string>

class PlayerDatas;

class ItemAbility
{
protected:
	std::string _name;
	std::string _explanatoryText;

	
public:
	std::string getExplanatoryText(){ return this->_explanatoryText; };
	virtual bool isWeaponChange(){ return false; };
	virtual bool isWearChange(){ return false; };
	//virtual bool isTrapChange(){ return false; };
	std::string toString();
	static std::shared_ptr<ItemAbility> createInstance(std::string fileName);
	virtual bool throwAbility(std::shared_ptr<PlayerDatas> playerDatas){ return false; };
	virtual void use(std::shared_ptr<PlayerDatas> playerDatas) = 0;
	ItemAbility();
	~ItemAbility();
};

