#include "carmodel.h"

void customerUserContact();
void customerMotionFunc(int,int);

static void (*func)() = customerUserContact;
static scrollBarX userScr;
static scrollBarY carScrY;
static bool userScroll =false ,carScrollY = false,grabCar = false ,zoomCar = false,negativeRotate= false;
static int oldX,oldY;
static float modelTranslateY = -2.3,modelTranslateX = 0, zoom = 1.4;

static char carlist[10][150];
static int carCount = 0,currentCarIndex = 0;
static float theta = 0, wheelTheta = 0.0;
static int curBackground = -1,maxBackground = 1;

class lightObject{
	public : GLenum light;
	bool isEnabled = false;
};

lightObject lights[10];
static int  lightCount = 0;

void customerCarModel(){
	glPushMatrix();
		glEnable(GL_SCISSOR_TEST);
			glScissor(viewport[2].x0,viewport[2].y0,viewport[2].x1,viewport[2].y1);
			glClearColor(0.05,0.05,0.05,0.6);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
			glClearColor(1,1,1,1);
		glDisable(GL_SCISSOR_TEST);
	glPopMatrix();
	glFlush();
	
	glPushMatrix();
		glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glViewport(viewport[2].x0,viewport[2].y0,viewport[2].x1,viewport[2].y1);
			if(viewport[2].x1 > viewport[2].y1)
				glOrtho(-3.0 * (GLfloat)viewport[2].x1/(GLfloat)viewport[2].y1 ,3.0 * (GLfloat)viewport[2].x1/(GLfloat)viewport[2].y1 ,-3,3,-12,12);
			else 
				glOrtho(-3,3,-3.0 * (GLfloat)viewport[2].y1/(GLfloat)viewport[2].x1 , 3.0 * (GLfloat)viewport[2].y1/ (GLfloat) viewport[2].x1  ,-12,12);
		glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			char temp[150] ;
			strcpy(temp,curCar.brand);
			strcat(temp, " ");
			strcat(temp,curCar.model);
			text[8].init(-4.6,2.8,temp);
			text[8].setTextStyle(GLUT_BITMAP_TIMES_ROMAN_24,24);
			text[8].setColor(0,0,0);
			text[8].borderType = NO_BORDER;
			text[8].drawText();
			
			gluLookAt(2.0,0.70,2.0,0.0,0.2,0.2,0.0,1.0,0.0);
			/*if(curBackground == -2){
			glColor3f(1.0,1.0,1.0);
				glPushMatrix();
				//glScalef(2,2,2);
				drawTexCube(3);
				glPopMatrix();
			}
			else */if(curBackground >= 0){
			glPushMatrix();
				glColor3f(1.0,1.0,1.0);
				GLfloat side[4][3] = {{ -12,-4,8},{8,-4,-12},{8,3,-12},{-12,5,8}};
				drawPolygon(side[0],side[1],side[2],side[3],curBackground);
			glPopMatrix();
			}
			else{
			glPushMatrix();
				glColor3f(0,153/255.0,0);
				glTranslatef(0,-2.6,0);
				glScalef(16,0.1,16);
				glutSolidCube(1);
			glPopMatrix();
			
		
			glPushMatrix();
				glColor3f(26/255.0, 179/255.0, 255/255.0);
				
				glTranslatef(0,0,-4.6);
				glScalef(20,8,0.1);
				glutSolidCube(1);
				
			glPopMatrix();
			
			glPushMatrix();
				glColor3f(51/255.0, 204/255.0, 255/255.0);
				glTranslatef(-5,0,0);
				glScalef(0.1,8,20);
				glutSolidCube(1);
			glPopMatrix();
			}
			glEnable(GL_LIGHTING);
			for(int i = 0 ; i < lightCount ; i++)
				if(lights[i].isEnabled)
					glEnable(lights[i].light);
			
			glTranslatef(0, modelTranslateY,0);
			glScalef(zoom,zoom,zoom);
			glRotatef(theta,0,1,0);
				drawModel();
			
			for(int i = 0 ; i < lightCount ; i++)
				glDisable(lights[i].light);
			glDisable(GL_LIGHTING);
	glPopMatrix();
	
	glutSwapBuffers();
}

