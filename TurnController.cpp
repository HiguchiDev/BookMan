#include "TurnController.h"
#include <algorithm>    // std::copy
#include <iterator>
#include <vector>
#include "FloorOfTheDungeon.h"
#include "DxLib.h"
#include "Collision.h"
#include "Character.h"

TurnController::TurnController()
{
	this->_TYPE = CharacterType::CharacterTypes::PLAYER;
}


TurnController::~TurnController()
{

}

bool TurnController::isMyTurn(CharacterType::CharacterTypes TYPE)
{
	return this->_TYPE == TYPE;
}

void TurnController::changeTurn()
{
	if (this->_TYPE == CharacterType::CharacterTypes::ENEMY){
		this->_TYPE = CharacterType::CharacterTypes::PLAYER;
		Collision::getInstance()->actionOfCollision(false);
	}
	else{
		this->_TYPE = CharacterType::ENEMY;
		Collision::getInstance()->actionOfCollision(true);
	}

	Collision::getInstance()->checkFinishFieldMaterials();
}

void TurnController::setTurnFinishedCharacter(std::shared_ptr<Character> character)
{
	if (this->_playerCharacter == character && this->_TYPE == CharacterType::PLAYER){
		this->changeTurn();
		this->_playerCharacter = nullptr;
	}
	else{
		std::vector< std::shared_ptr< Character > >::iterator cIter = std::find(this->_enemyCharacters.begin(), this->_enemyCharacters.end(), character);
		if (cIter != this->_enemyCharacters.end()){
			this->_enemyCharacters.erase(cIter);
		}

		if (this->_enemyCharacters.empty() && this->_TYPE == CharacterType::ENEMY){
			this->changeTurn();
		}
	}
}

void TurnController::initialize(std::vector<std::shared_ptr< Character >> enemyCharacters, std::shared_ptr<Character> playerCharacter)
{
	this->_playerCharacter = playerCharacter;

	this->_enemyCharacters.clear();

	for (int i = 0; i < enemyCharacters.size(); i++){
		this->_enemyCharacters.push_back(enemyCharacters[i]);
	}

	for (int i = 0; i < this->_enemyCharacters.size(); i++){
		if (this->_enemyCharacters[i]->isFinish()){
			this->_enemyCharacters.erase(this->_enemyCharacters.begin() + i);
			i--;
		}
	}

	this->_TYPE = CharacterType::CharacterTypes::PLAYER;
	if (enemyCharacters.empty()){
		Collision::getInstance()->actionOfCollision(false);
	}

	this->_playerCharacter->turnReset();

	for (auto enemy : this->_enemyCharacters){
		enemy->turnReset();
	}

}

bool TurnController::isFinish()
{
	if (this->_playerCharacter == nullptr &&
		this->_enemyCharacters.empty()){
		
		return true;
	}
	
	return false;
}