
static float winHeight = 0,winWidth = 0;

static Text text[11];
static int tCount = 0,tStart = 0;

static Button button[11] ;
static int bCount = 0,bStart = 0;

static EditText editText[11];
static int eCount = 0,eStart = 0;

static carDetail curCar;

static Viewport viewport[10];

int done =0;

static int mainWin ,subWin;

//Initialization functions
void menuInit();
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

static unsigned int textureNames[8];
typedef GLfloat point[3];


void drawPolygon(point a, point b, point c, point d,int n = 0)
{

   
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, textureNames[n]);
    
    glBegin(GL_QUADS);
   
    glTexCoord2f(0.0, 1.0);
    glVertex3fv(a);
    glTexCoord2f(1.0, 1.0);
    glVertex3fv(b);
    glTexCoord2f(1.0, 0.0);
    glVertex3fv(c); 
    glTexCoord2f(0.0, 0.0);
    glVertex3fv(d);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void drawTexCube(int n){
	glDisable(GL_COLOR_MATERIAL);
	 glEnable(GL_TEXTURE_2D);

   	 glBindTexture(GL_TEXTURE_2D, textureNames[n]);
   	  glBegin(GL_QUADS);
   	  glTexCoord2f(0.71,0.71);
   	  glVertex3f(-3,-3,-3);
   	  glTexCoord2f(0.95 ,0.7);
   	  glVertex3f(-3,-3,3);
   	  glTexCoord2f( 0.6, 0.84);
   	  glVertex3f(3,-3,3);
   	  
   	 glTexCoord2f(0.3 ,0.71);
   	  glVertex3f(3,-3,-3);
   	  glEnd();
   	  
   	  /*
v 4.111718 4.111718 -3.333788
v 4.111718 -3.333788 -3.333788
v 4.111718 -3.333788 4.111718
v -3.333788 4.111718 -3.333788
v -3.333788 -3.333788 -3.333788
v -3.333788 4.111718 4.111718
v -3.333788 -3.333788 4.111718
vt 0.053474 0.219929 0.358317 0.758356
vt 0.293767 0.289445  0.358317 0.758356
vt 0.358317 0.758356
vt 0.211682 1.150980
vt 0.406003 0.167492
vt 0.700949 0.291886
vt 0.696323 0.727251 0.700949 0.291886
vn 1.0000 0.0000 0.0000
vn 0.0000 1.0000 0.0000
vn 0.0000 0.0000 1.0000
usemtl Material
s off
f 7/1/1 5/2/1 4/3/1 6/4/1
f 5/2/2 7/1/2 3/5/2 2/6/2
f 5/2/3 2/6/3 1/7/3 4/3/3
*/
   	  
   	   glBegin(GL_QUADS);
   	  glTexCoord2f(0.72 ,0.72 );
   	  glVertex3f(-3,-3,-3);
   	  glTexCoord2f(0.95,0.79 );
   	  glVertex3f(-3,-3,3);
   	  glTexCoord2f(0.79, 0);
   	  glVertex3f(-3,3,3); 
   	 glTexCoord2f(  0.65 ,0.25);
   	  glVertex3f(-3,3,-3);
   	  glEnd();
   	  
   	   glBegin(GL_QUADS);
   	  glTexCoord2f(0.7 ,0.71 );
   	  glVertex3f(-3,-3,-3);
   	  glTexCoord2f( 0.65 ,0.242);
   	  glVertex3f(-3,3,-3);
   	  glTexCoord2f(0.31, 0.28 );
   	  glVertex3f(3,3,-3);
   	 glTexCoord2f( 0.3,0.31);
   	  glVertex3f(3,-3,-3);
   	  glEnd();
   	   
    	glDisable(GL_TEXTURE_2D);
}

//Load Image to Texture slot
void initTexture(const char filename[],int n=0)
{
    	int width, height, nrChannels;
    	unsigned char *image_data;

    	glGenTextures(1, &textureNames[n]);

    	image_data = stbi_load(filename, &width, &height, &nrChannels, 0);

    	glBindTexture(GL_TEXTURE_2D, textureNames[n]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
     	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
        stbi_image_free(image_data);
}

void renderAllText(){
	for(int i=0; i < bCount ;i++){
		button[i].drawText();
		button[i].drawBox();
	}
	
	for(int i=0; i < eCount ;i++){
		editText[i].drawText(editText[i].start);
		editText[i].drawBox();
	}
	for(int i=0; i < tCount ;i++){
		text[i].drawText();
		text[i].drawBox();
	}

	
}

void setViewport(Viewport *v,float x0,float y0,float x1,float y1,float orthox0,float orthoy0,float orthox1,float orthoy1,float orthox2=0,float orthoy2=0,float scrollx=0,float scrolly=0){
	*v = {x0,y0,x1,y1,orthox0,orthoy0,orthox1,orthoy1,orthox2,orthoy2,scrollx,scrolly,(x1/(orthoy0-orthox0)),(y1/(orthoy1-orthox1))};
	
}
