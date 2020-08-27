#include <GL/glut.h>

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
  
    // 色づけ
    glColor3d(1.0,0.0,0.0);

  // 図形
    glBegin(GL_POLYGON);
    glVertex2d(-0.9,-0.9);
    glVertex2d(0.9,-0.9);
    glVertex2d(0.9,0.9);
    glVertex2d(-0.9,0.9);
    glEnd();
   
    glFlush();
}

void resize(int w,int h){
    // ウインドウ全体をビューポートにする
    glViewport(0,0,w,h);

    //変換行列の初期化
    glLoadIdentity();

    // スクリーン上の表示領域をビューポートの大きさに比例させる
    glOrtho(-w/200,w/200.0,-h/200.0,h/200.0,-1.0,1.0);
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
    init();
    glutMainLoop();
    return 0;
}

/*
void glutInitWindowSize(int w, int h)
    新たに開くウインドウの幅と高さを指定
    デフォルトはw=h=300

void glutInitWindowPosition(int x, int y)
    新たに開くウインドウの位置を指定
    特に指定がないときは、ウインドウマネージャによってウインドウを開く位置を決定する
*/