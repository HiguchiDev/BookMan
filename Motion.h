#pragma once
#include "Action.h"
#include <unordered_map>
#include <vector>

//３Dモーションの再生をするクラス
class Motion
{
private:
	int _handle;
	std::unordered_map<Action::Actions, int> _motionNumMap;
	std::unordered_map<Action::Actions, float> _motionSpeedMap;
	std::vector<float> _playTime;
	std::vector<float> _totalTime;
	bool _loop;
	int _attachIndex;
	bool motioning;
	Action::Actions _ACTIVEACTION;
public:
	void resetAll();
	void finalize();
	void start(bool loop, Action::Actions ACTION);
	void reset();
	void stop();
	void update();
	bool isMotionFinish(Action::Actions ACTION);
	bool isMotionFinish();
	void addMotionMap(Action::Actions ACTION, int motionNum, float speed);
	Motion(int handle, Action::Actions ACTION, int motionNum, float speed);
	~Motion();
};

