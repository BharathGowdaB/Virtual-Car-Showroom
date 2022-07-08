#include<stdio.h>
#include<GL/glut.h>
#include "./HeaderFiles/define.h"
#include "./HeaderFiles/Text.h"
#include "./HeaderFiles/Extras.h"
#include "./HeaderFiles/main.h"
#include "./HeaderFiles/customer.h"
#include "./HeaderFiles/admin.h"


//Initial Display Function
void startDisplay(){

	glClearColor(1.0,1.0, 1, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	
	GLfloat sides[4][4]={{0,0,1},{1,0,1},{1,1,1},{0,1,1}};
	drawPolygon(sides[0],sides[1],sides[2],sides[3]);

	glutSwapBuffers();
	glFlush();
	
}

void startMenu(int key,int state,int x,int y){
	if(key == GLUT_LEFT_BUTTON){
		menuInit();
	}
}

void startReshape(int w,int h){
	glViewport(0, 0, w, h);
 	glMatrixMode(GL_PROJECTION);
 	glLoadIdentity();
	gluOrtho2D(0, 1, 0, 1);
 	glMatrixMode(GL_MODELVIEW);
 	glLoadIdentity();
 	winHeight = h/2;
	winWidth = w/2;
}


void startInit(){
	glViewport(0,0,winWidth * 2,winHeight * 2);
		glMatrixMode(GL_PROJECTION);
			gluOrtho2D(0,1,0,1);
		glMatrixMode(GL_MODELVIEW);
		
	bCount = eCount = tCount =0;
	/*
	text[0].init(-400,180,"BANGALORE INSTITUTE OF TECHNOLOGY",800);
	text[0].textAlign = TEXT_CENTER;
	text[0].borderType = NO_BORDER;
	text[0].setTextStyle(GLUT_BITMAP_TIMES_ROMAN_24,24);
	text[0].setPadding(20,20);
	tCount++;
	
	text[1].init(-400,150,"K R ROAD, V V PURUM, BANGALORE-560073",800);
	text[1].textAlign = TEXT_CENTER;
	text[1].borderType = NO_BORDER;
	text[1].setTextStyle(GLUT_BITMAP_HELVETICA_12,12);
	text[1].setPadding(5,5);
	tCount++;
	
	text[2].init(-400,110,"DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING",800);
	text[2].textAlign = TEXT_CENTER;
	text[2].borderType = NO_BORDER;
	text[2].setTextStyle(GLUT_BITMAP_HELVETICA_18,18);
	text[2].setPadding(5,5);
	tCount++;
	
	text[3].init(-400,0,"Computer Graphics Laboratory with Mini Project",800);
	text[3].textAlign = TEXT_CENTER;
	text[3].borderType = NO_BORDER;
	text[3].setTextStyle(GLUT_BITMAP_HELVETICA_18,18);
	text[3].setPadding(5,5);
	tCount++;
	
	text[4].init(-400,-40,"18CSL67",800);
	text[4].textAlign = TEXT_CENTER;
	text[4].borderType = NO_BORDER;
	text[4].setTextStyle(GLUT_BITMAP_HELVETICA_18,18);
	text[4].setPadding(5,5);
	tCount++;
	
	text[5].init(-400,-80,"\"3D CAR SHOWROOM\"",800);
	text[5].textAlign = TEXT_CENTER;
	text[5].borderType = NO_BORDER;
	text[5].setTextStyle(GLUT_BITMAP_HELVETICA_18,18);
	text[5].setPadding(5,5);
	tCount++;
	*/
	
	initTexture("./docs/mainFinal.jpeg");
	
	glViewport(0, 0, winWidth, winHeight);
 	glMatrixMode(GL_PROJECTION);
 	glLoadIdentity();
	gluOrtho2D(0,  winWidth, 0, winHeight);
 	glMatrixMode(GL_MODELVIEW);
 	glLoadIdentity();
	
	glutDisplayFunc(startDisplay);
	glutReshapeFunc(startReshape);
	glutMouseFunc(startMenu);
	glutPostRedisplay();	
}


//Menu Display Function
void menuDisplay(){
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
		glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glViewport(0, 0, winWidth * 2, winHeight * 2);
			glOrtho(-winWidth,winWidth,-winHeight,winHeight,-10,10);
		
		glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
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
	
	button[1].init(-70,100,"Admin",140);
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
	bCount++;
	
	text[0].init(-200,170,"3D CAR SHOWROOM",400);
	text[0].textAlign = TEXT_CENTER;
	text[0].borderType = NO_BORDER;
	text[0].setTextStyle(GLUT_BITMAP_TIMES_ROMAN_24,24);
	text[0].setPadding(20,20);
	tCount++;
	
	glutDisplayFunc(menuDisplay);
	glutReshapeFunc(menuReshape);
	glutMouseFunc(menuMouse);
	glutPostRedisplay();
}


int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1280,720);
	winWidth = 640;
	winHeight = 360;
	mainWin = glutCreateWindow("MENU");
	
	startInit();
	
	FILE *fp = fopen(FILE_CAR_LIST,"r");
	while(fscanf(fp,"%s %s\n",carlist[carCount],carlist[carCount + 1]) != EOF)
		carCount += 2;
	fclose(fp);
	currentCarIndex = 0;
	
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	
}
