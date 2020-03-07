#include "SaveBook.h"
#include "PositionConverter.h"
#include "ScreenMaterial.h"
#include "Motion.h"

SaveBook::SaveBook(std::string fileName, std::shared_ptr<Position> position) : Obstacle(fileName, position)
{
	this->_save = false;
	this->_open = false;
	this->_motion = std::make_shared<Motion>(this->_screenMaterial->getHandle(), Action::ATTACK, Action::ATTACK, 1.0f);	//開くモーションを登録
	this->_motion->addMotionMap(Action::MOVE, Action::MOVE, 1.0f);	//ゆらゆらモーション
	this->_motion->addMotionMap(Action::BENDBACKWARD, Action::BENDBACKWARD, 1.0f);	//閉じるモーション
	
}


SaveBook::~SaveBook()
{
}

bool SaveBook::beExamined()
{
	
	this->_save = true;
	this->_open = true;
	this->_motion->start(false, Action::ATTACK);
	return false;
}

void SaveBook::action()
{
	PositionConverter converter;


	this->_screenMaterial->setPosition(converter.get3DPosition(this->_position));

	this->_screenMaterial->draw();
	this->_motion->update();
	

	 if (!this->_save){
		if (this->_motion->isMotionFinish(Action::MOVE) && this->_motion->isMotionFinish(Action::MOVE) && this->_motion->isMotionFinish(Action::BENDBACKWARD)){
			this->_motion->start(true, Action::MOVE);
			for (int i = 0; i < 10; i++){
				this->_motion->update();
			}
		}
	}
}

bool SaveBook::isSave()
{
	return this->_save && this->_motion->isMotionFinish(Action::ATTACK);
}

void SaveBook::resetSave()
{
	this->_save = false;
	this->_motion->start(false, Action::BENDBACKWARD);
}