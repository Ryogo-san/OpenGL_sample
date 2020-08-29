#include <stdlib.h>
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

void idle(void){
    glutPostRedisplay();
}

void display(void){
    int i;
    static int r=0; /*回転角*/

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    /*視点位置と視線方向*/
    gluLookAt(3.0,4.0,5.0,0.0,0.,0.0,0.0,1.0,0.0);

    /*図形の回転*/
    glRotated((double)r, 0.0,1.0,0.0);

    glColor3d(0.0,0.0,0.0);
    glBegin(GL_LINES);
    for(int i=0;i<12;i++){
        glVertex3dv(vertex[edge[i][0]]);
        glVertex3dv(vertex[edge[i][1]]);
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

/*
・enshu17.cでは毎回画面を全部描き換えているため，表示がちらつく．
　これを防ぐため，画面を2つに分け，一方を表示している間に(見えな
　いところで)もう一方に図形を描き，それが完了したらこの2つの画面
　を入れ替えればよい．これをダブルバッファリングという．

・GLUTでダブルバッファリングを使用するには，glutInitDisplayMode()
　にGLUT_DOUBLEの指定を追加すれば良い．また，図形の描画後に実行し
　ているglFlush()をglutSwapBuffers()に置き換えて，ここで2つの画面
　を入れ替える．

int glutSwapBuffers(void)
    ダブルバッファリングの2つのバッファを交換する．
*/