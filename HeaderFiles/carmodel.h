#include<malloc.h>
#include<string.h>

static GLfloat vertex[500000][3];
static GLfloat normal[500000][3];
static GLfloat texCord[400000][2];
int face[500000][50][3];
static int vCount = 0, fCount = 0, nCount = 0, texCordCount = 0;

const GLfloat mat_shininess[] = {100.0};
class Material {
	public : float diffuse[3],ambient[3],specular[3],shininess;
		char name[40];
		Material *next = NULL;
};

struct matFace{
	int matIndex;
	int fstart=0,fend=0;
};

class Object {
	public : char name[40];
		struct matFace mat[10];
		int matexCordCount = 0;
		
};

static Material *material;
static Object *object;
static int mCount = 0,oCount = 0,aCount = 0;

void drawModel(){
	//printf("Model called\n");
	//glLightfv(GL_LIGHT0,GL_POSITION,light_position);
	//glLightfv(GL_LIGHT0,GL_DIFFUSE,light_intensity);
	int co = 0;
	for(int i = 1 ; i <= oCount ; i++){
		for(int m = 1 ; m <= object[i].matexCordCount ; m++)
		{
			glMaterialfv(GL_FRONT,GL_AMBIENT, material[object[i].mat[m].matIndex].ambient);
			glMaterialfv(GL_FRONT,GL_DIFFUSE, material[object[i].mat[m].matIndex].diffuse);
			glMaterialfv(GL_FRONT,GL_SPECULAR, material[object[i].mat[m].matIndex].specular);
			glMaterialfv(GL_FRONT,GL_SHININESS, mat_shininess);
			
			for(int f = object[i].mat[m].fstart ; f <= object[i].mat[m].fend ; f++){
				glBegin(GL_POLYGON);

					glNormal3fv(normal[face[f][1][2]]);
			
					for(int j = 1 ; j <= face[f][0][0] ; j++)
					{
					//glTexCoord2fv(texCord[face[i][j][1]]);
							glVertex3fv(vertex[face[f][j][0]]);
					}
				glEnd();
			}
			co += object[i].mat[m].fend - object[i].mat[m].fstart+1;
	
		}
	
	}
	//glutPostRedisplay();
}

void parseMaterial(const char filename[]){
	//printf("parse material called");
	FILE *fp = fopen(filename,"r");
	//if(!fp) return;
	char buf[1024];
	
	mCount  = 0;
	
	while(fscanf(fp,"%s",buf) != EOF){
		if(strcmp(buf,"Count:") == 0){
			fscanf(fp,"%d",&mCount);
			break;
		}
	}
	free(material);
	material =(Material*) malloc(mCount  * sizeof(Material));
	int i = 0;
	Material *cur = material;
	while(fscanf(fp,"%s",buf) != EOF){
		
		if(strcmp(buf,"newmtl") == 0){
			fscanf(fp,"%s\n",cur[i].name);
			fscanf(fp,"Ns %f\nKa %f %f %f\n",&cur[i].shininess,&cur[i].ambient[0],&cur[i].ambient[1],&cur[i].ambient[2]);
			fscanf(fp,"Kd %f %f %f\n",&cur[i].diffuse[0],&cur[i].diffuse[1],&cur[i].diffuse[2]);
			fscanf(fp,"Ks %f %f %f\n",&cur[i].specular[0],&cur[i].specular[1],&cur[i].specular[2]);
			i++;
		}
	
	}
	fclose(fp);
}

void parseObject(const char filename[]){
	char buf[1024];
	
	FILE *fp = fopen(filename,"r");
	//if(!fp) return;
	fCount = vCount = nCount = texCordCount =  oCount = aCount = 0;
	free(object);

	object = (Object*) malloc(100 * sizeof(Object));
	struct matFace *cur ;
	int j = 0;
	printf("Number of vertices = %d" ,vCount);
	while(fscanf(fp,"%s",buf) != EOF )
	{
		switch(buf[0]){
		
		case 'v' : if(buf[1] == 'n'){
				nCount++;
				fscanf(fp,"%f %f %f\n",&normal[nCount][0],&normal[nCount][1],&normal[nCount][2]);
			}
			else if(buf[1] =='t'){
				texCordCount++;
				fscanf(fp,"%f %f\n",&texCord[texCordCount][0],&texCord[texCordCount][1]);
			}
			else if(buf[1] == '\0'){
				vCount++;
				fscanf(fp,"%f %f %f\n",&vertex[vCount][0],&vertex[vCount][1],&vertex[vCount][2]);
			}
			break;
	
			  
		case 'f' : {
			j++;
			int i = 1; 
			fCount++;
			while(1){ 
				fscanf(fp,"%[\n]",buf);
				if(buf[0] == '\n') break;
				fscanf(fp,"%d",&face[fCount][i][0]);
				fscanf(fp,"/%d",&face[fCount][i][1]);
				fscanf(fp,"/%d",&face[fCount][i][2]);
				i++;
			  }
			 
			  face[fCount][0][0] = --i;
			  }
			  break;
		
		case 'o' : if(buf[1] == '\0'){
				oCount++;
				object[oCount-1].mat[object[oCount-1].matexCordCount].fend = fCount;
				//printf("%d\n",object[oCount-1].mat[object[oCount-1].matexCordCount].fend);
				fscanf(fp,"%s\n",object[oCount].name);
				object[oCount].matexCordCount = 0;
			}
			break;
		case 'u' : if(strcmp(buf,"usemtl") == 0){
				fscanf(fp,"%s\n",buf);
				int j = 0;
				while(j < mCount){
					if(strcmp(buf,material[j].name) == 0)
						break;
					j++;
				}
				//printf("%d\n",j);
				int c = ++object[oCount].matexCordCount;
				object[oCount].mat[c-1].fend = fCount;
				object[oCount].mat[c].matIndex = j;
				object[oCount].mat[c].fstart = fCount+1;
			}
			break;
		}
	}
	object[oCount].mat[object[oCount].matexCordCount].fend = fCount;
	fclose(fp);

	// //printf("v[1] = %f\n",normal[face[5][2][2]][1]);
	printf("Number of vertices = %d" ,vCount);
	printf("\nNumber of Object = %d\n",oCount);
	printf("\nNumber of faces = %d\n",fCount);
	printf("\nNumber of normals = %d\n",nCount);
	printf("\nNumber of texCord = %d\n",texCordCount);
}
