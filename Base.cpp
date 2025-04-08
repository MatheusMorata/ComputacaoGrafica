#include <GL/glut.h>

void init();
void display();

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    /*
    
    DESENHE AQUI

    */

    glFlush();
}

void init(){
    glClearColor(1.0, 1.0, 1.0, 1.0); // Cor inicial (BRANCO)

    // Projeção
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
}


int main(int argc, char** argv){
    int janela_x = 800;
    int janela_y = 800;
    int inicial_x = 200;
    int inicial_y = 200;

    glutInit(&argc, argv); // Inicializa o GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(janela_x, janela_y); // Tamanho da janela
    glutInitWindowPosition(inicial_x,inicial_y); // Posição inicial da janela
    glutCreateWindow("Codigo base"); // Título da janela
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
