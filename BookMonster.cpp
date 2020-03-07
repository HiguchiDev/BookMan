#include "BookMonster.h"
#include "DxLib.h"
#include "ScreenMaterial.h"
#include "PositionConverter.h"
#include "Position.h"
#include "TurnController.h"
#include "StatesPoint.h"
#include "Motion.h"
#include "PlayerFollow.h"
#include "Weapon.h"
#include "SwordOfTheTree.h"
#include "LevelUpper.h"
#include "Effect.h"
#include "EffectUpdater.h"
#include "ExpEffect.h"

BookMonster::BookMonster(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController) : Enemy(fileName, position, turnController)
{
	this->_characterName = "BookMonster";
	this->_active = false;
	this->_characterDatas = std::make_shared<CharacterData>(this->_characterName);
	this->_characterDatas->dataRead();
}


BookMonster::~BookMonster()
{
}

bool BookMonster::beExamined()
{
	if (this->_active == false){
		this->_active = true;
		return true;
	}
	else{
		return false;
	}
}

void BookMonster::update()
{

	this->draw();	//3D���f���̕`��


	float moveSpeed = 5.0;	//1�t���[���ɐi�ރX�s�[�h�B

	if (this->_active){
		this->_DIRECTION = this->_playerFollow.getFollowDirection(shared_from_this());	//�v���C���[��������p�������B

		this->_screenMaterial->animation(this->_positionConverter.get3DPosition(this->_position), moveSpeed);	//�Ȃ߂炩�ɓ����l�ɖ���Ă�ŏ��������W���X�V����B 
		this->_screenMaterial->rotate(this->_angleConverter.getAngle(this->_DIRECTION) + 90);	//�������Ă�������ithis->DIRECTION�j�ɉ����ĂRD���f������]������B
		this->_motion->update();	//���Đ����Ă��郂�[�V�������X�V����B
	}


	/*���W�̍X�V���I����� &&
	�U�����[�V�������I�����Ă��� &&
	�H�炢���[�V�������I�����Ă��� &&
	�s���������I�����Ă���   ->   �^�[���R���g���[���[�Ƀ^�[�����I���������Ƃ�m�点��B*/

	if ((this->_screenMaterial->isAnimationFinish() &&
		this->_motion->isMotionFinish(Action::Actions::ATTACK) &&
		//this->_motion->isMotionFinish(Action::Actions::BENDBACKWARD) &&
		this->_turnFinish) &&
		this->_active){

		this->_turnController->setTurnFinishedCharacter(shared_from_this());	//�^�[���R���g���[���[�́A�G�L�����S�������̊֐����ĂԂƃv���C���[�Ƀ^�[�����󂯓n���B
	}



}

//�^�[���Ɋւ�炸�s������
void BookMonster::move()
{
	int moveValueRow = 0;
	int moveValueColumn = 0;

	//�v���C���[�Ƃ̋����� 4 �ȉ��̎��A�ǂ��悤�ɐi�ށB
	if (abs(Collision::getInstance()->getPlayerPos()->getRow() - this->_position->getRow()) <= 4 &&
		abs(Collision::getInstance()->getPlayerPos()->getColumn() - this->_position->getColumn()) <= 4){	//��Βl�̍��� 4 �ȉ�

		// Row //
		//�v���C�����W - �����̍��W�� 0 �ȏ�̎��A�E�ɐi��
		if (Collision::getInstance()->getPlayerPos()->getRow() - this->_position->getRow() > 0){
			moveValueRow = 1;
		}
		//0�ȉ��Ȃ� ���ɂ����ށB
		else if (Collision::getInstance()->getPlayerPos()->getRow() - this->_position->getRow() < 0){
			moveValueRow = -1;
		}

		//	Column //
		//�v���C�����W - �����̍��W�� 0 �ȏ�̎��A�E�ɐi��
		if (Collision::getInstance()->getPlayerPos()->getColumn() - this->_position->getColumn() > 0){
			moveValueColumn = 1;
		}
		//0�ȉ��Ȃ� ���ɂ����ށB
		else if (Collision::getInstance()->getPlayerPos()->getColumn() - this->_position->getColumn() < 0){
			moveValueColumn = -1;
		}

	}
	//�v���C���[�Ƃ̋����� 5 �ȏ� �Ȃ�A�ǂ킸�Ƀ����_���ɐi��
	else{
		moveValueRow = _randomMove.getRandomMoveValue(1);
		moveValueColumn = _randomMove.getRandomMoveValue(1);
	}

	//Position�N���X��update�`�Ƃ������O�̊֐��́A���W�̍X�V����������� true ��Ԃ��B���s����� false ��Ԃ��B
	if (this->_position->update(this->_position->getRow() + moveValueRow, this->_position->getColumn() + moveValueColumn, this->_position->getHeight(), shared_from_this())){

		this->_motion->start(false, Action::Actions::MOVE);	//�ړ����[�V�����̍Đ��J�n
		this->_ACTION = Action::Actions::MOVE;	//�A�N�V������MOVE�ɕύX
	}
}

void BookMonster::actionOfCollision(std::shared_ptr<HitBox> hitBox)
{
	if (this->_active){
		hitBox->causeDamageToCharacter(this->_characterDatas, shared_from_this());

		if (this->_characterDatas->getStatesPoint()->getStatesPoint(State::States::HITPOINT) <= 0){
			this->_finish = true;
			this->_screenMaterial->setVisible(false);
			this->_motion->finalize();

			if (this->_TYPE == CharacterType::ENEMY){
				LevelUpper::addExp(this->_characterDatas);
			}

			std::shared_ptr<Effect> effect = std::make_shared<ExpEffect>();
			effect->setPos(this->_screenMaterial->getPosition());
			EffectUpdater::getInstance()->add(effect);

		}

		this->_motion->start(false, Action::BENDBACKWARD);
		this->_ACTION = Action::BENDBACKWARD;
	}
}


void BookMonster::attack()
{
	_weapon->attack(shared_from_this(), this->_DIRECTION);	//�����̕���ɍU���𖽗߂���B

	this->_motion->start(false, Action::ATTACK);	//�U�����[�V�����̊J�n�B
	this->_ACTION = Action::Actions::ATTACK;
}


//1�^�[���ɍs������
void BookMonster::action()
{
	if (this->_characterDatas->getStatesPoint()->getStatesPoint(State::HITPOINT) <= 0){
		this->_turnFinish = true;
	}
	else{
		//�����̃^�[�����I����Ă��Ȃ���
		if (_turnFinish == false){

			if (this->_active){
				//����8�}�X�ȓ��Ƀv���C���[�����݂���ꍇ�B
				if (abs(Collision::getInstance()->getPlayerPos()->getRow() - this->_position->getRow()) <= 1 &&
					abs(Collision::getInstance()->getPlayerPos()->getColumn() - this->_position->getColumn()) <= 1){
					this->attack();
				}
				//���Ȃ��ꍇ�B
				else{
					this->move();
				}
				this->_turnFinish = true;
	
			}
			else{
				this->_turnController->setTurnFinishedCharacter(shared_from_this());	//�^�[���R���g���[���[�́A�G�L�����S�������̊֐����ĂԂƃv���C���[�Ƀ^�[�����󂯓n���B
			}

		}
	}
}