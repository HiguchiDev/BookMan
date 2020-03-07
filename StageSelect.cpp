#include "StageSelect.h"
#include "SceneNames.h"
#include "Cursor.h"
#include "Key.h"
#include "BlackScreen.h"
#include "Object_3D_Duplicate.h"
#include "Action.h"
#include "Motion.h"
#include "PlayerDatas.h"


StageSelect::StageSelect(std::shared_ptr<PlayerDatas> playerDatas)
{
	
	this->_playerDatas = playerDatas;
	this->_stageNames.push_back(SceneNames::getName(SceneNames::SceneTypes::TUTORIALSTAGE));	
	this->_stageNames.push_back(SceneNames::getName(SceneNames::SceneTypes::SEABEDTEMPLESTAGE));
	this->_stageNames.push_back(SceneNames::getName(SceneNames::SceneTypes::MAZEOFGRASSLANDSTAGE));
	this->_stageNames.push_back(SceneNames::getName(SceneNames::SceneTypes::HANSELANDGRETELSTAGE));
	
	this->_difficlutys.push_back("難易度 ☆☆☆");
	this->_difficlutys.push_back("難易度 ★☆☆");
	this->_difficlutys.push_back("難易度 ★★☆");
	this->_difficlutys.push_back("難易度 ★★★");


	this->_sceneName = SceneNames::getName(SceneNames::SceneTypes::STAGESELECT);
	this->_finish = false;
	this->_cursor = std::make_shared<Cursor>(this->_stageNames.size(), 25.0f, 45.0f, -100.0f, -100.0f);

	for (int i = 0; i < 4; i++){
		this->_books.push_back(std::make_shared<Object_3D_Duplicate>("saveBook.pmd"));
		this->_books[i]->setPosition(VGet(50.0f * i, 240.0f, 0.0f));
		this->_books[i]->rotate(-90.0f);
		this->_motions.push_back(std::make_shared<Motion>(this->_books[i]->getHandle(), Action::ATTACK, Action::ATTACK, 1.0f));
		//this->_motions[i]->start(false, Action::ATTACK);
	}

	this->_bh = LoadGraph("空.png");
	this->_motions[0]->start(false, Action::ATTACK);
}


StageSelect::~StageSelect()
{
}

void StageSelect::update()
{
	DrawRotaGraph(1024 / 2, 768 / 2, 1.5, 0.0, this->_bh, TRUE);

	this->_cursor->update();

	SetCameraNearFar(10.0f, 1000.0f);
	SetCameraPositionAndTarget_UpVecY(VGet(80.0f, 400.0f, -10.0f), VGet(80.0f, 240.0f, -0.0f));
	//for (int i = 0; i < this->_stageNames.size(); i++){
	DrawString(400, 100, "Stage Select", GetColor(255, 255, 255));
	DrawString(400, 700, "決定 : SPACE  セーブ : F  移動 : A or D", GetColor(0, 0, 0));
	//}
		DrawString(400, 500, this->_stageNames[this->_cursor->getSelectedNum()].c_str(), GetColor(0, 0, 0));

		DrawString(400, 560, this->_difficlutys[this->_cursor->getSelectedNum()].c_str(), GetColor(0, 0, 0));
	//}

	if (Key::getInstance()->getHitFlame(KEY_INPUT_A) == 1 && this->_cursor->getSelectedNum() > 0){
		this->_cursor->move(MoveType::MoveTypes::UP);
		this->_motions[this->_cursor->getSelectedNum()]->start(false, Action::ATTACK);
		for (int i = 0; i < this->_books.size(); i++){
			if (i == this->_cursor->getSelectedNum()){
			}
			else{
				this->_motions[i]->reset();
				this->_motions[i]->start(false, Action::CANCEL);
			}
		}
	}
	else if (Key::getInstance()->getHitFlame(KEY_INPUT_D) == 1 && this->_cursor->getSelectedNum() < this->_stageNames.size() - 1 ){
		this->_cursor->move(MoveType::MoveTypes::DOWN);
		this->_motions[this->_cursor->getSelectedNum()]->start(false, Action::ATTACK);
		for (int i = 0; i < this->_books.size(); i++){
			if (i == this->_cursor->getSelectedNum()){
			}
			else{
				this->_motions[i]->reset();
				this->_motions[i]->start(false, Action::CANCEL);
			}
		}
	}
	else if (Key::getInstance()->getHitFlame(KEY_INPUT_F) == 1){
		this->_finish = true;
		this->_nextSceneName = SceneNames::getName(SceneNames::DATAWRITE);
	}
	else if (Key::getInstance()->getHitFlame(KEY_INPUT_SPACE) == 1){
		this->_nextSceneName = SceneNames::getName(SceneNames::STARTINGPREPARATION);
		
		this->_playerDatas->setActiveStageName(this->_stageNames[this->_cursor->getSelectedNum()]);
		this->_playerDatas->setStageFloor(0);
		this->_finish = true;
	}


	for (int i = 0; i < this->_books.size(); i++){
		this->_books[i]->draw();
	}

	
	for (int i = 0; i < this->_motions.size(); i++){
		this->_motions[i]->update();
	}

	if (this->_finish){
			
		this->_blackScreen->out();
	}
}

void StageSelect::finalize()
{
	DeleteGraph(this->_bh);
}