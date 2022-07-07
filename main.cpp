#include<stdio.h>
#include<GL/glut.h>
#include "./HeaderFiles/define.h"
#include "./HeaderFiles/Text.h"
#include "./HeaderFiles/Extras.h"
#include "./HeaderFiles/main.h"
#include "./HeaderFiles/customer.h"
#include "./HeaderFiles/admin.h"
#define STB_IMAGE_IMPLEMENTATION
#include "./HeaderFiles/stb_image.h"

static unsigned int textureNames[5];
typedef GLfloat point[3];

void drawPolygon(point a, point b, point c, point d)
{
   
     glDisable(GL_COLOR_MATERIAL);
     //glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
     glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, textureNames[0]);
    
    glBegin(GL_QUADS);
   
    glTexCoord2f(0.0, 1.0);
    glVertex3fv(a);
    glTexCoord2f(1.0, 1.0);
    glVertex3fv(b);
    glTexCoord2f(1.0, 0.0);
    glVertex3fv(c); //left
    glTexCoord2f(0.0, 0.0);
    glVertex3fv(d);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    //glEnable(GL_COLOR_MATERIAL);
}

void startDisplay(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glClearColor(0.0,0.0, 0, 0.0);
	
	GLfloat sides[4][4]={{0,0,1},{1,0,1},{1,1,1},{0,1,1}};
	drawPolygon(sides[0],sides[1],sides[2],sides[3]);

	glutSwapBuffers();
	glFlush();
	
}
void initTexture()
{
    
    int width, height, nrChannels;
    unsigned char *image_data;

    glGenTextures(1, textureNames);

   
        image_data = stbi_load("./docs/mainScreen.jpeg", &width, &height, &nrChannels, 0);

        glBindTexture(GL_TEXTURE_2D, textureNames[0]);

      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
       glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
        stbi_image_free(image_data);

}
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
void menuReshape(int w,int h){
	done = 0;
	winHeight = h/2;
	winWidth = w/2;
}

void startMenu(int key,int state,int x,int y){
	if(key == GLUT_LEFT_BUTTON){
		menuInit();
	}
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

void startInit(){
	glViewport(0,0,winWidth * 2,winHeight * 2);
		glMatrixMode(GL_PROJECTION);
			glOrtho(0,1,0,1,-10,10);
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
	
	initTexture();
	
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
	
	//printf("%s ,%s \n",carlist[0],carlist[2]);
	
	
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	
}
