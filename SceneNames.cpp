#include "SceneNames.h"


SceneNames::SceneNames()
{
}


SceneNames::~SceneNames()
{
}

bool SceneNames::isStageName(std::string name)
{
	return name == getName(SceneTypes::TUTORIALSTAGE) ||
		name == getName(SceneTypes::HANSELANDGRETELSTAGE) ||
		name == getName(SceneTypes::MAZEOFGRASSLANDSTAGE) ||
		name == getName(SceneTypes::SEABEDTEMPLESTAGE);
}

std::string SceneNames::getName(SceneTypes SCREENTYPE)
{
	switch (SCREENTYPE)
	{
	case SceneTypes::TUTORIALSTAGE:
		return "TutorialStage";
		break;
	case SceneTypes::HANSELANDGRETELSTAGE:
		return "HanselAndGretelStage";
		break;
	case SceneTypes::MAZEOFGRASSLANDSTAGE:
		return "MazeOfGrasslandStage";	//MazeOfGrasslandStage0.csv
		break;
	case SceneTypes::SEABEDTEMPLESTAGE:
		return "SeabedTempleStage";	//SeabedTempleStage0.csv
		break;
	case SceneTypes::DATAREAD:
		return "DataRead";
		break;
	case SceneTypes::ITEMSCREEN:
		return "ItemScreen";
		break;
	case SceneTypes::OPENING:
		return "Opening";
		break;
	case SceneTypes::DATAWRITE:
		return "DataWrite";
		break;
	case SceneTypes::STAGESELECT:
		return "StageSelect";
		break;
	case SceneTypes::PAUSEMENU:
		return "PauseMenu";
		break;
	case SceneTypes::STARTINGPREPARATION:
		return "StartingPreparation";
		break;
	case SceneTypes::KEYCONFIG:
		return "KeyConfig";
		break;
	case SceneTypes::EQUIPSCREEN:
		return "EquipScreen";
		break;
	case SceneTypes::ENDING:
		return "Ending";
		break;
	default:
		break;
	}
}
