#pragma once
#include <memory>
#include <unordered_map> 

class Player;
class Enemy;
class Obstacle;
class FieldMaterial;
class Position;
class Character;
class HitBox;
class Floor;
class Stairs;
class Item;
class PlayerItems;
class PlayerDatas;
class Trap;

class Collision
{
private:
	
	std::vector< std::vector<std::vector<std::shared_ptr< Obstacle > > > > _obstacleMap;
	std::vector< std::vector<std::vector<std::shared_ptr< Character > > > > _characterMap;
	std::vector<std::shared_ptr<Trap>> _traps;
	std::vector<std::shared_ptr<Item>> _items;
	std::vector< std::shared_ptr<HitBox>> _hitBoxs;
	std::unordered_map<std::shared_ptr< FieldMaterial >, std::shared_ptr< Position>> _fieldMaterialMap;
	std::vector<std::shared_ptr< FieldMaterial >> _registeredFieldMaterials;
	std::shared_ptr<Character> _player;
	std::shared_ptr<Stairs> _stairs;
	static std::shared_ptr<Collision> _instance;
	std::shared_ptr<PlayerDatas> _playerDatas;
public:
	Collision();

	bool checkTrap(bool isPlayer);

	void erase(std::shared_ptr<Obstacle> obstacle, std::shared_ptr<Position> position);
	void setPlayerDatas(std::shared_ptr<PlayerDatas> playerDatas);
	bool examine(int row, int column);

	bool isMovableTrapIncluding(std::shared_ptr<FieldMaterial> material, std::shared_ptr<Position> newPosition);
	bool isMovable(std::shared_ptr<FieldMaterial> material, std::shared_ptr<Position> newPosition);
	void add(std::shared_ptr<Obstacle> obstacle, std::shared_ptr< Position > position);
	void add(std::shared_ptr<Trap> trap, std::shared_ptr< Position > position);
	void add(std::shared_ptr<Character> character, std::shared_ptr<Position> position);
	void add(std::shared_ptr<HitBox> hitBox, std::shared_ptr<Position> position);
	void add(std::shared_ptr<Stairs> stairs, std::shared_ptr<Position> position);
	void add(std::shared_ptr<Item> item, std::shared_ptr<Position> position);
	void checkFinishFieldMaterials();
	void update(std::shared_ptr<Obstacle> material, std::shared_ptr<Position> newPosition);
	void update(std::shared_ptr<Character> material, std::shared_ptr<Position> newPosition);
	void actionOfCollision(bool isPlayer);
		
	std::shared_ptr<Position> getPlayerPos();
	void removeAll();

	static std::shared_ptr<Collision>& getInstance()
	{
		if (_instance.get() == nullptr){
	
			
			_instance = std::make_shared<Collision>();
		}
		return _instance;
	}

	static void create(){ _instance = std::make_shared<Collision>(); };
	~Collision();
};

