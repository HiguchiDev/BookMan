#include "Motion.h"
#include "DxLib.h"

void Motion::start(bool loop, Action::Actions ACTION)
{
	this->_totalTime[this->_motionNumMap[ACTION]] = 0.0f;
	this->_playTime[this->_motionNumMap[ACTION]] = 0.0f;

	this->_ACTIVEACTION = ACTION;
	auto itr = this->_motionNumMap.find(ACTION);
	this->_loop = loop;

	if (itr != this->_motionNumMap.end()){
		

		MV1DetachAnim(this->_handle, this->_attachIndex);	//今アタッチしているアニメーションをデタッチ

		this->_attachIndex = MV1AttachAnim(this->_handle, this->_motionNumMap[ACTION], -1, FALSE);	//新しいアニメーションをアタッチ

		if (this->_attachIndex == -1){
			//exit(1);
		}

		//再生時間などを取得
		this->_totalTime[this->_motionNumMap[ACTION]] = MV1GetAttachAnimTotalTime(this->_handle, this->_attachIndex);
		this->_playTime[this->_motionNumMap[ACTION]] = 0.0f;
		
		this->motioning = true;

	}
	else{
		printfDx("アクションが登録されていません。 Motion::addMotionMap\n");
	}
}

void Motion::finalize()
{
	for (int i = 0; i < this->_totalTime.size(); i++){
		this->_totalTime[i] = 0.0f;
	}
	for (int i = 0; i < this->_playTime.size(); i++){
		this->_playTime[i] = 0.0f;
		this->motioning = false;
	}

	MV1DetachAnim(this->_handle, this->_attachIndex);	//今アタッチしているアニメーションをデタッチ
}

bool Motion::isMotionFinish(Action::Actions ACTION)
{


	return this->_playTime[this->_motionNumMap[ACTION]] >= this->_totalTime[this->_motionNumMap[ACTION]] || !this->motioning;
}

void Motion::update()
{

	auto itr = this->_motionNumMap.find(this->_ACTIVEACTION);

	if (itr != this->_motionNumMap.end()){
		if (this->motioning && this->_playTime[this->_motionNumMap[this->_ACTIVEACTION]] < this->_totalTime[this->_motionNumMap[this->_ACTIVEACTION]]){
			int motionNum = this->_motionNumMap[this->_ACTIVEACTION];

			this->_playTime[motionNum] += this->_motionSpeedMap[this->_ACTIVEACTION];

			MV1SetAttachAnimTime(this->_handle, this->_attachIndex, this->_playTime[motionNum]);
			
		}
		else{
			
			if (this->_loop){
				this->_playTime[this->_motionNumMap[this->_ACTIVEACTION]] = 0.0f;
			}
			else{
				this->motioning = false;
			}
		}

	}
	else{
		printfDx("アクションが登録されていません。 Motion::addMotionMap\n");
	}


}

void Motion::resetAll()
{
	this->motioning = false;

	for (int i = 0; i < this->_totalTime.size(); i++){
		this->_totalTime[i] = 0.0f;
		this->_playTime[i] = 0.0f;
	}
}

void Motion::reset()
{
	this->_playTime[this->_motionNumMap[this->_ACTIVEACTION]] = 0.0f;
}

void Motion::stop()
{
	this->motioning = false;
}

bool Motion::isMotionFinish()
{
	return this->_playTime[this->_motionNumMap[this->_ACTIVEACTION]] >= this->_totalTime[this->_motionNumMap[this->_ACTIVEACTION]] ||
		!this->motioning;
}

void Motion::addMotionMap(Action::Actions ACTION, int motionNum, float speed)
{
	MV1DetachAnim(this->_handle, this->_attachIndex);


	this->_motionNumMap[ACTION] = motionNum;

	while ((signed)this->_playTime.size() <= motionNum){
		this->_playTime.push_back(0.0f);
		this->_totalTime.push_back(0.0f);
	}

	this->_attachIndex = MV1AttachAnim(this->_handle, motionNum, -1, FALSE);

	this->_totalTime[motionNum] = MV1GetAttachAnimTotalTime(this->_handle, this->_attachIndex);
	this->_playTime[motionNum] = this->_totalTime[motionNum];
	this->_motionSpeedMap[ACTION] = speed;

	this->motioning = false;
	this->_ACTIVEACTION = ACTION;

}

Motion::Motion(int handle, Action::Actions ACTION, int motionNum, float speed)
{
	this->_ACTIVEACTION = ACTION;
	this->_handle = handle;
	this->_motionNumMap[ACTION] = motionNum;

	while ((signed)this->_playTime.size() <= motionNum){
		this->_playTime.push_back(0.0f);
		this->_totalTime.push_back(0.0f);
	}
	
	this->_attachIndex = MV1AttachAnim(handle, motionNum, -1, FALSE);

	this->_totalTime[motionNum] = MV1GetAttachAnimTotalTime(handle, this->_attachIndex);
	this->_playTime[motionNum] = this->_totalTime[motionNum];
	this->_motionSpeedMap[ACTION] = speed;

	this->motioning = false;
}


Motion::~Motion()
{
}
