#include "Collision.h"
#include "Position.h"
#include "Obstacle.h"
#include "FieldMaterial.h"
#include "DxLib.h"
#include "FieldLength.h"
#include <algorithm>
#include <vector>
#include "HitBox.h"
#include "Character.h"
#include "Floor.h"
#include "Stairs.h"
#include "Item.h"
#include "PlayerDatas.h"
#include "PlayerItems.h"
#include "DamageDisplay.h"
#include "StatesPoint.h"
#include "Trap.h"
#include "PlayerWeapons.h"
#include "PlayerWearProtective.h"
#include "MessgeBox.h"
#include "ItemAbility.h"
#include "Weapon.h"

Collision::Collision()
{

	FieldLength fieldLength;

	if (_obstacleMap.empty()){
		for (int i = 0; i < fieldLength._ROW; i++){
			_obstacleMap.push_back(std::vector<std::vector<std::shared_ptr<Obstacle>>>());
			for (int j = 0; j < fieldLength._COLUMN; j++){
				_obstacleMap[i].push_back(std::vector<std::shared_ptr<Obstacle>>());
				for (int k = 0; k < fieldLength._HEIGHT; k++){
					_obstacleMap[i][j].push_back(nullptr);
				}
			}
		}
	}

	for (int i = 0; i < fieldLength._ROW; i++){
		_characterMap.push_back(std::vector<std::vector<std::shared_ptr<Character>>>());
		for (int j = 0; j < fieldLength._COLUMN; j++){
			_characterMap[i].push_back(std::vector<std::shared_ptr<Character>>());
			for (int k = 0; k < fieldLength._HEIGHT; k++){
				_characterMap[i][j].push_back(nullptr);
			}
		}
	}
}


Collision::~Collision()
{
}

bool Collision::examine(int row, int column)
{
	if (this->_characterMap[row][column][1] != nullptr){
		if (this->_characterMap[row][column][1]->beExamined()){
			return true;
		}
	}
	else if (this->_obstacleMap[row][column][1] != nullptr){
		if (this->_obstacleMap[row][column][1]->beExamined()){
			this->_obstacleMap[row][column][1] = nullptr;
			return true;
		}
	}
	
	return false;
}

std::shared_ptr<Position> Collision::getPlayerPos()
{
	if (this->_player != nullptr){
		return this->_player->getPos();
	}
	else{
		return nullptr;
	}
}

bool Collision::isMovable(std::shared_ptr<FieldMaterial> material, std::shared_ptr<Position> newPosition)
{
	if (_obstacleMap[newPosition->getRow()][newPosition->getColumn()][1] == nullptr &&
		_characterMap[newPosition->getRow()][newPosition->getColumn()][1] == nullptr  &&
		_characterMap[newPosition->getRow()][newPosition->getColumn()][1] != material){
		return true;
	}
	else{
		return false;
	}
}

bool Collision::isMovableTrapIncluding(std::shared_ptr<FieldMaterial> material, std::shared_ptr<Position> newPosition)
{
	if (_obstacleMap[newPosition->getRow()][newPosition->getColumn()][1] == nullptr &&
		_characterMap[newPosition->getRow()][newPosition->getColumn()][1] == nullptr  &&
		_characterMap[newPosition->getRow()][newPosition->getColumn()][1] != material){

		for (auto trap : this->_traps){
			if (trap->getPos()->getRow() == newPosition->getRow() &&
				trap->getPos()->getColumn() == newPosition->getColumn()){
				return false;
			}
		}

		return true;
		
	}
	else{
		return false;
	}
}

