#include "Character.h"
#include "DxLib.h"
#include "Position.h"
#include <memory>
#include "Collision.h"
#include "PositionConverter.h"
#include "ScreenMaterial.h"
#include "StatesPoint.h"
#include "HitBox.h"
#include "Motion.h"
#include "Direction_AngleConverter.h"
#include "PlayerDatas.h"
#include "CharacterData.h"
#include "TurnController.h"
#include "Enemy.h"
#include "Player.h"
#include "DamageDisplay.h"
#include "LevelUpper.h"
#include "EffectUpdater.h"
#include "ExpEffect.h"
#include "Ice.h"
#include "Mimic.h"
#include "Juggler.h"
#include "Miyamoto.h"
#include "Water.h"
#include "Ankou.h"
#include "Hana.h"
#include "Kingsuraimu.h"
#include "Kasya.h"
#include "Doraki.h"
#include "Golem.h"
#include "BookMonster.h"
#include "Egg.h"
#include "Mushroom.h"
#include "SmallAnimal.h"
#include "SmallBird.h"
#include "DiffGolem.h"
#include "DiffBookMonster.h"
#include "DiffEgg.h"
#include "DiffMushroom.h"
#include "DiffSmallAnimal.h"
#include "DiffSmallBird.h"
#include "DiffMimic.h"
#include "NormalEnemy.h"
#include "Kraken.h"
#include "Witch.h"
#include "TutorialEnemy.h"

Character::Character(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController) : FieldMaterial(fileName, position)
{
	this->_motion = std::make_shared<Motion>(this->_screenMaterial->getHandle(), Action::ATTACK, Action::ATTACK, 1.0f);
	
	this->_motion->addMotionMap(Action::Actions::MOVE, Action::Actions::MOVE, 1.0f);
	this->_motion->addMotionMap(Action::BENDBACKWARD, Action::BENDBACKWARD, 0.8f);

	
	this->_animationSpeed = 3.0f;
	this->_turnController = turnController;
	this->_DIRECTION = Direction::Directions::EAST;
	this->_turnFinish = false;
}

std::shared_ptr<CharacterData> Character::getCharacterData()
{
	return this->_characterDatas;
}

Direction::Directions Character::getDirection()
{
	return this->_DIRECTION;
}

void Character::initialize()
{
	//一度だけ呼ぶ
	if (this->_positionInitialized == false){
		this->initializePosition();
		this->_positionInitialized = true;
	}
}

Character::~Character()
{
}

void Character::turnReset()
{
	this->_turnFinish = false;
}

void Character::update()
{
	this->_motion->update();
	this->draw();


	if (this->_screenMaterial->isAnimationFinish() &&
		this->_motion->isMotionFinish(Action::Actions::ATTACK) &&
		this->_turnFinish ){

	
		this->_turnController->setTurnFinishedCharacter(shared_from_this());
	}

}

CharacterType::CharacterTypes Character::getType()
{
	return this->_TYPE;
}

void Character::initializePosition()
{
	Collision::getInstance()->add(shared_from_this(), this->_position);
	this->_position->updateHeight(1, shared_from_this());
}

void Character::updateCollisionInformation(std::shared_ptr<Position> newPosition){
	Collision::getInstance()->update(shared_from_this(), newPosition);
}

void Character::draw()
{
	this->_screenMaterial->animation(this->_positionConverter.get3DPosition(this->_position), this->_animationSpeed);

	if (this->_screenMaterial->isCameraIn()){
		this->_motion->update();
	}
	else{
		this->_motion->resetAll();
	}

	if (this->_visible){
		this->_screenMaterial->draw();
	}
}

void Character::actionOfCollision(std::shared_ptr<Trap> trap)
{

}

void Character::actionOfCollision(std::shared_ptr<Character> character)
{
	
}

std::shared_ptr<PlayerDatas> LevelUpper::_playerDatas;
int LevelUpper::_exp_nextLevelUp;

