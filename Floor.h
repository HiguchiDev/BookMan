#pragma once
#include "FieldMaterial.h"

class Position;
class ScreenMaterial;

#include <vector>

class Floor 
{
private:
	std::shared_ptr<Position> _position;
	
public:
	void draw();
	bool isLoadCompetion();
	std::shared_ptr<ScreenMaterial> _screenMaterial;
	Floor(std::string fileName, std::shared_ptr<Position> position);
	~Floor();
};

