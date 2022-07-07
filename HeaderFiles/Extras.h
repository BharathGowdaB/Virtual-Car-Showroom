const char alpha[] = "qwertyuiopasdfghjklzxcvbnm";

class scrollBarX{
	public : struct Viewport *vp;
		float x,scroll,xmin,xmax,ratio;
		float posx,posy;
	        
		int scrollWidth = 10;
		bool isEnabled = false;
		
		void init(Viewport *viewport,int maxWidth,float xp,float yp,int sWidth = 10){
			isEnabled = true;
			vp = viewport;
			x = 0;
			scroll = 0;
			xmax = vp->x1 * vp->x1 / maxWidth;
			xmin = vp->x1 - xmax;
			ratio = (maxWidth - vp->x1)/xmin;
			posx = xp;
			posy = yp;
			scrollWidth = sWidth;
		}
		
		void draw(){
			if(isEnabled){
			
			glPushMatrix();
				glBegin(GL_LINE_LOOP);
					glColor3f(0,0,0);
					glVertex2f(posx+x+scroll+5,posy-2);
					glVertex2f(posx+x+scroll+5,posy+scrollWidth+2);
					glVertex2f(posx+xmax-5 +scroll+ x,posy+scrollWidth+2);
					glVertex2f(posx+xmax-5 + scroll+x,posy);
				glEnd();
			
				glBegin(GL_POLYGON);
					glColor3f(.5,.5,.5);
					glVertex2f(posx+x+scroll+5,posy-2);
					glVertex2f(posx+x+scroll+5,posy+scrollWidth+2);
					glVertex2f(posx+xmax-5 +scroll+ x,posy+scrollWidth+2);
					glVertex2f(posx+xmax-5 + scroll+x,posy);
				glEnd();
				glBegin(GL_LINE_LOOP);
					glColor3f(0,0,0);
					glVertex2f(posx,posy);
					glVertex2f(posx,posy+scrollWidth);
					glVertex2f(posx + vp->x1 ,posy+scrollWidth);
					glVertex2f(posx + vp->x1 ,posy);
				glEnd();
				glBegin(GL_POLYGON);
					glColor3f(COLOR_LIGHT_GREY);
					glVertex2f(posx,posy);
					glVertex2f(posx,posy+scrollWidth);
					glVertex2f(posx + vp->x1 ,posy+scrollWidth);
					glVertex2f(posx + vp->x1 ,posy);
				glEnd();
				
			glPopMatrix();
			}
		}
};

class scrollBarY{
	public : struct Viewport *vp;
		float y,scroll,ymin,ymax,ratio;
		float posx,posy;
	        
		int scrollWidth = 10;
		bool isEnabled = false;
		
		void init(Viewport *viewport,int maxHeight,float xp,float yp,int sWidth = 10){
			isEnabled = true;
			vp = viewport;
			y = 0;
			scroll = 0;
			ymax = (vp->y1 + yp )* (vp->y1 + yp) / maxHeight;
			ymin = vp->y1 + yp + ymax;
			ymin *= -1.0;
			ratio = (maxHeight + vp->y1)/ymin;
			posx = xp;
			posy = yp;
			scrollWidth = sWidth;
		}
		
		void draw(){
			if(isEnabled){
			
			glPushMatrix();
				glBegin(GL_LINE_LOOP);
					glColor3f(0,0,0);
					glVertex2f(posx - 2 ,posy +  scroll+ y- 5);
					glVertex2f(posx - 2,posy + ( scroll + ymax + y - 5));
					glVertex2f(posx+scrollWidth+2,posy + ( scroll + ymax + y - 5));
					glVertex2f(posx+scrollWidth+2,posy +  scroll+ y - 5);
				glEnd();
			
				glBegin(GL_POLYGON);
					glColor3f(.5,.5,.5);
					glVertex2f(posx - 2 ,posy +  scroll + y- 5);
					glVertex2f(posx - 2,posy + ( scroll + ymax + y - 5));
					glVertex2f(posx+scrollWidth+2,posy + ( scroll + ymax + y - 5));
					glVertex2f(posx+scrollWidth+2,posy +  scroll+ y - 5);
				glEnd();
				glBegin(GL_LINE_LOOP);
					glColor3f(0,0,0);
					glVertex2f(posx,posy);
					glVertex2f(posx,-vp->y1 + scroll);
					glVertex2f(posx + scrollWidth ,-vp->y1 + scroll);
					glVertex2f(posx + scrollWidth ,posy);
				glEnd();
				glBegin(GL_POLYGON);
					glColor3f(COLOR_LIGHT_GREY);
					glVertex2f(posx,posy);
					glVertex2f(posx,-vp->y1 + scroll);
					glVertex2f(posx + scrollWidth ,-vp->y1 + scroll);
					glVertex2f(posx + scrollWidth ,posy);
				glEnd();
				
			glPopMatrix();
			}
		}
};



class carDetail {
	public :
		char model[20],brand[40];
		char price[30];
		char displacement[40],power[20],torque[20];
		char fuelType[10],fuelCapacity[15];
		char mileage[15] ;
		char transmissionType[10];
		char topSpeed[15];
		int safetyRate;
		
		void getData(const char filename[]){
			FILE *fp = fopen(filename,"r");
			
			fscanf(fp,"MODEL:%[^\n]\nBRAND:%[^\n]\nPRICE:%[^\n]\nDISPLACEMENT:%[^\n]\nPOWER:%[^\n]\nTORQUE:%[^\n]\nFUEL-TYPE:%[^\n]\nFUEL-CAPACITY:%[^\n]\nMILEAGE:%[^\n]\nTRANSMISSION-TYPE:%[^\n]\nTOP-SPEED:%[^\n]\nSAFETY-RATE:%d\n",model,brand,price,displacement,power,torque,fuelType,fuelCapacity,mileage,transmissionType,topSpeed,&safetyRate);
			fclose(fp);
		}
		
		float draw(int x,int y,float ratio,int initPadx=0,int initPady=0){
			int curHei = 0;
			Text drawer;
			const char *p[24] = { "Model : ",model,"Brand : ",brand,"Price : ",price,"Displacement : ",displacement,"Max Power : ",power,"Max Torque : ",torque,"Fuel Type : ",fuelType,"Fuel Tank Capacity : ",fuelCapacity,"Mileage : ",mileage,"Transmission Type : ",transmissionType,"Top Speed : ",topSpeed };
			
			p[22] = "Safety Rate : ";
			p[23] = "";
			
			int padx = 5,pady = 2;
			
			initPady = -30;
			x -= initPadx*2;

			drawer.init(initPadx,initPady,"");
			drawer.borderType = NO_BORDER;
			drawer.setPadding(10,10);
			
			for(int i= 0 ;i < 24 ;i += 2) {
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
				drawer.setBackground(COLOR_LIGHT_GREY);
				drawer.borderType = NO_BORDER;
				drawer.drawBox();
				
				drawer.pos[1] -= 6;
	
			}
			ratingStars(drawer.pos[0]+ x - 240,drawer.pos[1]+10,x/(float)y,safetyRate);
			return (-1.0 * drawer.pos[1] + 10) ;
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
