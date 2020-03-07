#pragma once
#include "Scene.h"
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

class PlayerDatas;
class Cursor;
class Stage;

class DataWrite
	: public Scene
{
private:
	std::unordered_map<int, std::shared_ptr<PlayerDatas>> _playerDatasMap;
	std::vector<std::shared_ptr<PlayerDatas>> _playerDatas_show;	//表示用のプレイヤーデータ
	std::shared_ptr<Cursor> _cursor;
	std::vector< std::string > _saveDataFileNames;
	std::shared_ptr<PlayerDatas> _playerDatas;
	float _menuDistanceRow;
	float _menuDistanceColumn;
	float _stringPositionX;
	int _menuHandle;
public:
	void update();
	void finalize();

	DataWrite(std::shared_ptr<PlayerDatas> playerDatas);
	~DataWrite();
};

