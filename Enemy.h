#pragma once
#include "Character.h"
#include "HitBox.h"
#include "Random.h"
#include "PlayerFollow.h"
#include "RandomMove.h"

class TurnController;

class Enemy
	: public Character
{
protected:
	
	PlayerFollow _playerFollow;	//プレイヤーの方角を取得するクラス。
	Random _randomGetter;	//確率を取得する。
	RandomMove _randomMove;
	virtual void move();
	virtual void attack();
public:
	virtual void actionOfCollision(std::shared_ptr<HitBox> hitBox);
	virtual bool beExamined(){ return false; };
	void initialize();
	virtual void update();	//自分のターンでなくても行わなれけばならない処理を書く。
	virtual void action();	//1ターンに行うことをかく
	Enemy(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController);
	~Enemy();
};

