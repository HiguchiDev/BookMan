#pragma once
#include "Cursor.h"
class CurorThereIsALimit :
	public Cursor
{
private:
	int _limitNum;
public:
	void move(MoveType::MoveTypes MOVETYPE);
	CurorThereIsALimit(int menuNum, float distanceRow, float distanceColumn, float x, float y, int limitNum);
	~CurorThereIsALimit();
};

