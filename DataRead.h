#pragma once
#include "Scene.h"
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

class PlayerDatas;
class Cursor;

class DataRead
	: public Scene
{
private:
	std::unordered_map<int, std::shared_ptr<PlayerDatas>> _playerDatasMap;
	std::vector<std::shared_ptr<PlayerDatas>> _playerDatas_show;	//表示用のプレイヤーデータ
	std::shared_ptr<Cursor> _cursor;
	std::vector< std::string > _saveDataFileNames;
	float _menuDistanceRow;
	float _menuDistanceColumn;
	float _stringPositionX;
	int _menuHandle;
public:
	void update();
	void finalize();
	DataRead(std::shared_ptr<PlayerDatas> playerDatas);
	~DataRead();
};

