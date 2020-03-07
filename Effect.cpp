#include "Effect.h"
#include "EffekseerForDXLib.h"
#include "Direction_AngleConverter.h"

void Effect::stop()
{

}

void Effect::start(Direction::Directions DIRECTION)
{
	// エフェクトを再生する。
	this->_playingEffectHandle = PlayEffekseer3DEffect(this->_effectHandle);

	Direction_AngleConverter da;

	SetRotationPlayingEffekseer3DEffect(this->_playingEffectHandle, 0.0f, (da.getAngle(DIRECTION) - 180) * DX_PI_F / 180.f, 0.0f);
	
	this->_finish = false;
}

void Effect::update()
{

	SetPosPlayingEffekseer3DEffect(this->_playingEffectHandle, this->_position.x, this->_position.y, this->_position.z);


	

	if (IsEffekseer3DEffectPlaying(this->_playingEffectHandle)){
		this->_finish = true;
	}



	
	// Effekseerにより再生中のエフェクトを描画する。
	

	
}

Effect::Effect(std::string fileName)
{
	SetUseASyncLoadFlag(false);
	this->_effectHandle = LoadEffekseerEffect(fileName.c_str());

	

	this->_playingEffectHandle = -1;
	this->_time = 0;
	
	this->_position = VGet(0.0, 0.0, 0.0);

	this->_finish = false;
}

void Effect::setPos(VECTOR position)
{
	this->_position = position;
}

Effect::~Effect()
{
	//this->finalize();
}

bool Effect::isEnd()
{
	return this->_finish;
}

void Effect::finalize()
{
//	DeleteEffekseerEffect(this->_effectHandle);
}
