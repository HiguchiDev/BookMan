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
	//��x�����Ă�
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
		return std::make_shared<Player>("��l��/��l��yoroi��.pmd", position, turnController, playerDate);
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
		return std::make_shared<Mimic>("��(�~�~�b�N)/��(�~�~�b�N).pmd", position, turnController);
	}
	else if (characterName == "MimicHensel"){
		return std::make_shared<Mimic>("��(�~�~�b�N)/��(�~�~�b�N).pmd", position, turnController);
	}
	else if (characterName == "�s�G��"){
		return std::make_shared<NormalEnemy>("�s�G��","�s�G��.pmd", position, turnController);
	}
	else if (characterName == "�_�[�N�s�G��"){
		return std::make_shared<NormalEnemy>("�_�[�N�s�G��","�_�[�N�s�G��.pmd", position, turnController);
	}
	else if (characterName == "�L�����f�B"){
		return std::make_shared<NormalEnemy>("�L�����f�B","�L�����f�B.pmd", position, turnController);
	}
	else if (characterName == "���b�h�L�����f�B"){
		return std::make_shared<NormalEnemy>("���b�h�L�����f�B","���b�h�L�����f�B.pmd", position, turnController);
	}
	else if (characterName == "��"){
		return std::make_shared<NormalEnemy>("��","bag.pmd", position, turnController);
	}
	else if (characterName == "����"){
		return std::make_shared<Witch>("����.pmd", position, turnController);
	}
	else if (characterName == "Juggler"){
		return std::make_shared<Juggler>("�W���O���[/Juggler.pmd", position, turnController);
	}
	else if (characterName == "Miyamoto"){
		return std::make_shared<Miyamoto>("�{�{/Miyamoto.pmd", position, turnController);
	}
	else if (characterName == "Water"){
		return std::make_shared<Water>("���̐���/Water.pmd", position, turnController);
	}
	else if (characterName == "Ankou"){
		return std::make_shared<Ankou>("�A���R�E/Ankou.pmd", position, turnController);
	}
	else if (characterName == "Hana"){
		return std::make_shared<Hana>("��/Hana.pmd", position, turnController);
	}
	else if (characterName == "Kingsuraimu"){
		return std::make_shared<NormalEnemy>("Kingsuraimu","�L���O�X���C��/Kingsuraimu.pmd", position, turnController);
	}
	else if (characterName == "Doraki"){
		return std::make_shared<Doraki>("�h���L�[/Doraki.pmd", position, turnController);
	}
	else if (characterName == "Kasya"){
		return std::make_shared<Kasya>("�Ύ�/Kasya.pmd", position, turnController);
	}
	else if (characterName == "Golem"){
		return std::make_shared<Golem>("�S�����X�N/�S�����X�N.pmd", position, turnController);
	}
	else if (characterName == "BookMonster"){
		return std::make_shared<BookMonster>("BookMonster/BookMonster.pmd", position, turnController);
	}
	else if (characterName == "Egg"){
		return std::make_shared<Egg>("���܂��N/���܂��N.pmd", position, turnController);
	}
	else if (characterName == "Mushroom"){
		return std::make_shared<Mushroom>("�L�m�R�N/�L�m�R�N.pmd", position, turnController);
	}
	else if (characterName == "SmallAnimal"){
		return std::make_shared<SmallAnimal>("���t���t�N/���t���t�N.pmd", position, turnController);
	}
	else if (characterName == "SmallBird"){
		return std::make_shared<SmallBird>("�؂�؂�N/�؂�؂�N.pmd", position, turnController);
	}
	else if (characterName == "DiffGolem"){
		return std::make_shared<DiffGolem>("�S�����X�N����/�S�����X�N����.pmd", position, turnController);
	}
	else if (characterName == "DiffBookMonster"){
		return std::make_shared<DiffBookMonster>("BookMonster����/BookMonster����.pmd", position, turnController);
	}
	else if (characterName == "DiffEgg"){
		return std::make_shared<DiffEgg>("���܂��N����/���܂��N����.pmd", position, turnController);
	}
	else if (characterName == "DiffMushroom"){
		return std::make_shared<DiffMushroom>("�L�m�R�N����/�L�m�R�N����.pmd", position, turnController);
	}
	else if (characterName == "DiffSmallAnimal"){
		return std::make_shared<DiffSmallAnimal>("���t���t�N����/���t���t�N����.pmd", position, turnController);
	}
	else if (characterName == "DiffSmallBird"){
		return std::make_shared<DiffSmallBird>("�؂�؂�N����/�؂�؂�N����.pmd", position, turnController);
	}
	else if (characterName == "DiffMimic"){
		return std::make_shared<DiffMimic>("��(�~�~�b�N)����/��(�~�~�b�N)����.pmd", position, turnController);
	}
	else if (characterName == "Ankouasyu"){
		return std::make_shared<NormalEnemy>("Ankouasyu", "�A���R�E����/Ankouasyu.pmd", position, turnController);
	}
	else if (characterName == "KingsuraimuRed"){
		return std::make_shared<NormalEnemy>("KingsuraimuRed","�L���O�X���C�����b�h/KingsuraimuRed.pmd", position, turnController);
	}
	else if (characterName == "�N���[�P������"){
		return std::make_shared<NormalEnemy>("�N���[�P������","�N���[�P���@��1/kurakenLegOne.pmd", position, turnController);
	}
	else if (characterName == "�N���[�P������"){
		return std::make_shared<NormalEnemy>("�N���[�P������","�N���[�P���@��2/kurakenLegTwo.pmd", position, turnController);
	}
	else if (characterName == "�N���[�P��"){
		return std::make_shared<Kraken>("�N���[�P���@�{��/kuraken.pmd", position, turnController);
	}
	else if (characterName == "MiyamotoDark"){
		return std::make_shared<NormalEnemy>("MiyamotoDark","�ŋ{�{/MiyamotoDark.pmd", position, turnController);
	}
	else if (characterName == "JugglerAsyu"){
		return std::make_shared<NormalEnemy>("JugglerAsyu","�W���O���[����/JugglerAsyu.pmd", position, turnController);
	}
	else if (characterName == "HanaAsyu"){
		return std::make_shared<NormalEnemy>("HanaAsyu","�Ԉ���/HanaAsyu.pmd", position, turnController);
	}
	else if (characterName == "Suisya"){
		return std::make_shared<NormalEnemy>("Suisya","����/Suisya.pmd", position, turnController);
	}
	else if (characterName == "Faire"){
		return std::make_shared<NormalEnemy>("Faire","�΂̐���/Faire.pmd", position, turnController);
	}
	else if (characterName == "GreenDoraki"){
		return std::make_shared<NormalEnemy>("GreenDoraki","�h���L�[�O���[��/GreenDoraki.pmd", position, turnController);
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