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
	
	PlayerFollow _playerFollow;	//�v���C���[�̕��p���擾����N���X�B
	Random _randomGetter;	//�m�����擾����B
	RandomMove _randomMove;
	virtual void move();
	virtual void attack();
public:
	virtual void actionOfCollision(std::shared_ptr<HitBox> hitBox);
	virtual bool beExamined(){ return false; };
	void initialize();
	virtual void update();	//�����̃^�[���łȂ��Ă��s��Ȃꂯ�΂Ȃ�Ȃ������������B
	virtual void action();	//1�^�[���ɍs�����Ƃ�����
	Enemy(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController);
	~Enemy();
};

