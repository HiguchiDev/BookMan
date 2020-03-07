#include "LoadScreen.h"
#include "Object_3D.h"
#include "DxLib.h"

LoadScreen::LoadScreen()
{
	this->_string = std::make_shared<Object_3D>("NowLoading.pmd");
	this->_camera = std::make_shared<Camera>(VGet(0.0, 0.0, -100.0), 1.0f, VGet(0, 0, 0));
}


LoadScreen::~LoadScreen()
{
}

void LoadScreen::start()
{
	this->_string->setPosition(VGet(100, 100, 100));
	this->_string->draw();
	this->_camera->initialize(VGet(200.0, 100.0, -100.0));
}

bool LoadScreen::isInitialized()
{
	return this->_string->isLoadCompletion();
}

void LoadScreen::iniitalize()
{
//	this->_string->load();
}