#include "Player.h"
#include "Object_3D.h"
#include "PositionConverter.h"
#include "Position.h"
#include "StatesPoint.h"
#include "TurnController.h"
#include "Direction_AngleConverter.h"
#include "Motion.h"
#include "Weapon.h"
#include "SwordOfTheTree.h"
#include <math.h>
#include "CharacterMoveDistance.h"
#include "MoveType_RotateConverter.h"
#include "Item.h"
#include "PlayerDatas.h"
#include "PlayerKeyConfig.h"
#include "PlayerDirectionGetter.h"
#include "PlayerItems.h"
#include "FirstPersonCamera.h"
#include "LevelUpper.h"
#include "WarpAnimation.h"
#include "FieldLength.h"
#include "MessgeBox.h"
#include "SubjectivityCamera.h"
#include "WearProtective.h"
#include "EffectUpdater.h"
#include "Trap.h"
#include "Object_3D_Duplicate.h"

std::shared_ptr<Collision> Collision::_instance;

Player::Player(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController, std::shared_ptr<PlayerDatas> playerDatas) : Character(fileName, position, turnController)
{
	this->_playerDatas = playerDatas;
	this->_DIRECTION = Direction::Directions::EAST;	//�ŏ��Ɍ����Ă������
	this->_moveDistance = std::make_shared<CharacterMoveDistance>();
	this->_rotateConveter = std::make_shared<MoveType_RotateConverter>();
	this->_levelUpper = std::make_shared<LevelUpper>(this->_playerDatas);
	
	this->_TYPE = CharacterType::CharacterTypes::PLAYER;

	this->initializeCamera();

	//�����̕� & �����̕���̎�l���f�[�^�́ACharacter�N���X�̃R���X�g���N�^�Œ�`����Ă���̂ŁA��l���݂̂̃��[�V������ǉ�
	this->_motion->addMotionMap(Action::NEUTRAL, Action::NEUTRAL, 0.1f);
	this->_motion->addMotionMap(Action::DEATH, Action::DEATH, 0.5f);
	this->_playerObjects.push_back(this->_screenMaterial);
	this->_playerMotions.push_back(this->_motion);

	//���ƕ���̑g�ݍ��킹�̃p�^�[���ɂ���Č����ڂ��ς��̂ŁA���̃f�[�^��ǂݍ���
	this->addPlayerObjectPattern("��l��/��l��������.pmd");
	this->addPlayerObjectPattern("��l��/��l��������.pmd");
	this->addPlayerObjectPattern("��l��/��l��������.pmd");
	this->addPlayerObjectPattern("��l��/��l��yoroi��.pmd");
	this->addPlayerObjectPattern("��l��/��l��yoroi��.pmd");

	this->initializeObjectMap();

	//��������͖؂̌� & ���U�[�X�[�c
	this->_WEARTYPE = WearProtective::Type::SWORDSMAN;
	this->_WEAPONTYPE = WeaponType::SWORD;
	
	this->_characterName = "�v���C���[";
	this->_DIRECTION = PlayerDirectionGetter::get(this->_camera->getDirection(), MoveType::MoveTypes::UP);	//�����ύX
	this->_screenMaterial->rotate(this->_rotateConveter->getRotate(this->_camera->getDirection(), MoveType::MoveTypes::UP));	//�����������

}

