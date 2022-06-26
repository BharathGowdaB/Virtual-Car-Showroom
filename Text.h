#include<stdlib.h>
#include<stdio.h>
#include<GL/glut.h>

class Text;
class Button;
class EditText;

struct Viewport{
	float x0,y0,x1,y1;
	float orthox0,orthoy0,orthox1,orthoy1,orthox2,orthoy2;
	float scrollX,scrollY;
	float aspectx,aspecty;
};


static EditText *curEditText;
static void (*callback)();
static float curWinWidth = 0 ,curWinHeight = 0;

class Text {
	public : float pos[2] = {0,0};
		int pad[2] = {0,0};
		int width = 1,height = 1;
		
		short borderType = LINE;
		float bgColor[3] = {1,1,1};
		float borderColor[3] = {0,0,0}; 
		
		unsigned char name[MAX_CHARACTERS+1] = "Text";
		float color[3] = {0,0,0};
		int textPos[2] = {0,0};
		int textLen = 0,textHei = 18;
		short textAlign = TEXT_LEFT;
		void *textstyle = GLUT_BITMAP_HELVETICA_18;
		
		void init(const char *names){
			init(0,0,names);	
		}
			
		void init(float p1,float p2,int w=0,int h=0){
			width = w;
			height = h;
			pos[0] = p1;
			pos[1] = p2;
			textAlign = TEXT_LEFT;
			textstyle = GLUT_BITMAP_HELVETICA_18;
			textHei = 18;
			borderType = LINE;
			setColor(0,0,0);
			setBackground(1,1,1);
			setPadding(0,0);
		}
		
		void init(float p1,float p2,const char *names,int w=0,int h=0){
			int i = 0;
			while(names[i] != '\0'){
				name[i++] = names[i];	
			}
			name[i] = '\0';
			init(p1,p2,w,h);
		}
		
		void setTextStyle(short align,void *textStyle,short textHeight = 18,float ratio = 1){
			textAlign = align;
			setTextStyle(textStyle,textHeight,ratio);
		}
		
		void setTextStyle(void *textStyle,short textHeight = 18,float ratio = 1){
			textLen = glutBitmapLength(textStyle,name) * ratio;
			textHei = textHeight;
			textstyle = textStyle;
			
			if(textLen + pad[0] * 2 > width){
				width = textLen + pad[0] * 2 ;
			}
			if(textHei + pad[1] * 2 > height){
				height = textHei + pad[1] * 2 ;
			}
			
			if(textAlign == TEXT_CENTER){
				textPos[0] = (int)(width/2 - textLen/2);	
			}
			else if(textAlign == TEXT_RIGHT){
				if(width - textLen - pad[0] > pad[0])
					textPos[0] = width - textLen - pad[0];
				else
					textPos[0] = -100000;
			}
			else{
				textPos[0] = pad[0];
			}
			textPos[1] = (int)(height - textHei)/2;
		}
		
		void setTextAlign(short align){
			textAlign = align;
			setTextStyle(textstyle,textHei);
		}
		
		void setBackground(float r,float g,float b){
			bgColor[0] = r;
			bgColor[1] = g;
			bgColor[2] = b;
		}
		
		void setBorderColor(float r,float g,float b){
			borderColor[0] = r;
			borderColor[1] = g;
			borderColor[2] = b;
		}
		
		void setColor(float r,float g,float b){
			color[0]=r;
			color[1] = g;
			color[2] = b;
		}
		
		void setPadding(int x,int y)
		{
			pad[0] = x;
			pad[1] = y;
			setTextStyle(textstyle,textHei);
		}
		
		void setValue(const char *names){
			int i = 0;
			while(names[i] != '\0'){
				name[i++] = names[i];	
			}
			name[i] = '\0';
			setTextStyle(textstyle,textHei);
		}
		
		void drawText(int start=0){
			int i = 0;
			if(start < 0) start = 0;
			glColor3fv(color);
			glRasterPos3i(pos[0] + textPos[0],pos[1]+ textPos[1],0);
			for(i=start;name[i] != '\0' ; i++)
				glutBitmapCharacter(textstyle,name[i]);
				
			if(borderType)
				drawBorder(borderColor);
			glFlush();
			
		}
		
		void drawText(float sx,float sy){
			int i = 0;
			glColor3fv(color);
			glPushMatrix();
			glTranslatef(pos[0] + textPos[0],pos[1] + textPos[1],0);
			
			glScalef(sx,sy,1);
			for(i=0;name[i] != '\0' ; i++)
				glutStrokeCharacter(GLUT_STROKE_ROMAN,name[i]);
			
			if(borderType)
				drawBorder(borderColor);
			
			glPopMatrix();
		}
		
		void drawBorder(float borderColor[]){
			glColor3fv(borderColor);
				glBegin(GL_LINE_LOOP);
				glVertex2i(pos[0],pos[1]);
				glVertex2i(pos[0],pos[1] + height);
				glVertex2i(pos[0] + width,pos[1] + height);;
				glVertex2i(pos[0] + width,pos[1]);
				glEnd();
			glFlush();
		}
		
