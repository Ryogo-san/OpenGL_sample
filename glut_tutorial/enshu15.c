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
    
    /*透視射影*/
    gluPerspective(30.0,(double)w/(double)h,1.0,100.0);
    glTranslated(0.0,0.0,-5.0);
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
glPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
    変換行列に透視変換の行列を乗ずる．foxyはカメラの画角で，単位は°．これが大きいほど
    ワイドレンズになり，小さいほど望遠レンズになる．aspectはアスペクト比.
    zNearとzFarは表示を行う奥行き方向の範囲で，zNearは手前，zFarは後方の位置を示す．

glTranslated(GLdouble x, GLdouble y, GLdouble z)
    変換行列に平行移動の行列を乗ずる．引数x,y,zには現在の位置からの相対的な移動量を指
    定する
*/