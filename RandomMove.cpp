#include "RandomMove.h"


RandomMove::RandomMove()
{
}


RandomMove::~RandomMove()
{
}

int RandomMove::getRandomMoveValue(int limit)
{
	if (limit == 0){
		return 0;
	}

	for (int i = 1; i <= limit; i++){
		if (this->_randomGetter.isWinning(100 / (limit + 1))){
			if (this->_randomGetter.isWinning(50)){
				return i;
			}
			else{
				return -i;
			}
		}
	}

	return 0;
}
