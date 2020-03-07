#include "BookMonster.h"
#include "DxLib.h"
#include "ScreenMaterial.h"
#include "PositionConverter.h"
#include "Position.h"
#include "TurnController.h"
#include "StatesPoint.h"
#include "Motion.h"
#include "PlayerFollow.h"
#include "Weapon.h"
#include "SwordOfTheTree.h"
#include "LevelUpper.h"
#include "Effect.h"
#include "EffectUpdater.h"
#include "ExpEffect.h"

BookMonster::BookMonster(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController) : Enemy(fileName, position, turnController)
{
	this->_characterName = "BookMonster";
	this->_active = false;
	this->_characterDatas = std::make_shared<CharacterData>(this->_characterName);
	this->_characterDatas->dataRead();
}


BookMonster::~BookMonster()
{
}

bool BookMonster::beExamined()
{
	if (this->_active == false){
		this->_active = true;
		return true;
	}
	else{
		return false;
	}
}

void BookMonster::update()
{

	this->draw();	//3Dモデルの描画


	float moveSpeed = 5.0;	//1フレームに進むスピード。

	if (this->_active){
		this->_DIRECTION = this->_playerFollow.getFollowDirection(shared_from_this());	//プレイヤーが居る方角を向く。

		this->_screenMaterial->animation(this->_positionConverter.get3DPosition(this->_position), moveSpeed);	//なめらかに動く様に毎回呼んで少しずつ座標を更新する。 
		this->_screenMaterial->rotate(this->_angleConverter.getAngle(this->_DIRECTION) + 90);	//今向いている方向（this->DIRECTION）に応じて３Dモデルを回転させる。
		this->_motion->update();	//今再生しているモーションを更新する。
	}


	/*座標の更新が終わった &&
	攻撃モーションが終了している &&
	食らいモーションが終了している &&
	行動処理が終了している   ->   ターンコントローラーにターンを終了したことを知らせる。*/

	if ((this->_screenMaterial->isAnimationFinish() &&
		this->_motion->isMotionFinish(Action::Actions::ATTACK) &&
		//this->_motion->isMotionFinish(Action::Actions::BENDBACKWARD) &&
		this->_turnFinish) &&
		this->_active){

		this->_turnController->setTurnFinishedCharacter(shared_from_this());	//ターンコントローラーは、敵キャラ全員がこの関数を呼ぶとプレイヤーにターンを受け渡す。
	}



}

//ターンに関わらず行う処理
void BookMonster::move()
{
	int moveValueRow = 0;
	int moveValueColumn = 0;

	//プレイヤーとの距離が 4 以下の時、追うように進む。
	if (abs(Collision::getInstance()->getPlayerPos()->getRow() - this->_position->getRow()) <= 4 &&
		abs(Collision::getInstance()->getPlayerPos()->getColumn() - this->_position->getColumn()) <= 4){	//絶対値の差が 4 以下

		// Row //
		//プレイヤ座標 - 自分の座標が 0 以上の時、右に進む
		if (Collision::getInstance()->getPlayerPos()->getRow() - this->_position->getRow() > 0){
			moveValueRow = 1;
		}
		//0以下なら 左にすすむ。
		else if (Collision::getInstance()->getPlayerPos()->getRow() - this->_position->getRow() < 0){
			moveValueRow = -1;
		}

		//	Column //
		//プレイヤ座標 - 自分の座標が 0 以上の時、右に進む
		if (Collision::getInstance()->getPlayerPos()->getColumn() - this->_position->getColumn() > 0){
			moveValueColumn = 1;
		}
		//0以下なら 左にすすむ。
		else if (Collision::getInstance()->getPlayerPos()->getColumn() - this->_position->getColumn() < 0){
			moveValueColumn = -1;
		}

	}
	//プレイヤーとの距離が 5 以上 なら、追わずにランダムに進む
	else{
		moveValueRow = _randomMove.getRandomMoveValue(1);
		moveValueColumn = _randomMove.getRandomMoveValue(1);
	}

	//Positionクラスのupdate～という名前の関数は、座標の更新が成功すると true を返す。失敗すると false を返す。
	if (this->_position->update(this->_position->getRow() + moveValueRow, this->_position->getColumn() + moveValueColumn, this->_position->getHeight(), shared_from_this())){

		this->_motion->start(false, Action::Actions::MOVE);	//移動モーションの再生開始
		this->_ACTION = Action::Actions::MOVE;	//アクションをMOVEに変更
	}
}

void BookMonster::actionOfCollision(std::shared_ptr<HitBox> hitBox)
{
	if (this->_active){
		hitBox->causeDamageToCharacter(this->_characterDatas, shared_from_this());

		if (this->_characterDatas->getStatesPoint()->getStatesPoint(State::States::HITPOINT) <= 0){
			this->_finish = true;
			this->_screenMaterial->setVisible(false);
			this->_motion->finalize();

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
}


void BookMonster::attack()
{
	_weapon->attack(shared_from_this(), this->_DIRECTION);	//自分の武器に攻撃を命令する。

	this->_motion->start(false, Action::ATTACK);	//攻撃モーションの開始。
	this->_ACTION = Action::Actions::ATTACK;
}


//1ターンに行う処理
void BookMonster::action()
{
	if (this->_characterDatas->getStatesPoint()->getStatesPoint(State::HITPOINT) <= 0){
		this->_turnFinish = true;
	}
	else{
		//自分のターンが終わっていない時
		if (_turnFinish == false){

			if (this->_active){
				//周囲8マス以内にプレイヤーが存在する場合。
				if (abs(Collision::getInstance()->getPlayerPos()->getRow() - this->_position->getRow()) <= 1 &&
					abs(Collision::getInstance()->getPlayerPos()->getColumn() - this->_position->getColumn()) <= 1){
					this->attack();
				}
				//しない場合。
				else{
					this->move();
				}
				this->_turnFinish = true;
	
			}
			else{
				this->_turnController->setTurnFinishedCharacter(shared_from_this());	//ターンコントローラーは、敵キャラ全員がこの関数を呼ぶとプレイヤーにターンを受け渡す。
			}

		}
	}
}