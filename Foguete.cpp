#include <GL/glut.h>

void init();
void display();

void init(){
    glClearColor(1.0, 1.0, 1.0);

    // Projeção
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(1, -1, 1, -1, 1,-1);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    /* DESENHANDO UM FOGUETE */


    glFlush();
}

int main(int argc, char** argv){
    int janela_x = 800;
    int janela_y = 800;
    int inicial_x = 200;
    int incial_y = 200;
    int titulo_janela = 'Foguete da NASA';

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(janela_x, janela_y);
    glutInitWindowPosition(inicial_x, inicial_y);
    glutCreateWindow(titulo_janela);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}