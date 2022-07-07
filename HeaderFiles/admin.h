
class customerNode {
	public : customerNode *previous = NULL ,*next = NULL;
		char name[50],phone[15],email[101],model[20],brand[40];
};

static customerNode node[100];
static scrollBarY scrollY;
static bool scrolling = false;
static  customerNode head;
static int custCount = 0,svalue = 0;

void adminDisplay(){
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glViewport(0,0,winWidth*2,winHeight*2);
			gluOrtho2D(0,winWidth*2,-winHeight*2 + scrollY.scroll,0 + scrollY.scroll);
		
	glMatrixMode(GL_MODELVIEW);
	
	glPushMatrix();
	Text  header;
	
	int w = winWidth * 2 / 5 - 64 , h = -50  ;
	
	header.init(0,scrollY.scroll - 50,"NAME", w ,50);
	header.setTextStyle(TEXT_CENTER,GLUT_BITMAP_HELVETICA_18,18);
	header.setColor(1,1,1);
	header.setBorderColor(1,1,1);
	header.setBackground(COLOR_TASKBAR);
	header.drawText();
	header.drawBox();
	
	header.setValue("PHONE");
	header.pos[0] = w ;
	header.setTextStyle(TEXT_CENTER,GLUT_BITMAP_HELVETICA_18,18);
	header.drawText();
	header.drawBox();
	
	header.setValue("EMAIL");
	header.width = w + 120;
	header.pos[0] = w * 2 ;
	header.setTextStyle(TEXT_CENTER,GLUT_BITMAP_HELVETICA_18,18);
	header.drawText();
	header.drawBox();
	
	header.setValue("MODEL");
	header.width = w;
	header.pos[0] = w * 3 + 120;
	header.setTextStyle(TEXT_CENTER,GLUT_BITMAP_HELVETICA_18,18);
	header.drawText();
	header.drawBox();
	
	header.setValue("BRAND");
	header.width = w+60;
	header.pos[0] = w * 4 + 120;
	header.setTextStyle(TEXT_CENTER,GLUT_BITMAP_HELVETICA_18,18);
	header.drawText();
	header.drawBox();
	
	header.setValue("Action");
	header.width = 140;
	header.pos[0] = w * 5 + 180;
	header.setTextStyle(TEXT_CENTER,GLUT_BITMAP_HELVETICA_18,18);
	header.drawText();
	header.drawBox();
	
	text[0].init(0,h,"", w ,50);
	text[0].setPadding(20,0);
	text[0].setBorderColor(1,1,1);
	
	text[1].init(w,h,"",w ,50);
	text[1].setPadding(20,0);
	text[1].setBorderColor(1,1,1);
	
	text[2].init(w * 2,h,"",w + 120 ,50);
	text[2].setPadding(20,0);
	text[2].setBorderColor(1,1,1);
	
	text[3].init(w * 3 + 120,h,"",w,50);
	text[3].setPadding(20,0);
	text[3].setBorderColor(1,1,1);
	
	text[4].init(w * 4 + 120,h,"",w+60,50);
	text[4].setPadding(20,0);
	text[4].setBorderColor(1,1,1);
	
	button[0].init(w * 5 + 180,h,"Remove",140,50);
	button[0].setColor(1,0,0);
	button[0].setBorderColor(1,1,1);
	
	scrollY.draw();
	
	customerNode *cur = head.next;
	bool odd = true;
	while(cur != NULL){
		text[0].setValue(cur->name);
		text[1].setValue(cur->phone);
		text[2].setValue(cur->email);
		text[3].setValue(cur->model);
		text[4].setValue(cur->brand);
		
		cur = cur->next;
		text[0].pos[1] -= 50;text[1].pos[1] -= 50;text[2].pos[1] -= 50;text[3].pos[1] -= 50;text[4].pos[1] -= 50;button[0].pos[1] -= 50;
		if(odd){
			odd= false;
			text[0].setBackground(1,1,1);
			text[1].setBackground(1,1,1);
			text[2].setBackground(1,1,1);
			text[3].setBackground(1,1,1);
			text[4].setBackground(1,1,1);
			button[0].setBackground(1,1,1);
		}
		else{
			odd= true;
			
			text[0].setBackground(COLOR_LIGHT_GREY);
			text[1].setBackground(COLOR_LIGHT_GREY);
			text[2].setBackground(COLOR_LIGHT_GREY);
			text[3].setBackground(COLOR_LIGHT_GREY);
			text[4].setBackground(COLOR_LIGHT_GREY);
			button[0].setBackground(COLOR_LIGHT_GREY);
		}
		
		text[0].drawText(); text[1].drawText(); text[2].drawText(); text[3].drawText(); text[4].drawText(); button[0].drawText();
		text[0].drawBox();text[1].drawBox();text[2].drawBox();text[3].drawBox();text[4].drawBox();button[0].drawBox();
	}
	
	scrollY.draw();
	glPopMatrix();
	
	glutSwapBuffers();
}

