#pragma once
#include "Obstacle.h"

class Motion;

class SaveBook :
	public Obstacle
{
private:
	std::shared_ptr<Motion> _motion;
	bool _save;
	bool _open;
public:
	bool beExamined();
	bool isSave();
	void resetSave();
	void action();
	SaveBook(std::string fileName, std::shared_ptr<Position> position);
	~SaveBook();
};

