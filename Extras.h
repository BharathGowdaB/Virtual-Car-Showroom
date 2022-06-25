
const char alpha[] = "qwertyuiopasdfghjklzxcvbnm";

class carDetail {
	public :
		char model[10],brand[50];
		char price[30];
		char engineSpec[20];
		char fuelType[10];
		float mileage ;
		short autoGear;
		short safetyRate;
		
		void getData(const char filename[]){
			FILE *fp = fopen(filename,"r");
			
			fscanf(fp,"MODEL:%[^\n]\nBRAND:%[^\n]\nPRICE:%[^\n]\nENGINE:%[^\n]\nFUEL:%s\nMILEAGE:%f\nAUTOGEAR:%hx\nRATE:%hx",model,brand,price,engineSpec,fuelType,&mileage,&autoGear,&safetyRate);
			
		}
		
		bool draw(int x,int y,float ratio,int initPadx=0,int initPady=0){
			int curHei = 0;
			Text drawer;
			const char *p[14] = { "Model : ",model,"Brand : ",brand,"Price : ",price,"Engine : ",engineSpec,"Gear Type : "};
			
			p[9] = autoGear ? "Auto" : "Manual";
			p[10] = "Mileage : ";
			char temp[18];  //has to change
			sprintf(temp,"%.2f kmpl",mileage);
			p[11] = temp;	
			p[12] = "Rating : ";
			p[13] = "";
			
			int padx = 5,pady = 2;
			
			
			drawer.init(0,-32,"Info",130,28);
			drawer.setPadding(0,10);
			drawer.setTextStyle(TEXT_CENTER,GLUT_BITMAP_HELVETICA_18,18);
			drawer.height = 26;
			drawer.setBackground(1,1,1);
			drawer.setColor(COLOR_TASKBAR);
			drawer.borderType = NO_BORDER;
			drawer.drawText();
			drawer.drawBox();
			
			drawer.init(0,-30,"",x+2,30);
			drawer.setBackground(COLOR_TASKBAR);
			drawer.drawBox();
			
			initPady = -30;
			x -= +initPadx*2;

			drawer.init(initPadx,initPady,"");
			drawer.borderType = NO_BORDER;
			drawer.setPadding(10,10);
			
			for(int i= 0 ;i< 14 ;i += 2) {
				drawer.width = x;
				drawer.setValue(p[i]);
				drawer.setColor(0,0,0);
				drawer.setTextStyle(TEXT_LEFT,GLUT_BITMAP_HELVETICA_18,18,ratio);
				drawer.pos[1] -= drawer.height + pady;
				drawer.drawText();
				
				drawer.width = x;
				drawer.setValue(p[i+1]);
				drawer.setTextStyle(TEXT_RIGHT,GLUT_BITMAP_HELVETICA_18,18,ratio);
				drawer.pos[1] -= drawer.height + pady;
				drawer.drawText();
				drawer.setBackground(218/255.0, 223/255.0, 232/255.0);
				drawer.borderType = NO_BORDER;
				drawer.drawBox();
				
				drawer.pos[1] -= 6;
	
			}
			
			ratingStars(drawer.pos[0]+ x - 240,drawer.pos[1]+10,x/(float)y,safetyRate);
			
			if(drawer.pos[1] + 6 > y*-1 )
				return false;
			return true; // scroll required
		}
		
		void ratingStars(float posx,float posy,float aspect,int rate = 0){
			
			for(int i = 0 ; i < 5 ; i++){
				posx += 40;
			glPushMatrix();
				
				glTranslatef(posx,posy,1);
				glScalef(30 ,30,1);
				if(i < rate)
					glColor3f(0.75,0.75,0);
				else
					glColor3f(1,1,1);
				glBegin(GL_LINE_LOOP);
					glVertex2f(0.2,0.1);
					glVertex2f(0.5,1);
					glVertex2f(0.5,0.35);
				glEnd();
				glBegin(GL_LINE_LOOP);
					glVertex2f(0.8,0.1);
					glVertex2f(0.5,0.35);
					glVertex2f(0.5,1);
				glEnd();
				glBegin(GL_LINE_LOOP);
					glVertex2f(0,0.7);
					glVertex2f(1,0.7);
					glVertex2f(0.5,0.35);
				glEnd();
				
				glBegin(GL_POLYGON);
					glVertex2f(0.2,0.1);
					glVertex2f(0.5,1);
					glVertex2f(0.5,0.35);
				glEnd();
				
				if(i < rate)
					glColor3f(0.8,0.8,0.2);
				else
					glColor3f(1,1,1);
				glBegin(GL_POLYGON);
					glVertex2f(0.8,0.1);
					glVertex2f(0.5,0.35);
					glVertex2f(0.5,1);
				glEnd();
				glBegin(GL_POLYGON);
					glVertex2f(0,0.7);
					glVertex2f(1,0.7);
					glVertex2f(0.5,0.35);
				glEnd();
				glFlush();
			glPopMatrix();
			}
			
		}
		
		
		
};
