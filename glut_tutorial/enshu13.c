#include <GL/glut.h>

void display(void){
  glClear(GL_COLOR_BUFFER_BIT);
  glRotated(25.0,0.0,1.0,0.0);
  glBegin(GL_POLYGON);
  glColor3d(1.0,0.0,0.0); // red
  glVertex2d(-0.9,-0.9);
  glColor3d(0.0,1.0,0.0); //green
  glVertex2d(0.9,-0.9);
  glColor3d(0.0,0.0,1.0); //blue
  glVertex2d(0.9,0.9);
  glColor3d(1.0,1.0,0.0); //yellow
  glVertex2d(-0.9,0.9);
  glEnd();
   
  glFlush();
}

void init(void){
  glClearColor(1.0,1.0,1.0,1.0);
}

int main(int argc,char *argv[]){
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGBA);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  init();
  glutMainLoop();
  return 0;
}

/*
glRotated(GLdouble angle, GLdouble x, GLdouble y, GLdouble z)
    変換行列に回転の行列を乗ずる．引数angleは回転角，x,y,zは回転軸の
    方向ベクトルを表す．

・ウインドウを最小化したり拡大したりして再描画すると図形の形が変わる
　が、これは回転行列が積算されるためである．
*/