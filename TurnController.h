#pragma once
#include <vector>
#include <memory>
#include "CharacterType.h"

class Character;
class FloorOfTheDungeon;

class TurnController
{
public:


	void update(std::shared_ptr<FloorOfTheDungeon> floorOfTheDungeon);
	bool isMyTurn(CharacterType::CharacterTypes TYPE);
	void setTurnFinishedCharacter(std::shared_ptr<Character> character);
	void actionOfTurnChange(std::shared_ptr<FloorOfTheDungeon> floorOfTheDungeon);
	void initialize(std::vector<std::shared_ptr< Character >> enemyCharacters, std::shared_ptr<Character> playerCharacter);
	bool isFinish();
	
	TurnController();
	~TurnController();
private:
	void changeTurn();
	CharacterType::CharacterTypes _TYPE;
	std::shared_ptr<Character> _playerCharacter;
	std::vector<std::shared_ptr< Character >> _enemyCharacters;
	
	
};