void Collision::add(std::shared_ptr<Obstacle> obstacle, std::shared_ptr<Position> position)
{
	std::vector<std::shared_ptr< FieldMaterial >>::iterator itr = std::find(_registeredFieldMaterials.begin(), _registeredFieldMaterials.end(), obstacle);

	if (itr == _registeredFieldMaterials.end() && _obstacleMap[position->getRow()][position->getColumn()][1] == nullptr){
		_obstacleMap[position->getRow()][position->getColumn()][1] = obstacle;
		_registeredFieldMaterials.push_back(obstacle);
	}
	else{
		if (itr != _registeredFieldMaterials.end()){
			printfDx("���łɓo�^�ς݂ł��B\n : Collision::add obstacle");
		}
		else if (_obstacleMap[position->getRow()][position->getColumn()][1] != nullptr){
			printfDx("���łɂ��̍��W�ɂ͏�Q�����L��܂�\n : Collision::add obstacle");
		}
	}


}

void Collision::add(std::shared_ptr<Character> character, std::shared_ptr<Position> position)
{
	_fieldMaterialMap[character] = std::make_shared<Position>(position->getRow(), position->getColumn(), position->getHeight());

	std::vector<std::shared_ptr< FieldMaterial >>::iterator itr = std::find(_registeredFieldMaterials.begin(), _registeredFieldMaterials.end(), character);

	if (itr == _registeredFieldMaterials.end()){
		_characterMap[position->getRow()][position->getColumn()][position->getHeight()] = character;
		if (character->getType() == CharacterType::CharacterTypes::PLAYER){
			_player = character;
		}
		_registeredFieldMaterials.push_back(character);
	}
	else{
		printfDx("���łɓo�^�ς݂ł��B\n : Collision::add character");
	}
}

void Collision::add(std::shared_ptr<Item> item, std::shared_ptr<Position> position)
{
	_fieldMaterialMap[item] = std::make_shared<Position>(position->getRow(), position->getColumn(), position->getHeight());

	std::vector<std::shared_ptr< FieldMaterial >>::iterator itr = std::find(_registeredFieldMaterials.begin(), _registeredFieldMaterials.end(), item);

	if (itr == _registeredFieldMaterials.end()){
		_items.push_back(item);

		_registeredFieldMaterials.push_back(item);
	}
	else{
		printfDx("���łɓo�^�ς݂ł��B\n : Collision::add item");
	}
}

void Collision::add(std::shared_ptr<Trap> trap, std::shared_ptr< Position > position)
{
	_fieldMaterialMap[trap] = std::make_shared<Position>(position->getRow(), position->getColumn(), position->getHeight());

	std::vector<std::shared_ptr< FieldMaterial >>::iterator itr = std::find(_registeredFieldMaterials.begin(), _registeredFieldMaterials.end(), trap);

	if (itr == _registeredFieldMaterials.end()){
		_traps.push_back(trap);

		_registeredFieldMaterials.push_back(trap);
	}
	else{
		printfDx("���łɓo�^�ς݂ł��B\n : Collision::add trap");
	}
}

//�I�������f�ނ����O����B
void Collision::checkFinishFieldMaterials()
{
	int row, column, height;

	//CharacterMap��hitBox����r������B
	for (auto registeredMaterial : _registeredFieldMaterials){
		//�I���ς݂�Material�ł���ꍇ
		if (registeredMaterial->isFinish()){
			//���W���擾
			row = registeredMaterial->getPos()->getRow();
			column = registeredMaterial->getPos()->getColumn();
			height = registeredMaterial->getPos()->getHeight();

			//Character
			if (_characterMap[row][column][height] == registeredMaterial){
				_characterMap[row][column][height] = nullptr;
			}			
			//Obstacle
			else if (_obstacleMap[row][column][height] == registeredMaterial){
				_obstacleMap[row][column][height] = nullptr;
			}
			//HitBox
			else{
				std::vector<std::shared_ptr< HitBox >>::iterator itr = std::find(_hitBoxs.begin(), _hitBoxs.end(), registeredMaterial);
				if (itr != _hitBoxs.end()){
					_hitBoxs.erase(itr);
				}

				std::vector<std::shared_ptr< Trap >>::iterator trapItr = std::find(_traps.begin(), _traps.end(), registeredMaterial);
				if (trapItr != _traps.end()){
					_traps.erase(trapItr);
				}
			}
		}
	}


	//�o�^���Ă���I������FieldMaterial������
	std::vector<std::shared_ptr<FieldMaterial>>::iterator it = _registeredFieldMaterials.begin();
	
	while (it != _registeredFieldMaterials.end()){
		if (it->get()->isFinish()){
			it = _registeredFieldMaterials.erase(it);
		}
		else{
			++it;
		}
	}
}

