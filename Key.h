#pragma once
#include <memory>
#include "DxLib.h"

class Key
{
private:
	int key[256];
	static std::unique_ptr<Key> _instance;
	
public:
	void update();
	int getHitFlame(int 
		Num);
	bool isHit(int keyNum);
	int getHitKey();
	static std::unique_ptr<Key>& getInstance();
	Key();
	
	~Key();
};