void Character::actionOfCollision(std::shared_ptr<HitBox> hitBox)
{
	hitBox->causeDamageToCharacter(this->_characterDatas, shared_from_this());

	if (this->_characterDatas->getStatesPoint()->getStatesPoint(State::States::HITPOINT) <= 0){
		this->_finish = true;
		this->_screenMaterial->setVisible(false);

		
		if (this->_TYPE == CharacterType::ENEMY){
			LevelUpper::addExp(this->_characterDatas);
		}

		std::shared_ptr<Effect> effect = std::make_shared<ExpEffect>();
		effect->setPos(this->_screenMaterial->getPosition());
		EffectUpdater::getInstance()->add(effect);

	}

	this->_motion->start(false, Action::BENDBACKWARD);
	this->_ACTION = Action::BENDBACKWARD;
}

std::shared_ptr<Character> Character::createCharacter(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController, std::shared_ptr<PlayerDatas> playerDate)
{
	if (fileName == "Player"){
		fileName += ".pmd";
		return std::make_shared<Player>("主人公/主人公yoroi剣.pmd", position, turnController, playerDate);
	}
	else{
		return nullptr;
	}
}

std::shared_ptr<Character> Character::createCharacter(std::string characterName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController)
{

	if (characterName == "Ice"){
		return std::make_shared<NormalEnemy>("Ice", "enemy.pmd", position, turnController);
	}
	else if (characterName == "Mimic"){
		return std::make_shared<Mimic>("宝箱(ミミック)/宝箱(ミミック).pmd", position, turnController);
	}
	else if (characterName == "MimicHensel"){
		return std::make_shared<Mimic>("宝箱(ミミック)/宝箱(ミミック).pmd", position, turnController);
	}
	else if (characterName == "ピエロ"){
		return std::make_shared<NormalEnemy>("ピエロ","ピエロ.pmd", position, turnController);
	}
	else if (characterName == "ダークピエロ"){
		return std::make_shared<NormalEnemy>("ダークピエロ","ダークピエロ.pmd", position, turnController);
	}
	else if (characterName == "キャンディ"){
		return std::make_shared<NormalEnemy>("キャンディ","キャンディ.pmd", position, turnController);
	}
	else if (characterName == "レッドキャンディ"){
		return std::make_shared<NormalEnemy>("レッドキャンディ","レッドキャンディ.pmd", position, turnController);
	}
	else if (characterName == "虫"){
		return std::make_shared<NormalEnemy>("虫","bag.pmd", position, turnController);
	}
	else if (characterName == "魔女"){
		return std::make_shared<Witch>("魔女.pmd", position, turnController);
	}
	else if (characterName == "Juggler"){
		return std::make_shared<Juggler>("ジャグラー/Juggler.pmd", position, turnController);
	}
	else if (characterName == "Miyamoto"){
		return std::make_shared<Miyamoto>("宮本/Miyamoto.pmd", position, turnController);
	}
	else if (characterName == "Water"){
		return std::make_shared<Water>("水の精霊/Water.pmd", position, turnController);
	}
	else if (characterName == "Ankou"){
		return std::make_shared<Ankou>("アンコウ/Ankou.pmd", position, turnController);
	}
	else if (characterName == "Hana"){
		return std::make_shared<Hana>("花/Hana.pmd", position, turnController);
	}
	else if (characterName == "Kingsuraimu"){
		return std::make_shared<NormalEnemy>("Kingsuraimu","キングスライム/Kingsuraimu.pmd", position, turnController);
	}
	else if (characterName == "Doraki"){
		return std::make_shared<Doraki>("ドラキー/Doraki.pmd", position, turnController);
	}
	else if (characterName == "Kasya"){
		return std::make_shared<Kasya>("火車/Kasya.pmd", position, turnController);
	}
	else if (characterName == "Golem"){
		return std::make_shared<Golem>("ゴレムス君/ゴレムス君.pmd", position, turnController);
	}
	else if (characterName == "BookMonster"){
		return std::make_shared<BookMonster>("BookMonster/BookMonster.pmd", position, turnController);
	}
	else if (characterName == "Egg"){
		return std::make_shared<Egg>("たまご君/たまご君.pmd", position, turnController);
	}
	else if (characterName == "Mushroom"){
		return std::make_shared<Mushroom>("キノコ君/キノコ君.pmd", position, turnController);
	}
	else if (characterName == "SmallAnimal"){
		return std::make_shared<SmallAnimal>("モフモフ君/モフモフ君.pmd", position, turnController);
	}
	else if (characterName == "SmallBird"){
		return std::make_shared<SmallBird>("ぺんぺん君/ぺんぺん君.pmd", position, turnController);
	}
	else if (characterName == "DiffGolem"){
		return std::make_shared<DiffGolem>("ゴレムス君亜種/ゴレムス君亜種.pmd", position, turnController);
	}
	else if (characterName == "DiffBookMonster"){
		return std::make_shared<DiffBookMonster>("BookMonster亜種/BookMonster亜種.pmd", position, turnController);
	}
	else if (characterName == "DiffEgg"){
		return std::make_shared<DiffEgg>("たまご君亜種/たまご君亜種.pmd", position, turnController);
	}
	else if (characterName == "DiffMushroom"){
		return std::make_shared<DiffMushroom>("キノコ君亜種/キノコ君亜種.pmd", position, turnController);
	}
	else if (characterName == "DiffSmallAnimal"){
		return std::make_shared<DiffSmallAnimal>("モフモフ君亜種/モフモフ君亜種.pmd", position, turnController);
	}
	else if (characterName == "DiffSmallBird"){
		return std::make_shared<DiffSmallBird>("ぺんぺん君亜種/ぺんぺん君亜種.pmd", position, turnController);
	}
	else if (characterName == "DiffMimic"){
		return std::make_shared<DiffMimic>("宝箱(ミミック)亜種/宝箱(ミミック)亜種.pmd", position, turnController);
	}
	else if (characterName == "Ankouasyu"){
		return std::make_shared<NormalEnemy>("Ankouasyu", "アンコウ亜種/Ankouasyu.pmd", position, turnController);
	}
	else if (characterName == "KingsuraimuRed"){
		return std::make_shared<NormalEnemy>("KingsuraimuRed","キングスライムレッド/KingsuraimuRed.pmd", position, turnController);
	}
	else if (characterName == "クラーケン足壱"){
		return std::make_shared<NormalEnemy>("クラーケン足壱","クラーケン　足1/kurakenLegOne.pmd", position, turnController);
	}
	else if (characterName == "クラーケン足弐"){
		return std::make_shared<NormalEnemy>("クラーケン足弐","クラーケン　足2/kurakenLegTwo.pmd", position, turnController);
	}
	else if (characterName == "クラーケン"){
		return std::make_shared<Kraken>("クラーケン　本体/kuraken.pmd", position, turnController);
	}
	else if (characterName == "MiyamotoDark"){
		return std::make_shared<NormalEnemy>("MiyamotoDark","闇宮本/MiyamotoDark.pmd", position, turnController);
	}
	else if (characterName == "JugglerAsyu"){
		return std::make_shared<NormalEnemy>("JugglerAsyu","ジャグラー亜種/JugglerAsyu.pmd", position, turnController);
	}
	else if (characterName == "HanaAsyu"){
		return std::make_shared<NormalEnemy>("HanaAsyu","花亜種/HanaAsyu.pmd", position, turnController);
	}
	else if (characterName == "Suisya"){
		return std::make_shared<NormalEnemy>("Suisya","水車/Suisya.pmd", position, turnController);
	}
	else if (characterName == "Faire"){
		return std::make_shared<NormalEnemy>("Faire","火の精霊/Faire.pmd", position, turnController);
	}
	else if (characterName == "GreenDoraki"){
		return std::make_shared<NormalEnemy>("GreenDoraki","ドラキーグリーン/GreenDoraki.pmd", position, turnController);
	}
	else if (characterName == "TutorialEnemy"){
		return std::make_shared<TutorialEnemy>("TutorialEnemy.pmd", position, turnController);
	}
	else{
		return nullptr;
	}
}

bool Character::isFinish(){
	return this->_finish;
}