//���̃^�C�v�ƕ���̃^�C�v��
void Player::initializeObjectMap()
{
	//�I�u�W�F�N�g�̓o�^
	this->_playerObjectMap[WearProtective::Type::SWORDSMAN][WeaponType::SWORD] = this->_playerObjects[0];
	this->_playerObjectMap[WearProtective::Type::WITCH][WeaponType::SWORD] = this->_playerObjects[0];
	this->_playerObjectMap[WearProtective::Type::WITCH][WeaponType::CANE] = this->_playerObjects[5];
	this->_playerObjectMap[WearProtective::Type::WITCH][WeaponType::HAMMER] = this->_playerObjects[4];
	this->_playerObjectMap[WearProtective::Type::SWORDSMAN][WeaponType::HAMMER] = this->_playerObjects[4];
	this->_playerObjectMap[WearProtective::Type::SWORDSMAN][WeaponType::CANE] = this->_playerObjects[5];

	//���[�V�����̓o�^
	this->_playerMotionMap[WearProtective::Type::SWORDSMAN][WeaponType::SWORD] = this->_playerMotions[0];
	this->_playerMotionMap[WearProtective::Type::WITCH][WeaponType::SWORD] = this->_playerMotions[0];
	this->_playerMotionMap[WearProtective::Type::WITCH][WeaponType::CANE] = this->_playerMotions[5];
	this->_playerMotionMap[WearProtective::Type::WITCH][WeaponType::HAMMER] = this->_playerMotions[4];
	this->_playerMotionMap[WearProtective::Type::SWORDSMAN][WeaponType::HAMMER] = this->_playerMotions[4];
	this->_playerMotionMap[WearProtective::Type::SWORDSMAN][WeaponType::CANE] = this->_playerMotions[5];
}

void Player::initializeCamera()
{
	VECTOR pos = this->_screenMaterial->getPosition();

	//�J�����̐��� & ������
	this->_camera = std::make_shared<Camera>(VGet(200, 740, 1390), 7.5f, pos);
	this->_camera->initialize(pos);
	this->moveCamera();
	this->_camera->update();
}

//�v���C���[�̌����ڂ̃p�^�[����ǉ�����B
void Player::addPlayerObjectPattern(std::string name)
{
	this->_playerObjects.push_back(std::make_shared<Object_3D_Duplicate>(name));
	
	this->_playerMotions.push_back(std::make_shared<Motion>(this->_playerObjects[this->_playerObjects.size() - 1]->getHandle(), Action::ATTACK, Action::ATTACK, 1.0f));

	//���[�V������o�^
	this->_playerMotions[this->_playerMotions.size() - 1]->addMotionMap(Action::MOVE, Action::MOVE, 1.0f);
	this->_playerMotions[this->_playerMotions.size() - 1]->addMotionMap(Action::BENDBACKWARD, Action::BENDBACKWARD, 1.8f);
	this->_playerMotions[this->_playerMotions.size() - 1]->addMotionMap(Action::NEUTRAL, Action::NEUTRAL, 0.8f);
	this->_playerMotions[this->_playerMotions.size() - 1]->addMotionMap(Action::DEATH, Action::DEATH, 0.5f);
}

std::shared_ptr<CharacterData> Player::getCharacterData()
{
	return this->_playerDatas;
}

Player::~Player()
{

}

bool Player::isFinish()
{
	return this->_finish && this->_motion->isMotionFinish(Action::DEATH) && this->_ACTION == Action::DEATH;
}

void Player::actionOfCollision(std::shared_ptr<HitBox> hitBox)
{
	const int wearDamage = 2;

	hitBox->causeDamageToCharacter(this->_playerDatas, shared_from_this());	//�_���[�W����

	this->_playerDatas->getEquipedWear()->giveDamage(wearDamage);	//���ւ̃_���[�W

	//��ꂽ�ꍇ�A���̖h��͂�1�ɂȂ�̂ŁA�X�V
	if (this->_playerDatas->getEquipedWear()->isBroken()){
		this->_playerDatas->updateStatesPoint();
	}
	
	//�H�炢���[�V�����Đ�
	this->_motion->start(false, Action::BENDBACKWARD);
	this->_ACTION = Action::BENDBACKWARD;
}

//㩂𓊂���
void Player::throwTrap()
{
	if (this->_playerDatas->getTrap() != nullptr){
		this->_playerDatas->getTrap()->throwTrap(this->_DIRECTION);	//�����Ă��������㩂𓊂���
	}
}

