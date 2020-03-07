#include "Ending.h"
#include "SceneNames.h"
#include "DxLib.h"
#include "LevelUpper.h"
#include "SceneUpdater.h"
#include "HitBoxUpdater.h"
#include "DamageDisplay.h"
#include "MessgeBox.h"
#include "EffectUpdater.h"
#include "BlackScreen.h"

Ending::Ending()
{
	this->_sceneName = SceneNames::getName(SceneNames::ENDING);

	this->_endingMessages.push_back("3Dモデル      Takashi Higuchi");
	this->_endingMessages.push_back("              Shota   Tokuchi");
	this->_endingMessages.push_back("              Masaki  Moriya");
	this->_endingMessages.push_back("シナリオ      Shota   Tokuchi");
	this->_endingMessages.push_back("プログラム    Takashi Higuchi");


	this->_endingMessages.push_back("HanselAndGretelStage      Takashi Higuchi");
	this->_endingMessages.push_back("MazeOfGrasslandStage      Shota   Tokuchi");
	this->_endingMessages.push_back("SeabedTempleStage         Masaki  Moriya");
	this->_endingMessages.push_back("");
	this->_endingMessages.push_back("");
	this->_endingMessages.push_back("");
	this->_endingMessages.push_back("");
	this->_endingMessages.push_back("");
	this->_endingMessages.push_back("あそんでくれてありがとう！");


	for (int i = 0; i < this->_endingMessages.size(); i++){
		this->_messageY.push_back(700 + (i * 100));
	}
}


Ending::~Ending()
{
}


void Ending::update()
{


	if (!this->_finish){


		if (this->_messageY[this->_endingMessages.size() - 1] <= 380){
			if (this->_interval++ >= 180){
				this->_finish = true;
			}
			for (int i = 0; i < this->_endingMessages.size(); i++){
				DrawString(300, this->_messageY[i], this->_endingMessages[i].c_str(), GetColor(255, 255, 255));
			}
		}
		else{
			for (int i = 0; i < this->_endingMessages.size(); i++){
				DrawString(300, this->_messageY[i], this->_endingMessages[i].c_str(), GetColor(255, 255, 255));
				this->_messageY[i] -= 1;
			}
		}
	}
	else{
		this->_blackScreen->out();

		if (this->_blackScreen->isBlackOut()){
			Collision::getInstance()->removeAll();

			LevelUpper::initialize(this->_playerDatas);
			SceneUpdater::create();
			HitBoxUpdater::create();
			DamageDisplay::create();
			MessgeBox::create();
			EffectUpdater::create();
		}
	}

}

void Ending::finalize()
{

}