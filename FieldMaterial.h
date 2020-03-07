#pragma once
#include <memory>
#include "Direction.h"
#include <string>
#include "Collision.h"

class ScreenMaterial;
class Position;


class FieldMaterial
{
protected:
	
	bool _finish;
	bool _visible;	
	bool _positionInitialized;
	virtual void initializePosition() = 0;
	std::shared_ptr<Position> _position;
	std::shared_ptr<ScreenMaterial> _screenMaterial;
public:
	virtual bool beExamined(){ return false; };
	std::shared_ptr<ScreenMaterial> getScreenMaterial(){ return this->_screenMaterial; };
	std::shared_ptr<Position> getPos();
	bool isFinish();
	bool isVisible();
	void setVisible(bool visible);
	void setFieldPos(std::shared_ptr<Position> position);
	virtual void draw();
	virtual void finalize();
	virtual void action();
	virtual void updateCollisionInformation(std::shared_ptr<Position> newPosition) = 0;
	
	virtual void initialize();
	bool isInitialized();

	FieldMaterial(std::string fileName, std::shared_ptr<Position> position);
	~FieldMaterial();
};

