#include <GL/glut.h>

void display(void){}

int main(int argc,char *argv[]){
    glutInit(&argc,argv);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

/*
void glutInit(int *argcp, char **argv)
    GLUTおよびOpenGL環境を初期化

int glutCreateWindow(char *name)
    ウインドウを開く．引数nameはそのウインドウの名前にの文字列で、タイトルバーなどに表示される

void glutDisplayFunc(void (*func)(void))
    引数funcは開いたウインドウ内に描画する関数へのポインタ．
    ウインドウが開かれたり他のウインドウによって隠されたウインドウが再び現れたりして、ウインドウを再描画する必要があるときに実行される

void glutMainLoop(void)
    無限ループで待ち受け状態になる
*/