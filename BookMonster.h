#pragma once
#include "Enemy.h"
#include "Character.h"
#include "HitBox.h"
#include "Random.h"
#include "PlayerFollow.h"
#include "RandomMove.h"

class TurnController;

class BookMonster :
	public Enemy
{
private:
	bool _active;
	void move();
	void attack();
public:
	void actionOfCollision(std::shared_ptr<HitBox> hitBox);
	bool beExamined();
	void update();	//自分のターンでなくても行わなれけばならない処理を書く。
	void action();	//1ターンに行うことをかく
	BookMonster(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController);
	~BookMonster();
};