void Player::move(MoveType::MoveTypes MOVETYPE)
{
	//�����Ă�������Ɛi�ޕ�������v���Ă���ꍇ�ړ�����B
	if (this->_DIRECTION == PlayerDirectionGetter::get(this->_camera->getDirection(), MOVETYPE) && !Key::getInstance()->getHitFlame(KEY_INPUT_P)){
		//	���W�X�V		
		if (this->_position->update(this->_position->getRow() + this->_moveDistance->getRowDistance(this->_camera->getDirection(), MOVETYPE),
									this->_position->getColumn() + this->_moveDistance->getColumnDistance(this->_camera->getDirection(), MOVETYPE),
									this->_position->getHeight() + this->_moveDistance->getHeightDistance(this->_camera->getDirection(), MOVETYPE), shared_from_this())){

			//���W�X�V�ɐ��������ꍇ�̓^�[���̍X�V���s��
			this->_turnFinish = true;

			if (this->_ACTION != Action::MOVE){
				this->_motion->start(false, Action::MOVE);	//�������[�V�����X�^�[�g
			}
			this->_ACTION = Action::Actions::MOVE;

		}
	}

	//�����Ă�������Ɛi�ޕ�������v���Ȃ��ꍇ�A�ړ��͂��������̕ύX�̂ݍs���B
	else{
		this->_DIRECTION = PlayerDirectionGetter::get(this->_camera->getDirection(), MOVETYPE);	//�����ύX
		this->_screenMaterial->rotate(this->_rotateConveter->getRotate(this->_camera->getDirection(), MOVETYPE));	//3D���f���̉�]
	}
}

void Player::moveCamera()
{
	VECTOR pos;

	pos = this->_positionConverter.get3DPosition(this->_position);

	this->_camera->move(pos, this->_screenMaterial->getPosition());
}

void Player::checkEquipTypeChange()
{

}

void Player::update()
{
	this->draw();
	this->moveCamera();
	this->_camera->update();
	this->throwTrap();


	if (this->_playerDatas->getEquipedWear()->getType() != this->_WEARTYPE || this->_playerDatas->getEquipedWeapon()->getType() != this->_WEAPONTYPE){
		this->_WEARTYPE = this->_playerDatas->getEquipedWear()->getType();
		this->_WEAPONTYPE = this->_playerDatas->getEquipedWeapon()->getType();

		this->_motion->resetAll();
		this->_motion = this->_playerMotionMap[this->_WEARTYPE][this->_WEAPONTYPE];
		this->_playerObjectMap[this->_WEARTYPE][this->_WEAPONTYPE]->initializePos(this->_screenMaterial->getPosition());
		this->_screenMaterial = this->_playerObjectMap[this->_WEARTYPE][this->_WEAPONTYPE];

		this->_DIRECTION = PlayerDirectionGetter::get(this->_camera->getDirection(), MoveType::MoveTypes::UP);	//�����ύX
		this->_screenMaterial->rotate(this->_rotateConveter->getRotate(this->_camera->getDirection(), MoveType::MoveTypes::UP));
	}
	
	if (this->_ACTION != Action::DEATH){
		if (this->_ACTION == Action::Actions::MOVE && this->_motion->isMotionFinish(Action::Actions::MOVE)){
			this->_motion->start(false, Action::Actions::MOVE);
		}
		else if (this->_ACTION == Action::NEUTRAL && this->_motion->isMotionFinish(Action::NEUTRAL)){
			this->_motion->start(false, Action::NEUTRAL);
		}

		if (this->_screenMaterial->isAnimationFinish() && this->_ACTION == Action::MOVE){

			if ((Key::getInstance()->getHitFlame(this->_playerDatas->getPlayerKeyConfig()->getMoveTypeKey(MoveType::MoveTypes::RIGHT)) ||
				Key::getInstance()->getHitFlame(this->_playerDatas->getPlayerKeyConfig()->getMoveTypeKey(MoveType::MoveTypes::LEFT)) ||
				Key::getInstance()->getHitFlame(this->_playerDatas->getPlayerKeyConfig()->getMoveTypeKey(MoveType::MoveTypes::DOWN)) ||
				Key::getInstance()->getHitFlame(this->_playerDatas->getPlayerKeyConfig()->getMoveTypeKey(MoveType::MoveTypes::UP)) ||
				Key::getInstance()->getHitFlame(this->_playerDatas->getPlayerKeyConfig()->getMoveTypeKey(MoveType::MoveTypes::LEFTLOWER)) ||
				Key::getInstance()->getHitFlame(this->_playerDatas->getPlayerKeyConfig()->getMoveTypeKey(MoveType::LEFTUPPER)) ||
				Key::getInstance()->getHitFlame(this->_playerDatas->getPlayerKeyConfig()->getMoveTypeKey(MoveType::MoveTypes::RIGHTLOWER)) ||
				Key::getInstance()->getHitFlame(this->_playerDatas->getPlayerKeyConfig()->getMoveTypeKey(MoveType::RIGHTUPPER))) &&
				!MessgeBox::getInstance()->isDisplay()){
			}
			else{
				this->_ACTION = Action::NEUTRAL;
			}
		}


		if (!EffectUpdater::getInstance()->isEffectRegeneration() &&
			this->_motion->isMotionFinish(Action::ATTACK) &&
			this->_turnFinish &&
			this->_screenMaterial->isAnimationFinish()
			|| (this->_playerDatas->getTrap() != nullptr && this->_playerDatas->getTrap()->isThrowStop())){

			if ((this->_playerDatas->getTrap() != nullptr && this->_playerDatas->getTrap()->isThrowStop())){
				this->_playerDatas->addThrowTrap(nullptr);
			}

			if (!Collision::getInstance()->checkTrap(true)){
				this->_turnController->setTurnFinishedCharacter(shared_from_this());
			}
		}
	}
	else{

	}
}

