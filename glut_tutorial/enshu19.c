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

/*面は頂点で設定*/
int face[][4]={
    {0,1,2,3},
    {1,5,6,7},
    {5,4,7,6},
    {4,0,3,7},
    {4,5,1,0},
    {3,2,6,7}
};

GLdouble color[][3]={
    {1.0,0.0,0.0}, /*赤*/
    {0.0,1.0,0.0}, /*緑*/
    {0.0,0.0,1.0}, /*青*/
    {1.0,1.0,0.0}, /*黃*/
    {1.0,0.0,1.0}, /*マゼンタ*/
    {0.0,1.0,1.0}  /*シアン*/
};

void idle(void){
    glutPostRedisplay();
}

void display(void){
    static int r=0; /*回転角*/

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    /*視点位置と視線方向*/
    gluLookAt(3.0,4.0,5.0,0.0,0.,0.0,0.0,1.0,0.0);

    /*図形の回転*/
    glRotated((double)r, 0.0,1.0,0.0);

    /*図形の描画*/
    glColor3d(0.0,0.0,0.0);
    glBegin(GL_QUADS);
    for(int i=0;i<6;i++){
        glColor3dv(color[i]);
        for(int j=0;j<4;j++){
            glVertex3dv(vertex[face[i][j]]);
        }
    }
    glEnd();
    glutSwapBuffers();

    /*一周回ったら回転角を0に戻す*/
    if(++r>=360) r=0;
}

void resize(int w, int h){
    glViewport(0,0,w,h);

    /*透視変換行列の設定*/
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0,(double)w/(double)h,1.0,100.0);
    
    /*モデルビュー変換行列の設定*/
    glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y){
    switch(button){
        case GLUT_LEFT_BUTTON:
            if(state==GLUT_DOWN){
                /*アニメーション開始*/
                glutIdleFunc(idle);
            }else{
                /*アニメーション停止*/
                glutIdleFunc(0);
            }
            break;
        
        case GLUT_RIGHT_BUTTON:
            if(state==GLUT_DOWN){
                /*コマ送り(1ステップだけ進める)*/
                glutPostRedisplay();
            }
            break;
        
        default:
            break;
    }
}

void keyboard(unsigned char key, int x, int y){
    switch(key){
        case 'q':
        case 'Q':
        case '\033':
            exit(0);
        default:
            break;
    }
}

void init(void){
    glClearColor(1.0,1.0,1.0,1.0);
}

int main(int argc, char *argv[]){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    init();
    glutMainLoop();
    return 0;
}