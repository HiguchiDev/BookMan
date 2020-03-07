#pragma once
#include "Scene.h"
#include <memory>
#include <unordered_map>
#include "MoveType.h"

class PlayerKeyConfig;
class Cursor;

class KeyConfigScreen :
	public Scene
{
private:
	bool _keyChange;
	std::shared_ptr<PlayerKeyConfig> _playerKeyConfig;
	std::unordered_map<MoveType::MoveTypes, std::string> _moveTypeToStringMap;
	
	std::vector<MoveType::MoveTypes> _moveTypes;

	std::shared_ptr<Cursor> _cursor;
public:
	void update();
	void finalize();
	KeyConfigScreen(std::shared_ptr<PlayerKeyConfig> playerKeyConfig);
	~KeyConfigScreen();
};