bool Player::isFree()
{
	return !EffectUpdater::getInstance()->isEffectRegeneration() &&
		this->_motion->isMotionFinish(Action::ATTACK) &&
		!this->_turnFinish &&
		this->_screenMaterial->isAnimationFinish();
}

void Player::rotateCamera(Direction::Directions DIRECTION)
{
	this->_camera->rotate(DIRECTION);
	this->_DIRECTION = PlayerDirectionGetter::get(this->_camera->getDirection(), MoveType::MoveTypes::UP);
	this->_screenMaterial->rotate(this->_rotateConveter->getRotate(this->_camera->getDirection(), MoveType::MoveTypes::UP));
}

void Player::attack()
{
	if (Key::getInstance()->getHitFlame(this->_playerDatas->getPlayerKeyConfig()->getActionTypeKey(Action::ATTACK)) == 1){
		this->_ACTION = Action::ATTACK;
		this->_turnFinish = true;
		this->_playerDatas->getEquipedWeapon()->attack(shared_from_this(), this->_DIRECTION);
		this->_motion->start(false, Action::ATTACK);

	}
}

void Player::initialize()
{
	//��x�����Ă�
	if (this->_positionInitialized == false){
		this->initializePosition();
		this->_positionInitialized = true;
	}

	if (this->_playerDatas->getEquipedWeapon() == nullptr){
		this->_playerDatas->initialize(shared_from_this());
	}

	this->_playerDatas->getPlayerItems()->initialize(this->_turnController, shared_from_this());

	//this->_screenMaterial->setVisible(false);
}

