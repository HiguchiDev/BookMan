#include "FloorObject_3D_Duplicate.h"


FloorObject_3D_Duplicate::FloorObject_3D_Duplicate(std::string fileName) : Object_3D_Duplicate(fileName)
{
}


FloorObject_3D_Duplicate::~FloorObject_3D_Duplicate()
{
}

void FloorObject_3D_Duplicate::draw()
{
//	int correction = 30;

	//À•WXV‚µ‚Ä‚©‚ç•`‰æ

	if (this->_visible && this->_handle != -1){
		MV1SetPosition(this->_handle, this->_position);
		MV1DrawModel(this->_handle);
	}
}