#pragma once

class shape {
protected:
	int shapeMatrix[4][4];
public:
	virtual int drawShape(float x, float y, int type, int rotation, int b[][10]) = 0;
	virtual int isShapeColliding(float row, float col, int shape, int rotation, int board[][10]) = 0;
};
