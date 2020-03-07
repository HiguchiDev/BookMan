#pragma once
#include "Enemy.h"
#include "Character.h"
#include "HitBox.h"
#include "Random.h"
#include "PlayerFollow.h"
#include "RandomMove.h"

class TurnController;

class DiffMimic :
	public Enemy
{
private:
	bool _active;
	void move();
	void attack();
public:
	void actionOfCollision(std::shared_ptr<HitBox> hitBox);
	bool beExamined();
	void update();	//�����̃^�[���łȂ��Ă��s��Ȃꂯ�΂Ȃ�Ȃ������������B
	void action();	//1�^�[���ɍs�����Ƃ�����
	DiffMimic(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController);
	~DiffMimic();
};

