#pragma once
#include "FieldMaterial.h"
#include <memory>
#include <string>

class Player;

class Stairs : public FieldMaterial, public std::enable_shared_from_this<Stairs>
{
private:
	bool _playerCollision;
public:
	Stairs(std::string fileName, std::shared_ptr<Position> position);
	~Stairs();
	void initializePosition();
	static std::shared_ptr<Stairs> createStairs(std::string fileName, std::shared_ptr<Position> position);
	void updateCollisionInformation(std::shared_ptr<Position> newPosition);
	void checkPlayerCollision(std::shared_ptr<Character> player);
	bool isPlayerCollision();
	void action();
};

