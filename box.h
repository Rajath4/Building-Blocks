#pragma once

#include "shapeFactory.h" 

class box : public shape
{ 
public:
	box(void);
	~box(void);
	int drawShape(float xpos, float ypos, int type, int rotation, int board[][10]);
	int isShapeColliding(float row, float col, int shape, int rotation, int board[][10]);
	int addToBoard(float xpos, float ypos, int type, int rotation, int board[][10]);
};