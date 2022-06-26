
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
