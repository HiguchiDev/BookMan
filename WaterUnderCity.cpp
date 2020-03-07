#include "WaterUnderCity.h"
#include "SceneNames.h"



WaterUnderCity::WaterUnderCity(std::shared_ptr<PlayerDatas> playerData) : Stage(playerData)
{

	_stageName = SceneNames::getName(SceneNames::TUTORIALSTAGE);

}


WaterUnderCity::~WaterUnderCity()
{
}
