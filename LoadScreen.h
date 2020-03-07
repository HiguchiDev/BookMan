#pragma once
#include "ScreenMaterial.h"
#include <memory>
#include "Camera.h"

class LoadScreen
{
private:
	std::shared_ptr< ScreenMaterial > _string;
	std::shared_ptr< Camera > _camera;

public:
	bool isInitialized();
	void iniitalize();
	void start();
	LoadScreen();
	~LoadScreen();
};

