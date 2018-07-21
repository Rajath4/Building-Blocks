#include <time.h>
#include <stdlib.h>
#include<stdio.h>

#include <iostream>
#include <gl\glew.h>
#include <gl\glut.h>
#include "board.h"
#include "box.h"
#include <string.h>

#include<math.h>

GLfloat xpos = 4;
GLfloat ypos = 15;
board *board::b = NULL;

void *font = GLUT_BITMAP_HELVETICA_18;
void *font1 = GLUT_BITMAP_TIMES_ROMAN_24;

int boardMap[15][10];
	box currentShape;
	static board *b;
	int curType;
	int nextType;
	int rotation;
	bool newShape;
	int totScore;


int mWidth  [7 /*kind */ ][4 /* rotation */ ] ={{2,2,2,2},
												{4,1,4,1},
												{2,3,2,3},
												{2,3,2,3},
												{2,3,2,3},
												{2,3,2,3},
												{2,3,2,3}};

int mHeight  [7 /*kind */ ][4 /* rotation */ ] ={{2,2,2,2},
												{1,4,1,4},
												{3,2,3,2},
												{3,2,3,2},
												{3,2,3,2},
												{3,2,3,2},
												{3,2,3,2}};

board::board(void)
{
	for(int i=0;i<15;i++){
		for(int j=0;j<10;j++){
			board::boardMap[i][j] = 0;
		}
	}

	b=this;
	srand (time(NULL));
	curType = rand() % 7;			//Defines Current shape
	nextType = rand() % 7;			//Defines Next shape
	rotation = 0;
	newShape = true;
	totScore = 0;
}

board::~board(void)
{
}

void board::init() {
	glClear(GL_COLOR_BUFFER_BIT);




	glColor3f(1.0, 1.0, 1.0);
	//Making a box (White Color)
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(0.01, 0.01, 0.0);
		glVertex3f(0.61, 0.01, 0.0);
		glVertex3f(0.01, 0.91, 0.0);
		glVertex3f(0.61, 0.91, 0.0);
	glEnd();
	
}
//Base joined shape
void board::drawSquare(int row, int col){
	float x = .06*col+0.01;
	float y = .06*(14-row)+0.01;
	glColor3f(0.8, 0.1, 0.4);			//Color of joined shape
	//glColor3f(0, 0, 0);				
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(x, y, 0.0);
		glVertex3f(x, y+0.06, 0.0);
		glVertex3f(x+0.06, y, 0.0);
		glVertex3f(x+0.06, y+0.06, 0.0);
	glEnd();
}


void board::drawPiecesOnBoard(){
	for (int i = 0;i<15;i++){
		for(int j=0;j<10;j++){
			if (b->boardMap[i][j] == 1){
				drawSquare(i,j);
			}
		}
	}

}

void board::checkLines(){
	bool lineComplete;
	int totLines = 0;
	//int tempScore = 0;

	for(int row = 14; row >=0;row--){
		lineComplete=true;
		for(int col=0;col<10;col++){
			if(b->boardMap[row][col] == 0){
				lineComplete=false;
			}
		}
		if(lineComplete){//line is complete. Shift board pieces down
			totLines++;
			b->totScore += 10;			//increment score
			int temp = row-1;
			for(;temp>=0;temp--){
				for(int j=0;j<10;j++){
					if(b->boardMap[temp][j] ==1){
						b->boardMap[temp][j] = 0;
						b->boardMap[temp+1][j] = 1;
					}else if(b->boardMap[temp][j] == 0){
						b->boardMap[temp+1][j] = 0;
					}
				}
			}
		}
		int temp = 0;		
	}
}

void board::moveY(){
			
	if (b->newShape) {
		xpos = 4;
		ypos = 15;
		//set new shape type
		srand (time(NULL));
		b->curType = b->nextType;
		b->nextType = rand() % 7;
		b->rotation = 0;
		b->newShape = false;
	} else {
		ypos--;
	}
}

void board::displayNextType() {
	b->currentShape.drawShape(12, 12, b->nextType, 0, b->boardMap); //To draw next shape
}

std::string s = "Next:";
std::string score = "Score:";
void board::renderStrings() {
	glColor3d(1.0,0.0,0.0);
	glRasterPos2d(0.75, 0.75);
	for(int n=0; n<s.size();++n){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[n]);
	}
	glRasterPos2d(0.75, 0.40);
	for(int n=0; n<score.size();++n){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, score[n]);
	}
	glRasterPos2d(0.75, 0.30);
	char sc [10];
	itoa (b->totScore, sc, 10);
	//std::cout<<"sc="<<sc<<std::endl;
	for(int n=0; n<10;++n){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, sc[n]);
	}
}
//Move to game over screen
void board::gameOver(){
	glutDisplayFunc(gameOverDisplay);
	gameOverDisplay();
	glEnd();
	glutSwapBuffers();
}

void board::draw() {
	init();
	int ret;
	int s = b->currentShape.isShapeColliding(xpos, ypos, b->curType, b->rotation, b->boardMap);
	int temp = (ypos - mHeight[b->curType][b->rotation] +1);
	switch (s){
	case 1:
		if (temp == 0){
			ypos++;
			b->currentShape.addToBoard(xpos, ypos, b->curType, b->rotation, b->boardMap);
			b->newShape = true;
		}
		break;
	case 2:
		ypos++;
		ret = b->currentShape.addToBoard(xpos, ypos, b->curType, b->rotation, b->boardMap);
		if(ret) {
			gameOver();
		}
		b->newShape = true;
		break;
	case -1:
		b->currentShape.drawShape(xpos, ypos, b->curType, b->rotation, b->boardMap);
		break;
	}
	drawPiecesOnBoard();
	displayNextType();
	renderStrings();
	checkLines();
}

