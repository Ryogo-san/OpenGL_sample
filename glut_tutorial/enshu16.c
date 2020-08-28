#include <GL/glut.h>

GLdouble vertex[][3]={
    {0.0,0.0,0.0},
    {1.0,0.0,0.0},
    {1.0,1.0,0.0},
    {0.0,1.0,0.0},
    {0.0,0.0,1.0},
    {1.0,0.0,1.0},
    {1.0,1.0,1.0},
    {0.0,1.0,1.0}
};

int edge[][2]={
    {0,1},
    {1,2},
    {2,3},
    {3,0},
    {4,5},
    {5,6},
    {6,7},
    {7,4},
    {0,4},
    {1,5},
    {2,6},
    {3,7}
};

void display(void){

    glClear(GL_COLOR_BUFFER_BIT);

    /*図形*/
    glColor3d(0.0,0.0,0.0);
    glBegin(GL_LINES);
    for(int i=0;i<12;i++){
        glVertex3dv(vertex[edge[i][0]]);
        glVertex3dv(vertex[edge[i][1]]);
    }
    glEnd();
    glFlush();
}

void resize(int w, int h){
    glViewport(0,0,w,h);
    glLoadIdentity();
    
    /**/
    gluPerspective(30.0,(double)w/(double)h,1.0,100.0);
    gluLookAt(3.0,4.0,5.0,0.0,0.0,0.0,0.0,1.0,0.0);
}

void init(void){
    glClearColor(1.0,1.0,1.0,1.0);
}

int main(int argc, char *argv[]){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    init();
    glutMainLoop();
    return 0;
}

/*
void gluLookAt(GLdouble ex, GLdouble ey, GLdouble ez, GLdouble cx, GLdouble cy, 
GLdouble cz, GLdouble ux, GLdouble uy, GLdouble uz)
    視点を任意の位置に指定する関数．
    ex,ey,ezは視点の位置，cx,cy,czは目標の位置，ux,uy,uzはウインドウに表示される
    画像の「上」の芳香を示すベクトル
*/