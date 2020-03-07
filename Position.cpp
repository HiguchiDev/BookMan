#include "Position.h"
#include "FieldMaterial.h"
#include "Collision.h"
#include "FieldLength.h"
#include "DxLib.h"

Position::Position(int row, int column, int height)
{
	this->_row = row;
	this->_column = column;
	this->_height = height;
}


Position::~Position()
{
}

int Position::getRow()
{
	return this->_row;
}

int Position::getColumn()
{
	return this->_column;
}

int Position::getHeight()
{
	return this->_height;
}

bool Position::acssesCheck(int r, int c, int h)
{
	if ((r >= 0 && r < FieldLength::_ROW) &&
		(c >= 0 && c < FieldLength::_COLUMN) &&
		(h >= 0 && h < FieldLength::_HEIGHT)){
		return true;
	}
	else{
		return false;
	}
}

bool Position::update(int row, int column, int height, std::shared_ptr< FieldMaterial > fieldMaterial)
{
	std::shared_ptr<Position> newPosition = std::make_shared<Position>(row, column, height);
	if (this->acssesCheck(row, column, height)){

		if (Collision::getInstance()->isMovable(fieldMaterial, newPosition)){
			fieldMaterial->updateCollisionInformation(newPosition);
			this->_row = row;
			this->_column = column;
			this->_height = height;


			return true;
		}
		else{
			return false;
		}
	}
	else{

		return false;
	}
}

bool Position::update(int row, int column, int height, std::shared_ptr< Trap > trap)
{
	if (this->acssesCheck(row, column, height)){

		this->_row = row;
		this->_column = column;
		this->_height = height;


		return true;
	}
	else{
		return false;
	}
}

bool Position::updateRow(int row, std::shared_ptr< FieldMaterial > fieldMaterial)
{

	std::shared_ptr<Position> newPosition = std::make_shared<Position>(row, this->_column, this->_height);
	if (this->acssesCheck(row, this->_column, this->_height)){
		if (Collision::getInstance()->isMovable(fieldMaterial, newPosition)){

			fieldMaterial->updateCollisionInformation(newPosition);
			this->_row = row;
			return true;
		}
		else{
			return false;
		}
	}
	else{

		return false;
	}
}

bool Position::updateColumn(int column, std::shared_ptr< FieldMaterial > fieldMaterial)
{
	std::shared_ptr<Position> newPosition = std::make_shared<Position>(this->_row, column, this->_height);

	if (this->acssesCheck(this->_row, column, this->_height)){
		if (Collision::getInstance()->isMovable(fieldMaterial, newPosition)){

			fieldMaterial->updateCollisionInformation(newPosition);
			this->_column = column;
			return true;
		}
		else{
			return false;
		}
	}
	else{

		return false;
	}
}

bool Position::updateHeight(int height, std::shared_ptr< FieldMaterial > fieldMaterial)
{
	if (this->acssesCheck(this->_row, this->_column, height)){
		if (Collision::getInstance()->isMovable(fieldMaterial, std::make_shared<Position>(this->_row, this->_column, height))){
			std::shared_ptr<Position> newPosition = std::make_shared<Position>(this->_row, this->_column, height);
			fieldMaterial->updateCollisionInformation(shared_from_this());
			this->_height = height;
			return true;
		}
		else{
			return false;
		}
	}
	else{
	
		return false;
	}
}

void Position::copy(std::shared_ptr<Position> position)
{
	this->_row = position->getRow();
	this->_column = position->getColumn();
	this->_height = position->getHeight();
}