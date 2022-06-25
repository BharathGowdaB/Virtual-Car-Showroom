
void customerUserContact();
static void (*func)() = customerUserContact;

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
			glOrtho(viewport[2].orthox0,viewport[2].orthoy0,viewport[2].orthox1,viewport[2].orthoy1,viewport[2].orthox2,viewport[2].orthoy2);
		glMatrixMode(GL_MODELVIEW);
	
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
			gluOrtho2D(viewport[0].orthox0,viewport[0].orthoy0,viewport[0].orthox1,viewport[0].orthoy1);
		glMatrixMode(GL_MODELVIEW);
		
			text[4].width = viewport[0].x1;
			if(button[1].isSelected){
				button[1].setColor(0,0,0);
				button[1].setBackground(1,1,1);

				button[2].setColor(1,1,1);
				button[2].setBackground(COLOR_TASKBAR);
				
				renderAllText();	
			}
			else{
				button[1].setColor(1,1,1);
				button[1].setBackground(COLOR_TASKBAR);
			
				button[2].setColor(0,0,0);
				button[2].setBackground(1,1,1);
				
				for(int i=1 ;i < 3 ;i++){
					button[i].drawText();
					button[i].drawBox();
				}
				text[4].drawBox();
				
			}			
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
			gluOrtho2D(viewport[1].orthox0,viewport[1].orthoy0,viewport[1].orthox1,viewport[1].orthoy1);
		glMatrixMode(GL_MODELVIEW);
			curCar.draw(viewport[1].x1,viewport[1].y1,(viewport[1].x1)/(winWidth*0.5),10,-10);
	glPopMatrix();
	
	glutSwapBuffers();
}

void selectButton1(){
	button[1].isSelected = true;
	button[2].isSelected = false;
	bStart = 0;
	eStart = 0;
	customerUserContact();
}

void selectButton2(){
	button[2].isSelected = true;
	button[1].isSelected = false;
	bStart = 1;
	eStart = 4;
	customerUserContact();
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
	//printf("submit called\n");
	FILE *fp = fopen("customerDetail.txt","a+");
	
	fprintf(fp,"Name:%s,Phone:%s,Email:%s\n",editText[0].name,editText[1].name,editText[2].name);
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

void customerMenufunc(int n){
	
	switch(n){
		case 4 : exit(0);
	}
}


void initCustomer(int x,int y){
	float xt = winWidth * 2.0;
	float yt = 190;
	
	if(1221 +180< xt){
		yt = 160;
		button[0].pos[0] = 1221 + 60;
		button[0].pos[1] = -128;
	}
	else{
		button[0].pos[0] = 1221 - button[0].width;
		button[0].pos[1] = -175;
	}
	
	//user-contact-viewport
	setViewport(&viewport[0],0,0,xt,yt,0,xt,-yt,0);
	
	//car-detail-viewport
	xt = winWidth * 0.5;
	yt = winHeight*2.0 - viewport[0].y1;
	setViewport(&viewport[1],0,viewport[0].y1,xt,yt,0,xt,-yt,0);	
	
	//car-view-viewport
	xt = winWidth * 1.5;
	yt = winHeight * 2.0 - viewport[0].y1;
	setViewport(&viewport[2],viewport[1].x1,viewport[0].y1,xt,yt,0,xt,-yt,0,-10,10);	
}

void reshapeCustomer(int w,int h){
	winHeight = h/2;
	winWidth = w/2;
	initCustomer(winWidth * 2,winHeight * 0.5);
}


void mouseCustomer(int key,int state,int x,int y){
	int yt = (winHeight * 2 - viewport[0].y1) - y ;
	if(key == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		for(int i=eStart ; i<eCount;i++){
			if(editText[i].onSelect(x,yt,func)) break;
		}
		for(int i=bStart ; i<bCount;i++){
			if(button[i].onClick(x,yt))break;
		}
	}
	
	yt = winHeight * 2.0 - y;

	if(x > viewport[2].x0 && yt > viewport[2].y0){
		printf("Menu attached\n");
		glutAttachMenu(GLUT_RIGHT_BUTTON);			
	}
	else{
		printf("Menu deattached\n");
		glutDetachMenu(GLUT_RIGHT_BUTTON);
	}	
}

void renderCustomer(){
	glClearColor(1,1,1,1);
	
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
	button[1].isSelected  = true;
	button[1].setOnClick(selectButton1);
	bCount++;
	
	button[2].init(130,-31," Accessories ",130,26);
	button[2].setPadding(0,0);
	button[2].height = 28;
	button[2].setTextStyle(TEXT_CENTER, GLUT_BITMAP_HELVETICA_18, 10,1);
	button[2].borderType = NO_BORDER;
	button[2].setOnClick(selectButton2);
	bCount++;
			
	initCustomer(winWidth * 2,winHeight * 0.5);
	
	text[4].init(0,-30,"",viewport[0].x1,30);
	text[4].height = 30;
	text[4].setBackground(COLOR_TASKBAR);
	tCount++;
	
	//set current car
	curCar.getData("CAR001.dtl");
	
	//menu
	glutCreateMenu(customerMenufunc);
	//glutCreateMenu(menufunc);
	glutAddMenuEntry("Next",1);
	glutAddMenuEntry("Previous",2);
	glutAddMenuEntry("Animate",3);
	glutAddMenuEntry("Exit",4);
	//glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	glutMouseFunc(mouseCustomer);
	glutKeyboardFunc(NULL);
	glutReshapeFunc(reshapeCustomer);
	glutDisplayFunc(customerDisplay);
	glutPostRedisplay();
}

