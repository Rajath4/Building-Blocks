#include "box.h"
#include <iostream>
#include <gl\glut.h>


int mShapes [7 /*kind */ ][4 /* rotation */ ][5 /* horizontal blocks */ ][5 /* vertical blocks */ ] =
{
// Square
  {
   {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 2, 1, 0},
    {0, 0, 3, 3, 0},
    {0, 0, 0, 0, 0}
    },
   {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 2, 1, 0},
    {0, 0, 3, 3, 0},
    {0, 0, 0, 0, 0}
    },
   {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 2, 1, 0},
    {0, 0, 3, 3, 0},
    {0, 0, 0, 0, 0}
    },
   {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 2, 1, 0},
    {0, 0, 3, 3, 0},
    {0, 0, 0, 0, 0}
    }
   },

// I
  {
   {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 3, 3, 3, 3},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
    },
   {
    {0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0}, 
    {0, 0, 2, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 3, 0, 0}
    },
   {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {3, 3, 3, 3, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
    },
   {
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 2, 0, 0},
    {0, 0, 3, 0, 0},
    {0, 0, 0, 0, 0}
    }
   }
  ,
// L
  {
   {
    {0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 2, 0, 0},
    {0, 0, 3, 3, 0},
    {0, 0, 0, 0, 0}
    },
   {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 1, 3, 3, 0},
    {0, 3, 0, 0, 0},
    {0, 0, 0, 0, 0}
    },
   {
    {0, 0, 0, 0, 0},
    {0, 3, 1, 0, 0},
    {0, 0, 2, 0, 0},
    {0, 0, 3, 0, 0},
    {0, 0, 0, 0, 0}
    },
   {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0},
    {0, 3, 3, 3, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
    }
   },
// L mirrored
  {
   {
    {0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 2, 0, 0},
    {0, 3, 3, 0, 0},
    {0, 0, 0, 0, 0}
    },
   {
    {0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0},
    {0, 3, 3, 3, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
    },
   {
    {0, 0, 0, 0, 0},
    {0, 0, 1, 3, 0},
    {0, 0, 2, 0, 0},
    {0, 0, 3, 0, 0},
    {0, 0, 0, 0, 0}
    },
   {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 3, 3, 1, 0},
    {0, 0, 0, 3, 0},
    {0, 0, 0, 0, 0}
    }
   },
// N
  {
   {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0},
    {0, 0, 2, 3, 0},
    {0, 0, 3, 0, 0},
    {0, 0, 0, 0, 0}
    },
   {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 3, 2, 0, 0},
    {0, 0, 3, 3, 0},
    {0, 0, 0, 0, 0}
    },
   {
    {0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 1, 3, 0, 0},
    {0, 3, 0, 0, 0},
    {0, 0, 0, 0, 0}
    },
   {
    {0, 0, 0, 0, 0},
    {0, 3, 1, 0, 0},
    {0, 0, 3, 3, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
    }
   },
// N mirrored
  {
   {
    {0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 3, 1, 0},
    {0, 0, 0, 3, 0},
    {0, 0, 0, 0, 0}
    },
   {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 2, 3, 0},
    {0, 3, 3, 0, 0},
    {0, 0, 0, 0, 0}
    },
   {
    {0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0},
    {0, 3, 2, 0, 0},
    {0, 0, 3, 0, 0},
    {0, 0, 0, 0, 0}
    },
   {
    {0, 0, 0, 0, 0},
    {0, 0, 1, 3, 0},
    {0, 3, 3, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
    }
   },
// T
  {
   {
    {0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 2, 3, 0},
    {0, 0, 3, 0, 0},
    {0, 0, 0, 0, 0}
    },
   {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 3, 2, 3, 0},
    {0, 0, 3, 0, 0},
    {0, 0, 0, 0, 0}
    },
   {
    {0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 3, 2, 0, 0},
    {0, 0, 3, 0, 0},
    {0, 0, 0, 0, 0}
    },
   {
    {0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 3, 3, 3, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
    }
   }
};

