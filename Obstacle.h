#pragma once
#include "FieldMaterial.h"
#include <string>
#include <vector>

class Position;
class Item;

class Obstacle
	: public FieldMaterial, public std::enable_shared_from_this<Obstacle>
{
private:
	void initializePosition();
	static std::vector< std::string > _obstacleNames;
public:
	virtual std::shared_ptr<Item> getChangedItem(){ return nullptr; };
	virtual void action();
	static std::shared_ptr<Obstacle> createObstacle(std::string fileName, std::shared_ptr<Position>);
	void updateCollisionInformation(std::shared_ptr<Position> newPosition);
	Obstacle(std::string fileName, std::shared_ptr<Position> position);
	~Obstacle();
};

