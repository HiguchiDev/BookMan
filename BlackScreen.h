#pragma once
#include "ScreenMaterial.h"
#include <memory>

class BlackScreen
{
private:
	bool _finish;
	static std::shared_ptr<ScreenMaterial> _blackScreen;
	
	int _value;
	bool _reversal;
	bool _blackIn;
public:int _transparency;
	bool isBlackIn();
	bool isBlackOut();
	void in();
	void out();
	bool isFinish();
	BlackScreen();
	~BlackScreen();
};