void Collision::setPlayerDatas(std::shared_ptr<PlayerDatas> playerDatas)
{
	this->_playerDatas = playerDatas;
}

std::unique_ptr<DamageDisplay> DamageDisplay::_instance;


bool Collision::checkTrap(bool isPlayer)
{

	bool result = false;

	if (isPlayer){
		for (int i = 0; i < (signed)this->_traps.size(); i++){
			if (_characterMap[this->_traps[i]->getPos()->getRow()][this->_traps[i]->getPos()->getColumn()][this->_traps[i]->getPos()->getHeight()] != nullptr &&
				!this->_traps[i]->isLodge()){

				this->_traps[i]->according(_characterMap[this->_traps[i]->getPos()->getRow()][this->_traps[i]->getPos()->getColumn()][this->_traps[i]->getPos()->getHeight()]->getCharacterData(), _characterMap[this->_traps[i]->getPos()->getRow()][this->_traps[i]->getPos()->getColumn()][this->_traps[i]->getPos()->getHeight()]);
				this->_traps[i]->setLodge(true);
				
				result = true;

				if (_characterMap[this->_traps[i]->getPos()->getRow()][this->_traps[i]->getPos()->getColumn()][this->_traps[i]->getPos()->getHeight()] == nullptr){
					
				}
			
			

				
			
			}
		}

		

		
	}
	else{
		for (int i = 0; i < (signed)this->_traps.size(); i++){
			if (_characterMap[this->_traps[i]->getPos()->getRow()][this->_traps[i]->getPos()->getColumn()][this->_traps[i]->getPos()->getHeight()] != nullptr &&
				_characterMap[this->_traps[i]->getPos()->getRow()][this->_traps[i]->getPos()->getColumn()][this->_traps[i]->getPos()->getHeight()]->getType() == CharacterType::ENEMY &&
				!this->_traps[i]->isLodge()){

				
				this->_traps[i]->according(_characterMap[this->_traps[i]->getPos()->getRow()][this->_traps[i]->getPos()->getColumn()][this->_traps[i]->getPos()->getHeight()]->getCharacterData(), _characterMap[this->_traps[i]->getPos()->getRow()][this->_traps[i]->getPos()->getColumn()][this->_traps[i]->getPos()->getHeight()]);
				this->_traps[i]->setLodge(true);
				result = true;
				if (_characterMap[this->_traps[i]->getPos()->getRow()][this->_traps[i]->getPos()->getColumn()][this->_traps[i]->getPos()->getHeight()] == nullptr){
					//printfDx("���[�v����\n");
				}
				
			}
		}
		for (int i = 0; i < (signed)this->_traps.size(); i++){
			//this->_traps[i]->according(_characterMap[this->_traps[i]->getPos()->getRow()][this->_traps[i]->getPos()->getColumn()][this->_traps[i]->getPos()->getHeight()]->getCharacterData(), _characterMap[this->_traps[i]->getPos()->getRow()][this->_traps[i]->getPos()->getColumn()][this->_traps[i]->getPos()->getHeight()]);
			this->_traps[i]->setLodge(false);
			//if (_characterMap[this->_traps[i]->getPos()->getRow()][this->_traps[i]->getPos()->getColumn()][this->_traps[i]->getPos()->getHeight()] == nullptr){
			//printfDx("���[�v����\n");
			//}
			//else{
			//printfDx("���[�v���s\n");
			//}

			//this->_traps.erase(this->_traps.begin() + i);
			//i--;
		}
	}

	return result;
}