void Player::action()
{
	//this->_turnFinish = false;
	if (this->_ACTION != Action::DEATH){
		if (this->_playerDatas->getStatesPoint()->getStatesPoint(State::HITPOINT) > 0){
			if (!EffectUpdater::getInstance()->isEffectRegeneration() &&
				!this->_turnFinish && this->_screenMaterial->isAnimationFinish() && this->_motion->isMotionFinish(Action::BENDBACKWARD)){

				//�A�j���[�V�����ƃ��[�V�������I������܂ňړ������Ȃ�

				if (!this->_mainView){
					if (Key::getInstance()->getHitFlame(this->_playerDatas->getPlayerKeyConfig()->getMoveTypeKey(MoveType::MoveTypes::RIGHT))){
						this->move(MoveType::RIGHT);
					}
					else if (Key::getInstance()->getHitFlame(this->_playerDatas->getPlayerKeyConfig()->getMoveTypeKey(MoveType::MoveTypes::LEFT))){
						this->move(MoveType::LEFT);
					}
					else if (Key::getInstance()->getHitFlame(this->_playerDatas->getPlayerKeyConfig()->getMoveTypeKey(MoveType::MoveTypes::DOWN))){
						this->move(MoveType::DOWN);
					}
					else if (Key::getInstance()->getHitFlame(this->_playerDatas->getPlayerKeyConfig()->getMoveTypeKey(MoveType::MoveTypes::UP))){
						this->move(MoveType::UP);
					}
					else if (Key::getInstance()->getHitFlame(this->_playerDatas->getPlayerKeyConfig()->getMoveTypeKey(MoveType::MoveTypes::LEFTLOWER))){
						this->move(MoveType::LEFTLOWER);
					}
					else if (Key::getInstance()->getHitFlame(this->_playerDatas->getPlayerKeyConfig()->getMoveTypeKey(MoveType::LEFTUPPER))){
						this->move(MoveType::LEFTUPPER);
					}
					else if (Key::getInstance()->getHitFlame(this->_playerDatas->getPlayerKeyConfig()->getMoveTypeKey(MoveType::MoveTypes::RIGHTLOWER))){
						this->move(MoveType::RIGHTLOWER);
					}
					else if (Key::getInstance()->getHitFlame(this->_playerDatas->getPlayerKeyConfig()->getMoveTypeKey(MoveType::RIGHTUPPER))){
						this->move(MoveType::RIGHTUPPER);
					}

					else if (Key::getInstance()->getHitFlame(KEY_INPUT_L) == 1 && this->_tempCamera == nullptr){
						this->_tempCamera = this->_camera;
						this->_mainView = true;
						this->_camera = std::make_shared<SubjectivityCamera>(VGet(200, 740, 1390), 7.5f, this->_screenMaterial->getPosition(), shared_from_this());
						this->_visible = false;
					}

					else{

						//if (this->_motion->isMotionFinish(Action::MOVE)){
						this->_ACTION = Action::NEUTRAL;
						if (this->_motion->isMotionFinish(Action::NEUTRAL)){
							this->_motion->start(true, Action::Actions::NEUTRAL);
						}

					}

					this->attack();

					if (Key::getInstance()->getHitFlame(KEY_INPUT_LEFT) == 1){
						if (this->_camera->getDirection() == Direction::EAST){
							this->rotateCamera(Direction::Directions::NORTH);
						}
						else if (this->_camera->getDirection() == Direction::WEST){
							this->rotateCamera(Direction::Directions::SOUTH);
						}
						else if (this->_camera->getDirection() == Direction::SOUTH){
							this->rotateCamera(Direction::Directions::EAST);
						}
						else if (this->_camera->getDirection() == Direction::NORTH){
							this->rotateCamera(Direction::Directions::WEST);
						}
					}
					else if (Key::getInstance()->getHitFlame(KEY_INPUT_RIGHT) == 1){
						if (this->_camera->getDirection() == Direction::EAST){
							this->rotateCamera(Direction::Directions::SOUTH);
						}
						else if (this->_camera->getDirection() == Direction::WEST){
							this->rotateCamera(Direction::Directions::NORTH);
						}
						else if (this->_camera->getDirection() == Direction::SOUTH){
							this->rotateCamera(Direction::Directions::WEST);
						}
						else if (this->_camera->getDirection() == Direction::NORTH){
							this->rotateCamera(Direction::Directions::EAST);
						}
					}

					/*
					// �����L�[�ŃJ�����̍��W���ړ�
					if (Key::getInstance()->getHitFlame(this->_playerDatas->getPlayerKeyConfig()->getCameraDirectionKey(Direction::Directions::EAST)) == 1)
					{
					this->rotateCamera(Direction::Directions::EAST);
					}
					else if (Key::getInstance()->getHitFlame(this->_playerDatas->getPlayerKeyConfig()->getCameraDirectionKey(Direction::Directions::WEST)) == 1)
					{
					this->rotateCamera(Direction::Directions::WEST);
					}
					else if (Key::getInstance()->getHitFlame(this->_playerDatas->getPlayerKeyConfig()->getCameraDirectionKey(Direction::Directions::NORTH)) == 1)
					{
					this->rotateCamera(Direction::Directions::NORTH);
					}
					else if (Key::getInstance()->getHitFlame(this->_playerDatas->getPlayerKeyConfig()->getCameraDirectionKey(Direction::Directions::SOUTH)) == 1)
					{
					this->rotateCamera(Direction::Directions::SOUTH);
					}*/

					//���ׂ�
					if (Key::getInstance()->getHitFlame(KEY_INPUT_J) == 1){
						std::unordered_map<Direction::Directions, int> _distanceOfRow;
						std::unordered_map<Direction::Directions, int> _distanceOfColumn;

						_distanceOfRow[Direction::Directions::EAST] = 0;
						_distanceOfColumn[Direction::Directions::EAST] = 1;

						_distanceOfRow[Direction::Directions::WEST] = 0;
						_distanceOfColumn[Direction::Directions::WEST] = -1;

						_distanceOfRow[Direction::Directions::NORTH] = -1;
						_distanceOfColumn[Direction::Directions::NORTH] = 0;

						_distanceOfRow[Direction::Directions::SOUTH] = 1;
						_distanceOfColumn[Direction::Directions::SOUTH] = 0;

						_distanceOfRow[Direction::Directions::EASTNORTH] = -1;
						_distanceOfColumn[Direction::Directions::EASTNORTH] = 1;

						_distanceOfRow[Direction::Directions::WESTNORTH] = -1;
						_distanceOfColumn[Direction::Directions::WESTNORTH] = -1;

						_distanceOfRow[Direction::Directions::EASTSOUTH] = 1;
						_distanceOfColumn[Direction::Directions::EASTSOUTH] = 1;

						_distanceOfRow[Direction::Directions::WESTSOUTH] = 1;
						_distanceOfColumn[Direction::Directions::WESTSOUTH] = -1;

						if (Collision::getInstance()->examine(this->_position->getRow() + _distanceOfRow[this->_DIRECTION], this->_position->getColumn() + _distanceOfColumn[this->_DIRECTION])){
							this->_turnFinish = true;
						}
					}

					if (Key::getInstance()->getHitFlame(this->_playerDatas->getPlayerKeyConfig()->getActionTypeKey(Action::MENUOPEN)) == 1){

					}
				}
			}

			if (Key::getInstance()->getHitFlame(this->_playerDatas->getPlayerKeyConfig()->getActionTypeKey(Action::CANCEL)) == 1){
				if (this->_tempCamera != nullptr){
					this->_mainView = false;
					this->_camera = this->_tempCamera;
					this->_tempCamera = nullptr;
					this->_visible = true;
				}
			}
		}
		else{
			this->_finish = true;
			this->_motion->start(false, Action::DEATH);
			this->_ACTION = Action::DEATH;
		}
	}
}

