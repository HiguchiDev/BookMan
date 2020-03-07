#include "PositionConverter.h"
#include "Position.h"

PositionConverter::PositionConverter() : _BLOCKBASE(50), _BLOCKDEPTH(50), _BLOCKHEIGHT(50)
{

}


PositionConverter::~PositionConverter()
{
}

VECTOR PositionConverter::get3DPosition(std::shared_ptr<Position> position)
{
	return VGet(this->_BLOCKBASE * position->getRow(), this->_BLOCKHEIGHT * position->getHeight(), this->_BLOCKDEPTH * position->getColumn());
}