void mouseAdmin(int key,int state,int x,int y){
	if(key == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x > winWidth * 2.0 - 110 && x < winWidth * 2.0 - 40 ){
		y -= scrollY.scroll;
		
		int ch = y/50 - 1;
		if(ch < custCount && ch >= 0){
		customerNode *cur = head.next,*prev = &head;
		for(int i=0 ;i <ch ; i++){
			cur = cur->next;
		}
		prev = cur->previous;
		prev->next = cur->next;
		if(cur->next != NULL)
			cur->next->previous = prev;
		custCount--;
		glutPostRedisplay();
		}
	}

	if(key == GLUT_LEFT_BUTTON && state == GLUT_UP){
		scrolling = false;
	}
	if(key == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		scrolling = true;
		oldY = y;
		oldX = x;
	}
}

void adminMotionFunc(int x,int y){
	if(scrolling){
		if(oldX < scrollY.posx)
			scrollY.y += y - oldY ;
		else if(-oldY > scrollY.posy + scrollY.ymax + scrollY.y && -oldY < scrollY.posy +  scrollY.y ){
			scrollY.y -= y - oldY;
		}
		else
			carScrollY = false;
			
		oldY = y;
		if(scrollY.y < scrollY.ymin){
			scrollY.y =  scrollY.ymin;
		}
		if(scrollY.y > 0){
			scrollY.y = 0;
		}
	
		scrollY.scroll = scrollY.y * scrollY.ratio;
		glutPostRedisplay();
	}
}

void adminReshape(int w,int h){
	winHeight = h/2;
	winWidth = w/2;
	setViewport(&viewport[0],0,0,w,h,0,w,-h,0);
	if(  (custCount + 1) * 50 > h)
	{	
		scrollY.init(&viewport[0],-custCount * 50.0 - 50,w-15,-50,20);
		glutMotionFunc(adminMotionFunc);
	}
	else{
		scrollY.isEnabled = false;
		scrollY.scroll = 0;
		glutMotionFunc(NULL);
	}
}


void loadData(){
	
	
	FILE *fp = fopen(FILE_CUSTOMER_INFO,"r+");
	head.next = &node[0];
	node[0].previous = &head;
	customerNode *cur = head.next;
	custCount = 0;
	int i = 1;
	while(i < 100 && fscanf(fp,"#NAME:%[^#]#PHONE:%[^#]#EMAIL:%[^#]#MODEL:%[^#]#BRAND:%[^\n]\n",cur->name,cur->phone,cur->email,cur->model,cur->brand) != EOF){
		printf("%s\n",cur->name);
		cur->next = &node[i];
		node[i].previous = cur;
		cur = cur->next;
		i++;
	 }
	 cur->previous->next = NULL;
	custCount = i-1;
	
	printf("custCount = %d\n",custCount);
}


void adminMenuFunc(int n){
	switch(n){
		case 0 : loadData();
			glutPostRedisplay();
			break;
			
		case 1 : { customerNode *cur = head.next;
			FILE *fp = fopen(FILE_CUSTOMER_INFO,"w");
			while(cur != NULL){
				fprintf(fp,"#NAME:%s#PHONE:%s#EMAIL:%s#MODEL:%s#BRAND:%s\n", cur->name,cur->phone,cur->email,cur->model,cur->brand);
				cur = cur->next;
			}
			fclose(fp);
			}
			break;
			
		case 2 : menuInit();
			glutPostRedisplay();
			break;
		
	}
}


void renderAdmin(){
	
	loadData();
	
	setViewport(&viewport[0],0,0,winWidth*2.0,winHeight*2,0,winWidth*2,-winHeight*2,0);
	if( (custCount + 1 ) * 50 > winHeight*2)
	{	
		scrollY.init(&viewport[0],-custCount * 50.0 - 50,winWidth*2-15,-50,20);
		glutMotionFunc(adminMotionFunc);
	}
	else{
		scrollY.isEnabled = false;
		scrollY.scroll = 0;
		glutMotionFunc(NULL);
	}
	
	glutCreateMenu(adminMenuFunc);
	glutAddMenuEntry("Reload",0);
	glutAddMenuEntry("Save",1);
	glutAddMenuEntry("Back",2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	glutReshapeFunc(adminReshape);
	glutMouseFunc(mouseAdmin);
	glutDisplayFunc(adminDisplay);
	glutPostRedisplay();
	
}
