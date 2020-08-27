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
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGBA);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize); //
  init();
  glutMainLoop();
  return 0;
}

/*
void glViewport(GLint x, GLint y, GLsizei w, GLsizei h)
    ビューポートを設定する。
    ビューポートとは、開いたウインドウの中で、実際に描画が行われる領域をいう

void glLoadIdentity(void)
    変換行列に単位行列を設定する

void glOrtho(GLdouble l, GLdouble r, GLdouble b, GLdouble t, GLdouble n, GLdouble f)
    ワールド座標系を正規化デバイス座標系に平行投影する行列を変換行列に乗ずる
    引数はlに表示領域の左端の位置，rに右端の位置，bに下端の位置，tに上端の位置，nに前方面の位置，fに後方面の位置を指定
    これは、ビューポートに表示される空間の座標軸の設定に他ならない

glutReshapeFunc(void (*func)(int w, int h))
    引数funcには，ウインドウがリサイズされたときに実行する関数のポインタを与える．
    この関数の引数にはリサイズ後のウインドウの幅と高さが渡される
*/