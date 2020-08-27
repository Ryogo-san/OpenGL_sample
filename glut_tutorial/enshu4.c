#include <GL/glut.h>

void display(void){
  glClear(GL_COLOR_BUFFER_BIT);
  
  // 色づけ
  glColor3d(1.0,0.0,0.0);

  // 直線描画
  glBegin(GL_LINE_LOOP);
  glVertex2d(-0.9,-0.9);
  glVertex2d(0.9,-0.9);
  glVertex2d(0.9,0.9);
  glVertex2d(-0.9,0.9);
  glEnd();
   
  glFlush();
}

void init(void){
  glClearColor(0.0,0.0,1.0,1.0);
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
void glColor3d(GLdouble r, GLdouble g, GLdouble b)
    r,g,bの値を0~1で指定
*/