void Player::action(int key)
{
	//this->_turnFinish = false;
	if (this->_ACTION != Action::DEATH){
		if (this->_playerDatas->getStatesPoint()->getStatesPoint(State::HITPOINT) > 0){
			if (!EffectUpdater::getInstance()->isEffectRegeneration() &&
				!this->_turnFinish && this->_screenMaterial->isAnimationFinish() && this->_motion->isMotionFinish(Action::BENDBACKWARD)){

				//�A�j���[�V�����ƃ��[�V�������I������܂ňړ������Ȃ�

				if (!this->_mainView){
					if (this->_playerDatas->getPlayerKeyConfig()->getMoveTypeKey(MoveType::MoveTypes::RIGHT) == key){
						this->move(MoveType::RIGHT);
					}
					else if (this->_playerDatas->getPlayerKeyConfig()->getMoveTypeKey(MoveType::MoveTypes::LEFT) == key){
						this->move(MoveType::LEFT);
					}
					else if (this->_playerDatas->getPlayerKeyConfig()->getMoveTypeKey(MoveType::MoveTypes::DOWN) == key){
						this->move(MoveType::DOWN);
					}
					else if (this->_playerDatas->getPlayerKeyConfig()->getMoveTypeKey(MoveType::MoveTypes::UP) == key){
						this->move(MoveType::UP);
					}
					else if (this->_playerDatas->getPlayerKeyConfig()->getMoveTypeKey(MoveType::MoveTypes::LEFTLOWER) == key){
						this->move(MoveType::LEFTLOWER);
					}
					else if (this->_playerDatas->getPlayerKeyConfig()->getMoveTypeKey(MoveType::LEFTUPPER) == key){
						this->move(MoveType::LEFTUPPER);
					}
					else if (this->_playerDatas->getPlayerKeyConfig()->getMoveTypeKey(MoveType::MoveTypes::RIGHTLOWER) == key){
						this->move(MoveType::RIGHTLOWER);
					}
					else if (this->_playerDatas->getPlayerKeyConfig()->getMoveTypeKey(MoveType::RIGHTUPPER) == key){
						this->move(MoveType::RIGHTUPPER);
					}

					else if (KEY_INPUT_L == key && this->_tempCamera == nullptr){
						this->_tempCamera = this->_camera;
						this->_mainView = true;
						this->_camera = std::make_shared<SubjectivityCamera>(VGet(200, 740, 1390), 7.5f, this->_screenMaterial->getPosition(), shared_from_this());
						this->_visible = false;
					}

					else{

						//if (this->_motion->isMotionFinish(Action::MOVE)){
						this->_ACTION = Action::NEUTRAL;
						if (this->_motion->isMotionFinish(Action::NEUTRAL)){
							this->_motion->start(true, Action::Actions::NEUTRAL);
						}

					}

					if (this->_playerDatas->getPlayerKeyConfig()->getActionTypeKey(Action::ATTACK) == key){
						this->_ACTION = Action::ATTACK;
						this->_turnFinish = true;
						this->_playerDatas->getEquipedWeapon()->attack(shared_from_this(), this->_DIRECTION);
						this->_motion->start(false, Action::ATTACK);

					}

					if (KEY_INPUT_LEFT == key){
						if (this->_camera->getDirection() == Direction::EAST){
							this->rotateCamera(Direction::Directions::NORTH);
						}
						else if (this->_camera->getDirection() == Direction::WEST){
							this->rotateCamera(Direction::Directions::SOUTH);
						}
						else if (this->_camera->getDirection() == Direction::SOUTH){
							this->rotateCamera(Direction::Directions::EAST);
						}
						else if (this->_camera->getDirection() == Direction::NORTH){
							this->rotateCamera(Direction::Directions::WEST);
						}
					}
					else if (KEY_INPUT_RIGHT == key){
						if (this->_camera->getDirection() == Direction::EAST){
							this->rotateCamera(Direction::Directions::SOUTH);
						}
						else if (this->_camera->getDirection() == Direction::WEST){
							this->rotateCamera(Direction::Directions::NORTH);
						}
						else if (this->_camera->getDirection() == Direction::SOUTH){
							this->rotateCamera(Direction::Directions::WEST);
						}
						else if (this->_camera->getDirection() == Direction::NORTH){
							this->rotateCamera(Direction::Directions::EAST);
						}
					}

					/*
					// �����L�[�ŃJ�����̍��W���ړ�
					if (Key::getInstance()->getHitFlame(this->_playerDatas->getPlayerKeyConfig()->getCameraDirectionKey(Direction::Directions::EAST)) == 1)
					{
					this->rotateCamera(Direction::Directions::EAST);
					}
					else if (Key::getInstance()->getHitFlame(this->_playerDatas->getPlayerKeyConfig()->getCameraDirectionKey(Direction::Directions::WEST)) == 1)
					{
					this->rotateCamera(Direction::Directions::WEST);
					}
					else if (Key::getInstance()->getHitFlame(this->_playerDatas->getPlayerKeyConfig()->getCameraDirectionKey(Direction::Directions::NORTH)) == 1)
					{
					this->rotateCamera(Direction::Directions::NORTH);
					}
					else if (Key::getInstance()->getHitFlame(this->_playerDatas->getPlayerKeyConfig()->getCameraDirectionKey(Direction::Directions::SOUTH)) == 1)
					{
					this->rotateCamera(Direction::Directions::SOUTH);
					}*/

					//���ׂ�
					if (KEY_INPUT_J == key){
						std::unordered_map<Direction::Directions, int> _distanceOfRow;
						std::unordered_map<Direction::Directions, int> _distanceOfColumn;

						_distanceOfRow[Direction::Directions::EAST] = 0;
						_distanceOfColumn[Direction::Directions::EAST] = 1;

						_distanceOfRow[Direction::Directions::WEST] = 0;
						_distanceOfColumn[Direction::Directions::WEST] = -1;

						_distanceOfRow[Direction::Directions::NORTH] = -1;
						_distanceOfColumn[Direction::Directions::NORTH] = 0;

						_distanceOfRow[Direction::Directions::SOUTH] = 1;
						_distanceOfColumn[Direction::Directions::SOUTH] = 0;

						_distanceOfRow[Direction::Directions::EASTNORTH] = -1;
						_distanceOfColumn[Direction::Directions::EASTNORTH] = 1;

						_distanceOfRow[Direction::Directions::WESTNORTH] = -1;
						_distanceOfColumn[Direction::Directions::WESTNORTH] = -1;

						_distanceOfRow[Direction::Directions::EASTSOUTH] = 1;
						_distanceOfColumn[Direction::Directions::EASTSOUTH] = 1;

						_distanceOfRow[Direction::Directions::WESTSOUTH] = 1;
						_distanceOfColumn[Direction::Directions::WESTSOUTH] = -1;

						if (Collision::getInstance()->examine(this->_position->getRow() + _distanceOfRow[this->_DIRECTION], this->_position->getColumn() + _distanceOfColumn[this->_DIRECTION])){
							this->_turnFinish = true;
						}
					}

					if (Key::getInstance()->getHitFlame(this->_playerDatas->getPlayerKeyConfig()->getActionTypeKey(Action::MENUOPEN)) == 1){

					}
				}
			}

			if (this->_playerDatas->getPlayerKeyConfig()->getActionTypeKey(Action::CANCEL) == key){
				if (this->_tempCamera != nullptr){
					this->_mainView = false;
					this->_camera = this->_tempCamera;
					this->_tempCamera = nullptr;
					this->_visible = true;
				}
			}
		}
		else{
			this->_finish = true;
			this->_motion->start(false, Action::DEATH);
			this->_ACTION = Action::DEATH;
		}
	}
}

void Player::changeDirection(MoveType::MoveTypes MOVETYPE)
{
	if (MOVETYPE == MoveType::MoveTypes::RIGHT){
		if (this->_camera->getDirection() == Direction::Directions::EAST){
			this->_DIRECTION = Direction::Directions::EAST;
		}
		else if (this->_camera->getDirection() == Direction::Directions::WEST){

		}
	}
}

/*void Player::actionOfCollision(std::shared_ptr<Item> item)
{

}

void Player::actionOfCollision(std::shared_ptr<AttackDecision> attckDecision)
{

}*/

/*void Player::finalize()
{

}*/

