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
    glFlush();

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
    glutInitDisplayMode(GLUT_RGBA);
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
・アニメーションを実現するには, このウィンドウの再描画イベントを連続的に発生させる必要がある. 
　プログラム中でウィンドウの再描画イベントを発生させるには, glutPostRedisplay() 関数を用いる.
  これをプログラムが「暇なとき」に繰り返し呼び出すことで, アニメーションが実現できます. プログ
  ラムが暇になったときに実行する関数は, glutIdleFunc() で指定する.

・繰り返し描画を行うには, 描画の度に座標変換の行列を設定する必要がある.

・座標変換のプロセス
    1. 図形の空間中での位置決定「モデリング変換」
    2. その空間を視点から見た空間に直す「視野変換」
    3. その空間をコンピュータ内の空間にあるスクリーンに投影する「透視変換」
    4. スクリーン上の図形をディスプレイ上の表示領域に切り出す「ビューポート変換」

・図形だけを動かす場合はモデリング変換の行列だけを変換すればよく，OpenGLでは「モデリング-ビュー
　イング変換」の変換行列(モデルビュー変換行列)と，「透視変換」の変換行列を独立して取り扱う手段が
　提供されている．モデルビュー変換行列を設定する場合は glMatrixMode(GL_MODELVIEW), 透視変換行列
　を設定する場合は glMatrixMode(GL_PROJECTION) を実行する．

void glutPostRedisplay(void)
    再描画イベントを発生させる.

void glutIdleFunc(void (*func)(void))
    引数funcには，このプログラムが暇なときに実行する関数のポインタを指定する．

void glMatrixMode(GLenum mode)
    設定する変換行列を指定する．引数 mode が GL_MODELVIEW ならモデルビュー変換行列, GL_PROJECTION 
    なら透視変換行列を指定する．
*/