//���̊֐����ĂԖ��ɁAHitBox�̓��Z�b�g�����B
void Collision::actionOfCollision(bool isPlayer)
{
	//Item
	if (isPlayer){

		for (int i = 0; i < (signed)this->_items.size(); i++){
			if (this->_items[i]->getPos()->getRow() == this->_player->getPos()->getRow() &&
				this->_items[i]->getPos()->getColumn() == this->_player->getPos()->getColumn() &&
				this->_items[i]->getPos()->getHeight() == this->_player->getPos()->getHeight()){

				if ((this->_items[i]->isWeaponChange() && !this->_playerDatas->getPlayerWeapons()->isFull()) ||
					(this->_items[i]->isWearChange() && !this->_playerDatas->getPlayerWears()->isFull())){
					this->_items[i]->getAbility()->use(this->_playerDatas);
					this->_items[i]->finalize();
					this->_items.erase(this->_items.begin() + i);
					//if (this->_items.size() != 0){
					i--;
					
				}


				else if (!this->_items[i]->isWeaponChange() && !this->_items[i]->isWearChange() && this->_playerDatas->getPlayerItems()->add(this->_items[i]->getAbility())){
					
					this->_items[i]->finalize();
					this->_items.erase(this->_items.begin() + i);
					//if (this->_items.size() != 0){
						i--;
					//}
				}

				else if ((this->_items[i]->isWeaponChange() || this->_items[i]->isWearChange())){
					MessgeBox::getInstance()->add("�����т������ς��ł��B���Ă邻���т͂��ꂼ��R�܂łł��B");

				}
			}
		}

		if (_stairs != nullptr){
			this->_stairs->checkPlayerCollision(this->_player);	//�K�i�Ƃ̏Փ˔���
		}
		else{
			printfDx("Stairs���o�^����Ă��܂���B\n");
		}

	}
	else{
		this->checkTrap(false);
	}

	int hitBoxRow, hitBoxColumn, hitBoxHeight;

	for (int i = 0; i < (signed)this->_hitBoxs.size(); i++){

		hitBoxRow = _hitBoxs[i]->getPos()->getRow();
		hitBoxColumn = _hitBoxs[i]->getPos()->getColumn();
		hitBoxHeight = _hitBoxs[i]->getPos()->getHeight();

		//HitBox�̍��W�ɃL�����N�^�[������@���@HitBox�̃^�C�v�ƃL�����N�^�[�̃^�C�v���Ⴄ�ꍇ�A�Փ˂������Ƃ�m�点��B
		if (this->_characterMap[hitBoxRow][hitBoxColumn][hitBoxHeight] != nullptr &&
			this->_characterMap[hitBoxRow][hitBoxColumn][hitBoxHeight]->getType() != _hitBoxs[i]->getCharacterType()){

			//hitBox���v���C���[�̂��̂������ꍇ�A����̑ϋv�x����
			if (this->_characterMap[hitBoxRow][hitBoxColumn][hitBoxHeight]->getType() == CharacterType::ENEMY){
				this->_playerDatas->getEquipedWeapon()->giveDamage(2);
			}

			this->_characterMap[hitBoxRow][hitBoxColumn][hitBoxHeight]->actionOfCollision(this->_hitBoxs[i]);

			//	DamageDisplay::getInstance()->add(std::make_shared<Position>(hitBoxRow, hitBoxColumn, hitBoxHeight), this->_hitBoxs[i]->getStatesDamegeValue()->getStatesPoint(State::States::HITPOINT));
		}

		this->_hitBoxs[i]->finalize();	//�Փ˂̗L���Ɋւ�炸�I��������B
	}
}

