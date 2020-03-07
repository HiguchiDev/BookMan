#pragma once
#include "FieldMaterial.h"
#include "Key.h"
#include <memory>
#include "ScreenMaterial.h"
#include "Camera.h"
#include "Character.h"
#include "Collision.h"
#include "HitBox.h"
#include "MoveType.h"
#include "Direction_AngleConverter.h"
#include "PositionConverter.h"
#include "WearProtective.h"
#include "Weapon.h"

class MoveType_RotateConverter;
class CharacterMoveDistance;
class Motion;
class PlayerDatas;
class LevelUpper;

class Player
	: public Character
{
private:
	WearProtective::Type _WEARTYPE = WearProtective::Type::SWORDSMAN;

	std::vector<std::shared_ptr<ScreenMaterial>> _playerObjects;
	std::vector<std::shared_ptr<Motion>> _playerMotions;
	std::unordered_map<WearProtective::Type, std::unordered_map<WeaponType::Type, std::shared_ptr<ScreenMaterial>>> _playerObjectMap;
	std::unordered_map<WearProtective::Type, std::unordered_map<WeaponType::Type, std::shared_ptr<Motion>>> _playerMotionMap;

	std::shared_ptr<LevelUpper> _levelUpper;
	std::shared_ptr< Camera > _camera;
	std::shared_ptr< Camera > _tempCamera;
	std::shared_ptr<Weapon> weapon;
	std::shared_ptr<CharacterMoveDistance> _moveDistance;
	std::shared_ptr<MoveType_RotateConverter> _rotateConveter;
	std::shared_ptr<PlayerDatas> _playerDatas;
	bool _death = false;
	MoveType::MoveTypes _MOVETYPE;
	WeaponType::Type _WEAPONTYPE;
	VECTOR CameraPos;
	int AttachIndex2;
	int TotalTime2;
	void moveCamera();
	void checkEquipTypeChange();
	void rotateCamera(Direction::Directions DIRECTION);
	void move(MoveType::MoveTypes MOVETYPE);
	void attack();
	void changeDirection(MoveType::MoveTypes MOVETYPE);
	std::shared_ptr<Trap> _trap;

	void initializeCamera();
	void initializeObjectMap();
	void addPlayerObjectPattern(std::string name);
	bool _mainView = false;
public:
	void throwTrap();
	void initialize();
	std::shared_ptr<CharacterData> getCharacterData();
	void update();
	bool isFree();
	void action();
	void action(int key);
	bool isFinish();
	void actionOfCollision(std::shared_ptr<HitBox> hitBox);
	Player(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController, std::shared_ptr<PlayerDatas> playerDatas);
	~Player();
};

