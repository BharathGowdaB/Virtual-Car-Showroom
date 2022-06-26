#include<stdio.h>
#include<GL/glut.h>
#include "define.h"
#include "Text.h"
#include "Extras.h"
#include "main.h"
#include "customer.h"
#include "admin.h"

void menuDisplay(){
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
		glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glViewport(0, 0, winWidth * 2, winHeight * 2);
			glOrtho(-winWidth,winWidth,-winHeight,winHeight,-10,10);
		
		glMatrixMode(GL_MODELVIEW);
			renderAllText();	
	glPopMatrix();	
	
	glutSwapBuffers();
}


void menuReshape(int w,int h){
	done = 0;
	winHeight = h/2;
	winWidth = w/2;
}


void menuMouse(int key,int state,int x,int y){
	x -= winWidth;
	y -= winHeight;
	y *= -1;
	printf("%d,%d\n",x,y);
	if(key == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		button[0].onClick(x,y);
		button[1].onClick(x,y);
		if(button[2].onClick(x,y)){
			exit(0);
		}
		editText[0].onSelect(x,y,func);
	}
}

void Exit(){
	exit(0);
}

void menuInit(){
	
	glViewport(0,0,winWidth * 2,winHeight * 2);
		glMatrixMode(GL_PROJECTION);
			glOrtho(-1*winWidth,winWidth,-1*winHeight,winHeight,-10,10);
		glMatrixMode(GL_MODELVIEW);
		
	bCount = eCount = tCount =0;
		
	// Buttons
	button[0].init(-70,50,"Customer",140);
	button[0].setPadding(10,10);
	button[0].setColor(1,1,1);
	button[0].setTextStyle(GLUT_BITMAP_HELVETICA_18,18);
	button[0].setBackground(0.2,0.2,0.8);
	button[0].setOnClick(renderCustomer);
	bCount++;
	
	button[1].init(-70,100,"Administer",140);
	button[1].setPadding(10,10);
	button[1].setColor(1,1,1);
	button[1].setTextStyle(GLUT_BITMAP_HELVETICA_18,18);
	button[1].setBackground(0.2,0.2,0.8);
	button[1].setOnClick(renderAdmin);
	bCount++;
	
	button[2].init(-70,0,"Exit",140);
	button[2].setPadding(10,10);
	button[2].setColor(1,1,1);
	button[2].setTextStyle(GLUT_BITMAP_HELVETICA_18,18);
	button[2].setBackground(0.2,0.2,0.8);
	//button[2].setOnClick(Exit);
	bCount++;
	
	text[0].init(-200,170,"3D SHOWROOM",400);
	text[0].textAlign = TEXT_CENTER;
	text[0].borderType = NO_BORDER;
	text[0].setTextStyle(GLUT_BITMAP_TIMES_ROMAN_24,24);
	text[0].setPadding(20,20);
	tCount++;
	
	glutDisplayFunc(menuDisplay);
	glutReshapeFunc(menuReshape);
	glutMouseFunc(menuMouse);
	
}
int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1280,586);
	winWidth = 1280;
	winHeight =586;
	mainWin = glutCreateWindow("MENU");
	
	menuInit();
	
	
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	
}
