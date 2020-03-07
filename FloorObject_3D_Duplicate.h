#pragma once
#include "Object_3D_Duplicate.h"
class FloorObject_3D_Duplicate :
	public Object_3D_Duplicate
{
public:
	void draw();
	FloorObject_3D_Duplicate(std::string fileName);
	~FloorObject_3D_Duplicate();
};