int mDisplace  [7 /*kind */ ][4 /* rotation */ ][2 /* position */] =
{
/* Square */
  {
	{-2, -2}, 
    {-2, -2},
    {-2, -2},
    {-2, -2}
   },
/* I */
  {
	{-1, -2},
    {-2, -1},
    {0, -2},
    {-2, 0}
   },
/* L */
  {
	{-2, -1},
    {-1, -2},
    {-1, -1},
    {-1, -1}
   },
/* L mirrored */
  {
	{-1, -1},
    {-1, -1},
    {-2, -1},
    {-1, -2}
   },
/* N */
  {
	{-2, -1},
    {-1, -2},
    {-1, -1},
    {-1, -1}
   },
/* N mirrored */
  {
	{-2, -1},
    {-1, -2},
    {-1, -1},
    {-1, -1}
   },
/* T */
  {
	{-2, -1},
    {-1, -2},
    {-1, -1},
    {-1, -1}
   },
};

float color [7][3] = {{.3,.7,.3}, {.5,.5,.5}, {.8,.8,.8}, {1,.2,.6}, {.2,1,.6}, {.2,.6,1}, {1,1,0}};


box::box(void)
{
	int shapeMatrix = {0};
}


box::~box(void)
{
}

int box::addToBoard(float xpos, float ypos, int type, int rotation, int board[][10]){
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (mShapes[type][rotation][i][j] != 0) {
				int tempCol = xpos + j + mDisplace[type][rotation][0];
				int tempRow = 14 - ypos + i + mDisplace[type][rotation][1]+1;
				board[tempRow][tempCol] = 1;
				if(tempRow == 0) {
					return 1;
				}
			}
		}
	}
	return 0;
}


int box::isShapeColliding(float xpos, float ypos, int type, int rotation, int board[][10]){
	float x = .06*xpos+0.01;
	float y = .06*ypos+0.01;
	
	float a,b,c,d;
	int isColliding = -1;
	//check if the piece is going out of the borders of the board
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (mShapes[type][rotation][i][j] != 0) {

				int tempCol = xpos + j + mDisplace[type][rotation][0];
				int tempRow = 14 - ypos + i + mDisplace[type][rotation][1]+1;
				if(board[tempRow][tempCol] == 1){ // collision with existing piece
					isColliding = 2;
					break;
				}

				a = x+j*.06+(mDisplace[type][rotation][0]*.06);b =y-i*0.06-(mDisplace[type][rotation][1]*.06); c= x+0.06+(j*0.06)+(mDisplace[type][rotation][0]*.06); d=y-0.06-(i*0.06)-(mDisplace[type][rotation][1]*.06);
				if(a>=0.62 || a<=0.0 || c>=0.62 || c<=0.01 || b==0.91 || b<=0.01 || d==0.91 || d<=0.01) {
					isColliding = 1;
					break;
				}

			}
		}
	}
	return isColliding;
}

//Draw the object shape
int box::drawShape(float xpos, float ypos, int type, int rotation, int board[][10]) {

	float x = .06*xpos+0.01;
	float y = .06*ypos+0.01;
	float a,b,c,d;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (mShapes[type][rotation][i][j] != 0) {
				a = x+j*.06+(mDisplace[type][rotation][0]*.06);b =y-i*0.06-(mDisplace[type][rotation][1]*.06); c= x+0.06+(j*0.06)+(mDisplace[type][rotation][0]*.06); d=y-0.06-(i*0.06)-(mDisplace[type][rotation][1]*.06);
				glColor3f(color[type][0], color[type][1], color[type][2]);	//Shape Color
				glBegin(GL_TRIANGLE_STRIP);
					glVertex3f(a, b, 0.0);
					glVertex3f(a, d, 0.0);
					glVertex3f(c, b, 0.0);
					glVertex3f(c, d, 0.0);
				glEnd();
			}
		}
	}
	return 0;
}