void Collision::update(std::shared_ptr<Obstacle> material, std::shared_ptr<Position> newPosition)
{
	
	try{
		if (_fieldMaterialMap.find(material) == _fieldMaterialMap.end()){
			throw material;
		}
		std::shared_ptr<Position> oldPos = _fieldMaterialMap[material];	//�A�b�v�f�[�g�O��material�̍��W

		if(_obstacleMap[newPosition->getRow()][newPosition->getColumn()][newPosition->getHeight()] == nullptr &&
			_obstacleMap[oldPos->getRow()][oldPos->getColumn()][oldPos->getHeight()] == material){
		
			_obstacleMap[newPosition->getRow()][newPosition->getColumn()][newPosition->getHeight()] = material;
			_obstacleMap[oldPos->getRow()][oldPos->getColumn()][oldPos->getHeight()] = nullptr;

			_fieldMaterialMap[material]->copy(newPosition);
		}
	}
	catch (...){
		printfDx("Collision �ɓo�^����Ă��܂���ACollision::add�@���Ăт܂������H :  Collision::Obstacle \n");
	}
}


void Collision::update(std::shared_ptr<Character> material, std::shared_ptr<Position> newPosition)
{
	try{
		if (_fieldMaterialMap.find(material) == _fieldMaterialMap.end()){
			throw material;
		}
		
		std::shared_ptr<Position> oldPos = _fieldMaterialMap[material];	//�A�b�v�f�[�g�O��material�̍��W


		if (_characterMap[newPosition->getRow()][newPosition->getColumn()][newPosition->getHeight()] == nullptr &&
			_characterMap[oldPos->getRow()][oldPos->getColumn()][oldPos->getHeight()] == material){
			_characterMap[newPosition->getRow()][newPosition->getColumn()][newPosition->getHeight()] = material;
			_characterMap[oldPos->getRow()][oldPos->getColumn()][oldPos->getHeight()] = nullptr;

			_fieldMaterialMap[material]->copy(newPosition);

		}
	}
	catch (...){
		printfDx("Collision �ɓo�^����Ă��܂���ACollision::add�@���Ăт܂������H :  Collision::Character \n");
	}
}

void Collision::erase(std::shared_ptr<Obstacle> obstacle, std::shared_ptr<Position> position)
{
	this->_obstacleMap[position->getRow()][position->getColumn()][1] = nullptr;
}

void Collision::add(std::shared_ptr<HitBox> hitBox, std::shared_ptr<Position> position)
{
	std::vector<std::shared_ptr< FieldMaterial >>::iterator itr = std::find(_registeredFieldMaterials.begin(), _registeredFieldMaterials.end(), hitBox);
	
	if (itr == _registeredFieldMaterials.end() && position->getRow() >= 0 && position->getRow() < 50 &&
		position->getColumn() >= 0 && position->getColumn() < 50 ){
		_hitBoxs.push_back(hitBox);
		_registeredFieldMaterials.push_back(hitBox);
	}
	else{
		printfDx("���łɓo�^�ς݂ł��B\n : Collision::add hitbox");
	}
}

void Collision::add(std::shared_ptr<Stairs> stairs, std::shared_ptr<Position> position)
{
	if (_stairs == nullptr){
		_stairs = stairs;
	}
	else{
		printfDx("���łɓo�^�ς݂ł��B\n : Collision::add Stairs");
	}
}

void Collision::removeAll()
{
	//for ()

	for (int i = 0; i < FieldLength::_ROW; i++){
		for (int j = 0; j < FieldLength::_COLUMN; j++){
			for (int k = 0; k < FieldLength::_HEIGHT; k++){
				this->_characterMap[i][j][k] = nullptr;
				this->_obstacleMap[i][j][k] = nullptr;
			}
		}
	}

	this->_items.clear();
	this->_traps.clear();
	this->_hitBoxs.clear();
	this->_player = nullptr;
	this->_registeredFieldMaterials.clear();
	this->_stairs = nullptr;
	this->_fieldMaterialMap.clear();
}
//std::shared_ptr<Collision> Collision::_instance;