void Timer(int iUnused)
{
    glutPostRedisplay();
	glutSwapBuffers();
    glutTimerFunc(1000, Timer, 0);
	board::moveY();
}

void board::keyPressed(int key, int x, int y){
	switch(key)
	{
	case GLUT_KEY_UP:
		if(b->rotation == 3) {
			if(xpos + mWidth[b->curType][0] < 10.5) {
				if((b->currentShape.isShapeColliding(xpos, ypos, b->curType, b->rotation, b->boardMap)) < 0){
					b->rotation = 0;
					glutPostRedisplay();
					glutSwapBuffers();
				}
			} 
		} else if(xpos + mWidth[b->curType][b->rotation+1] < 10.5) {
			if((b->currentShape.isShapeColliding(xpos, ypos, b->curType, b->rotation, b->boardMap)) < 0){
				b->rotation += 1;
				glutPostRedisplay();
				glutSwapBuffers();
			}
		}

	break;	
	case GLUT_KEY_DOWN:
		ypos--;
		glutPostRedisplay();
		glutSwapBuffers();
	break;
	case GLUT_KEY_LEFT:
		if(xpos > 0){
			xpos -= 1;
			if((b->currentShape.isShapeColliding(xpos, ypos, b->curType, b->rotation, b->boardMap)) < 0){
				glutPostRedisplay();
				glutSwapBuffers();
			} else {
				xpos++;
			}
		}
	break;
	case GLUT_KEY_RIGHT:
		if(xpos + mWidth[b->curType][b->rotation] < 10){
			xpos++;
			if((b->currentShape.isShapeColliding(xpos, ypos, b->curType, b->rotation, b->boardMap)) < 0){
				glutPostRedisplay();
				glutSwapBuffers();
			}else {
				xpos--;
			}
		}
	break;
	}	
}

void board::initialize(){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

void board::initializeBoard(int argc, char* argv[]){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(900, 700);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("BUILDING BLOCKS");
	myinit();
	glutDisplayFunc(display0);
	//glutDisplayFunc(gameOverDisplay);
	glutSpecialFunc(keyPressed);
	glutKeyboardFunc(myKey4);
	//Timer(0);
	glutMainLoop();
}


void board::myinit()
{
	

	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 0); //Background of Home Screen
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(24.0, 0.0, 24.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	

}
void board::display0(void)
{
	myinit();

	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(-1.0, -1.0);

	glVertex2f(-1.0, 30.0);

	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(30.0, 30.0);

	glVertex2f(30.0, -1.0);

	glEnd();

	




	//glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 1.0, 1.0);
	output(20, 3, "SHRI MADHWA VADIRAJA INSTITUTE OF TECHNOLOGY & MANAGEMENT");
	output(24, 6, "***************************************************************************************************************************************************************************************");

	glColor3f(0.0, 1.0, 1.0);
	output(20, 11, "MINI PROJECT ON COMPUTER GRAPHICS & VISUALIZATION");
	glColor3f(1.0, 1.0, 1.0);
	outputMaxFont(15, 13, "BUILDING BLOCKS");
	glColor3f(219, 213, 176);
	output(23, 17, "DEVELOPED BY");
	output(23, 18, "---------------");
	output(23, 19, "RAJATH - 4MW15CS071");
	output(23, 20, "PRAKHYATH YADAV - 4MW15CS067");
	output(7, 17, "PROJECT GUIDE");
	output(7, 18, "----------------");
	output(7, 19, "Mrs. SOWMYA S");
	glColor3f(1.0, 1.0, 0.0);
	output(15, 23, "PRESS S KEY TO CONTINUE");
	glutSwapBuffers();
}
void board::gameOverDisplay(void)
{
	myinit();
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(-1.0, -1.0);

	glVertex2f(-1.0, 30.0);

	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(30.0, 30.0);

	glVertex2f(30.0, -1.0);

	glEnd();


	

	
	
	char sc[10];
	itoa(b->totScore, sc, 10);
	glColor3f(1.0, 1.0, 1.0);
	outputMaxFont(15, 5, "GAME OVER");
	glColor3f(1.0, 0.0, 0.0);
	output(17, 12, "*********************************************");
	outputMaxFont(16, 10, "YOUR SCORE IS : ");
	outputMaxFont(14, 11, sc);
	output(17, 9, "**********************************************");


	glColor3f(0.0, 1.0, 0.0);
	output(17, 16, "THANK YOU FOR PLAYING BUILDING BLOCKS");
	output(19, 18, "----------------------------------------------");



	glColor3f(1.0, 1.0, 0.0);
	output(15, 23, "PRESS Q KEY TO QUIT");
	glutSwapBuffers();
}

void board::output(int x, int y, char *string)
{
	int len, i;
	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i<len; i++)
	{
		glutBitmapCharacter(font, string[i]);
	}
}
void board::outputMaxFont(int x, int y, char *string)
{
	int len, i;
	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i<len; i++)
	{
		glutBitmapCharacter(font1, string[i]);
	}
}

void board::myKey4(unsigned char key, int x, int y)
{
	if (key == 's' || key == 'S')
	{
		initialize();
		Timer(0);

		glutDisplayFunc(draw);
		draw();
		glEnd();
		glutSwapBuffers();
		
	}
	else if (key == 'q' || key == 'Q')
	{
		exit(0);
	}
}


