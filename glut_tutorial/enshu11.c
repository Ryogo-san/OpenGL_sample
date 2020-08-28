#include <stdio.h>
#include <GL/glut.h> 
#define MAXPOINTS 100      /*記憶する点の数*/ 
GLint point[MAXPOINTS][2]; /*座標を記憶する配列*/
int pointnum=0;            /*記憶した座標の数*/
int rubberband=0;          /*ラバーバンドの消去*/

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);

    glFlush();
}

void resize(int w, int h){
    glViewport(0,0,w,h);
    glLoadIdentity();

    /*スクリーン上の座標系をマウスの座標系に一致させる*/
    glOrtho(-0.5, (GLdouble)w-0.5, (GLdouble)h-0.5, -0.5,-1.0,1.0);
}

void mouse(int button, int state, int x, int y){
    switch(button){
        case GLUT_LEFT_BUTTON:
            /*ボタンを操作した位置を記録する*/
            point[pointnum][0]=x;
            point[pointnum][1]=y;
            if(state==GLUT_UP){
                /*ボタンを押した位置から離した位置まで線を引く*/
                glColor3d(0.0,0.0,0.0);
                glBegin(GL_LINES);
                glVertex2iv(point[pointnum-1]); /*押した位置*/
                glVertex2iv(point[pointnum]);   /*離した位置*/
                glEnd();
                glFlush();

                /*始点ではラバーバンドを描いていないので消さない*/
                rubberband=0;
            }else{}
            if(pointnum<MAXPOINTS) ++pointnum; /*押した*/
            break;
        
        case GLUT_MIDDLE_BUTTON:
            break;
        
        case GLUT_RIGHT_BUTTON:
            break;
        
        default:
            break;
    }
}

void motion(int x, int y){
    static GLint savepoint[2]; /*以前のラバーバンドの端点*/

    /*論理演算機能ON*/
    glEnable(GL_COLOR_LOGIC_OP);
    glLogicOp(GL_INVERT);

    glBegin(GL_LINES);
    if(rubberband){
        /*以前のラバーバンドを消す*/
        glVertex2iv(point[pointnum-1]);
        glVertex2iv(savepoint);
    }

    /*新しいラバーバンドを描く*/
    glVertex2iv(point[pointnum-1]);
    glVertex2i(x,y);
    glEnd();
    glFlush();

    /*論理演算機能OFF*/
    glLogicOp(GL_COPY);
    glDisable(GL_COLOR_LOGIC_OP);

    /*今描いたラバーバンドの端点を保存*/
    savepoint[0]=x;
    savepoint[1]=y;

    /*今描いたラバーバンドは次のタイミングで消す*/
    rubberband=1;
}

void init(void){
    glClearColor(1.0,1.0,1.0,1.0);
}

int main(int argc,char *argv[]){
    glutInitWindowPosition(100,100);
    glutInitWindowSize(320,240);
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutReshapeFunc(resize); 
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    init();
    glutMainLoop();
    return 0;
}

/*
・ドラッグ中はマウスの位置を継続的に取得する必要があり，glutMotionfunc()で実現可能である

・マウスのドラッグ注は線分をマウスに追従して描くようにする．これをラバーバンドという．

・ラバーバンドを実現する場合，マウスを動かしたときに直前に描いたラバーバンドを消す必要があり，また，
　ラバーバンドを描いたことによってウインドウにすでに描かれていた内容が壊されるので，その部分をもう
　一度描き直す必要がある．

・そこでラバーバンドを描く際には，線を背景とは異なる色で描く代わりに，描こうとする線上の画素の色を
　反転させる．これにより，もう一度同じ線上の画素の色を反転することで，そこに描かれていた以前の線が
　消えてウインドウに描かれた図形が元に戻る．このためにglLogicOp()を使用する．

・マウスのボタンを押した直後はまだラバーバンドは描かれていないことに注意．つまり，押した直後はラバ
　ーバンドの消去は行わないようにする．これをrubberbandという変数で実現する．

glEnable(GLenum cap)
    引数capに指定した機能を使用可能にする．

glDisable(GLenum cap)
    引数capに指定した機能を使用不可にする．

glLogicOp(GLenum opcode)
    引数opcodeにはウインドウに描かれている内容と，これから描こうとする内容との間で行う論理演算のタ
    イプを指定する．GL_COPYはこれから描こうとする内容をそのままウインドウ内に描く．GL_INVERTはウイ
    ンドウに描かれている内容の，これから描こうとする図形の領域を反転する．

glutMotionFunc(void (*func)(int x, int y))
    引数funcには，マウスのいずれかのボタンを押しながらマウスを動かしたときに実行する関数のポインタ
    を与える．この関数の引数xとyには，現在のマウスの位置が渡される．
*/