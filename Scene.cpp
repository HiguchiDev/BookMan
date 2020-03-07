#include "Scene.h"
#include "SceneNames.h"
#include "ItemListScreen.h"
#include "Stage.h"
#include "DataRead.h"
#include "PlayerDatas.h"
#include "Opening.h"
#include "DataWrite.h"
#include "StageSelect.h"
#include "PauseMenu.h"
#include "StartingPreparation.h"
#include "BlackScreen.h"
#include "PlayerKeyConfig.h"
#include "KeyConfigScreen.h"
#include "EquipScreen.h"
#include "Tutorial.h"
#include "Ending.h"


Scene::Scene()
{
	this->_finish = false;
	this->_sceneChange = false;
	this->_nextSceneName = "null";

	this->_blackScreen = std::make_shared<BlackScreen>();
}


Scene::~Scene()
{

}

std::string Scene::getChangedSceneName()
{
	return this->_changedSceneName;
}

bool Scene::isChangeScene()
{
	return this->_sceneChange && this->_blackScreen->isFinish();
}

std::string Scene::getNextSceneName()
{
	return this->_nextSceneName;
}

std::string Scene::getSceneName()
{
	return this->_sceneName;
}

bool Scene::isFinish()
{
	return this->_finish && this->_blackScreen->isBlackOut();
}

bool Scene::isInitialized()
{
	return this->_blackScreen->isBlackIn();
}

void Scene::initialize()
{
	this->_blackScreen->in();
}

std::shared_ptr<Scene> Scene::createScene(std::string sceneName, std::shared_ptr<PlayerDatas> playerData)
{
	if (sceneName == SceneNames::getName(SceneNames::SceneTypes::ITEMSCREEN)){
		return std::make_shared<ItemListScreen>(playerData);
	}
	else if (sceneName == SceneNames::getName(SceneNames::SceneTypes::DATAREAD)){
		return std::make_shared<DataRead>(playerData);
	}
	else if (sceneName == SceneNames::getName(SceneNames::SceneTypes::TUTORIALSTAGE)){
		return std::make_shared<Turorial>(playerData, sceneName);
	}
	if(	sceneName == SceneNames::getName(SceneNames::SceneTypes::HANSELANDGRETELSTAGE) ||
		sceneName == SceneNames::getName(SceneNames::SceneTypes::MAZEOFGRASSLANDSTAGE) ||
		sceneName == SceneNames::getName(SceneNames::SceneTypes::SEABEDTEMPLESTAGE)){

		return std::make_shared<Stage>(playerData, sceneName);
	}
	else if (sceneName == SceneNames::getName(SceneNames::SceneTypes::OPENING)){
		return std::make_shared<Opening>();
	}
	else if (sceneName == SceneNames::getName(SceneNames::SceneTypes::DATAWRITE)){
		return std::make_shared<DataWrite>(playerData);
	}
	else if (sceneName == SceneNames::getName(SceneNames::SceneTypes::STAGESELECT)){
		return std::make_shared<StageSelect>(playerData);
	}
	else if (sceneName == SceneNames::getName(SceneNames::SceneTypes::PAUSEMENU)){
		return std::make_shared<PauseMenu>(playerData);
	}
	else if (sceneName == SceneNames::getName(SceneNames::SceneTypes::STARTINGPREPARATION)){
		return std::make_shared<StartingPreparation>(playerData);
	}
	else if (sceneName == SceneNames::getName(SceneNames::SceneTypes::KEYCONFIG)){
		return std::make_shared<KeyConfigScreen>(playerData->getPlayerKeyConfig());
	}
	else if (sceneName == SceneNames::getName(SceneNames::SceneTypes::EQUIPSCREEN)){
		return std::make_shared<EquipScreen>(playerData);
	}
	else if (sceneName == SceneNames::getName(SceneNames::SceneTypes::ENDING)){
		return std::make_shared<Ending>();
	}
	else{
		return nullptr;
	}
}

void Scene::returnAction()
{

	this->_sceneChange = false;
	this->_blackScreen = std::make_shared<BlackScreen>();
}