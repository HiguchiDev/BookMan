#pragma once
#include <memory>

class FieldMaterial;
class Position;
class Trap;

class Position
	: public std::enable_shared_from_this<Position>
{	
private:
	int _row;
	int _column;
	int _height;
	bool acssesCheck(int r, int c, int h);
public:
	int getRow();
	int getColumn();
	int getHeight();
	bool update(int row, int column, int height, std::shared_ptr< FieldMaterial > fieldMaterial);
	bool update(int row, int column, int height, std::shared_ptr< Trap > trap);
	bool updateRow(int row, std::shared_ptr< FieldMaterial > fieldMaterial);
	bool updateColumn(int column, std::shared_ptr< FieldMaterial > fieldMaterial);
	bool updateHeight(int height, std::shared_ptr< FieldMaterial > fieldMaterial);
	void copy(std::shared_ptr<Position> position);

	Position(int row, int column, int height);
	~Position();
};