		void drawBox(){
			glColor3fv(bgColor);
			glBegin(GL_POLYGON);
				glVertex2i(pos[0],pos[1]);
				glVertex2i(pos[0],pos[1] + height);
				glVertex2i(pos[0] + width,pos[1] + height);;
				glVertex2i(pos[0] + width,pos[1]);
			glEnd();
			
			glFlush();
		}
		
};

class Button : public Text {
	public : bool isEnabled = true;
		bool isSelected = false;
		void (*callback)() ;
		void init(const char *names){
			isEnabled = true;isSelected = false;
			callback = NULL;
			Text::init(names);
			pad[0] = 10;
			setTextStyle(TEXT_CENTER,GLUT_BITMAP_9_BY_15,15);
		}
		
		void init(float p1,float p2,int w=100,int h = 30){
			isEnabled = true;isSelected = false;
			callback = NULL;
			Text::init(p1,p2,w,h);
			pad[0] = 10;
			setTextStyle(TEXT_CENTER,GLUT_BITMAP_HELVETICA_18,18);
		}
		
		void init(float p1,float p2,const char *names,int w=100,int h=30){
			isEnabled = true;isSelected = false;
			callback = NULL;
			Text::init(p1,p2,names,w,h);
			pad[0] = 10;
			setTextStyle(TEXT_CENTER,GLUT_BITMAP_HELVETICA_18,18);

		}
		
		void setOnClick(void (*func)()){
			callback = func;
		}
		
		bool onClick(int x,int y){
		 	if(isEnabled){
				int dx = x - pos[0];
				int dy = y - pos[1];
				if(dx < 0 || dy < 0) return false ;
				if(dx <= width && dy <= height){
					if(callback != NULL){
						callback();
						
					}
					return true;
				}
			}
			return false;
			
		}	
		
};

class EditText : public Text{
	public : int chCount = 0,start=0,textWid = 9;
		struct Viewport *vp;
		
		
		EditText(){
			width = 100;
			height = 38;
			pad[0] = 10;
			while(name[chCount] != '\0')
				chCount++;
			chCount--;
			
		}
		
		void init(const char *names){
			chCount = start = 0;
			Text::init(names);
			pad[0] = 10;
			setTextStyle(GLUT_BITMAP_9_BY_15,15,9);
			while(name[chCount] != '\0')
				chCount++;
		}
		
		void init(float p1,float p2,int w=100,int h = 30){
			chCount = start = 0;
			Text::init(p1,p2,w,h);
			pad[0] = 10;
			setTextStyle(GLUT_BITMAP_9_BY_15,15,9);
		}
		
		void init(float p1,float p2,const char *names,int w=100,int h=30){
			chCount = start = 0;
			Text::init(p1,p2,names,w,h);
			pad[0] = 10;
			setTextStyle(GLUT_BITMAP_9_BY_15,15,9);
			while(name[chCount] != '\0')
				chCount++;
		}
		static void editText(unsigned char key,int x,int y){
		
			if(key == '\b' ){
				if(curEditText->chCount > 0){
				curEditText->chCount -= 1;
				if(curEditText->start == curEditText->chCount - 4) curEditText->start--;
				}
			}
			else if(key == 13){ //enter
				curEditText->setBorderColor(1,1,1);
				glutKeyboardFunc(NULL);
			}
			else if(curEditText->chCount < MAX_CHARACTERS){
				curEditText->name[curEditText->chCount] = key;
		 		curEditText->chCount++;
		 		curEditText->resetTextLen();
		 	}
		 	curEditText->name[curEditText->chCount] = '\0';
		 	callback();
		}
		
		bool onSelect(int x,int y,void (*call)())
		{
			int dx = x - pos[0];
			int dy = y - pos[1];
			
			if(dx < 0 || dy < 0) return false;
			if(dx <= width && dy <= height){
				//printf("%d, %d\n",x,y);
				if(curEditText != NULL)
					curEditText->setBorderColor(0,0,0);
				curEditText = this;
				callback = call;
				curEditText->setBorderColor(1,0,0);
				curEditText->borderType = LINE;
				callback();
				glutKeyboardFunc(editText);
				return true;
				
			}
			return false;
		}
		
		
		
		void setTextStyle(void *textStyle,int textHeight = 18,int textWidth = 9){
			textLen = glutBitmapLength(textStyle,name);
			textHei = textHeight;
			textstyle = textStyle;
			textWid = textWidth;
			textPos[0] = (int)pad[0];
			textPos[1] = (int)(height - textHei)/2;
		}
		
		void setPadding(int x,int y)
		{
			pad[0] = x;
			pad[1] = y;
			if(height < textHei + pad[1]*2)
				height = textHei + pad[1]*2;
			else
				pad[1] = (height - textHei)/2;	
			setTextStyle(textstyle,textHei);
		}
		
		void setValue(const char *names){
			chCount = 0;
			while(names[chCount] != '\0'){
				name[chCount++] = names[chCount];	
			}
			name[chCount] = '\0';
			setTextStyle(textstyle,textHei);
			start = 0;
			resetTextLen();
		}
	
		
		void resetTextLen(){
			textLen = glutBitmapLength(textstyle,name);
			if(textLen - textWid * start >= width - pad[0] * 2){
				start = chCount - (width - pad[0] * 2) / textWid;
			}
		}
		

};


