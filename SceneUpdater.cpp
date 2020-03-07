#include "SceneUpdater.h"
#include "Scene.h"
#include "Stage.h"
#include "DataRead.h"
#include "ItemListScreen.h"
#include "PlayerDatas.h"
#include "DxLib.h"
#include "Opening.h"
#include "DataWrite.h"
#include "StageSelect.h"
#include "BlackScreen.h"
#include "StartingPreparation.h"
#include "Key.h"
#include "Item.h"
#include "Trap.h"

SceneUpdater::SceneUpdater()
{
	this->_playerDatas = std::make_shared<PlayerDatas>();
	this->_gameScenes.push_back(Scene::createScene(SceneNames::getName(SceneNames::SceneTypes::TUTORIALSTAGE), _playerDatas));
	this->_gameScenes.push_back(Scene::createScene(SceneNames::getName(SceneNames::SceneTypes::HANSELANDGRETELSTAGE), _playerDatas));
	this->_gameScenes.push_back(Scene::createScene(SceneNames::getName(SceneNames::SceneTypes::MAZEOFGRASSLANDSTAGE), _playerDatas));
	this->_gameScenes.push_back(Scene::createScene(SceneNames::getName(SceneNames::SceneTypes::SEABEDTEMPLESTAGE), _playerDatas));

	this->_gameScenes.push_back(std::make_shared<DataRead>(this->_playerDatas));
	this->_gameScenes.push_back(std::make_shared<Opening>());
	
	this->_activeScene = this->_gameScenes[this->_gameScenes.size() - 1];

	this->_gameScenes.push_back(std::make_shared<ItemListScreen>(this->_playerDatas));

	this->_gameScenes.push_back(std::make_shared<DataWrite>(this->_playerDatas));

	this->_gameScenes.push_back(Scene::createScene(SceneNames::getName(SceneNames::SceneTypes::STAGESELECT), _playerDatas));
	this->_gameScenes.push_back(Scene::createScene(SceneNames::getName(SceneNames::SceneTypes::PAUSEMENU), _playerDatas));
	this->_gameScenes.push_back(Scene::createScene(SceneNames::getName(SceneNames::SceneTypes::STARTINGPREPARATION), _playerDatas));
	this->_gameScenes.push_back(Scene::createScene(SceneNames::getName(SceneNames::SceneTypes::KEYCONFIG), _playerDatas));
	this->_gameScenes.push_back(Scene::createScene(SceneNames::getName(SceneNames::SceneTypes::EQUIPSCREEN), _playerDatas));
	this->_gameScenes.push_back(Scene::createScene(SceneNames::getName(SceneNames::SceneTypes::ENDING), _playerDatas));
	this->_finish = false;


}


SceneUpdater::~SceneUpdater()
{
}

void SceneUpdater::addStageMaterial(std::shared_ptr<Trap> trap)
{
	this->_activeStage->addStageMaterial(trap);
}

void SceneUpdater::addStageMaterial(std::shared_ptr<Item> item)
{
	this->_activeStage->addStageMaterial(item);
}


std::string SceneUpdater::getActiveStageName()
{
	return this->_activeStageName;
}

void SceneUpdater::update()
{
	if (this->_activeScene != nullptr){

		this->_activeScene->update();

		if (SceneNames::isStageName(this->_activeScene->getSceneName())){
			this->_playerDatas->draw();
		}

		if (this->_activeScene->getSceneName() == SceneNames::getName(SceneNames::TUTORIALSTAGE)){



		}
		if (!this->_activeScene->isInitialized()){
			this->_activeScene->initialize();
		}



		//シーンのチェンジ
		if (this->_activeScene->isChangeScene()){
	
			if (SceneNames::isStageName(this->_activeScene->getSceneName())){
				this->_activeStageName = this->_activeScene->getSceneName();
			}

			for (auto scene : this->_gameScenes){
				if (this->_activeScene->getChangedSceneName() == scene->getSceneName()){
					this->_activeScene = scene;
					//this->_activeScene->returnAction();
					break;
				}
			}
		}
		//シーンチェンジ（破棄版）
		else if (this->_activeScene->isFinish()){
		
				for (int i = 0; i < this->_gameScenes.size(); i++){
					//アクティブなシーンと合致する要素を探す
					if (this->_activeScene->getSceneName() == this->_gameScenes[i]->getSceneName()){

						this->_activeScene->finalize();	//アクティブなシーンを終了させる。
						this->_gameScenes[i] = Scene::createScene(this->_activeScene->getSceneName(), this->_playerDatas);	//新しいアクティブであったシーンのインスタンスを生成する。

						//次のシーンに切り替える。
						for (int j = 0; j < this->_gameScenes.size(); j++){
							if (this->_activeScene->getNextSceneName() == this->_gameScenes[j]->getSceneName()){
								this->_activeScene = this->_gameScenes[j];
								this->_activeScene->returnAction();

								if (SceneNames::isStageName(this->_activeScene->getSceneName())){
								
									this->_activeStage = this->_activeScene;
								}

								i = this->_gameScenes.size();
								break;
							}
						}



					}
				}
			}
	}

}

std::shared_ptr<SceneUpdater> SceneUpdater::_instance = nullptr;

std::shared_ptr<SceneUpdater> SceneUpdater::getInstance()
{
	if (_instance == nullptr){
		_instance = std::make_shared< SceneUpdater >();
	}

	return _instance;
}