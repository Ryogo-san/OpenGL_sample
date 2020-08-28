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
    glOrtho(-2.0,2.0,-2.0,2.0,-2.0,2.0);
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
glVertex3dv(const GLdouble *v)
    三次元の座標値を指定する

・このプログラムは、立方体が画面に平行投射されるため，正方形しか描かれない．
*/