void customerUserContact(){
	glPushMatrix();
		glEnable(GL_SCISSOR_TEST);
			glScissor(viewport[0].x0,viewport[0].y0,viewport[0].x1,viewport[0].y1);
			glClearColor(1,1,1,1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(1,1,1,1);
		glDisable(GL_SCISSOR_TEST);
	glPopMatrix();
	glFlush();
	
	glPushMatrix();
		glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glViewport(viewport[0].x0,viewport[0].y0,viewport[0].x1,viewport[0].y1);
			gluOrtho2D(viewport[0].orthox0 + userScr.scroll,viewport[0].orthoy0+userScr.scroll,viewport[0].orthox1,viewport[0].orthoy1);
		glMatrixMode(GL_MODELVIEW);
			
			userScr.posx = userScr.scroll;
			userScr.draw();
			text[4].pos[0] = userScr.scroll;
			button[1].pos[0] = userScr.scroll;
			text[4].width = viewport[0].x1;
			renderAllText();	
			text[4].drawBox();
						
	glPopMatrix();
	glutSwapBuffers();
}

void customerCarSpec(){
	glPushMatrix();
		glEnable(GL_SCISSOR_TEST);
			glScissor(viewport[1].x0,viewport[1].y0,viewport[1].x1,viewport[1].y1);
			glClearColor(1,1,1,1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDisable(GL_SCISSOR_TEST);
	glPopMatrix();
	glFlush();
	
	
	glPushMatrix();
		glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glViewport(viewport[1].x0,viewport[1].y0,viewport[1].x1,viewport[1].y1);
			gluOrtho2D(viewport[1].orthox0,viewport[1].orthoy0,viewport[1].orthox1 + carScrY.scroll,viewport[1].orthoy1+ carScrY.scroll);
		glMatrixMode(GL_MODELVIEW);
			text[10].pos[1] = carScrY.scroll - 30;
			text[9].pos[1] = carScrY.scroll - 30;
			text[10].drawText();
			text[10].drawBox();
			text[9].drawBox();
			carScrY.draw();
			curCar.draw(viewport[1].x1,viewport[1].y1,1,10,-10);
			
	glPopMatrix();
	glutSwapBuffers();
}

void customerMotionFunc(int x,int y){
	if(userScroll){
		userScr.x += (x - oldX) ;
		
		oldX = x;
		if(userScr.x > userScr.xmin ){
			userScr.x = userScr.xmin;
		}
		if(userScr.x < 0){
			userScr.x = 0;
		}
		userScr.scroll = userScr.x * userScr.ratio;
		customerUserContact();
		
	}
	if(carScrollY){
		
		if(oldX < carScrY.posx)
			carScrY.y += y - oldY ;
		else if(-oldY > (carScrY.posy + carScrY.ymax + carScrY.y) && -oldY < (carScrY.posy + carScrY.y)){
			carScrY.y -= y - oldY;
		}
		else
			carScrollY = false;
			
		oldY = y;
		if(carScrY.y < carScrY.ymin){
			carScrY.y =  carScrY.ymin;
		}
		if(carScrY.y > 0){
			carScrY.y = 0;
		}
		
		carScrY.scroll = carScrY.y * carScrY.ratio;
		customerCarSpec();
	}

	if(grabCar){
		modelTranslateY -= (6.0 * viewport[2].aspecty/(float)viewport[2].y1) * (y - oldY);
		modelTranslateX += (6.0 * viewport[2].aspectx/(float)viewport[2].x1) * (x - oldX);
		oldY = y; oldX = x;
		if(modelTranslateY < -2.5)
			modelTranslateY = -2.5;
		else if(modelTranslateY > 1.5)
			modelTranslateY = 1.5;
		glutPostRedisplay();
	}
	if(zoomCar){
		printf("new zoom = %f \n", zoom + (oldY - y) * 0.001);
		zoom += (oldY-y) * 0.1;
		if(zoom < 0.8)
			zoom = 0.8;
		else if(zoom > 2.5)
			zoom = 2.5;
		oldY = y;
		glutPostRedisplay();
	}
	
}

void customerDisplay(){
	customerUserContact();
	customerCarModel();	
	customerCarSpec();
	
	glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glViewport(0,0,winWidth*2,winHeight*2);
			gluOrtho2D(0,winWidth*2,0,winHeight*2);
	glMatrixMode(GL_MODELVIEW);
		
	glutSwapBuffers();	
}

void customerFormSubmit(){
	FILE *fp = fopen(FILE_CUSTOMER_INFO,"a+");
	
	fprintf(fp,"#NAME:%s #PHONE:%s #EMAIL:%s #MODEL:%s #BRAND:%s \n",editText[0].name,editText[1].name,editText[2].name,curCar.model,curCar.brand);
	fclose(fp);
	editText[0].setValue("");
	editText[1].setValue("");
	editText[2].setValue("");
	button[0].setValue("Submitted");
	button[0].setColor(1,1,1);
	button[0].setBackground(0,.5,0);
	button[0].isEnabled = false;
	customerUserContact();
}

void idle(){
	if(negativeRotate){
		theta -= 0.42;
		theta = theta < 0.0 ? 359.0 : theta;
	}
	else{
		theta += 0.42;
		theta = theta > 360.0 ? theta - 360.0 : theta;
	}
	
	customerCarModel();
}

void customerMenuFunc(int n){
	
	switch(n){
		case 1 :	currentCarIndex+=2;
				if(currentCarIndex >= carCount) currentCarIndex -= carCount;
				curCar.getData(carlist[currentCarIndex ]);
				parseMaterial(carlist[(currentCarIndex)+1]);
				parseObject(carlist[(currentCarIndex)]);
				glutPostRedisplay();
			break;

		case 2 :	currentCarIndex -= 2;
				if(currentCarIndex < 0) currentCarIndex += carCount;
				printf(" Car Count = %d , index %d\n" ,carCount,currentCarIndex);
				curCar.getData(carlist[currentCarIndex]);
				parseMaterial(carlist[(currentCarIndex)+1]);
				parseObject(carlist[(currentCarIndex)]);
				glutPostRedisplay();
			break;
		
		case 3 : 	curBackground++;
				if(curBackground >= maxBackground) curBackground = -1;
				glutPostRedisplay();
				break;
		case 4 : menuInit();
			glutIdleFunc(NULL);
			glutPostRedisplay();
			break;
	}
}

void customerAnimateFunc(int n){
	
	switch(n){
		case 1 : 	negativeRotate = false;
				glutIdleFunc(idle);
				break;
		case 2 : 	negativeRotate = true;
				glutIdleFunc(idle);
				break;
		case 3 : glutIdleFunc(NULL);
				break;
	}
}

void initCustomer(int x,int y){
	float xt = winWidth * 2.0;
	float yt = 190 > winHeight * 0.5 ? 190 : winHeight * 0.5;
	
	if(1221 +180< xt){
		yt -= 30;
		button[0].pos[0] = 1221 + 60;
		button[0].pos[1] = -128;
	}
	else{
		button[0].pos[0] = 1221 - button[0].width;
		button[0].pos[1] = -175;
	}
	
	//user-contact-viewport
	setViewport(&viewport[0],0,0,xt,yt,0,xt,-yt,0);
	if(xt < 1221){
		viewport[0].y1 += 20;
		viewport[0].orthox1 -= 20;
		userScr.init(&viewport[0],1240,0,-yt-20,20);
	}
	else{
		userScr.scroll = 0;
		userScr.isEnabled = false;
	}
	
	//car-detail-viewport
	xt = 400 > winWidth * 0.5 ? 400 : winWidth * 0.5;
	yt = winHeight*2.0 - viewport[0].y1;
	setViewport(&viewport[1],0,viewport[0].y1,xt,yt,0,xt,-yt,0);	
	
	if(CAR_SPEC_LEN  > viewport[1].y1){
		carScrY.init(&viewport[1],-CAR_SPEC_LEN,xt-10,-30,20);
	}
	else{
		carScrY.isEnabled = false;
		carScrY.scroll = 0;
	}
	
	//car-view-viewport
	xt = winWidth * 2.0 - xt;
	yt = winHeight * 2.0 - viewport[0].y1;
	setViewport(&viewport[2],viewport[1].x1,viewport[0].y1,xt,yt,0,xt,-yt,0,-10,10);
	
}

void reshapeCustomer(int w,int h){
	winHeight = h/2;
	winWidth = w/2;
	initCustomer(winWidth * 2,winHeight * 0.5);
}



void mouseCustomer(int key,int state,int x,int y){
	//stop scrolling
	if(key == GLUT_LEFT_BUTTON && state == GLUT_UP){
		grabCar = false;
		userScroll = false;
		carScrollY =false;
	}
	
	if(key == GLUT_MIDDLE_BUTTON && state == GLUT_UP){
		zoomCar = false;
	}
	else if(key == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN){
		zoomCar = true;
		oldY = y;
	}
	//Viewport[0] : user-contact mouse operations
	int yt = (winHeight * 2 - viewport[0].y1) - y ;
	int xt = x + userScr.scroll;
	if(key == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		for(int i=eStart ; i<eCount;i++){
			if(editText[i].onSelect(xt,yt,func)) break;
		}
		
		button[0].onClick(xt,yt);
	}
	
	//User-Content-Scroll bar
	if(key == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		if(x < userScr.xmax + userScr.x && x > userScr.x && yt < 0){
			userScroll = true;
			oldX = x;
		}
	}
	
	
	yt = -y;
	
	if(key == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		if(y < viewport[1].y1 && x < viewport[1].x1){
			carScrollY = true;
			oldY = y;
			oldX = x;
		}
		
	}
	
	//viewport[2] : Car Model mouse operations
	yt = winHeight * 2.0 - y;
	
	if(key == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x > viewport[2].x0 && yt > viewport[2].y0){
		grabCar = true;
		oldY = y; oldX = x;
		
	}
	

}

void enableLight(int n)
{
	if(lights[n].isEnabled)
		lights[n].isEnabled = false;
	else
		lights[n].isEnabled = true;
	customerCarModel();
}


void renderCustomer(){
	initTexture("./docs/index2.jpg");
	initTexture("./docs/index3.jpg",1);
	maxBackground++;
	//initTexture("index4.jpg",2);
	//maxBackground++;
	//initTexture("3DCube.jpg",3);
	glClearColor(1,1,1,1);
{
	eCount = tCount = bCount =0;
	
	float tempPosY = -130,tempPosX = 10;
	
	text[0].init(tempPosX,tempPosY,"Name :  ",0,40);
	text[1].init(tempPosX,tempPosY,"Phone :  ",0,40);
	text[2].init(tempPosX,tempPosY,"Email :  ",0,40);
	text[3].init(tempPosX,-80,"Enter Contact Details : ",300,40);
	text[3].borderType = NO_BORDER;
	tCount = 4;
			
	float w = 0;
	
	w = 60;
	
	text[0].pos[0] = tempPosX ;
	text[0].borderType = NO_BORDER;
	
	tempPosX += text[0].width;				
	editText[0].init(tempPosX,tempPosY+5,"",280,30);
	editText[0].vp = &viewport[0];
	eCount++;
		
	tempPosX += editText[0].width + w;
	
	text[1].pos[0] = tempPosX;
	text[1].borderType = NO_BORDER;
	
	tempPosX += text[1].width;
	editText[1].init(tempPosX,tempPosY+5,"",280,30);
	editText[1].vp = &viewport[0];
	eCount++;
	
	tempPosX += editText[1].width+w;
	
	text[2].pos[0] = tempPosX ;
	text[2].borderType = NO_BORDER;	
	
	tempPosX += text[2].width;
	editText[2].init(tempPosX,tempPosY+5,"",330,30);
	editText[2].vp = &viewport[0];
	eCount++;	
	
	tempPosX += editText[2].width;
	
	printf("x = %f\n",tempPosX);
	
	button[0].init(0,0,"Submit",100,30);
	button[0].setPadding(5,8);
	button[0].setColor(1,1,1);
	button[0].borderType = NO_BORDER;
	button[0].setBackground(COLOR_BLUE_BUTTON);
	button[0].setOnClick(customerFormSubmit);
	bCount++;
	
	button[1].init(0,-31," Form ",130,26);
	button[1].setPadding(0,0);
	button[1].height = 28;
	button[1].setTextStyle(TEXT_CENTER, GLUT_BITMAP_HELVETICA_18, 10,1);
	button[1].borderType = NO_BORDER;
	button[1].setColor(1,1,1);
	button[1].setBackground(COLOR_TASKBAR);
	button[1].isSelected  = true;
	bCount++;	
		
	initCustomer(winWidth * 2,winHeight * 0.5);
	
	text[4].init(0,-30,"",viewport[0].x1,30);
	text[4].height = 30;
	text[4].setBackground(COLOR_TASKBAR);
	tCount++;
	
	text[10].init(0,-32,"Info",130,28);
	text[10].setPadding(0,10);
	text[10].setTextStyle(TEXT_CENTER,GLUT_BITMAP_HELVETICA_18,18);
	text[10].height = 26;
	text[10].setColor(1,1,1);
	text[10].setBackground(COLOR_TASKBAR);
	text[10].borderType = NO_BORDER;
			
	text[9].init(0,-30,"",1000,30);
	text[9].setBackground(COLOR_TASKBAR);
	
}
	//set current car
	printf("carcount = %d",carCount);
	currentCarIndex = 0;
	curCar.getData(carlist[currentCarIndex]);
	
	parseMaterial(carlist[(currentCarIndex)+1]);
	parseObject(carlist[(currentCarIndex)]);

	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	
	GLfloat light_intensity[]= {0.8,0.8,0.8,1.0};
	GLfloat light_position[]={-3.0,4.0,3.0,0.0};

	lightCount =0 ;
	lights[lightCount].light = GL_LIGHT0;
	lights[lightCount].isEnabled = true;
	lightCount++;
	
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,light_intensity);
	glLightfv(GL_LIGHT0,GL_SPECULAR,light_intensity);
	
	lights[lightCount].light = GL_LIGHT1;
	lights[lightCount].isEnabled = true;
	lightCount++;
	
	light_position[0] = 3;
	glLightfv(GL_LIGHT1,GL_POSITION,light_position);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,light_intensity);
	glLightfv(GL_LIGHT1,GL_SPECULAR,light_intensity);
	
	lights[lightCount].light = GL_LIGHT2;
	lights[lightCount].isEnabled = false;
	lightCount++;
	
	light_position[1] = -1;
	glLightfv(GL_LIGHT2,GL_POSITION,light_position);
	glLightfv(GL_LIGHT2,GL_DIFFUSE,light_intensity);
	glLightfv(GL_LIGHT2,GL_SPECULAR,light_intensity);
	
	lights[lightCount].light = GL_LIGHT3;
	lights[lightCount].isEnabled = false;
	lightCount++;
	
	light_position[0] = -3;
	glLightfv(GL_LIGHT3,GL_POSITION,light_position);
	glLightfv(GL_LIGHT3,GL_DIFFUSE,light_intensity);
	glLightfv(GL_LIGHT3,GL_SPECULAR,light_intensity);
	
	//menu
	int light = glutCreateMenu(enableLight);
	glutAddMenuEntry("LIGHT 0",0);
	glutAddMenuEntry("LIGHT 1",1);
	glutAddMenuEntry("LIGHT 2",2);
	glutAddMenuEntry("LIGHT 3",3);
	
	int animate = glutCreateMenu(customerAnimateFunc);
	glutAddMenuEntry(" Rotate AntiClockWise ",1);
	glutAddMenuEntry(" Rotate ClockWise " ,2);
	glutAddMenuEntry(" Stop Rotation ",3);
	int main = glutCreateMenu(customerMenuFunc);
	
	glutAddMenuEntry(" Next ",1);
	glutAddMenuEntry(" Previous ",2);
	glutAddMenuEntry(" Next BackGround ",3);
	glutAddSubMenu(" Animate ",animate);
	glutAddSubMenu(" Light " ,light);
	glutAddMenuEntry(" Back ",4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	
	glutMouseFunc(mouseCustomer);
	glutMotionFunc(customerMotionFunc);
	glutKeyboardFunc(NULL);
	glutReshapeFunc(reshapeCustomer);
	glutDisplayFunc(customerDisplay);
	glutPostRedisplay();
}

