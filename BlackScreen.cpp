#include "BlackScreen.h"
#include "Object_2D.h"

std::shared_ptr<ScreenMaterial> BlackScreen::_blackScreen;

BlackScreen::BlackScreen()
{
	if (_blackScreen == nullptr){
		_blackScreen = std::make_shared<Object_2D>("blackScreen.png");
	}

	_blackScreen->setPosition(VGet(0, 0, 0));
	this->_transparency = 255;	//^‚ÁˆÃ

	this->_value = 7;
	this->_finish = false;
	this->_reversal = false;
	this->_blackIn = false;
}


BlackScreen::~BlackScreen()
{

}


void BlackScreen::in()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, this->_transparency);

	this->_transparency -= this->_value;

	if (this->_transparency <= 0){
		this->_blackIn = true;
	}


	
	_blackScreen->draw();

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

bool BlackScreen::isBlackIn()
{
	return this->_blackIn;
}

bool BlackScreen::isBlackOut()
{
	return this->_finish;
}

void BlackScreen::out()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, this->_transparency);

	this->_blackIn = true;
	this->_transparency += this->_value;

	if (this->_transparency >= 255){
		this->_finish = true;
	}

	//this->_blackScreen->setPosition(VGet(0, 0, 0));
	_blackScreen->draw();

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

bool BlackScreen::isFinish()
{
	return this->_finish;
}