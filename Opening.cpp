#include "Opening.h"
#include "Cursor.h"
#include "Key.h"
#include "SceneNames.h"
#include "BlackScreen.h"
#include "ScreenMaterial.h"
#include "Object_3D_Duplicate.h"

Opening::Opening()
{
	this->_menuDistanceRow = 0.0f;
	this->_menuDistanceColumn = 30.0f;
	this->_stringPositionX = 450.0f;
	this->_cursor = std::make_shared<Cursor>(2, this->_menuDistanceRow, this->_menuDistanceColumn, this->_stringPositionX - 60, 500.0f);

	this->_menu.push_back("‚Â‚Ã‚«‚©‚ç");
	this->_nextSceneNameMap[this->_menu[this->_menu.size() - 1]] = SceneNames::getName(SceneNames::SceneTypes::DATAREAD);

	this->_menu.push_back("‚Í‚¶‚ß‚©‚ç");
	this->_nextSceneNameMap[this->_menu[this->_menu.size() - 1]] = SceneNames::getName(SceneNames::SceneTypes::STAGESELECT);

	this->_sceneName = SceneNames::getName(SceneNames::SceneTypes::OPENING);
	this->_openingTitle = std::make_shared<Object_3D_Duplicate>("openingTitle2.pmd");

	//this->_testBackScreen = LoadGraph("ƒeƒXƒg”wŒi.png");

	this->_bh = LoadGraph("‹ó.png");
	SetCameraNearFar(1.0f, 1000.0f);
	SetCameraPositionAndTarget_UpVecY(VGet(320.0f, 240.0f, -550.0f), VGet(320.0f, 240.0f, -0.0f));
}

void Opening::update()
{
	DrawRotaGraph(1024 / 2, 768 / 2, 1.5, 0.0, this->_bh, TRUE);
//	DrawGraph(0, );
		this->_cursor->update();

	for (int i = 0; i < (signed)this->_menu.size(); i++){
		DrawString((int)this->_stringPositionX, 500 + (int)(i * this->_menuDistanceColumn), this->_menu[i].c_str(), GetColor(0, 0, 0));
	}
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	this->_openingTitle->draw();
	
	if (!this->_finish){ 
		this->_openingTitle->setPosition(this->_position);
		this->_position.x = 320.0f;
		this->_position.y = 350.0f;
		this->_position.z = 0.0f;


		if (Key::getInstance()->getHitFlame(KEY_INPUT_W) == 1){
			this->_cursor->move(MoveType::UP);
		}
		else if (Key::getInstance()->getHitFlame(KEY_INPUT_X) == 1){
			this->_cursor->move(MoveType::DOWN);
		}
		else if (Key::getInstance()->getHitFlame(KEY_INPUT_A) == 1){
			this->_cursor->move(MoveType::LEFT);
		}
		else if (Key::getInstance()->getHitFlame(KEY_INPUT_D) == 1){
			this->_cursor->move(MoveType::RIGHT);
		}
		else if (Key::getInstance()->getHitFlame(KEY_INPUT_SPACE) == 1){

			this->_nextSceneName = this->_nextSceneNameMap[this->_menu[this->_cursor->getSelectedNum()]];
			
			this->_finish = true;

		}
		DrawString(100, 700, "ˆÚ“® : X or W   Œˆ’è : SPACE", GetColor(0, 0, 0));
	}
	else{
		this->_blackScreen->out();
	}


	
}

void Opening::finalize()
{
	DeleteGraph(this->_bh);
}

Opening::~Opening()
{
}
